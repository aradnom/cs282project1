
#include "simphys/collision.h"
#include <iostream>
#include <math.h>

namespace simphys {

	Collision::Collision( std::shared_ptr<Particle> p1 ) {
		restitution = 0.75f; // Set a default restitution of something < 1.0
		particles.push_back( p1 );
	}

	Collision::Collision( std::shared_ptr<Particle> p1, std::shared_ptr<Particle> p2, float _inter ) {
		restitution = 0.75f;
		inter = _inter;
		normal = ( p1->getVelocity() - p2->getVelocity() );
		normal.normalize();
		particles.push_back( p1 );
		particles.push_back( p2 );
	}
	
	void Collision::resolveInter () {
		float buffer = 4.0f;  // Small buffer just to alleviate issues with objects immediately hitting again
		float totalMass = particles[0]->getMass() + particles[1]->getMass();
		float newDifference = sqrt( ( pow( particles[0]->getRadius() + particles[1]->getRadius(), 2 ) - inter ) + buffer );

		// Calculate new difference to objects based on mass
		vec3 p1adjustment = ( newDifference * ( particles[0]->getMass() / totalMass ) ) * normal;
		vec3 p2adjustment = ( newDifference * ( particles[1]->getMass() / totalMass ) ) * normal;

		particles[0]->setPosition( particles[0]->getPosition() - p1adjustment );
		particles[1]->setPosition( particles[1]->getPosition() + p2adjustment );
	}

	void Collision::resolveVelocity () {
		vec3 p1v = particles[0]->getVelocity();
		vec3 p2v = particles[1]->getVelocity(); 

		// The objects are moving away from each other or both are infinite mass
		if ( p1v < 0 || ( 1.0f / particles[0]->getMass() <= 0 && 1.0f / particles[1]->getMass() ) ) return; 

		// Get total mass
		float imasses = particles.size() > 1 ? 
			( 1.0f / particles[0]->getMass() ) + ( 1.0f / particles[1]->getMass() ) : 
			1.0f / particles[0]->getMass();
		
		// Get closing velocity
		vec3 velocity = particles.size() > 1 ? p1v - p2v : p1v;

		// Create new velocity
		vec3 newVelocity = velocity * -restitution;

		// Velocity delta
		vec3 delta = newVelocity - velocity;

		// Impulsa from delta and inverse masses
		vec3 impulse = delta * ( 1.0f / imasses );

		//newVelocity = impulse.dotProduct( normal );
		newVelocity.setX( impulse.getX() * normal.getX() );
		newVelocity.setY( impulse.getY() * normal.getY() );
		newVelocity.setZ( impulse.getZ() * normal.getZ() );

		// Final velocities
		vec3 p1new = newVelocity * ( 1.0f / particles[0]->getMass() );
		vec3 p2new = newVelocity * ( -1.0f / particles[1]->getMass() );
	
		particles[0]->setVelocity( p1v + p1new );
		particles[1]->setVelocity( p2v + p2new );
	}

}
