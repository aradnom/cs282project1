#include "simphys/particle.h"
#include <iostream>

namespace simphys {

  Particle::Particle()
    : pos{0.0f, 0.0f, 0.0f}
	, lastPos{0.0f, 0.0f, 0.0f}
    , vel{0.0f, 0.0f, 0.0f}
    , acc{0.0f, 0.0f, 0.0f}
    , accumulatedForces{0.0f, 0.0f, 0.0f}
    , damping{1.0f}
    , invMass{1.0f}
	, radius{32.0f} { }

  void Particle::setPosition(const vec3& newPos) {
    pos = newPos;
  }

  void Particle::setVelocity(const vec3& newVel) {
    vel = newVel;
  }

  void Particle::setAcceleration(const vec3& newAcc) {
    acc = newAcc;
  }

  void Particle::setDamping(float d) {
    damping = d;
  }

  void Particle::setMass(float m) {
    // TODO - decide if this is reasonable. Error handling?
    invMass = 1.0f / m;
  }
	
	void Particle::setRadius( float r ) {
		radius = r;
	}

  vec3 Particle::getPosition() const {
    return pos;
  }

  vec3 Particle::getVelocity() const {
    return vel;
  }
  
  vec3 Particle::getAcceleration() const {
    return acc;
  }

  float Particle::getDamping() const {
    return damping;
  }
  
  float Particle::getMass() const {
    return 1.0f / invMass;
  }

	float Particle::getRadius() const {
		return radius;
	}

  void Particle::integrate(fseconds duration, int type) { // Defaults to Euler

    // don't move objects that have "infinite mass."
    if (invMass <= 0.0f) {
      return;
    }

	// Universal properties
	//lastPos = pos; // Only necessary for position Verlet
	vec3 resultantAcc = acc + (invMass * accumulatedForces);

    auto dt = duration.count();

	if ( type == 1 ) { // Euler
		// update position using Euler integration
		pos = pos + dt * vel;

		// update velocity using Euler integration
		vel = vel + dt * resultantAcc;

		// incorporate damping
		vel = vel * std::pow(damping, dt);
	} else if ( type == 2 ) { // RK
		// Pop RK4 in here at some point because... why not
	} else { // Velocity Verlet
		pos = pos + ( vel * dt ) + ( 0.5f * resultantAcc * dt * dt );

		// Assumes acc doesn't change between steps - still need to solve for acc+1 to be accurate if a changes
		vel = vel + ( 0.5f * 2 * resultantAcc ) * dt;	
	}   

    clearForces();

  }

  void Particle::clearForces() {
    accumulatedForces = vec3{0.0f, 0.0f, 0.0f};
  }

  void Particle::applyForce(const vec3& force) {
    accumulatedForces = accumulatedForces + force;
  }

}
