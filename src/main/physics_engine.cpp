#include "simphys/physics_engine.h"
#include "simphys/sim_world.h"
#include "simphys/spring_force.h"

#include <memory>
#include <chrono>
#include <iostream>

namespace simphys {

  using std::shared_ptr;
  typedef std::chrono::duration<float, std::ratio<1,1> > fseconds;

  void PhysicsEngine::tick(fseconds dt) {

    if (dt - lastTick > fseconds{0.001}) {
      lastTick = dt;

      //auto objects = sw->getObjects();
      //for (auto& obj : objects) {
      for (auto& r : reg) {
	auto sfg = r.first;
	auto p = r.second;
	
	// apply the spring force.
	sfg->update(p, dt);

	// really cheap way of testing for collisions with ground.
	if (p->getPosition().getY() > 0.0f)
	  p->integrate(dt);

      }
    } 
  }

  void PhysicsEngine::setSimWorld(shared_ptr<SimWorld> simworld) {
    sw = simworld;
  }

  shared_ptr<SimWorld> PhysicsEngine::getSimWorld() const {
    return sw;
  }

  void PhysicsEngine::addSpringPair(shared_ptr<SpringForce> fg, shared_ptr<Particle> p) {
    reg.push_back(std::make_pair(fg, p));
  }

}
