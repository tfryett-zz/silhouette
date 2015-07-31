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

#ifndef LAYOUT_HXX
#define LAYOUT_HXX

#include <vector>
#include <string>
#include <functional>
#include "cell.hxx"

namespace sil {

  /// class Layout
  ///
  /// This class is the overall container for sil. That is if you
  /// wish to import from or write to a GDSII file you must do so
  /// through this class. Think of this class as a library of Cell
  /// objects which constitute the fabriaction flow you are wishing
  /// to create.
  class Layout {
  private:

    std::vector<Cell*> cellVec; //!< \brief The collection of Cell pointers which constitute a Layout.

  protected:

  public:
    /// \brief The default constructor for this class.
    Layout(void);

    /// \brief The method used to add a Cell object to this Layout.
    ///
    /// @usrCell The Cell object you wish to add to this Layout.
    ///
    /// Cells that are added to a Layout can be considered to be a
    /// component of a larger fabrication flow. An example would be
    /// the design for a transistor that is to be repeatedly used.
    /// Having it be defined as a Cell would allow for a CellReference
    /// to take the place of each transitor. This not only saves
    /// space but also acts to counter mistakes in trying to define
    /// many copies of the same thing.
    void addCell(Cell& usrCell);

    /// \brief Writes all of the contained Cell objects to a file.
    ///
    /// @filename The name of the file to write to.
    void write(std::string filename);

    /// \brief Returns all of the Cell objects that are contained.
    std::vector<Cell*> getCells(void) const;

  };
}

#endif // LAYOUT_HXX
