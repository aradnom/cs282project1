#include <memory>
#include "simphys/force_generator.h"
#include "simphys/vec3.h"
#include "simphys/particle.h"

namespace simphys {

	using std::shared_ptr;

	class vec3;
	class Particle;

	class ForceWind : public ForceGenerator {
	private:
		
		vec3 wind;

	public:
		// Assign gravity value to force
		ForceWind ( const vec3 _wind );

		// Updated particle with gravity
		void update ( shared_ptr<Particle> p, fsecond dt );
	};

}
