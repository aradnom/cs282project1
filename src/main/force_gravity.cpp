
namespace simphys {

	class vec3;
	class Particle;

	class ForceGravity : public ForceGenerator {
	private:
		
		vec3 gravity;

	public:
		// Assign gravity value to force
		ForceGravity ( const vec3 _gravity ) { gravity = _gravity; }

		// Updated particle with gravity
		void update(shared_ptr<Particle> p, fsecond dt) {
			if ( p->getMass <= 0 ) return;
			
			p->applyForce( gravity );
		}
	};

}
