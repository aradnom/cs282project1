#include <memory>
#include "simphys/force_generator.h"
#include "simphys/vec3.h"
#include "simphys/particle.h"
#include "simphys/force_gravity.h"

namespace simphys {

	using std::shared_ptr;

	class vec3;
	class Particle;
	
	// Assign gravity value to force
	ForceGravity::ForceGravity ( const vec3 _gravity ) : gravity{_gravity} {}

	// Updated particle with gravity
	void ForceGravity::update(shared_ptr<Particle> p, fsecond dt) {
		if ( p->getMass() <= 0 ) return;
			
		p->applyForce( gravity );
	}
}
