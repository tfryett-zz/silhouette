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

#ifndef LINE_HXX
#define LINE_HXX

#include "coord.hxx"
#include <vector>

namespace foom {

  /// \brief The Line Class - it is not a drawable quantitiy - It is not a 
  /// drawable object - for utility purposes
  ///
  /// This type of object is used for boolean processes and for utility methods
  /// such as reflecting an object across a line object.
  class LineSeg {
  private:
    std::vector<CoordPnt> limits; //!< defines the limits of line segment

  protected:
  public:

    /// \brief Creates a line defined by two end points defined by two CoordPnt 
    /// objects.
    ///
    /// @startSeg The beginning of the line segment
    /// @endSeg The end of the line segment
    LineSeg(CoordPnt startSeg, CoordPnt endSeg);
    
    /// \brief Reset the start of the line segment.
    ///
    /// @startSeg where the line segment will have its new start
    void setStartSeg(const CoordPnt &startSeg);

    /// \brief Restart the end of the line segment.
    ///
    /// @setEndSeg the new end of the line segment
    void setEndSeg(const CoordPnt &endSeg);

    /// \brief Retrieve a copy of the CoordPnt object that is at the start of the line
    /// segment.
    CoordPnt getStartPnt(void) const;

    /// Retrieve a copy of the CoordPnt object that is at the start of the line
    /// segment.
    CoordPnt getEndPnt(void) const;

    /// Return the length of the LineSeg object
    double length(void);

    /// Returns the rotation of the LineSeg object with respect to the positive
    /// x-axis (radians, -pi <= rad <= pi)
    double angleOffset(void);

    /// Returns the rotation of the LineSeg object with respect to the positive
    /// x-axis (degrees -180 <= degree <= 180 )
    double angleOffsetDegree(void);

    /// Returns the coordinate point that lies at the center of the line segment.
    CoordPnt getCenter(void) const;

  }; // class LineSeg 

  LineSeg operator+(const LineSeg& lin1, const LineSeg& lin2);

  LineSeg operator-(const LineSeg& lin1, const LineSeg& lin2);

  //----------------------------------------------------------------//
  // Line utility functions
  // contains functions which do not make sense to have as methods/
  // class memebers or are better represented as functions than
  // methods. They are all included in this header as they are 
  // intimately related to the LineSeg class, and will be expected
  // to be available when the LinSeg class is available.

  /// \brief Determines if two lines intersect.
  ///
  /// @lin1 The first line to consider.
  /// @lin2 The second line to consider.
  ///
  /// Returns true if lin1 crosses lin2. Note that we purposefully
  /// implement this function so that two lines that are colinear
  /// and overlap return false.
  bool lineSegIntersect(LineSeg lin1, LineSeg lin2);

  /// \brief Finds if the point pnt is on the line segment seg.
  ///
  /// @seg The line segment in question.
  /// @pnt The coordinate point in question.
  ///
  /// Returns true if pnt is on seg, false otherwise.
  bool pointOnLineSeg(LineSeg seg, CoordPnt pnt);

  /// \brief Finds the orientation of the coordinate point to the line
  /// segment.
  ///
  /// @seg The line segment.
  /// @pnt The coordinate point.
  ///
  /// The function returns following values
  /// 0 --> lin1.getStartPnt() pnt and lin1.getEndPnt() are colinear
  /// 1 --> Clockwise
  /// 2 --> Counterclockwise
  int orientation(LineSeg seg, CoordPnt pnt);

} // namespace foom

#endif // LINE_HXX
