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

#include "../include/square.hxx"

namespace foom {
  // Use the default constructor for both the Rectangle and the Polygon default
  // constructors 
  Square::Square(void) : Rectangle() {};

  // Use the Rectangle constructor but assume make sure both sides have the 
  // same length
  Square::Square(CoordPnt usrCenter, double sideLength) : 
    Rectangle(usrCenter, sideLength, sideLength) {};
}