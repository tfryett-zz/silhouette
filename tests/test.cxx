#include <math.h>
#include "../src/silhouette.hxx"

void writePerturbedL3(sil::Cell& cell, sil::CoordPnt centerCoord,
	     int numBragg, double period, double radius,
	     double dr, double dx, double perturbRadius);

const double PI = acos(-1);

int main() {

  sil::Layout FullStructure;

  // 1550 nm
  sil::Cell pCell1550 = sil::Cell("Perturbed920");

  int numBragg = 31;
  double midPeriod = 0.264;
  double midRadius = 0.065;
  double variationPerBlock = 0.01;
  double dx = 0.176;
  double dr = -0.107;
  int numColRow = 15;

  double L3toL3Spacing = numBragg*midPeriod + 25;
  for (int numCol = 0; numCol < numColRow; numCol++) {
    double curPeriod = midPeriod*(1 + variationPerBlock*(numCol - std::floor(numColRow/2) ));
    for (int numRow = 0; numRow < numColRow; numRow++) {
      double curRadius = midRadius*(1 + variationPerBlock*(numCol - std::floor(numColRow/2) ));
      double perturbedRadius = curRadius/4.;
      sil::CoordPnt L3Pos = sil::CoordPnt(L3toL3Spacing*numCol,
					  L3toL3Spacing*numRow);
      writePerturbedL3(pCell1550, L3Pos, numBragg, curPeriod, curRadius, dr, dx,
	      perturbedRadius);      

    }
  }

  FullStructure.addCell(pCell1550);

  FullStructure.write("testing.gds");

  return 0;
}



void writePerturbedL3(sil::Cell& cell, sil::CoordPnt centerCoord,
	     int numBragg, double period, double radius,
		      double dr, double dx, double perturbRadius) {

  // an L3 photonic crystal has symmetry about the x and y axis.
  // Use this to make the algorithm easier
  // skip the three missing holes. Start with the offset cavities
  double yPos = 0;
  double xPos = period*(2 + dx);
  sil::CoordPnt holeCenter = sil::CoordPnt(xPos, yPos) + centerCoord;
  sil::Circle hole = sil::Circle(holeCenter, radius*(1 + dr));
  cell.addPolygon(hole);
  // add symmetric point
  holeCenter = sil::CoordPnt(-xPos, yPos) + centerCoord;
  hole = sil::Circle(holeCenter, radius*(1 + dr));
  cell.addPolygon(hole);
  // add rest of the holes for this row
  for (int colNum = 3; colNum < (int) std::floor(numBragg/2); colNum++) {
    // still 0 y position
    xPos = colNum*period;
    holeCenter = sil::CoordPnt(xPos, yPos) + centerCoord;
    hole = sil::Circle(holeCenter, radius);
    cell.addPolygon(hole);

    xPos *= -1;
    holeCenter = sil::CoordPnt(xPos, yPos) + centerCoord;
    hole = sil::Circle(holeCenter, radius);
    cell.addPolygon(hole);
  }

  for (int rowNum = 1; rowNum < (int) std::floor(numBragg/2 - 1);
       rowNum++) {
    for (int colNum = 0; colNum < (int) std::floor(numBragg/2); colNum++) {
      double xShift;
      if (rowNum % 2 == 1)
	xShift = 0.5*period;
      else
	xShift = 0;

      bool addPerturb = (rowNum % 2 == 1 && rowNum < 5 &&
			 colNum % 2 == 1 && colNum < 5);

      yPos = rowNum*period*sin(PI/3.);
      xPos = xShift + colNum*period;
      holeCenter = sil::CoordPnt(xPos, yPos) + centerCoord;
      hole = sil::Circle(holeCenter, radius);
      cell.addPolygon(hole);
      if (addPerturb) {
	xPos -= radius; // perturbation is on left side
	holeCenter = sil::CoordPnt(xPos, yPos) + centerCoord;
	hole = sil::Circle(holeCenter, perturbRadius);
	cell.addPolygon(hole);
      }

      yPos = rowNum*period*sin(PI/3.);
      xPos = -(xShift + colNum*period);
      holeCenter = sil::CoordPnt(xPos, yPos) + centerCoord;
      hole = sil::Circle(holeCenter, radius);
      cell.addPolygon(hole);
      if (addPerturb) {
	xPos -= radius; // perturbation is on left side
	holeCenter = sil::CoordPnt(xPos, yPos) + centerCoord;
	hole = sil::Circle(holeCenter, perturbRadius);
	cell.addPolygon(hole);
      }

      yPos = -rowNum*period*sin(PI/3.);
      xPos = xShift + colNum*period;
      holeCenter = sil::CoordPnt(xPos, yPos) + centerCoord;
      hole = sil::Circle(holeCenter, radius);
      cell.addPolygon(hole);
      if (addPerturb) {
	xPos -= radius; // perturbation is on left side
	holeCenter = sil::CoordPnt(xPos, yPos) + centerCoord;
	hole = sil::Circle(holeCenter, perturbRadius);
	cell.addPolygon(hole);
      }

      yPos = -rowNum*period*sin(PI/3.);
      xPos = -(xShift + colNum*period);
      holeCenter = sil::CoordPnt(xPos, yPos) + centerCoord;
      hole = sil::Circle(holeCenter, radius);
      cell.addPolygon(hole);
      if (addPerturb) {
	xPos -= radius; // perturbation is on left side
	holeCenter = sil::CoordPnt(xPos, yPos) + centerCoord;
	hole = sil::Circle(holeCenter, perturbRadius);
	cell.addPolygon(hole);
      }

    }
  }
}
