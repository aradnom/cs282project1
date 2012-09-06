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
    , invMass{1.0f} { }

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

  void Particle::integrate(fseconds duration, int type) { // Defaults to Euler

    // don't move objects that have "infinite mass."
    if (invMass <= 0.0f) {
      return;
    }

	// Universal properties
	//lastPos = pos; // Only necessary for position Verlet
	vec3 resultantAcc = acc + (invMass * accumulatedForces);

	if ( type == 1 ) { // Euler
		// update position using Euler integration
		pos = pos + duration.count() * vel;

		// update velocity using Euler integration
		vel = vel + duration.count() * resultantAcc;

		// incorporate damping
		vel = vel * damping;
	} else if ( type == 2 ) { // RK

	} else { // Velocity Verlet
		pos = pos + ( vel * duration.count() ) + ( 0.5f * resultantAcc * duration.count() * duration.count() );

		// Assumes acc doesn't change between steps - still need to solve for acc+1 to be accurate if a changes
		vel = vel + ( 0.5f * 2 * resultantAcc ) * duration.count();	
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
