/*
  Main program.
*/

#include <iostream>
#include <memory>

#include "simphys/sim_world.h"
#include "simphys/sim_engine.h"
#include "simphys/simobject.h"
#include "simphys/simobject2D.h"
#include "simphys/particle.h"
#include "simphys/vec3.h"
#include "simphys/spring_force.h"
#include "simphys/force_gravity.h"
#include "simphys/force_wind.h"

int main(int argc, char **argv) {

  // Check for timescale flag and set appropriately
  float timeScale = argc > 1 ? atof( argv[1] ) : 1.0f;	

  // create a simulator
  simphys::SimEngine sim;

  auto clock_ptr = std::make_shared< simphys::Clock<fseconds> >(fseconds{0.0f});
  sim.setClock(clock_ptr, timeScale);

  // create a world to simulate
  auto world_ptr = std::make_shared<simphys::SimWorld>();
  sim.setSimWorld(world_ptr);

  // create and initialize the anchor point
  simphys::Particle p_anchor;
  simphys::Sprite s_anchor;
  auto anchor_ptr = std::make_shared<simphys::SimObject2D>(p_anchor, s_anchor);
  auto anchor_state = anchor_ptr->getState();
  anchor_state->setPosition(simphys::vec3{420.0f, 500.0f, 0.0f});

  // create and initialize an object
  simphys::Particle p;
  simphys::Sprite s;
  auto obj_ptr = std::make_shared<simphys::SimObject2D>(p, s);
  auto objState = obj_ptr->getState();
  objState->setPosition(simphys::vec3{100, 500.5, 0});
  objState->setVelocity(simphys::vec3{200.0, 60.0, 0});
  objState->setAcceleration(simphys::vec3{0, 0, 0});
  objState->setMass(1.0);
  objState->setDamping(0.8);

  // Create a second object
  simphys::Particle p2;
  simphys::Sprite s2;
  auto obj_ptr2 = std::make_shared<simphys::SimObject2D>(p2, s2);
  auto objState2 = obj_ptr2->getState();
  objState2->setPosition(simphys::vec3{200, 10, 0});
  objState2->setMass(2.0);
  objState2->setDamping(0.9);

  // Add particles to the engine
  (sim.getPhysicsEngine())->addParticle( objState );
  (sim.getPhysicsEngine())->addParticle( objState2 );

  // Add force generators to the registry for object one
  auto gravity = std::make_shared<simphys::ForceGravity>(-9.8f); // Go down
  (sim.getPhysicsEngine())->addForce( gravity, objState );  
  auto wind = std::make_shared<simphys::ForceWind>(simphys::vec3{-10.0f,0,0}); // Blow towards left side of screen
  (sim.getPhysicsEngine())->addForce( wind, objState ); 
  auto springy = std::make_shared<simphys::SpringForce>(anchor_state->getPosition(), 1, 300.0); // Jump around
  (sim.getPhysicsEngine())->addForce( springy, objState );

  // Object 2
  auto gravity2 = std::make_shared<simphys::ForceGravity>(10.0f); // Go up
  (sim.getPhysicsEngine())->addForce( gravity2, objState2 );  
  auto wind2 = std::make_shared<simphys::ForceWind>(simphys::vec3{5.0f,0.0f,0}); // Blow towards right side of screen
  (sim.getPhysicsEngine())->addForce( wind2, objState2 ); 

  // add objects to the world.
  world_ptr->add(anchor_ptr);
  world_ptr->add(obj_ptr);
  world_ptr->add(obj_ptr2);

  // initialize the simulator and run it.
  sim.init();
  sim.run();

}
