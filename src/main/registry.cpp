#include <chrono>
#include <memory>
#include "simphys/registry.h"
#include "simphys/force_generator.h"

namespace simphys {

	typedef std::chrono::duration<float, std::ratio<1,1> > fsecond;
	using std::shared_ptr;

	void ForceRegistry::addForce ( shared_ptr<ForceGenerator> force, shared_ptr<Particle> p ) {		
		forces.push_back( ForcePair{ force, p } );
	}	

	void ForceRegistry::removeForce ( shared_ptr<ForceGenerator> force, shared_ptr<Particle> p ) {
		std::vector<ForcePair>::iterator i = forces.begin();

		for ( auto& f : forces ) {
			i++;
			if ( f.force == force && f.p == p )
				forces.erase( i );

		}			
	}

	void ForceRegistry::clearParticle ( shared_ptr<Particle> p ) {
		std::vector<ForcePair>::iterator i = forces.begin();

		for ( auto& f : forces ) {
			i++;
			if ( f.p == p )
				forces.erase( i );

		}		
	}

	void ForceRegistry::update ( fsecond dt ) {
		for ( auto& f : forces )
			f.force->update( f.p, dt );		  	
	}
}

