#ifndef SPRING_FORCE_H
#define SPRING_FORCE_H

#include <memory>
#include <chrono>

#include "simphys/force_generator.h"

namespace simphys {

  class Particle;
  class vec3;
  typedef std::chrono::duration<float, std::ratio<1,1> > fsecond;
  using std::shared_ptr;

  class SpringForce : public ForceGenerator {
  private:
    shared_ptr<vec3> anchor;
    float springConstant;
    float restLength;

  public:
    SpringForce(vec3 anchor, float springConstant_, float restLength_);
    void setAnchor(vec3 anchor);
    void update(shared_ptr<Particle> p, fsecond dt);
  };

}

#endif // SPRING_FORCE_H
