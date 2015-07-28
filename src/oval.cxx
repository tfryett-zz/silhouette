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
#include "../include/coord.hxx"
#include "../include/oval.hxx"
#include <cmath>
#include <stdexcept>

namespace sil {

  Oval::Oval(CoordPnt usrCenter, double majorAxisLength, double minorAxisLength,
             int numCoordPnts) {
    // Throw an exception if numCoordPnts is not reasonably high (at least 4)
    if (numCoordPnts < 4) 
      throw std::invalid_argument("numCoordPnts is too small to be effective.");
    if (majorAxisLength < minorAxisLength)
      throw std::invalid_argument("The major radius must be larger than the minor radius");
    // The angular separation of the vertices
    const double PI = std::acos(-1); // compiler limited representation of pi
    double angularSep = 2*PI/numCoordPnts;
    double angularPos = 0.;
    for (int i = 0; i < numCoordPnts; i++) {
      double localRadius = majorAxisLength*minorAxisLength/
        std::sqrt(std::pow(minorAxisLength*std::cos(angularPos), 2) +
                  std::pow(majorAxisLength*std::sin(angularPos), 2));
      double vertexX = localRadius*std::cos(angularPos);
      double vertexY = localRadius*std::sin(angularPos);
      vertices.push_back(CoordPnt(vertexX + usrCenter.getX(), 
                                  vertexY + usrCenter.getY()));
      angularPos += angularSep;
    }
    
    // set all of the oval field values for this object
    // area of an ellipse is a*b*pi (acos(-1) = most precise version of pi)
    this->minorLength = minorAxisLength;
    this->majorLength = majorAxisLength;
    this->eccentricity = findEccentricity();
    this->center = usrCenter;
  }

  Oval::Oval(LineSeg majorAxis, double minorAxisLength, int numCoordPnts) :
    Oval(majorAxis.getCenter(), minorAxisLength, numCoordPnts) {
    this->rotate(majorAxis.getCenter(), majorAxis.angleOffset());
  }

  // The eccentricity is defined as:
  // e = sqrt((a^2 - b^2)/a^2)
  // where e is the eccentricity, a is the major axis length, b is the minor
  // axis length.
  double Oval::findEccentricity(void) const {
    return std::sqrt((pow(majorLength, 2) - pow(minorLength, 2))
                             /pow(majorLength, 2));
  }

}
