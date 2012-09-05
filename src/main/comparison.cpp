// Program for comparing different integration methods

#include <iostream>
#include <chrono>
#include <thread>
#include <functional>

using std::function;

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

	std::cin.get();
}
