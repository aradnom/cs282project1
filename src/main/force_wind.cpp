#include <memory>
#include "simphys/force_generator.h"
#include "simphys/vec3.h"
#include "simphys/particle.h"
#include "simphys/force_wind.h"

namespace simphys {

	using std::shared_ptr;

	class vec3;
	class Particle;
	
	// Assign gravity value to force (arbitrary direction)
	ForceWind::ForceWind ( const vec3 _wind ) : wind{ _wind } {}

	// Updated particle with gravity
	void ForceWind::update ( shared_ptr<Particle> p, fsecond dt ) {
		if ( p->getMass() <= 0 ) return;
			
		p->applyForce( wind );
	}
}
