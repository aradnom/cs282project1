#include "simphys/spring_force.h"

#include <memory>
#include <chrono>

#include "simphys/vec3.h"
#include "simphys/particle.h"

namespace simphys {
  
  using std::shared_ptr;
  typedef std::chrono::duration<float, std::ratio<1,1> > fsecond;

  SpringForce::SpringForce(vec3 anchor_, float springConstant_, float restLength_)
    : anchor{std::make_shared<vec3>(anchor_)}
    , springConstant{springConstant_}
    , restLength{restLength_} {  }

  void SpringForce::setAnchor(vec3 anchor_) {
    *this->anchor = anchor_;
  }

  void SpringForce::update(shared_ptr<Particle> p, fsecond dt) {
    auto dir = p->getPosition() - *anchor;
    auto norm = dir.norm();
    if (norm < restLength) {
      return;
    }
    norm = (restLength - norm) * springConstant;
    p->applyForce(dir.normalized() * norm);
  }  

}
