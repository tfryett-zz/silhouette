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

#include "../include/cell.hxx"
#include "../include/gdsfile.hxx" // must keep

namespace sil {

  // The full blooded Cell object constructor.
  Cell::Cell(std::string usrCellname) {
    this->setCellname(usrCellname);
    time_t now = time(0);
    tm *ltm = localtime(&now);
    this->timeCreated.year = 1900 + ltm->tm_year;
    this->timeCreated.month =  1 + ltm->tm_mon;
    this->timeCreated.day =  ltm->tm_mday;
    this->timeCreated.hour =  1 + ltm->tm_hour;
    this->timeCreated.minute = 1 + ltm->tm_min;
    this->timeCreated.second = 1 + ltm->tm_sec;
  }

  // Allows the user to reset this cell's name
  void Cell::setCellname(std::string usrCellname) {
    if (usrCellname.size() > 32)
      throw std::invalid_argument("Cell name must be under 32 characters.");
    if (usrCellname.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_?$") !=
	std::string::npos)
      throw std::invalid_argument("Cell name contains invalid characters.");
    this->cellname = usrCellname;
  }

  // Simple member function that returns the specified cell's name
  std::string Cell::getCellname() const {
    return this->cellname;
  }

  std::vector<Polygon>& Cell::getPolygonList() const {
    return const_cast<std::vector<sil::Polygon> &> (this->polyList);
  }
  
  // Returns the data about when this cell was created 
  timeData Cell::getTimeData() const {   
    return this->timeCreated;
  }

  void Cell::addPolygon(sil::Polygon usrPolygon) {
    this->polyList.push_back(usrPolygon);
  }

  void Cell::addPath(Path usrPath) {
    this->pathList.push_back(usrPath);
  }

  void Cell::addCellReference(CellReference usrCellReference) {
    this->cellReferenceList.push_back(usrCellReference);
  }

  std::vector<Path>& Cell::getPathList() const {
    return const_cast<std::vector<sil::Path> &> (this->pathList);
  }

  std::vector<CellReference>& Cell::getCellReferenceList() const {
    return const_cast<std::vector<sil::CellReference> &> (this->cellReferenceList);
  }

  std::vector<CellArray>& Cell::getCellArrayList(void) const {
    return const_cast<std::vector<sil::CellArray> &> (this->cellArrayList);
  }

}


