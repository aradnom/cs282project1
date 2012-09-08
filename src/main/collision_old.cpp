
#include "simphys/collision.h"
#include <iostream>
#include <math.h>

namespace simphys {

	Collision::Collision( std::shared_ptr<Particle> p1 ) {
		restitution = 0.9f; // Set a default restitution of something < 1.0
		particles.push_back( p1 );
	}

	Collision::Collision( std::shared_ptr<Particle> p1, std::shared_ptr<Particle> p2, float _inter ) {
		restitution = 0.9f;
		inter = _inter;
		normal = ( p1->getVelocity() - p2->getVelocity() );
		normal.normalize();
		particles.push_back( p1 );
		particles.push_back( p2 );
	}
	
	void Collision::resolveInter () {
		float buffer = 10.0f;  // Small buffer just to alleviate issues with objects immediately hitting again
		float totalMass = particles[0]->getMass() + particles[1]->getMass();
		float newDifference = sqrt( ( pow( particles[0]->getRadius() + particles[1]->getRadius(), 2 ) - inter ) + buffer );

		vec3 p1adjustment = ( newDifference * ( particles[0]->getMass() / totalMass ) ) * normal;
		vec3 p2adjustment = ( newDifference * ( particles[1]->getMass() / totalMass ) ) * normal;

		// Apply new difference to objects based on mass		
		//std::cout << newDifference << " | ";
		//std::cout << p1adjustment.norm() << " | ";
		//std::cout << p2adjustment.norm() << " | ";
		//std::cout << "\n";

		particles[0]->setPosition( particles[0]->getPosition() - p1adjustment );
		particles[1]->setPosition( particles[1]->getPosition() + p2adjustment );
	}

	void Collision::resolveVelocity () {
		vec3 p1v = particles[0]->getVelocity();
		vec3 p2v = particles[1]->getVelocity(); 

		// The objects are moving away from each other or both are infinite mass
		if ( p1v < 0 || ( 1.0f / particles[0]->getMass() <= 0 && 1.0f / particles[1]->getMass() ) ) return; 

		// Get total mass
		float mass = particles.size() > 1 ? particles[0]->getMass() + particles[1]->getMass() : particles[0]->getMass();
		
		// Get closing velocity
		vec3 velocity = particles.size() > 1 ? p1v - p2v : p1v;

		//std::cout << mass << " | ";
		//std::cout << p1v.getX() << " " << p1v.getY() << " | ";
		//std::cout << p2v.getX() << " " << p2v.getY() << " | ";
		//std::cout << velocity.getX() << " " << velocity.getY() << " | ";

		// Contact normal
		normal = ( p1v - p2v );
		normal.normalize();

		// Closing speed and new speed
		float speed = velocity.dotProduct( normal );
		float newSpeed = -speed * restitution;
		
		//std::cout << normal.getX() << " " << normal.getY() << " | ";
		//std::cout << speed << " | ";
		//std::cout << newSpeed << " | "; 

		// Change in velocity
		float delta = speed - newSpeed;

		//std::cout << delta << " | ";		

		// Impulse and impulse per mass kg
		float impulse = delta * mass;
		vec3 imass = impulse * normal;

		vec3 p1vNew = p1v - ( imass * ( 1.0f / particles[0]->getMass() ) );
		vec3 p2vNew = p2v + ( imass * ( 1.0f / particles[1]->getMass() ) );	

		particles[0]->setVelocity( p1vNew );
		particles[1]->setVelocity( p2vNew );

		//std::cout << p1vNew.getX() << " " << p1vNew.getY() << " | ";
		//std::cout << p2vNew.getX() << " " << p2vNew.getY() << " | ";
		std::cout << "\n";
	}

}
