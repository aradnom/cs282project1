#include "simphys/sim_engine.h"

#include <chrono>
#include <iostream>
#include <memory>

#include <X11/Xlib.h>

#include "simphys/render_engine.h"
#include "simphys/input_manager.h"
#include "simphys/physics_engine.h"
#include "simphys/clock.h"

namespace simphys {

  typedef std::chrono::duration<float, std::ratio<1, 1> > fseconds;

  SimEngine::SimEngine()
    : running{true} 
    , rt_c{nullptr}
    , sw_ptr{nullptr} { }

  /*
    Initialize the engine.
  */
  void SimEngine::init() {
    // initialize X11 display
    d = XOpenDisplay(nullptr);

    // pass display to rendering and input subsystems.
    re.setDisplay(d);
    im.setDisplay(d);

    // initialize rendering
    re.init();

    // set simulation world
    re.setSimWorld(sw_ptr);
    pe.setSimWorld(sw_ptr);

    // set input's parent
    im.setParentEngine(std::shared_ptr<SimEngine>{this});

  }

  /*
    Run the main loop.
  */
  void SimEngine::run() {
    
    std::chrono::duration<float, std::ratio<1,1> > dt{0.016f};

    while(running) {
      rt_c->update(dt);
      auto startLoop = std::chrono::high_resolution_clock::now();
      im.poll();
      pe.tick(rt_c->getTicks());
      re.draw();
      auto endLoop = std::chrono::high_resolution_clock::now();
      dt = endLoop - startLoop;
    }
    
    // At this point the sim is over and we need to clean up.
    cleanup();
    
  }

  void SimEngine::cleanup() {
    // nothing yet.
  }

  std::shared_ptr<SimWorld> SimEngine::getSimWorld() const {
    return sw_ptr;
  }

  void SimEngine::setSimWorld(std::shared_ptr<SimWorld> sw) {
    sw_ptr = sw;
  }

  void SimEngine::setClock(std::shared_ptr<Clock<fseconds> > clock, float timeScale) {
	clock->setScale( timeScale );
    rt_c = clock;
  }
  
}
