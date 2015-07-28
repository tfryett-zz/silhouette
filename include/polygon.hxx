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

#ifndef POLYGON_HXX
#define POLYGON_HXX

#include <vector>
#include <cmath> // for trig functions
#include <sstream>
#include <stdexcept>
#include "coord.hxx"
#include "line.hxx"

namespace foom {

  class Polygon {
  private:

  protected:
    CoordPnt center; //!< Coordinate of the center of the polyon.
    int Layer; //!< The layer that the polygon belongs to. Usually corresponds to a fabrication step.
    int DataType; //!< Another number that details information, such as metal to be used.
    std::vector<CoordPnt> boundingBox; //!< The bounding box of the structure. Good for collision detection.
    
    //!< a vector of verticies that can be used to define the nature of varius
    // objects
    std::vector<CoordPnt> vertices;

    /// \brief Recalculates and relocates the center of the Polygon object.
    void findResetCenter(void);

    /// \brief Calcultes and returns the area of the polygon.
    double getArea(void) const;

    /// \brief Checks the vertices for their validity and conformity
    /// to the GDSII standards for BOUNDARY records, and then sets
    /// the polygons vertices to be usrVertices if all checks out.
    void setVertices(std::vector<CoordPnt> usrVertices);

    /// \brief Determines the bounding box from the "vertices" field.
    ///
    /// This method itterates over the "vertices" field to find the maximum and
    /// minimum displacements in the x and y directions. The resulting bounding
    /// box will have its sides parallel to the x and y axis.
    std::vector<CoordPnt> findBoundingBox(void) const;

    /// \brief Determines if the set of vertices passed in define a 
    ///        Polygon that contains an internal void.
    ///
    /// @usrVertices The vector of vertices that defines a polygon.
    ///
    /// As per the GDSII standard we must avoid any polygon (i.e 
    /// BOUNDARY record) that contains internal voids (same condition
    /// as having edges that cross one another. If such a condition
    /// exists this method returns true, otherwise it returns false.
    bool containsInternalVoid(std::vector<CoordPnt> usrVertices);

    /// \brief Thd default constructor for the Polygon class.
    ///
    /// Class is made protected so that child classes may inherit it 
    /// but it is not directly callable since it doess not make any
    /// shapes.
    Polygon(void);

  public:

    /// \brief The full constructor for the polygon class.
    ///
    /// @usrVertices The list of vertices that defines the polygon.
    /// @usrLayer The layer at which the polygon will reside.
    /// @usrDataType the data type of which the polygon will belong.
    Polygon(std::vector<CoordPnt> usrVertices, int usrLayer, 
	    int usrDataType);

    /// \brief The full constructor for the polygon class.
    ///
    /// @usrVertices The list of vertices that defines the polygon.
    /// @usrLayer The layer at which the polygon will reside.
    Polygon(std::vector<CoordPnt> usrVertices, int usrLayer);

    /// \brief Generates a polygon defined by the vector of vertices passed in
    /// as the argument.
    ///
    /// @usrVertices The list of vertices that defines the polygon.
    ///
    /// Constructs the polygon from the vector of points passed into the 
    /// constructor. The order of the points matters greatly as the polygon 
    /// will be constructed by the points in the exact order they are passed in.
    Polygon(std::vector<CoordPnt> usrVertices);

    /// \brief Allows the user to rotate any Polygon objects.
    ///
    /// @rotatePnt The CoordPnt object that defines the point about which the 
    /// Polygon object should be rotated.
    /// @rotationAngle The angle (in radians) to rotate the Polygon object by.
    void rotate(CoordPnt rotatePnt, double rotationAngle);

    /// \brief Returns the int corresponding the the layer it is located on.
    int getLayer(void) const;
    
    /// \brief Allows the user to set the layer to the specified int.
    void setLayer(int newLayer);

    /// \brief Returns the int corresponding the the datatype of the polygon.
    int getDataType(void) const;
    
    /// \brief Allows the user to set the datatype to the specified int.
    void setDataType(int newDataType);

    /// \brief Returns a reference to the coordinate point list that comprises
    /// a polygon.
    std::vector<CoordPnt> &getVertices(void) const;

    /// \brief Determines if the coordinate point passed in lies
    /// within the polygon.
    ///
    /// @pnt The coordinate point in question.
    ///
    /// Returns true only if @pnt is inside the polygon ("this").
    /// In this definition inside does not include the boundaries,
    /// therefore if @pnt lies on this's boundary this method will
    /// return false. To note this algorithm uses the "casting ray"
    /// approach.
    bool pointInsidePolygon(CoordPnt pnt);
    
  }; // class polygon

  /*
  Polygon operator+(Polygon& poly1, Polygon& poly2);

  Polygon operator-(Polygon& poly1, Polygon& poly2);
  */
}

#endif // POLYGON_HXX
