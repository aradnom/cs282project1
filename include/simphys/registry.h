#ifndef FORCE_REGISTRY
#define FORCE_REGISTRY

#include <chrono>
#include <memory>
#include <vector>

namespace simphys {

	class Particle;
	class ForceGenerator;

	typedef std::chrono::duration<float, std::ratio<1,1> > fsecond;

	using std::shared_ptr;

	class ForceRegistry {
	protected:

		// Simple pair of force, particle to be entered into registry
		struct ForcePair {
			ForcePair () {}

			ForcePair ( shared_ptr<ForceGenerator> _force, shared_ptr<Particle> _p ) { 
				force = _force;
				p = _p;
			}			

			shared_ptr<ForceGenerator> force;
			shared_ptr<Particle> p;
		};
	
		// The Registry of Forces.  Which sounds like a team of superheroes.  That fight crime sequentially.
		std::vector<ForcePair> forces;
	
	public:

		// Add to the registry
		void addForce ( shared_ptr<ForceGenerator> force, shared_ptr<Particle> p );

		// Remove pair from the registry
		void removeForce ( shared_ptr<ForceGenerator> force, shared_ptr<Particle> p );

		// Clear all forces from a specified particle
		void clearParticle ( shared_ptr<Particle> p );

		// Do the work
		void update ( fsecond dt );
	
	};
}

#endif
