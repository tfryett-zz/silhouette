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

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <stdint.h>
#include <unordered_map>
#include <string.h>

typedef double float64;

// switches the endianess of the input (num)
int16_t int16Swap(int16_t num);

// switches the endianess of the input (num)
int32_t int32Swap(int32_t num);

// switches the endianess of the input (num)
float64 float64Swap(float64 num);

int main() {
  const int16_t HEADER_SIZE = 2*sizeof(int16_t);

  // These are the record markers needed for reading and writing to 
  // gds2 files. The first byte specifies the "record" and the second 
  // specifies the typeof data contained in the record.
  // E.g. for HEADER: 0x00 specifies header that this is a header 
  // record and 0x02 specifies that the record contains unsigned two 
  // byte integer data.
  std::unordered_map<int16_t, std::string> headerMap;
  headerMap = {
    {0x0002, "HEADER"}, 
    {0x0102, "BGNLIB"},
    {0x0206, "LIBNAME"},
    {0x0305, "UNITS"},
    {0x0400, "ENDLIB"},
    {0x0502, "BGNSTR"},
    {0x0606, "STRNAME"},
    {0x0700, "ENDSTR"},
    {0x0800, "BOUNDARY"},
    {0x0900, "PATH"},
    {0x0A00, "SREF"},
    {0x0B00, "AREF"},
    {0x0C00, "TEXT"},
    {0x0D02, "LAYER"},
    {0x0E02, "DATATYPE"},
    {0x0F03, "WIDTH"},
    {0x1003, "XY"},
    {0x1100, "ENDEL"},
    {0x1206, "SNAME"},
    {0X1302, "COLROW"},
    {0x1500, "NODE"},
    {0x1602, "TEXTTYPE"},
    {0x1701, "PRESENTATION"},
    {0x1906, "STRING"},
    {0x1A01, "STRANS"},
    {0x1B05, "MAG"},
    {0x1C05, "ANGLE"},
    {0x1F06, "REFLIBS"},
    {0x2006, "FONTS"},
    {0x2102, "PATHTYPE"},
    {0x2202, "GENERATIONS"},
    {0x2306, "ATTRTABLE"},
    {0x2601, "ELFLAGS"},
    {0x2A02, "NODETYPE"},
    {0x2B02, "PROPATTR"},
    {0x2C06, "PROPVALUE"},
    {0x2D00, "BOX"},
    {0x2E02, "BOXTYPE"},
    {0x2F02, "PLEX"},
    {0x3203, "TAPENUM"},
    {0x3302, "TAPECODE"},
    {0x3602, "FORMAT"},
    {0x3706, "MASK"},
    {0x3800, "ENDMASKS"}
  };

  std::unordered_map<int16_t, std::string> noDataMap;  
  noDataMap = {
    {0x0400, "ENDLIB",},
    {0x0700, "ENDSTR"},
    {0x0800, "BOUNDARY"},
    {0x0900, "PATH"},
    {0x0A00, "SREF"},
    {0x0B00, "AREF"},
    {0x0C00, "TEXT"},
    {0x1100, "ENDEL"},
    {0x1500, "NODE"},
    {0x2D00, "BOX"},
    {0x3800, "ENDMASKS"}
  };

  std::unordered_map<int16_t, std::string> bitArrayDataMap;
  bitArrayDataMap = {
    {0x1701, "PRESENTATION"},
    {0x1A01, "STRANS"},
    {0x2601, "ELFLAGS"}
  };

  std::unordered_map<int16_t, std::string> twoByteSignedIntDataMap;
  twoByteSignedIntDataMap = {
    {0x0D02, "LAYER"},
    {0x0E02, "DATATYPE"},
    {0x0002, "HEADER"}, 
    {0x0102, "BGNLIB"},
    {0x0502, "BGNSTR"},
    {0X1302, "COLROW"},
    {0x1602, "TEXTTYPE"},
    {0x2102, "PATHTYPE"},
    {0x2202, "GENERATIONS"},
    {0x2A02, "NODETYPE"},
    {0x2B02, "PROPATTR"},
    {0x2E02, "BOXTYPE"},
    {0x2F02, "PLEX"},
    {0x3302, "TAPECODE"},
    {0x3602, "FORMAT"}
  };

  std::unordered_map<int16_t, std::string> fourByteSignedIntDataMap;
  fourByteSignedIntDataMap = {
    {0x0F03, "WIDTH"},
    {0x1003, "XY"},
    {0x3203, "TAPENUM"}
  };

  std::unordered_map<int16_t, std::string> eightByteRealDataMap;
  eightByteRealDataMap = {
    {0x0305, "UNITS"},
    {0x1B05, "MAG"},
    {0x1C05, "ANGLE"}
  };

  std::unordered_map<int16_t, std::string> asciiDataMap;
  asciiDataMap = {
    {0x0206, "LIBNAME"},
    {0x0606, "STRNAME"},
    {0x1206, "SNAME"},
    {0x1906, "STRING"},
    {0x1F06, "REFLIBS"},
    {0x2006, "FONTS"},
    {0x2306, "ATTRTABLE"},
    {0x2C06, "PROPVALUE"},
    {0x3706, "MASK"}
  };

  // Input stream
  // get user input as to what file to use
  std::cout << "Enter gdsII file name to be dumped: ";
  // usually bad practice but we want one and only one word input
  std::string filename; 
  std::cin >> filename;
  /// std::string filename = "example2.gds";
  // open the file for binary and read only
  std::ifstream gdsfile;
  gdsfile.open(filename.c_str(), std::ios::binary);

  // Output Stream
  std::cout << "Enter the output file (default is to the terminal): ";
  std::string outputFilename;
  std::cin >> outputFilename;
  // std::string outputFilename = "testing.txt";
  std::ofstream output;
  output.open(outputFilename);

  // check to make sure the file was actually opened and if not 
  // tell the user and then quit. If file was opened proceed with the
  // file checks
  if (gdsfile.is_open()){
    // first determine the file size
    std::streampos begin = gdsfile.tellg();
    gdsfile.seekg(0, std::ios::end);
    std::streampos end = gdsfile.tellg();
    int filesize = (int) (end - begin);
    // If the file is empty tell the user and quit with an error
    if (filesize == 0) {
      output << "The specified file is empty." << std::endl;
      return -1;
    }
    output << filename << std::endl;
    output << "File is: " << filesize << " bytes long." << std::endl;

    // reposition the "Get" pointer to the start of the file
    gdsfile.seekg(0, std::ios::beg);

    // The record label telling what it is. To be compared to the keys in
    // headerMap
    int16_t recordLabel; 
    int16_t recordSize = 0; // we will store each record's size in this
    int itterations = 0;
    while ((int) (end - gdsfile.tellg()) - HEADER_SIZE > 0) {
      itterations++;
      std::cout << "Made it through " << itterations <<
	" itterations. " << std::dec << (int) (end - gdsfile.tellg())
		<< " bytes left" << std::endl;
      gdsfile.read((char*) &recordSize, sizeof(int16_t));
      recordSize = int16Swap(recordSize);
      gdsfile.read((char*) &recordLabel, sizeof(int16_t));
      recordLabel = int16Swap(recordLabel);
      std::cout << "recordSize is: " << recordSize << std::endl;
      std::unordered_map<int16_t, std::string>::const_iterator sol =
	headerMap.find(recordLabel);      
      std::string headerName;
      if (sol == headerMap.end()) {
	std::cout << "Ran into a problem. Could not find header." << 
	  std::endl;

	std::cout << "Ended at: " << std::hex << recordLabel << std::endl;
	std::cout << std::dec << (int) (end - gdsfile.tellg()) << std::endl;
	std::cout << "The record size reported was" << std::dec 
		  << recordSize << std::endl;
	while ((int) ((end - gdsfile.tellg()) - sizeof(int16_t)) >= 0) {
	  int16_t data;
	  gdsfile.read((char*) &data, sizeof(data));	  
	  output << std::hex << data << " ";
	  recordSize -= sizeof(data);
	}
	return -1;
      } else
	headerName = sol->second;
      output << "/*--------------------------------------*/" << std::endl;
      output << "Record type: " << headerName << " (" << std::hex
	     << recordLabel << ")" << std::endl;
      output << "Record size " << std::dec << recordSize << " bytes" 
	     << std::endl;

      recordSize -= HEADER_SIZE;
      // enough file to account for this record
      if ((int) (end - gdsfile.tellg()) - recordSize > 0) {
	// find data type
	std::unordered_map<int16_t, std::string>::const_iterator nonData =
	  noDataMap.find(recordLabel);      
	std::unordered_map<int16_t, std::string>::const_iterator bitData =
	  bitArrayDataMap.find(recordLabel);      
	std::unordered_map<int16_t, std::string>::const_iterator twoByteData =
	  twoByteSignedIntDataMap.find(recordLabel);      
	std::unordered_map<int16_t, std::string>::const_iterator fourByteData =
	  fourByteSignedIntDataMap.find(recordLabel);      
	std::unordered_map<int16_t, std::string>::const_iterator eightByteData =
	  eightByteRealDataMap.find(recordLabel);      
	std::unordered_map<int16_t, std::string>::const_iterator asciiData =
	  asciiDataMap.find(recordLabel);      

	if (nonData != noDataMap.end()) {
	  output << "((No data present))" << std::endl;
	  continue; // no data for this record
	} else if (bitData != bitArrayDataMap.end()) {
	  while ((int) (recordSize - sizeof(int8_t)) >= 0) {
	    int8_t data;
	    gdsfile.read((char*) &data, sizeof(data));	  
	    output << data << " ";
	    recordSize -= sizeof(data);
	  }
	} else if (twoByteData != twoByteSignedIntDataMap.end()) {
	  while ((int) (recordSize - sizeof(int16_t)) >= 0) {
	    int16_t data;
	    gdsfile.read((char*) &data, sizeof(data));	  
	    data = int16Swap(data);
	    output << data << " ";
	    recordSize -= sizeof(data);
	  }
	} else if (fourByteData != fourByteSignedIntDataMap.end()) {
	  while ((int) (recordSize - sizeof(int32_t)) >= 0) {
	    int32_t data;
	    gdsfile.read((char*) &data, sizeof(data));	  
	    data = int32Swap(data);
	    output << data << " ";
	    recordSize -= sizeof(data);
	  }
	} else if (eightByteData != eightByteRealDataMap.end()) {
	  while ((int) (recordSize - sizeof(int64_t)) >= 0) {
	    float64 data;
	    gdsfile.read((char*) &data, sizeof(data));	  
	    data = float64Swap(data);
	    output << data << " ";
	    recordSize -= sizeof(data);
	  }
	} else if (asciiData != asciiDataMap.end()) {
	  while ((int) (recordSize - sizeof(char)) >= 0) {
	    char data;
	    gdsfile.read((char*) &data, sizeof(data));	  
	    output << data;
	    recordSize -= sizeof(data);
	  }
	} else {
	  std::cout << "Data type not recognized. Dumping the rest" << 
	    " of the data" << std::endl;
	  output << "Data type not recognized. Dumping the rest" << 
	    " of the data" << std::endl;
	}

	// make sure the next data is on
	output << std::endl;
      	
      } else { // not enough. Dump rest of file
	output << "The file ended before the record headers indicated." <<
		  " Dumping the rest of the file." <<std::endl;
      }
    }      
  } else {
    output << "Failed to open file." << std::endl;
    return -1;
  }

  gdsfile.close();
  return 0;
}


// switches the endianess of the input (num)
int16_t int16Swap(int16_t num) {
  unsigned char byte1, byte2;
  byte1 = num & 255;
  byte2 = (num >> 8) & 255;
  return (byte1 << 8) + byte2;
}

// switches the endianess of the input (num)
int32_t int32Swap(int32_t num) {
  unsigned char byte1, byte2, byte3, byte4;
  byte1 = num & 255;
  byte2 = (num >> 8) & 255;
  byte3 = (num >> 16) & 255;
  byte4 = (num >> 24) & 255;
  return ((int32_t) byte1 << 24) + ((int32_t) byte2 << 16) + 
    ((int32_t) byte3 << 8) + byte4;
}

// switches the endianess of the input (num)
float64 float64Swap(float64 num) {
  float64 ans;
  unsigned char* floatToConvert = (unsigned char*) &num;
  unsigned char* ansFloat = (unsigned char*) &ans;
  ansFloat[0] = floatToConvert[7];
  ansFloat[1] = floatToConvert[6];
  ansFloat[2] = floatToConvert[5];
  ansFloat[3] = floatToConvert[4];
  ansFloat[4] = floatToConvert[3];
  ansFloat[5] = floatToConvert[2];
  ansFloat[6] = floatToConvert[1];
  ansFloat[7] = floatToConvert[0];
  return ans;
}

