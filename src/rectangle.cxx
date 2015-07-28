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

#include "../include/rectangle.hxx"
#include "../include/coord.hxx"

namespace sil {

  // This constructor does the same exact thing as the default constructor for 
  // the polygon class - so just call it to do the work.
  Rectangle::Rectangle(void) : Polygon() {};

  // The usual constructor for this class
  Rectangle::Rectangle(CoordPnt usrCenter, double width, double height) {
    center = usrCenter;
    double maxX = usrCenter.getX() + width/2;
    double minX = usrCenter.getX() - width/2;
    double maxY = usrCenter.getY() + height/2;
    double minY = usrCenter.getY() - height/2;
    vertices.push_back(CoordPnt(minX, maxY)); // upper left corner
    vertices.push_back(CoordPnt(maxX, maxY)); // upper right corner
    vertices.push_back(CoordPnt(maxX, minY)); // lower right corner
    vertices.push_back(CoordPnt(minX, minY)); // lower left corner
    boundingBox = vertices; // for rectangles these are the same
  }
}
