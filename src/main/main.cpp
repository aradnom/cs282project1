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

void setObjectVelocities ( simphys::vec3 & obj1, simphys::vec3 & obj2, int argc, char **argv ) {
	if ( argc > 2 )
		obj1.setX( atof( argv[2] ) );
	if ( argc > 3 )
		obj1.setY( atof( argv[3] ) );
	if ( argc > 4 )
		obj2.setX( atof( argv[4] ) );
	if ( argc > 5 )
		obj2.setY( atof( argv[5] ) );
}

int main(int argc, char **argv) {
	// Set default object velocities to something sensible for colliding
	simphys::vec3 obj1velocity{100,50,0};
	simphys::vec3 obj2velocity{-100,50,0};

  // Check for timescale flag and set appropriately
  float timeScale = argc > 1 ? atof( argv[1] ) : 1.0f;	

	// Modify velocities from command line if specified
	setObjectVelocities( obj1velocity, obj2velocity, argc, argv );

  // create a simulator
  simphys::SimEngine sim;

  auto clock_ptr = std::make_shared< simphys::Clock<fseconds> >(fseconds{0.0f});
  sim.setClock(clock_ptr, timeScale);

  // create a world to simulate
  auto world_ptr = std::make_shared<simphys::SimWorld>();
  sim.setSimWorld(world_ptr);

  // create and initialize an object
  simphys::Particle p;
  simphys::Sprite s;
  auto obj_ptr = std::make_shared<simphys::SimObject2D>(p, s);
  auto objState = obj_ptr->getState();
  objState->setPosition(simphys::vec3{200, 100, 0});
	objState->setVelocity(obj1velocity);
  objState->setMass(50.0);
  objState->setDamping(0.8);

  // Create a second object
  simphys::Particle p2;
  simphys::Sprite s2;
  auto obj_ptr2 = std::make_shared<simphys::SimObject2D>(p2, s2);
  auto objState2 = obj_ptr2->getState();
  objState2->setPosition(simphys::vec3{1000, 100, 0});
	objState2->setVelocity(obj2velocity);
  objState2->setMass(50.0);
  objState2->setDamping(0.8);

  // Add force generators to set up a basic collision
  auto gravity = std::make_shared<simphys::ForceGravity>(-25.0f);
  (sim.getPhysicsEngine())->addForce( gravity, objState );  
  auto wind = std::make_shared<simphys::ForceWind>(simphys::vec3{10.0f,0.0f,0}); // Blow towards right side of screen
  (sim.getPhysicsEngine())->addForce( wind, objState ); 

  // Object 2
  auto gravity2 = std::make_shared<simphys::ForceGravity>(-25.0f);
  (sim.getPhysicsEngine())->addForce( gravity2, objState2 );  
  auto wind2 = std::make_shared<simphys::ForceWind>(simphys::vec3{-10.0f,0.0f,0}); // Blow towards left side of screen
  (sim.getPhysicsEngine())->addForce( wind2, objState2 );

  // add objects to the world.
  world_ptr->add(obj_ptr);
  world_ptr->add(obj_ptr2);

  // initialize the simulator and run it.
  sim.init();
  sim.run();

}
