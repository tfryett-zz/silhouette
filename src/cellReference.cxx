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

#include "../include/cellReference.hxx"
#include "../include/cell.hxx"

namespace sil {

  CellReference::CellReference(Cell& referenceCell, int centerX, 
			       int centerY) : refCell(referenceCell) {
    this->center = CoordPnt(centerX, centerY);
    this->magnification = 1.0;
    this->rotation = 0.0;
  }

  CellReference::CellReference(Cell& referenceCell) :
    refCell(referenceCell) {
    this->center = CoordPnt(0, 0);
    this->magnification = 1.0;
    this->rotation = 0.0;
  }

  CellReference::CellReference(Cell& referenceCell, CoordPnt centerPnt) :
    refCell(referenceCell) {
    this->center = centerPnt;
    this->magnification = 1.0;
    this->rotation = 0.0;
  }


  std::vector<CoordPnt> CellReference::findVertices(void) {
    std::vector<CoordPnt> boundingVertex;
    std::vector<Polygon> polygonVec = this->refCell.getPolygonList();
    double totMax = std::numeric_limits<double>::max();
    double totMin = std::numeric_limits<double>::min();
    double minX = totMax;
    double minY = totMax;
    double maxX = totMin;
    double maxY = totMin;
    // find the minimum and maximum values of x and y coordinates
    for(std::vector<Polygon>::iterator polyIt = polygonVec.begin(); 
	polyIt != polygonVec.end(); ++polyIt) {
      std::vector<CoordPnt> vertexVec = polyIt->getVertices();
      for (std::vector<CoordPnt>::iterator vertIt = vertexVec.begin();
	   vertIt != vertexVec.end(); ++vertIt) {
	if (vertIt->getX() > maxX)
	  maxX = vertIt->getX();
	if (vertIt->getX() < minX)
	  minX = vertIt->getX();
	if (vertIt->getY() > maxY)
	  maxY = vertIt->getY();
	if (vertIt->getY() < minY)
	  minY = vertIt->getY();
      }
    }
    // check to make sure they actually changed into something
    if (minX == totMax && minY == totMax && 
	maxX == totMin && maxY == totMin)
      throw std::logic_error("Invalid polygons detected.");
    else if ((minX == maxX) && (minY == maxY))
      throw std::logic_error("Invalid polygons detected.");

    boundingVertex.push_back(CoordPnt(minX, minY));
    boundingVertex.push_back(CoordPnt(minX, maxY));
    boundingVertex.push_back(CoordPnt(maxX, minY));
    boundingVertex.push_back(CoordPnt(maxX, maxY));
    return boundingVertex;
  }

  double CellReference::getMagnification(void) const {
    return this->magnification;
  }

  void CellReference::setMagneification(double newMagnification) {
    this->magnification = newMagnification;
  }

  double CellReference::getRotation(void) const {
    return this->rotation;
  }

  void CellReference::setRotation(double newRotation) {
    this->rotation = newRotation;
  }

  CoordPnt CellReference::getCenter(void) const {
    return this->center;
  }

  void CellReference::setCenter(CoordPnt newCenter) {
    this->center = newCenter;
  }

  std::string CellReference::getCellname() const {
    return this->refCell.getCellname();
  }
}
