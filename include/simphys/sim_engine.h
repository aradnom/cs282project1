#ifndef SIM_ENGINE_H
#define SIM_ENGINE_H

#include <X11/Xlib.h>

#include "sim_world.h"
#include "render_engine.h"
#include "input_manager.h"
#include "physics_engine.h"
#include "clock.h"

#include <memory>
#include <chrono>

namespace simphys {
  
  typedef std::chrono::duration<float, std::ratio<1,1> > fseconds;

  class SimEngine {
  private:
    /*
      Is the engine presently running?
    */
    bool running;

    /*
      X11 display to be shared by subsystems.
    */
    Display *d;

    /*
      Real-time clock.
    */
    std::shared_ptr<Clock<fseconds> > rt_c;

    /*
      Engine subsystems.
    */
    RenderEngine re;
    InputManager im;
    PhysicsEngine pe;

    /*
      The world to simulate.
    */
    std::shared_ptr<SimWorld> sw_ptr;

  public:

    std::shared_ptr<Clock<fseconds> > clock() {
      return rt_c;
    }
    
    /*
      Basic constructor.
    */
    SimEngine();

    /*
      Initialize subsystems.
    */
    void init();
    
    /*
      Run the main simulation loop.
    */
    void run();

    /*
      Initiate cleanup.
    */
    void cleanup();

    /*
      Access the simulation world to perform updates.
    */
    std::shared_ptr<SimWorld> getSimWorld() const;
    
    /*
      Set simulation world.
    */
    void setSimWorld(std::shared_ptr<SimWorld> sw);

    /*
      Set the clock.
    */

    void setClock(std::shared_ptr<Clock<fseconds> > clock, float timeScale = 1.0f);

    PhysicsEngine* getPhysicsEngine() {
      return &pe;
    }
  };

}

#endif // SIM_ENGINE_H
