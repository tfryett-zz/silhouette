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

#include "polygon.hxx"

namespace sil {

  Polygon::Polygon(std::vector<CoordPnt> usrVertices, int usrLayer, 
		   int usrDataType) {
    this->setVertices(usrVertices);
    this->setLayer(usrLayer);
    this->setDataType(usrDataType);
  }

  Polygon::Polygon(std::vector<CoordPnt> usrVertices, int usrLayer) :
    Polygon(usrVertices, usrLayer, 0) {}

  Polygon::Polygon(std::vector<CoordPnt> usrVertices) :
    Polygon(usrVertices, 1) {}

  Polygon::Polygon() {
    this->setLayer(1);
    this->setDataType(0);
  }

  std::vector<CoordPnt> Polygon::findBoundingBox() const {
    // Initialize the variables to store the maximum and minimum values of 
    // x and y that we find
    int maxY = vertices[0].getY();
    int minY = vertices[0].getY();
    int maxX = vertices[0].getX();
    int minX = vertices[0].getX();
    // Test to find out what the minimum and maximum extent of the x and y
    // are and store them in the corresponding variables
    for (std::vector<CoordPnt>::const_iterator it = vertices.begin(); 
         it != vertices.end(); ++it) {
      if (maxY < it->getY())
        maxY = it->getY();
      else if (minY > it->getY())
        minY = it->getY();
      if (maxX < it->getX())
        maxX = it->getX();
      else if (minX > it->getX())
        minX = it->getX();
    }
    // create the std::vector to store the appropriate points in
    std::vector<CoordPnt> newBoundingBox;
    newBoundingBox.push_back(CoordPnt(minX, maxY)); // upper left corner
    newBoundingBox.push_back(CoordPnt(maxX, maxY)); // upper right corner
    newBoundingBox.push_back(CoordPnt(maxX, minY)); // lower right corner
    newBoundingBox.push_back(CoordPnt(minX, minY)); // lower left corner
    // return completed bounding box
    return newBoundingBox;
  }

  // Rotates the Polygon objects about rotatePnt by rotationAngle radians.
  void Polygon::rotate(CoordPnt rotatePnt, double rotationAngle) {
    // Create the rotation matrix
    double rotationMatrix[2][2];
    rotationMatrix[0][0] = std::cos(rotationAngle);
    rotationMatrix[0][1] = -1.*std::sin(rotationAngle);
    rotationMatrix[1][0] = std::sin(rotationAngle);
    rotationMatrix[1][1] = std::cos(rotationAngle);
    // create a position vector (column) for rotatePnt
    double rotateVec[2];
    rotateVec[0] = rotatePnt.getX();
    rotateVec[1] = rotatePnt.getY();
    // create a position column vector for the vertices
    double vertexVec[2];
    // Now rotate each vertex point about the rotatePnt
    for (std::vector<CoordPnt>::iterator it = vertices.begin();
         it != vertices.end(); ++it) {
      // set up the position vector for this vertex
      vertexVec[0] = it->getX();
      vertexVec[1] = it->getY();
      // make the rotation point the origin
      vertexVec[0] -= rotateVec[0];
      vertexVec[1] -= rotateVec[1];
      // rotate the vertex
      vertexVec[0] = rotationMatrix[0][0]*vertexVec[0] + 
	rotationMatrix[0][1]*vertexVec[1];
      vertexVec[1] = rotationMatrix[1][0]*vertexVec[0] + 
	rotationMatrix[1][1]*vertexVec[1];
      // now shift the matrix back
      vertexVec[0] += rotateVec[0];
      vertexVec[1] += rotateVec[1];
      // now reassign the vertices to their new locations
      it->setX(vertexVec[0]);
      it->setY(vertexVec[1]);
    }
    // update the center field
    this->findResetCenter();
  }
   
  // Resets the center field
  void Polygon::findResetCenter() {
    int numVertices = 0;
    double xSum = 0.;
    double ySum = 0.;
    for (std::vector<CoordPnt>::iterator it = vertices.begin(); 
         it != vertices.end(); ++it) {
      xSum += it->getX();
      ySum += it->getY();
      numVertices++;
    }
    // Reset the center field to be the average values from the vertices
    this->center = CoordPnt(xSum/numVertices, ySum/numVertices);
  }

  int Polygon::getLayer() const {
    return this->Layer;
  }

  void Polygon::setLayer(int newLayer) {
    if (newLayer >= 0 && newLayer < 64)
      this->Layer = newLayer;
    else {
      std::stringstream errorMsg;
      errorMsg << "The layer assigned out of range. User attempted to"
	       << " assign a value of " << newLayer << ", but " 
	       << "layers must be equal to or between 0 and 63.\n";
      std::invalid_argument(errorMsg.str());
    }
  }

  int Polygon::getDataType() const {
    return this->DataType;
  }

  void Polygon::setDataType(int newDataType) {
    if (newDataType >= 0 && newDataType < 64)
      this->Layer = newDataType;
    else {
      std::stringstream errorMsg;
      errorMsg << "The data type assigned out of range. User attempted"
	       << " to assign a value of " << newDataType << ", but"
	       << " data types must be equal to or between 0 and 63.\n";
      std::invalid_argument(errorMsg.str());
    }
  }

  std::vector<CoordPnt> &Polygon::getVertices() const {
    return const_cast<std::vector<sil::CoordPnt> &> (this->vertices);
  }

  bool Polygon::containsInternalVoid(std::vector<CoordPnt> usrVertices) {
    // test to make sure what was passed in couuld actually be a polygon
    // if we don't the next test will always throw an error and it will
    // be harder to determine what went wrong than if we catch it here
    // like this.
    if (usrVertices.size() < 3) {
      std::stringstream errorMsg;
      errorMsg << "The number of vertices must be equal to or larger"
	       << " than three. User passed in a vector of "
	       << usrVertices.size() << ".\n";
      throw std::invalid_argument(errorMsg.str());
    }

    // even a single intersection implies an internal void. neither
    // are allowed by gdsII standards so quit at the first one found.
    uint upperLimit = usrVertices.size();
    for (uint i = 0; i <= upperLimit; i++) {
      LineSeg lin1(usrVertices[i], usrVertices[i + 1]);
      for (uint j = i + 2; j <= upperLimit; i++) {
	LineSeg lin2(usrVertices[j], usrVertices[j + 1]);
	if (lineSegIntersect(lin1, lin2))
	  return true;
      }
    }

    return false;
  }

  void Polygon::setVertices(std::vector<CoordPnt> usrVertices) {
    if (usrVertices.size() < 3 || usrVertices.size() > 199) {
      std::stringstream errorMsg;
      errorMsg << "Each polygon may only have 3-199 vertices. User"
	       << " tried to initiate a polygon with " 
	       << usrVertices.size() << " vertices.\n";
      throw std::invalid_argument(errorMsg.str());
    }

    if (!this->containsInternalVoid(usrVertices))
      this->vertices = usrVertices;
    // update the bounding box
    this->boundingBox = this->findBoundingBox();
  }

  bool Polygon::pointInsidePolygon(CoordPnt pnt) {
    // for the ray casting techneique we need to use a point that is
    // garunteed to be outside of the polygon (we want to reuse the
    // algorithm for determining the intersection of two line segments)
    // Use the point that has the same y coordinate as @pnt but has
    // an x coordinate that is one unit towards +inf than the largest
    // x coordinate in the vertex list.
    uint numVertices = this->boundingBox.size();
    int maxXCoord = std::abs(this->boundingBox[0].getX());
    int maxYCoord = std::abs(this->boundingBox[0].getY());
    for (uint i = 1; i < numVertices; i++) {
      if (std::abs(this->boundingBox[i].getX()) > maxXCoord) 
	maxXCoord = std::abs(this->boundingBox[i].getX());
      if (std::abs(this->boundingBox[i].getY()) > maxYCoord)
	maxYCoord = std::abs(this->boundingBox[i].getY());
    }
    CoordPnt rayCastCoord = CoordPnt(maxXCoord*1.1, pnt.getY());
    LineSeg rayCast = LineSeg(pnt, rayCastCoord);

    // now detect if the ray (rayCast) intersects any of the sides of
    // the polygon. If rayCast intersects an odd number of sides then
    // @pnt is inside the polygon, otherwise it is outside.
    numVertices = this->vertices.size();
    int intersectionCount = 0;
    for (uint i = 0; i < numVertices - 1; i++) {
      LineSeg polySide = LineSeg(this->vertices[i], this->vertices[i + 1]);
      if (lineSegIntersect(rayCast, polySide)) // linesegintersect in line.cxx & line.hxx
	intersectionCount++;
      // If it hits a vertex determining what happes can be tricky, so
      // let us just first solve for a ray that does not intersect with
      // any vertices and then solve. This is more computationally
      // heavy so save it for if the first attempt did not work.
      if (pointOnLineSeg(rayCast, this->vertices[i])) { // from line.cxx line.hxx
	// first cast a ray from @pnt to each of the vertices and then
	// determine the place where the maximum angular separation is
	// so we can aim for half way inbetween those vertices which
	// will give us the best chance of success.
	double rayCast1Angle = LineSeg(pnt, this->vertices[0]).angleOffset();
	double rayCast2Angle = LineSeg(pnt, this->vertices[1]).angleOffset();
	double maxAngularSep = std::abs(rayCast2Angle - rayCast1Angle);
	double bestAngle = (rayCast2Angle + rayCast1Angle)/2.0;
	for (uint j = 1; j < numVertices - 1; j++) {
	  rayCast1Angle = LineSeg(pnt, this->vertices[j]).angleOffset();
	  rayCast2Angle = LineSeg(pnt, this->vertices[j + 1]).angleOffset();
	  double curAngleSep = std::abs(rayCast2Angle - rayCast1Angle);
	  if (curAngleSep > maxAngularSep)
	    bestAngle = (rayCast1Angle + rayCast2Angle)/2.0;
	}

	double boundingCircRadius = std::sqrt(pow(maxXCoord, 2) +
					      pow(maxYCoord, 2));
	CoordPnt rayPnt = CoordPnt(boundingCircRadius*std::cos(bestAngle),
			  boundingCircRadius*std::sin(bestAngle));
	rayCast = LineSeg(pnt, rayPnt);

	// retry the same algorithm with the new rayCast line
	intersectionCount = 0; // restart the count
	for (uint j = 0; j < numVertices - 1; j++) {
	  LineSeg polySide = LineSeg(this->vertices[j], this->vertices[j + 1]);
	  if (lineSegIntersect(rayCast, polySide)) // linesegintersect in line.cxx & line.hxx
	    intersectionCount++;
	}
	break; // get out of the loop since we have our answer now.
      }
    }

    return (intersectionCount % 2 == 1);
  }

  /*
  // Uses the Weiler-Atherton Algorithm
  Polygon operator-(Polygon& poly1, Polygon& poly2) {

    // We will use this struct to keep track of the intersection
    // points. It is important to mark the points as either leaving
    // or entering the clipping region (@poly2). We will use this
    // bool value to mark when to add points from @poly1 or @poly2
    // to the clipped polygon we will return. To that end we will 
    // keep track of the indices of the points that come right before
    // the intersection for both polygons to speed the algorithm up.
    struct intersectPnt {
      Polygon Pnt;
      bool enteringPoly2;
      int poly1FirstIndex;
      int poly2FirstIndex;
    };
    
    // where we will store all of the points that are the
    // intersection between sides of the two different polygons
    std::vector<intersectPnt> intersectionPoints;

    int numVerticesPoly1 = poly1.getVertices().size();
    int numVerticesPoly2 = poly2.getVertices().size();
    for (int p1VertexNum = 0; p1VertexNum < numVerticesPoly1; p1VertexNum++) {
      int secondVertexNumPoly1; // use to make sure we wrap around
      if (p1VertexNum == numVerticesPoly1 - 1)
	secondVertexNumPoly1 = 0;
      else
	secondVertexNumPoly1 = p1VertexNum + 1;
      LineSeg p1Lin = LineSeg(poly1.getVertices()[p1VertexNum],
			      poly1.getVertices()[secondVertexNumPoly1]);
      for (int p2VertexNum = 0; p2VertexNum < numVerticesPoly2; p2VertexNum++) {
	int secondVertexNumPoly2;
	if (p2VertexNum == numVerticesPoly2 - 1)
	  secondVertexNumPoly2 = 0;
	else
	  secondVertexNumPoly2 = p1VertexNum + 1;
	LineSeg p2Lin = LineSeg(poly1.getVertices()[p1VertexNum],
				poly1.getVertices()[secondVertexNumPoly2]);

	// test if p2Lin and p1Lin intersect
	if (lineSegIntersect(p1Lin, p2Lin)) {
	  // take advantage of the fact that the function
	  // lineSegIntersect does not allow both LineSegs to have
	  // the same slope
	  double errorMargin = 1e-6;
	  // i.e. p1Lin has slope of infinity. We know p2Lin must
	  // have a defined slope
	  if (std::abs(p1Lin.getStartPnt().getX() -
		       p1Lin.getEndPnt().getX()) < errorMargin) {
	    
	  }
	}
	
      } // ends loop over polygon 2 vertices
    } // ends loop over polygon 1 vertices

  }
  */

  

} // end namespace sil
