// This file is a part of silhouette (2D Geometry suite)
//
// Copyright 2015 Taylor Fryett
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <string>
#include <sstream>
#include "../include/coord.hxx"

namespace sil {

  /*! 
    The default constructor. Creates a coordinate point at the origin
    
    Example use:
    coord origin = new CoordPnt(void);
  */
  CoordPnt::CoordPnt(void) {
    x = 0;
    y = 0;
  }
  
  /*!
    
  */
  CoordPnt::CoordPnt(double usrX, double usrY) {
    x = usrX;
    y = usrY;
  }

  // constructor that copies the passed in coord point object
  CoordPnt::CoordPnt(const CoordPnt &p) {
    x = p.x;
    y = p.y;
  }

  CoordPnt CoordPnt::operator + (const CoordPnt &p) {
    return CoordPnt(x + p.getX(), y + p.getY());
  }

  CoordPnt CoordPnt::operator += (const CoordPnt &p) {
    x += p.getX();
    y += p.getY();
    return *this;
  }

  CoordPnt CoordPnt::operator - (const CoordPnt &p) {
    return CoordPnt(x - p.getX(), y - p.getY());
  }

  CoordPnt CoordPnt::operator -= (const CoordPnt &p) {
    x -= p.getX();
    y -= p.getY();
    return *this;
  }

  CoordPnt &CoordPnt::operator = (const CoordPnt &p) {
    x = p.x;
    y = p.y;
    return *this;
  }


  // returns a copy of the field "x"
  double CoordPnt::getX(void) const {
    return this->x;
  }

  // allows user to reset the field "x"
  void CoordPnt::setX(double usrX) {
    this->x = usrX;
  }

  // returns a copy of the field "y"
  double CoordPnt::getY(void) const {
    return this->y;
  }

  // allows user to reset the field "y"
  void CoordPnt::setY(double usrY) {
    this->y = usrY;
  }

  // allows the user to turn a CoordPnt object into a print friendly string
  std::string CoordPnt::toString(void) const {
    std::ostringstream output;
    output << "(" << this->getX() << ", " << this->getY() << ")";
    return output.str();
  }

  CoordPnt operator+(const CoordPnt& coord1, const CoordPnt& coord2) {
    return CoordPnt(coord1.getX() + coord2.getX(), 
		    coord1.getY() + coord2.getY());
  }
  
  CoordPnt operator-(const CoordPnt& coord1, const CoordPnt& coord2) {
    return CoordPnt(coord1.getX() - coord2.getX(), 
		    coord1.getY() - coord2.getY());
  }

  CoordPnt operator*(int multiplier, const CoordPnt& coord) {
    return CoordPnt(coord.getX()*multiplier, coord.getY()*multiplier);
  }

  CoordPnt operator*(const CoordPnt& coord, int multiplier) {
    return CoordPnt(coord.getX()*multiplier, coord.getY()*multiplier);
  }

}
