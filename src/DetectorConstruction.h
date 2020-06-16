// -----------------------------------------------------------------------------
//  nanoDotCal | DetectorConstruction.h
//
//  Class for the definition of the detector geometry and materials.
//   * Author: David Lorca
//   * Creation date: 05 - Feb - 2020
// -----------------------------------------------------------------------------

#ifndef DETECTOR_CONSTRUCTION_H
#define DETECTOR_CONSTRUCTION_H

#include <G4VUserDetectorConstruction.hh>
#include "globals.hh"

class G4Material;


class DetectorConstruction: public G4VUserDetectorConstruction
{
public:
  DetectorConstruction();
  virtual ~DetectorConstruction();
  virtual G4VPhysicalVolume* Construct();
  virtual void ConstructSDandField();
 private:
  G4Material* DefineNeon() const;
};

#endif
