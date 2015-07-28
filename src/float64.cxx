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

#include "../include/float64.hxx"

namespace sil {
  namespace utils {

    float64::float64() {
      this->GDSII_representation.reset();
      this->IEEE_representation = 0;
    }

    float64::float64(double num) {

      this->IEEE_representation = num;

      int end = this->GDSII_representation.size() - 1; 

      if (num < 0) {
	this->GDSII_representation[end] = 1;
	num = -num;
      }

      int exponent = 0;
      double mantissa;
      if (num < 1e-77) // 16^{-64} smallest number possible
	this->GDSII_representation.reset(); // all to zero. Represents zero
      else {
	exponent = (int) log(num)/log(16.0);
	mantissa = num/pow(16.0, exponent);
	// may be off by one power of 16
	if (mantissa < 1.0/16.0) {
	  mantissa *= 16.0;
	  exponent++;
	} else if (mantissa >= 1.0) {
	  mantissa /= 16.0;
	  exponent--;
	}
	if (!(mantissa < 1 && mantissa >= 1.0/16.0)) {
	  std::stringstream errorMsg;
	  errorMsg << "Mantissa must be inbetween 1 and 1/16. "
		   << "It is " << mantissa << "\n";
	  throw std::logic_error(errorMsg.str());
	}
	if (!(exponent >= -64 && exponent < 63)) {
	  std::stringstream errorMsg;
	  errorMsg << "Exponent must be equal to or greater than "
		   << " 64, and less than 64. It is " << exponent
		   << "\n";
	  throw std::logic_error(errorMsg.str());
	}
	  
      }

      // we need to have an exponential offset
      exponent += 64;

      int numOfExponentBits = 7;
      for (int i = 1; i <= numOfExponentBits; i++) {
	if (exponent >= 128/pow(2, i)) {
	  this->GDSII_representation[end - i] = 1;
	  exponent -= 128/pow(2, i);
	}
      }

      int numOfMantissaBits = 7*8;
      int bitOffset = 7; // start at the eighth bit
      for (int i = 1; i <= numOfMantissaBits; i++) {
	if (mantissa >= 1.0/pow(2, i)) {
	  this->GDSII_representation[end - (i + bitOffset)] = 1;
	  mantissa -= 1.0/pow(2, i);
	}
      }


      
    } // float64(double num)

    std::vector<char> float64::toChar() {
      int numBytes = 8; // 64 bits is 8 bytes
      int numBitsInByte = 8;
      int end = this->GDSII_representation.size() - 1;
      std::vector<char> ans;
      ans.reserve(numBytes);
      for (int i = 0; i < numBytes; i++) {
	std::bitset<8> byte;
	for (int j = 0; j < numBitsInByte; j++) {
	  byte[j] = this->GDSII_representation[end -
					       (j + i*numBitsInByte)];
	}
	ans[i] = (char) byte.to_ulong();
      }
      return ans;
    }
    
    float64 float64::operator=(double& input) {
      return float64(input);
    }

    std::bitset<64> float64::getGDSIIrepresentation(void) const {
      return this->GDSII_representation;
    }

    double float64::getIEErepresentation(void) const {
      return this->IEEE_representation;
    }

  } // namespace utils
} // namespace sil
