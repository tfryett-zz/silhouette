#include "../include/silhouette.hxx"
#include "../include/float64.hxx"
#include <iostream>
#include <bitset>

int main() {

  sil::Layout FullStructure;
  sil::Cell cell = sil::Cell("MyCell");
  sil::Circle mycirc = sil::Circle(sil::CoordPnt(0,0), 3);
  cell.addPolygon(mycirc);
  FullStructure.addCell(cell);
  FullStructure.write("testing.gds");

  sil::utils::float64 mystuff;
  mystuff = -2.0;
  std::cout << mystuff.getGDSIIrepresentation() << std::endl;

  std::bitset<8> myset;
  myset[0] = 1;
  std::cout << myset << std::endl;

  return 0;
}
