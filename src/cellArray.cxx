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

#include "../include/cellArray.hxx"
#include "../include/cell.hxx"

namespace foom {

  CellArray::CellArray(Cell& cell, CoordPnt usrStartingPos, 
		       int usrNumCol, int usrNumRow, double usrXSpacing, 
		       double usrYSpacing) : refCell(cell) {
    this->startingPos = usrStartingPos;
    this->setNumCol(usrNumCol);
    this->setNumRow(usrNumRow);
    this->xSpacing = usrXSpacing;
    this->ySpacing = usrYSpacing;
  }

  void CellArray::setStartingPos(CoordPnt newStartingPos) {
    this->startingPos = newStartingPos;
  }

  CoordPnt CellArray::getStartingPos() const {
    return this->startingPos;
  }

  void CellArray::setXSpacing(double newXSpacing) {
    this->xSpacing = newXSpacing;
  }
    
  double CellArray::getXSpacing(void) const {
    return this->xSpacing;
  }

  void CellArray::setYSpacing(double newYSpacing) {
    this->ySpacing = newYSpacing;
  }
    
  double CellArray::getYSpacing(void) const {
    return this->ySpacing;
  }

  void CellArray::setNumCol(int newNumCol) {
    // the magic number 32,767 is from the GDSII standard. No reason
    // was given, but we will adhere to the rule.
    if (newNumCol > 0 && newNumCol <= 32767)
      this->numCol = newNumCol;
    else {
      std::stringstream errorMsg;
      errorMsg << "The number of columns may not exceed 32,767, and"
	       << " must be nonzero. User entered " << newNumCol 
	       << ".\n";
      std::invalid_argument(errorMsg.str());
    }
  }

  int CellArray::getNumCol() const {
    return this->numCol;
  }

  void CellArray::setNumRow(int newNumRow) {
    // the magic number 32,767 is from the GDSII standard. No reason
    // was given, but we will adhere to the rule.
    if (newNumRow > 0 && newNumRow <= 32767)
      this->numRow = newNumRow;
    else {
      std::stringstream errorMsg;
      errorMsg << "The number of rows may not exceed 32,767, and"
	       << " must be nonzero. User entered " << newNumRow 
	       << ".\n";
      std::invalid_argument(errorMsg.str());
    }  
  }

  int CellArray::getNumRow() const {
    return this->numRow;
  }

  double CellArray::getRotation() const {
    return this->rotation;
  }
    
  void CellArray::setRotation(double newRotation) {
    this->rotation = newRotation;
  }

  double CellArray::getMagnification() const {
    return this->magnification;
  }

  void CellArray::setMagnification(double newMagnification) {
    if (newMagnification > 0)
      this->numRow = newMagnification;
    else {
      std::stringstream errorMsg;
      errorMsg << "The number of rows may not exceed 32,767, and"
	       << " must be nonzero. User entered " << newMagnification 
	       << ".\n";
      std::invalid_argument(errorMsg.str());
    }  
  }

  std::string CellArray::getCellname() const {
    return this->refCell.getCellname();
  }

}
