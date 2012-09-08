/*
  A 3D Vector.

  \author Richard Kelley.
*/

#ifndef VEC3_H
#define VEC3_H

#include <string>
#include <cmath>

namespace simphys {
  
  class vec3 {
  private:
    float x;
    float y;
    float z;
  public:
    /*
      Constructor.
      \param x_, y_, z_ the coordinates of the vector.
    */
    vec3(float x_ = 0.0f, float y_ = 0.0f, float z_ = 0.0f);

    /*
      Copy constructor.
    */
    vec3(const vec3& other);

    /*
      Copy assignment operator.
    */
    vec3& operator=(const vec3& other);

		// Comparison operator - note these are comparing speed (magnitude)
		bool operator < ( vec3 & other );

		bool operator < ( float speed );

    /*
      Move operator
    */
    // TODO

    /*
      Return the norm of the vector.
    */
    float norm() const;

    /*
      Return the square of the norm, for efficiency.
    */
    float norm_sq() const;

    /*
      Return the unit vector pointing in the same direction as this
      vector.
     */
    vec3 normalized() const;

    /*
      Normalize this vector.
    */
    void normalize();

    /*
      Dot product of this vector with the other vector
     */
    float dotProduct(const vec3& other) const;

    /*
      Cross product of this vector with the other vector.
     */
    vec3 crossProduct(const vec3& other) const;

    /*
      Getters and setters for the member variables.
    */
    float getX() const;
    float getY() const;
    float getZ() const;
    void setX(float newX);
    void setY(float newY);
    void setZ(float newZ);

    /*
      return a string representation of this vector.
    */
    std::string toString();    

    /*
      Compare for equality using a precision appropriate for numerical
      simulation.
    */
    bool operator==(const vec3& other) {
      float precision = 0.0001f;
      return (std::fabs(x - other.x) < precision && 
	      std::fabs(y - other.y) < precision && 
	      std::fabs(z - other.z) < precision);
    }

  };

  /*
    Operations on vec3 inputs.
  */
  vec3 operator+(const vec3& v1, const vec3& v2);
  vec3 operator-(const vec3& v1, const vec3& v2);
  vec3 operator*(float, const vec3& v1);
  vec3 operator*(const vec3& v1, float);
  
}

#endif // VEC3_H
