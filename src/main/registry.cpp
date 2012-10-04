#include <memory>
#include "simphys/registry.h"

namespace simphys {

	using std::shared_ptr;

	void ForceRegistry::addForce ( shared_ptr<ForceGenerator> force, shared_ptr<Particle> p ) {
		ForcePair newPair( force, p );
		
		forces.push_back( newPair );
	}	

	void ForceRegistry::removeForce ( shared_ptr<ForceGenerator> force, shared_ptr<Particle> p ) {
		std::vector<ForcePair>::iterator i = forces.begin();
		
		for ( ; i != forces.end(); i++ )	
			if ( i->force == force && i->p == p )
				forces.erase( i );			
	}

	void ForceRegistry::clearParticle ( shared_ptr<Particle> p ) {
		std::vector<ForcePair>::iterator i = forces.begin();
		
		for ( ; i != forces.end(); i++ )	
			if ( i->p == p )
				forces.erase( i );		
	}

	void ForceRegistry::update ( float dt ) {
		std::vector<ForcePair>::iterator i = forces.begin();
		
		for ( ; i != forces.end(); i++ )	
			i->force->update( i->p, dt );
	}
}

