// Class for detecting collisions within a simulation

#ifndef DETECTOR_H
#define DETECTOR_H

#include <string>
#include <vector>
#include <chrono>
#include <memory>
#include "simphys/sim_world.h"
#include "simphys/collision.h"

namespace simphys {

	using std::shared_ptr;
  
  	class Detector {
	private:
		
		vector<Collision> collisions;

	public:

		Detector( shared_ptr<SimWorld> sw );
		
		shared_ptr<vector<Collision> > generateCollisions();
	};

}

#endif
