#include "../include/silhouette.hxx"
#include "../include/float64.hxx"
#include <iostream>
#include <bitset>
#include <stdexcept>

int main() {

  sil::Layout FullStructure;
  sil::Cell cell = sil::Cell("MyCell");
  sil::Circle mycirc = sil::Circle(sil::CoordPnt(0,0), 3);
  cell.addPolygon(mycirc);
  FullStructure.addCell(cell);
  FullStructure.write("testing.gds");

  return 0;
}


