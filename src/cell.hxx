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

#ifndef CELL_HXX
#define CELL_HXX

#include <string>
#include <vector>
#include <ctime>
#include "polygon.hxx"
#include "path.hxx"
#include "cellReference.hxx"
#include "cellArray.hxx"

/// \brief A struct to contain all of the date and time information needed by GDSII standards.
struct timeData {
  int year; 
  int month; 
  int day; 
  int hour; 
  int minute; 
  int second; 
};

namespace sil {

  /// Cells that are added to a Layout can be considered to be a
  /// component of a larger fabrication flow. An example would be
  /// the design for a transistor that is to be repeatedly used.
  /// Having it be defined as a Cell would allow for a CellReference
  /// to take the place of each transitor. This not only saves
  /// space but also acts to counter mistakes in trying to define
  /// many copies of the same thing.
  class Cell {
  private:

  protected:
    std::string cellname; //!< The name this object.
    std::vector<Polygon> polyList; //<! The vector of objects the cell contains.
    std::vector<Path> pathList; //!< The vector of path objects in the cell.
    std::vector<CellReference> cellReferenceList; //!< The vector of CellReference objects that this cell contains.
    std::vector<CellArray> cellArrayList; //!< The vector of CellArray objects that this cell contains.
    timeData timeCreated; //!< The struct containing a year, month, ... second.

  public:

    /// \brief Creates a Cell object with the specified cellname.
    Cell(std::string usrCellname);
    
    /// \brief Sets the cell name to be that of what the user specifies.
    ///
    /// @usrCellname The name of this cell.
    void setCellname(std::string usrCellname);

    /// \brief Returns the cell name for this object.
    std::string getCellname(void) const;

    /// \brief Returns a const reference to the Entity List
    std::vector<Polygon>& getPolygonList(void) const;

    /// \brief Returns a vector full of the info about when the cell was 
    /// created
    ///
    /// The elements of the returned vector are members of a struct
    /// of type timeData with fields as follows:
    /// Year
    /// Month
    /// Day
    /// Hour
    /// Minute
    /// Second
    timeData getTimeData(void) const;

    /// \brief Adds a polygon to the Cell.
    ///
    /// @usrPolygon The polygon to add to the Cell.
    void addPolygon(Polygon usrPolygon);

    /// \brief Adds a path to the Cell.
    ///
    /// @usrPath The path to add to the Cell.    
    void addPath(Path usrPath);

    /// \brief Returns the vector of Path objects in this Cell;
    std::vector<Path>& getPathList(void) const;

    /// \brief Adds a cell reference to the vector of cellReferences;
    ///
    /// @usrCellReference The CellReference object to add to this Cell.
    void addCellReference(CellReference usrCellReference);

    /// \brief Adds a cell reference array to the vector of cellArrays.
    ///
    /// @usrCellArray The CellArray object to add to this Cell.
    void addCellArray(CellArray usrCellArray);

    /// \brief Returns the vector of CellReferences contained in this Cell.
    std::vector<CellReference>& getCellReferenceList(void) const;

    /// \brief Returns the vector of CellArrays contained in this Cell.
    std::vector<CellArray>& getCellArrayList(void) const;
  }; // class Cell
} // namespace sil

#endif // LAYER_HXX
