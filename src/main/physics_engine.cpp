#include "simphys/physics_engine.h"
#include "simphys/sim_world.h"
#include "simphys/spring_force.h"
#include "simphys/registry.h"

#include <memory>
#include <chrono>
#include <iostream>

namespace simphys {

  using std::shared_ptr;
  typedef std::chrono::duration<float, std::ratio<1,1> > fseconds;

  void PhysicsEngine::tick(fseconds dt) {

    if (dt - lastTick > fseconds{0.001}) {
      lastTick = dt;

	  // Apply all forces in the registry
	  registry.update( dt );

	  // Integrate all particles
	  for ( auto& p : particles ) {
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

  void PhysicsEngine::addParticle( shared_ptr<Particle> p ) {
	particles.push_back( p );
  }

  void PhysicsEngine::addForce( shared_ptr<ForceGenerator> fg, shared_ptr<Particle> p ) {
    registry.addForce( fg, p );
  }

}
