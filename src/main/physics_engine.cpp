#include "simphys/physics_engine.h"
#include "simphys/sim_world.h"

#include <memory>
#include <chrono>
#include <iostream>

namespace simphys {

  using std::shared_ptr;
  typedef std::chrono::duration<float, std::ratio<1,1> > fseconds;

  void PhysicsEngine::tick(fseconds dt) {

    if (dt - lastTick > fseconds{0.0}) {
      lastTick = dt;
      auto objects = sw->getObjects();
      for (auto& obj : objects) {
	auto p = obj->getState();
	
	// really cheap way of testing for collisions with ground.
	if (p->getPosition().getY() > 0.0f) {
	  p->integrate(dt, 3);
	} 
      }
    } 
  }

  void PhysicsEngine::setSimWorld(shared_ptr<SimWorld> simworld) {
    sw = simworld;
  }

  shared_ptr<SimWorld> PhysicsEngine::getSimWorld() const {
    return sw;
  }

}
