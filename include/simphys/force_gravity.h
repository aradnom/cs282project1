#include <memory>
#include "simphys/force_generator.h"
#include "simphys/vec3.h"
#include "simphys/particle.h"

namespace simphys {

	using std::shared_ptr;

	class vec3;
	class Particle;

	class ForceGravity : public ForceGenerator {
	private:
		
		vec3 gravity;

	public:
		// Assign gravity value to force
		ForceGravity ( const vec3 _gravity );

		// Updated particle with gravity
		void update(shared_ptr<Particle> p, fsecond dt);
	};

}
