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

#ifndef OVAL_HXX
#define OVAL_HXX

#include "polygon.hxx"
#include "line.hxx"
#include "coord.hxx"
#include <cmath>
#include <stdexcept>

namespace sil {


  /// \brief A class to create ovals of any specification.
  ///
  /// This is a class that generates ovals, typically defined by their center,
  /// minor axis, major axis, and their orientation. Along with these quantities
  /// the number of points that lies on the circumfrence also needs to be 
  /// defined.
  ///
  /// All objects of this class satisfy the general equation for an ellipse:
  /// x^2/a^2 + y^2/b^2 = 1
  /// where a and b are the lengths of the minor or major axis.
  class Oval : public Polygon {
  private:

  protected:
    double eccentricity; //!< The ellipse eccentricity (0 for a circle, 1 for a line segment)
    double minorLength; //<! The minor axis length
    double majorLength; //!< The major axis length
    //! \brief Returns the eccentricity of the referenced oval object.
    double findEccentricity(void) const;
  public:

    /// \brief Defines an arbitrary oval.
    /// 
    /// @majorAxis The LineSeg object that defines the placement and length of the
    /// major axis.
    /// @minorAxisLength The length of the minor axis.
    /// @numCoordPnts The number of CoordPnt objects that will represent the 
    /// discretization of the oval objct.
    ///
    /// Allows the user to construct an arbitrary oval by specifying the 
    /// major and minor axis. Since specifying the minor axis by a lineseg would 
    /// at best be redudant, instead we use a length to avoid such a problem.
    Oval(LineSeg majorAxis, double minorAxisLength, int numCoordPnts = 16);

    /// \brief Defines an arbitrary oval.
    /// 
    /// @majorAxisLength The length of the major axis (centered on usrCenter).
    /// @minorAxisLength The length of the minor axis (centered on usrCenter).
    /// @numCoordPnts The number of CoordPnt objects that will represent the 
    /// discretization of the oval objct.
    /// 
    /// Allows the user to construct an arbitrary oval by specifying the 
    /// major and minor axis lengths. This should be the constructor to use the 
    /// majority of the time, unless you have some specific need to use another 
    /// type of constructor.
    /// raised.
    Oval(CoordPnt usrCenter, double majorAxisLength, double minorAxisLength,
         int numCoordPnts = 16);

  };

}

#endif // OVAL_HXX
