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

#ifndef RECTANGLE_HXX
#define RECTANGLE_HXX

#include "polygon.hxx"

namespace sil {
  /*!
    \brief Class to create Rectangles.
   */
  class Rectangle : public Polygon {
  private:

  protected:

  public:
    /*!
      \brief The default constructor - creates a square that straddles the 
      origin.

      This is identical to the constructor for the polygon class.
     */
    Rectangle(void);

    /*!
      \brief Construct the rectangle specified by width, height, and the 
      center of the rectangle.

      @usrCenter The coordinate of the center of the new Rectangle object.
      @width The width of the Rectangle object
      @height The height of the Rectangle object.
     */
    Rectangle(CoordPnt usrCenter, double width, double height);
  };

}

#endif // RECTANGLE_HXX
