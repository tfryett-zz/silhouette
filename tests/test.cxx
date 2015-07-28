#include "../include/silhouette.hxx"
#include "../include/float64.hxx"
#include <iostream>
#include <bitset>

int main() {

  foom::Layout FullStructure;
  foom::Cell cell = foom::Cell("MyCell");
  foom::Circle mycirc = foom::Circle(foom::CoordPnt(0,0), 3);
  cell.addPolygon(mycirc);
  FullStructure.addCell(cell);
  FullStructure.write("testing.gds");

  foom::utils::float64 mystuff;
  mystuff = -2.0;
  std::cout << mystuff.getGDSIIrepresentation() << std::endl;

  std::bitset<8> myset;
  myset[0] = 1;
  std::cout << myset << std::endl;

  return 0;
}
