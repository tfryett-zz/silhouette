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

#ifndef FLOAT64_HXX
#define FLOAT64_HXX

#include <bitset>
#include <vector>
#include <cmath>
#include <sstream>
#include <stdexcept>

namespace sil {
  namespace utils {

    class float64 {
    private:
      std::bitset<64> GDSII_representation;

      double IEEE_representation;

    protected:

    public:
      float64(void);

      float64(double inputNum);

      std::vector<char> toChar(void);

      float64 operator=(double& input);

      std::bitset<64> getGDSIIrepresentation(void) const;

      double getIEErepresentation(void) const;
    };
    
  }
}


#endif // FLOAT64_HXX
