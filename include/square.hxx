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

#ifndef SQUARE_HXX
#define SQUARE_HXX

#include "rectangle.hxx" // also includes "coord.hxx"

namespace foom {

  /*!
    \brief Class for making squares.

    This is a specialized version of the Rectangle class.
   */
  class Square : public Rectangle {
  private:

  protected:

  public:
    /*!
      \brief Creates a square of sidelength 2 that straddles the origin.
     */
    Square(void);

    /*!
      \brief Constructs a square from the Rectangle constructor.
     */
    Square(CoordPnt usrCenter, double sideLength);

  };

}

#endif // SQUARE_HXX
