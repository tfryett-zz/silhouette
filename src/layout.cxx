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

#include "../include/layout.hxx"
// keep the gdsfile header here so that it is not automatically 
// included when one includes "sil.hxx". This will add a barrier for
// users against creating and handling GDS_File classes themselves,
// which they should not do.
#include "../include/gdsfile.hxx" 

namespace sil {

  Layout::Layout() {}

  void Layout::addCell(Cell& usrCell) {
    this->cellVec.push_back(&usrCell);
  }

  std::vector<Cell*> Layout::getCells() const {
    return this->cellVec;
  }

  void Layout::write(std::string usrFilename) {
    sil::utils::GDS_File myFile(usrFilename);
    myFile.Write(this->cellVec);
  }

} // namespace sil

// Add the python extensions
void export_Layout() {
  boost::python::class_<sil::Layout>("Layout")
    .def("addCell", &sil::Layout::addCell)
    .def("getCells", &sil::Layout::getCells)
    .def("write", &sil::Layout::write)
    ;
}
