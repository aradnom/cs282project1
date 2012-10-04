#include "simphys/render_engine.h"

#include "simphys/sim_world.h"
#include "simphys/simobject2D.h"
#include "simphys/sprite.h"

#include <iostream>
#include <memory>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>
#include <X11/keysym.h>

#include <GL/glew.h>
#include <GL/glxew.h>
#include <GL/glx.h>

namespace simphys {

  using std::shared_ptr;

  // Based on code at
  // http://www.opengl.org/archives/resources/features/OGLextensions/
  // TODO - replace with C++ regex.
  bool extensionSupported(const char *extList, const char *ext) {
    const char *start;
    const char *where, *terminator;

    where = strchr(ext, ' ');
    if ( where || *ext == '\0' )
      return false;

    for ( start = extList; ; ) {
      where = strstr( start, ext );

      if ( !where )
	break;

      terminator = where + strlen( ext );

      if ( where == start || *(where - 1) == ' ' )
	if ( *terminator == ' ' || *terminator == '\0' )
	  return true;

      start = terminator;
    }

    return false;

  }

  // Setup the window and the rendering context.
  void RenderEngine::setupWindow() {
    XSetWindowAttributes winAttribs;
    GLint winmask;
    GLint majorVer = 0;
    GLint minorVer = 0;
    XVisualInfo *visualInfo;
    GLXFBConfig *fbConfigs;
    int numConfigs = 0;

    static int fbAttribs[] = {
      GLX_RENDER_TYPE, GLX_RGBA_BIT,
      GLX_X_RENDERABLE, True,
      GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
      GLX_DOUBLEBUFFER, True,
      GLX_RED_SIZE, 8,
      GLX_BLUE_SIZE, 8,
      GLX_GREEN_SIZE, 8,
      0
    };

    // At this point we have to do manual initialization for some functions.
    // TODO - solve this call's problem.
    glXCreateContextAttribsARB = (GLXContext(*)(Display* dpy,
      GLXFBConfig config, GLXContext share_context, Bool direct, const
      int *attrib_list))
      glXGetProcAddressARB((GLubyte*)"glXCreateContextAttribsARB");

    glXChooseFBConfig = (GLXFBConfig*(*)(Display *dpy, int screen, const int *attrib_list, int *nelements))
      glXGetProcAddressARB((GLubyte*)"glXChooseFBConfig");
    
    glXGetVisualFromFBConfig = (XVisualInfo*(*)(Display *dpy, GLXFBConfig config))
      glXGetProcAddressARB((GLubyte*)"glXGetVisualFromFBConfig");
    
    glXCreateNewContext = (GLXContext(*)(Display*,GLXFBConfig,int,GLXContext,Bool))
      glXGetProcAddressARB((GLubyte*)"glXCreateNewContext");
    
    glXQueryVersion(dpy, &majorVer, &minorVer);
    std::cout << "Supported GLX version: "
	      << majorVer << "." << minorVer
	      << std::endl;
    
    fbConfigs = glXChooseFBConfig(dpy, DefaultScreen(dpy),
				  fbAttribs, &numConfigs);
    visualInfo = glXGetVisualFromFBConfig(dpy, fbConfigs[0]);
    
    
    winAttribs.event_mask = KeyPressMask |
      ButtonPressMask | PointerMotionMask | ExposureMask |
      VisibilityChangeMask | StructureNotifyMask;
    
    winAttribs.border_pixel = 0;
    winAttribs.bit_gravity = StaticGravity;
    winAttribs.colormap = XCreateColormap(dpy,
					  RootWindow(dpy, visualInfo->screen),
					  visualInfo->visual, AllocNone);
    
    winmask = CWBorderPixel | CWBitGravity | CWEventMask | CWColormap;
    
    w = XCreateWindow(dpy, DefaultRootWindow(dpy), 20, 20,
		      windowWidth, windowHeight, 0,
		      visualInfo->depth, InputOutput,
		      visualInfo->visual, winmask, &winAttribs);
    XMapWindow(dpy, w);

    /*
      Get extension list and determine if glXCreateContextAttribsARB
      is supported.
    */
    const char *glxExts = glXQueryExtensionsString(dpy, DefaultScreen(dpy));
    
    if (!extensionSupported(glxExts, "GLX_ARB_create_context") || 
	!glXCreateContextAttribsARB) {
      std::cout << "Using old-style context creation." << std::endl;
      ctx = glXCreateNewContext(dpy, fbConfigs[0], GLX_RGBA_TYPE, 0, True);
    } else if (glXCreateNewContext) {
      std::cout << "Running glXCreateContextAttribs" << std::endl;
      GLint attribs[] = {
        GLX_CONTEXT_MAJOR_VERSION_ARB, 4,
        GLX_CONTEXT_MINOR_VERSION_ARB, 2,
        0
      };
      ctx = glXCreateContextAttribsARB(dpy, fbConfigs[0], NULL, True, attribs);
    } 
    glXMakeCurrent(dpy, w, ctx);
    
    GLenum err = glewInit();
    if (GLEW_OK != err) {
      std::cerr << "GLEW Error: " << glewGetErrorString(err);
    }
    
    const GLubyte *s = glGetString(GL_VERSION);
    std::cout << "GL Version: " << s << std::endl; 
  }

  // Setup OpenGL rendering parameters.
  void RenderEngine::setupGL() {
    glViewport(0,0, windowWidth, windowHeight);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 1333, 0, 1000);
    
    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);
  }
  
  // Constructor
  RenderEngine::RenderEngine()
    : windowHeight{480}
    , windowWidth{640}
    , sw{nullptr} { }

  // Initialize the rendering engine.
  void RenderEngine::init() {
    setupWindow();
    setupGL();
  }

  // Set the display
  void RenderEngine::setDisplay(Display* d) {
    dpy = d;
  }

  // Perform drawing.
  void RenderEngine::draw() const {
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);

    // draw the sprites in the sim world.
    auto objects = sw->getObjects();
    for (const auto& obj : objects) {
      (obj->getSprite())->draw();
    }

    glXSwapBuffers(dpy, w);
  }

  void RenderEngine::setSimWorld(shared_ptr<SimWorld> simworld) {
    sw = simworld;
  }

  shared_ptr<SimWorld> RenderEngine::getSimWorld() const {
    return sw;
  }

}
