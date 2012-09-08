#ifndef PHYSICS_ENGINE_H
#define PHYSICS_ENGINE_H

#include <memory>
#include <chrono>
#include <vector>
#include "simphys/registry.h"
#include "simphys/collision.h"

namespace simphys {

  class Particle;
  class SimWorld;
  class SpringForce;

  using std::shared_ptr;
  
  typedef std::chrono::duration<float, std::ratio<1,1> > fseconds;

  class PhysicsEngine {
  private:
    shared_ptr<SimWorld> sw;
    fseconds lastTick;
	ForceRegistry registry;
	std::vector<Collision> collisions;

  public:
    PhysicsEngine()
      : lastTick{fseconds{0.016}} {}

    /*
      Update state.
    */
    void tick(fseconds dt);

	void getCollisions();

    void setSimWorld(shared_ptr<SimWorld> simworld);
    shared_ptr<SimWorld> getSimWorld() const;

	void addForce( shared_ptr<ForceGenerator> fg, shared_ptr<Particle> p );

  };

}

#endif // PHYSICS_ENGINE_H
