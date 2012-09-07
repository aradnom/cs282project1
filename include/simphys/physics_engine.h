#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H

#include <memory>
#include <chrono>
#include <vector>
#include "simphys/registry.h"

namespace simphys {

  class Particle;
  class SimWorld;
  class SpringForce;
  class ForceRegistry;

  using std::shared_ptr;
  
  typedef std::chrono::duration<float, std::ratio<1,1> > fseconds;

  typedef std::vector< std::pair<shared_ptr<SpringForce>, 
    shared_ptr<Particle> > > SpringRegistry;

  class PhysicsEngine {
  private:
    shared_ptr<SimWorld> sw;
    SpringRegistry reg;
    fseconds lastTick;
	std::vector<shared_ptr<Particle> > particles;
	ForceRegistry registry;

  public:
    PhysicsEngine()
      : lastTick{fseconds{0.016}} { }

    /*
      Update state.
    */
    void tick(fseconds dt);

    void setSimWorld(shared_ptr<SimWorld> simworld);
    shared_ptr<SimWorld> getSimWorld() const;

    void addSpringPair(shared_ptr<SpringForce> fg, shared_ptr<Particle> p);

	void addParticle( shared_ptr<Particle> p );

	void addForce( shared_ptr<ForceGenerator> fg, shared_ptr<Particle> p );

  };

}

#endif // PHYSICS_ENGINE_H
