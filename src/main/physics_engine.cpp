#include "simphys/physics_engine.h"
#include "simphys/sim_world.h"
#include "simphys/spring_force.h"
#include "simphys/registry.h"
#include "simphys/collision.h"

#include <vector>
#include <memory>
#include <chrono>
#include <iostream>
#include <math.h>

namespace simphys {

  using std::shared_ptr;
  typedef std::chrono::duration<float, std::ratio<1,1> > fseconds;

  void PhysicsEngine::tick(fseconds dt) {

    if (dt - lastTick > fseconds{0.001}) {
      lastTick = dt;

	  	// Apply all forces in the registry
	  	registry.update( dt );

	  	//std::vector<shared_ptr<SimObject2D> > objects = sw->getObjects();

	  	// Iterate through all particles and do... stuff		
	  	for ( auto & p : sw->getObjects() ) {
	    	if ( p->getState()->getPosition().getY() < 0.0f) continue; // This particle is under the floor. =(

				p->getState()->integrate( dt );
	  	}

			// Deal with collisions
			getCollisions();
			for ( auto & c : collisions ) {
	    	std::cout << "boo";
	  	}
    } 
  }

  void PhysicsEngine::getCollisions () {
		collisions.clear(); // Clear old collision information
	
		// Iterate through particles and generate collision objects for those found
		// to be colliding.  For the time being, based on simple object radius and 
		// will simply compare objects against each other to determine collision.	
		for ( auto & first : sw->getObjects() ) {
			for ( auto & second : sw->getObjects() ) {
				if ( first == second ) continue; // Move on if comparing to self
				vec3 distance = ( first->getState()->getPosition() - second->getState()->getPosition() );

				if ( distance.norm_sq() < pow( first->getState()->getRadius() + second->getState()->getRadius(), 2 ) ) {
					//std::cout << distance.norm_sq() << "\n"; // A collision has occurred
					Collision collision( first->getState(), second->getState() );
					collisions.push_back( collision );
					continue;
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

  void PhysicsEngine::addForce( shared_ptr<ForceGenerator> fg, shared_ptr<Particle> p ) {
    registry.addForce( fg, p );
  }

}
