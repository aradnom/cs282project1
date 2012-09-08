/*
  Implementation of the vec3 class.

  \author Richard Kelley
*/

#include <cmath>
#include <string>

#include "simphys/vec3.h"

simphys::vec3::vec3(float x_, float y_ , float z_ ) 
  : x(x_), y(y_), z(z_) {
}

simphys::vec3::vec3(const vec3& other) {
  this->x = other.x;
  this->y = other.y;
  this->z = other.z;
}

simphys::vec3& simphys::vec3::operator=(const vec3& other) {
  
  if (this == &other) {
    return *this;
  }

  this->x = other.x;
  this->y = other.y;
  this->z = other.z;

  return *this;
}

bool simphys::vec3::operator < ( vec3 & other ) {
	return other.norm_sq() < this->norm_sq() ? true : false;
}

bool simphys::vec3::operator < ( float speed ) {
	return this->norm_sq() < speed ? true : false;
}

float simphys::vec3::norm() const {
  return std::sqrt(x*x + y*y + z*z);
}

float simphys::vec3::norm_sq() const {
  return (x*x + y*y + z*z);
}

simphys::vec3 simphys::vec3::normalized() const {
  float n = norm();
  return vec3(x / n, y / n, z / n);
}

void simphys::vec3::normalize() { 
  float n = norm();
  x /= n;
  y /= n;
  z /= n;
}

float simphys::vec3::dotProduct(const simphys::vec3& other) const {
  return x * other.x + y * other.y + z * other.z;
}

simphys::vec3 simphys::vec3::crossProduct(const simphys::vec3& other) const {
  return vec3(y * other.getZ() - z * other.getY(), 
	      z * other.getX() - x * other.getZ(), 
	      x * other.getY() - y * other.getX());
}

float simphys::vec3::getX() const {
  return x;
}

float simphys::vec3::getY() const {
  return y;
}

float simphys::vec3::getZ() const {
  return z;
}

void simphys::vec3::setX(float newX) {
  x = newX;
}

void simphys::vec3::setY(float newY) {
  y = newY;
}

void simphys::vec3::setZ(float newZ) {
  z = newZ;
}

std::string simphys::vec3::toString() {
      return "(" + std::to_string(x) + 
	"," + std::to_string(y) + 
	"," + std::to_string(z) + ")";
}

simphys::vec3 simphys::operator+(const simphys::vec3& v1, const simphys::vec3& v2) {
  return vec3(v1.getX() + v2.getX(), 
	      v1.getY() + v2.getY(), 
	      v1.getZ() + v2.getZ());
}

simphys::vec3 simphys::operator-(const simphys::vec3& v1, const simphys::vec3& v2) {
  return vec3(v1.getX() - v2.getX(), 
	      v1.getY() - v2.getY(), 
	      v1.getZ() - v2.getZ());
}

simphys::vec3 simphys::operator*(float c, const simphys::vec3& v1) {
  return vec3(c * v1.getX(), 
	      c * v1.getY(), 
	      c * v1.getZ());
}

simphys::vec3 simphys::operator*(const simphys::vec3& v1, float c) {
  return vec3(v1.getX() * c, 
	      v1.getY() * c, 
	      v1.getZ() * c);
}
