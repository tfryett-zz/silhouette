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

#ifndef COORD_HXX
#define COORD_HXX

#include <string>

namespace sil {
  
  /// \brief The Coordinate Point Class - Is not a drawable object - for utility
  /// purposes
  /// 
  /// This is used to make drawable objectsa and perform abstract operations 
  /// such as rotation about a point and forming lines for creating reflections
  /// accross said line.
  class CoordPnt {
  private:
    double x; //!< The x Coordinate point
    double y; //!< The y Coordinate point

  protected:

  public:
    /// \brief default contructor - set Coordinate to the origin
    CoordPnt(void);

    /// \brief constructor with user specified x and y values
    ///
    /// @usrX the x Coordinate point (double) of the new object
    /// @usrY the y Coordinate point (double) of the new object
    CoordPnt(double usrX, double usrY);

    /// \brief copy initializer - creates a new identical object
    CoordPnt(const CoordPnt &p);

    /// \brief Allows two Coord objects to be summed together
    CoordPnt operator + (const CoordPnt &p);

    /// \brief Allows the coord1 += coord2 operation 
    // (as in coord1 = coord1 + coord2)
    CoordPnt operator += (const CoordPnt &p);

    /// \brief Allows two CoordPnt objects to be subtracted from one another
    CoordPnt operator - (const CoordPnt &p);

    /// \brief Allows the coord1 -= coord2 operation 
    /// (as in coord1 = coord1 - coord2)
    CoordPnt operator -= (const CoordPnt &p);

    /// \brief Allows an assingment of one coord object to another
    CoordPnt &operator = (const CoordPnt &p);

    /// \brief returns the value of the x field in the CoordPnt object
    double getX(void) const;

    /// \brief returns the value of the y field in the CoordPnt object
    double getY(void) const;

    /// \brief Resets the x value of the Coordinate to the user specified value
    ///
    /// @usrX the x (double) value to set the x Coordinate value to
    void setX(double usrX);

    /// \brief Resets the y value of the Coordinate to the user specified value
    ///
    /// @usrY the y (double) value to set the y Coordinate value to
    void setY(double usrY);

    /// \brief creates a string "(x, y)" that creates a printable 
    std::string toString(void) const;
  };

  /// \brief Operator to "scale" a point (move further from origin).
  CoordPnt operator*(int multiplier, const CoordPnt& coord);

  /// \brief Operator to "scale" a point (move further from origin).
  CoordPnt operator*(const CoordPnt& coord, int multiplier);

  /// \brief Operator to add two points.
  CoordPnt operator+(const CoordPnt& coord1, const CoordPnt& coord2);

  /// \brief Operator to subtract two points.
  CoordPnt operator-(const CoordPnt& coord1, const CoordPnt& coord2);

}

#endif // COORD_HXX
