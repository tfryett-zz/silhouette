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

#ifndef CELL_ARRAY_CXX
#define CELL_ARRAY_CXX

#include "coord.hxx"
#include <sstream>
#include <stdexcept>

namespace foom {

  // must have the concept of the cell class to have references to
  // instances of the class
  class Cell; 

  /// class CellArray
  ///
  /// \brief The GDSII represenation of an array of referenced cells.
  ///
  /// This class is used primarily to save memory and to reduce human
  /// error. The concept is very similar to constant references in
  /// C and C++ in that it is a low memory "stand in" that does not
  /// allow for direct modification of the referenced cell, but does
  /// become updated when the instance of the referenced cell is
  /// changed.
  class CellArray {
  private:
    Cell& refCell; //!< The actual reference that makes it a cell reference.
    int numCol; //!< The number of times @refCell will be written in the x direction.
    int numRow; //!< The number of times @refCell will be written in the y direction.
    double xSpacing; //!< The spacing between each refCell in the x direction.
    double ySpacing; //!< The spacing between each refCell in the y direction.
    CoordPnt startingPos; //!< The coordinate of the lower left @refCell of the array of @refCell
    double magnification; //!< The magnification factor to apply to each @refCell
    double rotation; //!< The Rotation to apply to each of @refCell.

  protected:

  public:
    /// \brief The sole constructor for the CellArray class
    ///
    /// @cell The reference to the cell we want to reference.
    /// @usrStartingPos The coordinate of the lower left part of the cell array.
    /// @usrNumCol The number of columns in the cell array.
    /// @usrNumRow The number of rows in the cell array.
    /// @xSpacing The spacing between each column.
    /// @ySpacing The spacing between each row.
    CellArray(Cell& cell, CoordPnt usrStartingPos, int usrNumCol, 
	      int usrNumRow, double xSpacing, double ySpacing);

    /// \brief Sets the position of the lower left corner to @newStartingPos.
    ///
    /// @newStartingPos the new position of the lower left corner of the array.
    void setStartingPos(CoordPnt newStartingPos);

    /// \brief Returns the position of the lower left corner of the array.
    CoordPnt getStartingPos(void) const;

    /// \brief Sets the spacing between array columns.
    ///
    /// @newXSpacing the new spacing between array columns.
    ///
    /// The x spacing is allowed to be negative, which will cause the
    /// array to propogate along the negative x direction.
    void setXSpacing(double newXSpacing);
    
    /// \brief Returns the spacing inbetween columns.
    double getXSpacing(void) const;

    /// \brief Sets the spacing between array rows.
    ///
    /// @newXSpacing the new spacing between array rows.
    ///
    /// The x spacing is allowed to be negative, which will cause the
    /// array to propogate along the negative y direction.
    void setYSpacing(double newYSpacing);
    
    /// \brief Returns the spacing inbetween rows.
    double getYSpacing(void) const;

    /// \brief Sets a new spacing inbetween columns.
    ///
    /// @newNumCol The number of columns to be set.
    ///
    /// First checks if @newNumCol is a valid number of columns 
    /// (that is @newNumCol > 0) and then sets the member @numCol 
    /// or if it is not a valid number of columns throws an
    /// std::invalid_argument exception.
    void setNumCol(int newNumCol);

    /// \brief Returns the number of columns in the array.
    int getNumCol(void) const;

    /// \brief Sets a new spacing inbetween rows.
    ///
    /// @newNumRow The number of rows to be set.
    ///
    /// First checks if @newNumRow is a valid number of rows 
    /// (that is @newNumRow > 0) and then sets the member @numRow 
    /// or if it is not a valid number of rows throws an
    /// std::invalid_argument exception
    void setNumRow(int newNumRow);

    /// \brief Returns the number of rows in the array.
    int getNumRow(void) const;

    /// \brief Returns the name of the referenced cell.
    std::string getCellname(void) const;

    /// \brief Returns the value of rotation of the array members (in radians).
    double getRotation(void) const;
    
    /// \brief Sets a value for the rotation of the array members (in radians.)
    ///
    /// @newRotation The rotation of the array members (in radians).
    void setRotation(double newRotation);

    /// \brief Returns the value of magnification of each array element.
    ///
    /// A magnification of 1.0 means no magnification.
    double getMagnification(void) const;

    /// \brief Sets the value of magnification of each array element to be @newMagnification.
    ///
    /// @newMagnification The magnification to be set.
    ///
    /// A magnification of 1.0 means no magnification. Only positive
    /// magnification is allowed, and is only limted by the capacity
    /// of an eight byte double.
    void setMagnification(double newMagnification);

  };
}

#endif // CELL_ARRAY_CXX
