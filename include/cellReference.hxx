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

#ifndef CELL_REFERENCE_HXX
#define CELL_REFERENCE_HXX

#include "coord.hxx"
#include "polygon.hxx"
#include <vector>
#include <limits>
#include <stdexcept>

namespace foom {

class Cell;

class CellReference {
private:
  const Cell& refCell;
  std::vector<CoordPnt> findVertices(void);
  CoordPnt center;

protected:
  double magnification; //!< The amount the referenced cell will be magnified compared to the origianl.
  double rotation; //!< The ammount the reference cell will be rotated
  std::vector<CoordPnt> vertices;

public:
  CellReference(Cell& referenceCell);
  CellReference(Cell& referenceCell, CoordPnt centerPnt);
  CellReference(Cell& referenceCell, int centerX, int centerY);

  double getMagnification(void) const;

  void setMagneification(double newMagnification);

  double getRotation(void) const;

  void setRotation(double newRotation);

  CoordPnt getCenter(void) const;

  void setCenter(CoordPnt newCenter);

  std::string getCellname(void) const;

};

}

#endif // CELL_REFERENCE_HXX
