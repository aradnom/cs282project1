// Program for comparing different integration methods

#include <iostream>
#include <chrono>
#include <thread>
#include <functional>

using std::function;

float euler ( float pos, float & vel, float dt ) {
	// Update velocity
	vel = dt * -9.8f + vel;
    
	// Calculate new position
	return dt * vel + pos;
}

float verlet ( float pos, float & vel, float dt ) {
	pos = pos + ( vel * dt ) + ( 0.5f * -9.8f * dt * dt );

	// Assumes acc doesn't change between steps - would need to solve for acc+1 to be accurate if a changes
	vel = vel + ( 0.5f * 2 * -9.8f ) * dt;

	return pos;	
}

/*
  Integrate the equation dx/dt = f(x,t) using the 4th-order RK method.
  
  \param f the RHS of the equation we're integrating
  \param t the current time
  \param x the current position, x(t)
  \param duration the time delta
*/
float rk4(function<float(float, float)> f, float t, float x, float duration) {
  float f1 = duration * f(t, x);
  float f2 = duration * f(t + 0.5f * duration, x + 0.5f * f1);
  float f3 = duration * f(t + 0.5f * duration, x + 0.5f * f2);
  float f4 = duration * f(t + duration, x + f3);
  return x + (1.0f/6.0f) * (f1 + 2.0f * f2 + 2.0f * f3 + f4);
}

int main ( int argc, char *argv[] ) {

  // parameters of our time-keeping.
  int frequency = 120;
  int millisPerTick = int{1000 * (1.0 / frequency)};
  std::chrono::milliseconds tick{millisPerTick};

  // The velocity at time t and position x.
  auto f = [](float t, float x) {
    return -9.8f * t;
  };

  // Starting velocities for euler and verlet
  float vel_euler = 0.0f;
  float vel_verlet = 0.0f; //0.5f * -9.8f * ((1.0f / frequency) * (1.0f / frequency)) // t+1, 2nd degree taylor

  // The initial position of our object.
  float position_rk4, position_verlet, position_euler;
  position_rk4 = position_verlet = position_euler = 1000.0f;

  float time = 0.0f;
  while (time < 1.0f) {
	// Update the position using euler
	position_euler = euler( position_euler, vel_euler, (1.0f / frequency) );

	// Update the position using position verlet
	position_verlet = verlet( position_verlet, vel_verlet, (1.0f / frequency) );

    // update the position using rk4.
    position_rk4 = rk4(f, time, position_rk4, (1.0f / frequency));	

    // update time.
    time += (1.0f / frequency);

    // This sleeping is not necessary for the math to work out, but
    // you'll want to start getting familiar with time and threads.
    std::this_thread::sleep_for(tick);
  }

  // Math tells us how far the object should have fallen.
  float expectedY = 1000.0f - 9.8 * time * time * 0.5f;

  // output.
  std::cout << "The expected position is: " << expectedY << "\n\n";

  std::cout << "Euler: " << position_euler << "\n";
  std::cout << "Difference: " << position_euler - expectedY << "\n\n";

  std::cout << "Verlet: " << position_verlet << "\n";
  std::cout << "Difference: " << position_verlet - expectedY << "\n\n";
  
  std::cout << "RK4: " << position_rk4 << "\n";
  std::cout << "Difference: " << position_rk4 - expectedY << std::endl; 

	std::cin.get();
}
