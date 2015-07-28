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

#include "../include/line.hxx"
#include <cmath>

namespace sil {

  // normal constructor 
  LineSeg::LineSeg(CoordPnt startSeg, CoordPnt endSeg) {
    limits.push_back(startSeg);
    limits.push_back(endSeg);
  }

  // sets the starting part of the line segment
  void LineSeg::setStartSeg(const CoordPnt &startSeg) {
    this->limits[0] = startSeg;
  }

  // sets the ending part of the line segment
  void LineSeg::setEndSeg(const CoordPnt &endSeg) {
    this->limits[1] = endSeg;
  }

  // returns the start of the line segment
  CoordPnt LineSeg::getStartPnt() const {
    CoordPnt returnPnt = limits[0];
    return returnPnt;
  }

  // returns the end of the line segment
  CoordPnt LineSeg::getEndPnt() const {
    CoordPnt returnPnt = limits[1];
    return returnPnt;
  }

  // Returns the length of the line segment
  double LineSeg::length() {
    CoordPnt startPnt = this->getStartPnt();
    CoordPnt endPnt = this->getEndPnt();
    double xSeparation = std::abs(startPnt.getX() - endPnt.getX());
    double ySeparation = std::abs(startPnt.getY() - endPnt.getY());
    // use the standard distance equation:
    //     d = sqrt(x^2 + y^2)
    return std::sqrt(std::pow(xSeparation, 2) + std::pow(ySeparation, 2));
  }

  // Returns the rotation of the LineSeg object with respect to the positive
  // x-axis (radians)
  double LineSeg::angleOffset() {
    CoordPnt startPnt = this->getStartPnt();
    CoordPnt endPnt = this->getEndPnt();
    double xSeparation = std::abs(startPnt.getX() - endPnt.getX());
    double ySeparation = std::abs(startPnt.getY() - endPnt.getY());
    // atan is the arctangent function
    return std::atan2(ySeparation, xSeparation);
  }

  // Returns the rotation of the LineSeg object with respect to the positive
  // x-axis in degrees
  double LineSeg::angleOffsetDegree() {
    double rotInRad = angleOffset();
    // acos is the arccosine function. This provides the most precise value of
    // the constant pi allowed by the user's compiler.
    double pi = std::acos(-1.); 
    // Degrees = 180/pi * Radians
    return rotInRad*180./pi;
  }

  // Returns a CoordPnt that is at the average point of the two limit points of
  // the LineSeg object.
  CoordPnt LineSeg::getCenter() const {
    return CoordPnt((limits[0].getX() + limits[1].getX())/2., 
                                  (limits[0].getY() + limits[1].getY())/2.);
  }

  LineSeg operator+(const LineSeg& lin1, const LineSeg& lin2) {
    return LineSeg(lin1.getStartPnt() + lin2.getStartPnt(),
		   lin1.getEndPnt() + lin2.getEndPnt());
  }

  LineSeg operator-(const LineSeg& lin1, const LineSeg& lin2) {
    return LineSeg(lin1.getStartPnt() - lin2.getStartPnt(),
		   lin1.getEndPnt() - lin2.getEndPnt());
  }

  bool pointOnLineSeg(LineSeg seg, CoordPnt pnt) {
    if ( pnt.getX() <= std::max(seg.getStartPnt().getX() , seg.getEndPnt().getX()) &&
	 pnt.getX() >= std::min(seg.getStartPnt().getX() , seg.getEndPnt().getX()) &&
	 pnt.getY() <= std::max(seg.getStartPnt().getY() , seg.getEndPnt().getY()) &&
	 pnt.getY() >= std::min(seg.getStartPnt().getY() , seg.getEndPnt().getY())
	 )
      return true;
    else
      return false;
  }
 
  int orientation(LineSeg seg, CoordPnt pnt) {
    // See 10th slides from following link for derivation of the formula
    // http://www.dcs.gla.ac.uk/~pat/52233/slides/Geometry1x1.pdf
    CoordPnt firstToPnt = pnt - seg.getStartPnt();
    CoordPnt lastToPnt = seg.getEndPnt() - pnt;
    int val = firstToPnt.getY()*lastToPnt.getX() -
      firstToPnt.getX()*lastToPnt.getY();
    //    int val = (q.y - p.y) * (r.x - q.x) -
    //         (q.x - p.x) * (r.y - q.y);
 
    if (val == 0) // colinear 
      return 0;  
    else
      return (val > 0)? 1: 2; // clock or counterclock wise
  }

  bool lineSegIntersect(LineSeg lin1, LineSeg lin2) {
    int orient1 = orientation(lin1, lin2.getStartPnt());
    int orient2 = orientation(lin1, lin2.getEndPnt());
    int orient3 = orientation(lin2, lin1.getStartPnt());
    int orient4 = orientation(lin2, lin1.getEndPnt());

    // General case:
    // The line segments are at different angles and they intersect.
    if (orient1 != orient2 && orient3 != orient4)
        return true;
    else 
      return false; 

    /*
      Provided for reference if there is ever the need to determine
      if two parallel lines intersect.

      // Special Cases
      // lin1 and lin2.getStartpnt() are coliniar and 
      // lin2.getStartpnt() lies on lin1
      if (orient1 == 0 && pointOnLineSeg(lin1, lin2.getStartPnt()))
        return true;
 
      // lin1 and lin2.getEndpnt() are coliniar and 
      // lin2.getEndpnt() lies on lin1
      if (orient2 == 0 && pointOnLineSeg(lin1, lin2.getEndPnt())) 
        return true;
 
      // lin2 and lin1.getStartpnt() are coliniar and 
      // lin1.getStartpnt() lies on lin2
      if (orient3 == 0 && pointOnLineSeg(lin2, lin1.getStartPnt())) 
        return true;
 
      // lin2 and lin1.getEndpnt() are coliniar and 
      // lin1.getEndpnt() lies on lin2
      if (orient4 == 0 && pointOnLineSeg(lin2, lin1.getEndPnt())) 
        return true;
    */
  }
  
}
