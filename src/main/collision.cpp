
#include "simphys/collision.h"

namespace simphys {

	Collision::Collision( std::shared_ptr<Particle> p1, std::shared_ptr<Particle> p2 ) {

	}
	
	void Collision::resolveInterpenetration () {
		
	}

	void Collision::resolveVelocity () {
		vec3 velocity = particles[0]->getVelocity();

		if ( particles.size() > 1 ) // Otherwise assume a wall was hit
			velocity = velocity + particles[1]->getVelocity();

		// The objects are moving away from each other or both are infinite mass
		if ( velocity < 0 || ( 1.0f / particles[0]->getMass() <= 0 && 1.0f / particles[1]->getMass() ) ) return; 

		vec3 delta = ( (-1.0f * velocity) * restitution ) + velocity;

		velocity = (-1.0f * velocity) * restitution; // New velocity post-collision

		vec3 impulse = delta * ( 1.0f / ( particles[0]->getMass() + particles[1]->getMass() ) );

		//return velocity * normal;
	}

}
