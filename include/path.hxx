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

#ifndef PATH_HXX
#define PATH_HXX

#include "coord.hxx"
#include <vector>
#include <stdexcept>
#include <sstream>

namespace sil {

  class Path {
  private:
    std::vector<CoordPnt> coordPath; //!< The points through which the path traverses.
    double pathWidth; //!< The width of the path.
    int pathType; //!< Determines the shape of end points. Can be 0, 1, or 2.
    int layer;
    int dataType;

  protected:
    
  public:
    //! Full constructor for the path class.
    Path(std::vector<CoordPnt> usrCoordPath, double usrPathWidth, 
	 int usrPathType, int usrLayer, int usrDataType);

    Path(std::vector<CoordPnt> usrCoordPath, double usrPathWidth, 
	 int usrPathType, int usrLayer);

    Path(std::vector<CoordPnt> usrCoordPath, double usrPathWidth, 
	 int usrPathType);

    Path(std::vector<CoordPnt> usrCoordPath, double usrPathWidth);

    Path(std::vector<CoordPnt> usrCoordPath);

    int getPathType(void) const;

    void setPathType(int newPathType);

    double getPathWidth(void) const;

    void setPathWidth(double newPathWidth);

    std::vector<CoordPnt> getCoordPath(void) const;

    void setCoordPath(std::vector<CoordPnt> newCoordPath);

    void appendToCoordPath(CoordPnt nextCoordPnt);

    void setDataType(int newDataType);

    int getDataType(void) const;

    void setLayer(int newLayer);

    int getLayer(void) const;

  };

}

#endif // PATH_HXX
