// -----------------------------------------------------------------------------
//  simTest | DetectorConstruction.cpp
//
//  Definition of detector geometry and materials.
//   * Author: David Lorca
//   * Creation date: 05 - Feb - 2020
// -----------------------------------------------------------------------------

#include "DetectorConstruction.h"

#include <G4Box.hh>
#include <G4Tubs.hh>
#include <G4LogicalVolume.hh>
#include <G4PVPlacement.hh>
#include <G4NistManager.hh>
#include <G4SystemOfUnits.hh>
#include <G4VisAttributes.hh>
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4Material.hh"
#include "G4Element.hh"

#include "G4SDManager.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4PSDoseDeposit.hh"
#include "G4PSTrackLength.hh"
#include "G4PSFlatSurfaceCurrent.hh"
#include "G4PSCylinderSurfaceCurrent.hh"
#include "G4PSTrackCounter.hh"
#include "G4PSCellCharge.hh"
#include "G4PSCellFlux.hh"
#include "G4PSNofCollision.hh"
#include "G4PSNofSecondary.hh"
#include <G4SDKineticEnergyFilter.hh>
#include <G4SDChargedFilter.hh>

#include <string>
#include <vector>
#include <map> 

DetectorConstruction::DetectorConstruction(): G4VUserDetectorConstruction()
{
}


DetectorConstruction::~DetectorConstruction()
{
}


G4VPhysicalVolume* DetectorConstruction::Construct()
{

  G4Colour  white   (1.0, 1.0, 1.0) ;  // white
  G4Colour  grey    (0.5, 0.5, 0.5) ;  // gray
  G4Colour  black   (0.0, 0.0, 0.0) ;  // black
  G4Colour  red     (1.0, 0.0, 0.0) ;  // red
  G4Colour  green   (0.0, 1.0, 0.0) ;  // green
  G4Colour  blue    (0.0, 0.0, 1.0) ;  // blue
  G4Colour  cyan    (0.0, 1.0, 1.0) ;  // cyan
  G4Colour  magenta (1.0, 0.0, 1.0) ;  // magenta
  G4Colour  yellow  (1.0, 1.0, 0.0) ;  // yellow
  G4Colour  brown(0.7, 0.4, 0.1);

  // WORLD /////////////////////////////////////////////////
  G4String world_name = "WORLD";
  G4double world_size = 6.*m;
  // G4Material* world_mat = G4NistManager::Instance()->FindOrBuildMaterial("G4_AIR");
  G4Material* world_mat = G4NistManager::Instance()->FindOrBuildMaterial("G4_WATER");

  G4Box* world_solid_vol =
    new G4Box(world_name, world_size/2., world_size/2., world_size/2.);

  G4LogicalVolume* world_logic_vol =
    new G4LogicalVolume(world_solid_vol, world_mat, world_name);
  world_logic_vol->SetVisAttributes(G4VisAttributes::Invisible);

  G4VPhysicalVolume* world_phys_vol =
    new G4PVPlacement(0, G4ThreeVector(0.,0.,0.),
                      world_logic_vol, world_name, 0, false, 0, true);
  //WORLD /////////////////////////////////////////////////
  

  // DETECTOR //////////////////////////////////////////////

  G4String detector_name = "DETECTOR";
  G4double detector_diam   = 50.0*cm;
  G4double detector_length = 50.0*cm;
  //G4Material* detector_mat = DefineNeon();
  // G4Material* detector_mat = G4NistManager::Instance()->FindOrBuildMaterial("G4_SODIUM_IODIDE");
  G4Material* detector_mat = G4NistManager::Instance()->FindOrBuildMaterial("G4_ALUMINUM_OXIDE");
  
  G4Tubs* detector_solid_vol =
    new G4Tubs(detector_name, detector_diam/4., detector_diam/2., detector_length/2., 0., 360.*deg);

  G4LogicalVolume* detector_logic_vol =
    new G4LogicalVolume(detector_solid_vol, detector_mat, "DETECTOR_LV");

  G4VisAttributes* DetectorVisAttributes = new G4VisAttributes(blue);
  detector_logic_vol->SetVisAttributes(DetectorVisAttributes); 

  //rotation matrix
  G4RotationMatrix* Yver = new G4RotationMatrix();
  Yver->rotateX(M_PI/2.*rad);

  new G4PVPlacement(Yver, G4ThreeVector(0.,0.,0.),
                    detector_logic_vol, detector_name, world_logic_vol, false, 0, true);

  //////////////////////////////////////////////////////////

  //place the wold!!                                                                                                                                                         
  return world_phys_vol;  
}


void DetectorConstruction::ConstructSDandField()
{
  G4SDManager::GetSDMpointer()->SetVerboseLevel(1);
  
  // declare water cylinder a MultiFunctionalDetector scorer                                                                                  
  //                                                                                                                                          

  G4MultiFunctionalDetector* cilind = new G4MultiFunctionalDetector("DETECTOR");
  G4SDManager::GetSDMpointer()->AddNewDetector(cilind);

  /*
  G4MultiFunctionalDetector* cilindFilter = new G4MultiFunctionalDetector("DETECTORFilter");
  G4SDManager::GetSDMpointer()->AddNewDetector(cilindFilter);
  
  G4SDKineticEnergyFilter* KinEnergyFilter =                                                                                                
    new G4SDKineticEnergyFilter("kineticenergyFilter",0.01, 1.02);//MeV units
  cilindFilter->SetFilter(KinEnergyFilter);
  */
  
  G4VPrimitiveScorer* primitiv10 = new G4PSEnergyDeposit("energy_dep");                                                                       
  cilind->RegisterPrimitive(primitiv10);
  //cilindFilter->RegisterPrimitive(primitiv10);


  G4VPrimitiveScorer* primitiv12 = new G4PSTrackLength("track_length");                                                                       
  cilind->RegisterPrimitive(primitiv12);                                                                                                 
    /*
    G4VPrimitiveScorer* primitiv11 = new G4PSDoseDeposit("dose_dep");                                                                           
    cilind->RegisterPrimitive(primitiv11);                                                                                                      

  */
  SetSensitiveDetector("DETECTOR_LV",cilind);
  //SetSensitiveDetector("DETECTOR_LV",cilindFilter);
}

G4Material* DetectorConstruction::DefineNeon() const
{
  G4String material_name = "GNe";
  G4Material* material = G4Material::GetMaterial("material_name", false);

  if (!material) {
    G4double density = 16.0 * kg/m3;
    G4double pressure = 20.0 * bar;
    G4double temperature = 300. * kelvin;
    material = new G4Material(material_name, density, 1,
			                        kStateGas, temperature, pressure);
    G4Element* Ne = G4NistManager::Instance()->FindOrBuildElement("Ne");
    material->AddElement(Ne,1);
  }

  return material;
}
