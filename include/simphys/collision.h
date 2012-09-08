// Class for generating a collision between two particles - instantiated by getCollisions
// wherever a collision between two particles is detected

#ifndef COLLISION_H
#define COLLISION_H

#include <string>
#include <memory>
#include <vector>
#include "simphys/particle.h"

namespace simphys {

	using std::shared_ptr;
  
  class Collision {
	protected:

		// If the size of this is 1, assume collision was with the ground (only 1 particle was involved
		std::vector<shared_ptr<Particle> > particles; 
		float restitution;
		vec3 normal;

		void resolveInterpenetration();
		void resolveVelocity();

	public:
		Collision( std::shared_ptr<Particle> p1 );
		Collision( std::shared_ptr<Particle> p1, std::shared_ptr<Particle> p2 );

	};

}

#endif
