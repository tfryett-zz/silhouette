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

#include "../include/path.hxx"

namespace sil {

  Path::Path(std::vector<CoordPnt> usrCoordPath, double usrPathWidth, 
	     int usrPathType, int usrLayer, int usrDataType) {
    this->setCoordPath(usrCoordPath);
    this->pathWidth = usrPathWidth;
    this->setPathType(usrPathType); // check for validity and then set value
    this->setLayer(usrLayer);
    this->setDataType(usrDataType);
  }

  Path::Path(std::vector<CoordPnt> usrCoordPath, double usrPathWidth, 
	     int usrPathType, int usrLayer) :
    Path::Path(usrCoordPath, usrPathWidth, usrPathType, usrLayer, 0) {}

  Path::Path(std::vector<CoordPnt> usrCoordPath, double usrPathWidth, 
	     int usrPathType) :
    Path::Path(usrCoordPath, usrPathWidth, usrPathType, 0) {}

  Path::Path(std::vector<CoordPnt> usrCoordPath, double usrPathWidth) :
    Path::Path(usrCoordPath, usrPathWidth, 0) {}

  Path::Path(std::vector<CoordPnt> usrCoordPath) :
    Path::Path(usrCoordPath, 0) { 
  }

  void Path::setPathType(int newPathType) {
    if (newPathType >= 0 && newPathType <= 2)
      this->pathType = newPathType;
    else  {
      std::ostringstream warning;
      warning << "Only path types 0, 1, and 2 are defined. User " 
	      << "tried to use a path type of " << newPathType 
	      << "." << std::endl;
      throw std::invalid_argument(warning.str());
    }
  }

  int Path::getPathType(void) const {
    return this->pathType;
  }

  double Path::getPathWidth(void) const {
    return this->pathWidth;
  }

  void Path::setPathWidth(double newPathWidth) {
    this->pathWidth = newPathWidth;
  }

  std::vector<CoordPnt> Path::getCoordPath(void) const {
    return this->coordPath;
  }

  void Path::setCoordPath(std::vector<CoordPnt> newCoordPath) {
    if (newCoordPath.size() > 1 && newCoordPath.size() < 200) 
      this->coordPath = newCoordPath;
    else {
      std::stringstream errorMsg;
      errorMsg << "The number of coordinates in a Path must"
	       << " be in the range 2-199. User tried to set" 
	       << " a path with " << newCoordPath.size() << ".\n";
      throw std::invalid_argument(errorMsg.str());
    }
  }

  void Path::appendToCoordPath(CoordPnt nextCoordPnt) {
    if (this->coordPath.size() < 199) // can have up to 199 coordiantes
      this->coordPath.push_back(nextCoordPnt);
    else {
      std::stringstream errorMsg;
      errorMsg << "Path has its maximum number of coordinates already.\n";
      throw std::invalid_argument(errorMsg.str());
    }
  }

  void Path::setDataType(int newDataType) {
    if (newDataType >= 0 && newDataType < 64)
      this->dataType = newDataType;
    else {
      std::stringstream errorMsg;
      errorMsg << "Invalid data type. Data types must be "
	       << "in the range 0-63, but user specified "
	       << "data type of " << newDataType << ".\n";
      throw std::invalid_argument(errorMsg.str());
    }
  }

  int Path::getDataType(void) const {
    return this->dataType;
  }

  void Path::setLayer(int newLayer) {
    if (newLayer >= 0 && newLayer < 64)
      this->dataType = newLayer;
    else {
      std::stringstream errorMsg;
      errorMsg << "Invalid layer. Layers must be "
	       << "in the range 0-63, but user specified "
	       << "layer as " << newLayer << ".\n";
      throw std::invalid_argument(errorMsg.str());
    }
  }

  int Path::getLayer(void) const {
    return this->layer;
  }

}
