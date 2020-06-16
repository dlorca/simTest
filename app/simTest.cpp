// -----------------------------------------------------------------------------
//  simTest | simTest.cpp
//
//  Main program of the simTest detector simulation.
//   * Author: David Lorca
//   * Creation date: 05 - Feb - 2020
// -----------------------------------------------------------------------------

#include "DetectorConstruction.h"
#include "PrimaryGeneration.h"
#include "SteppingAction.h"
#include "Analysis.hh"

#include <G4RunManager.hh>
#include <G4UImanager.hh>
#include <G4VisExecutive.hh>
#include <G4UIExecutive.hh>
#include <FTFP_BERT_HP.hh>
#include <G4EmStandardPhysics_option4.hh>
#include "G4TScoreNtupleWriter.hh"

int main(int argc, char** argv)
{
  // Detect interactive mode (if no arguments) and define UI session
  //
  G4UIExecutive* ui = 0;
  if ( argc == 1 ) {
    ui = new G4UIExecutive(argc, argv);
  }

  int seed = 1;
  CLHEP::HepRandom::setTheSeed(seed);
  
  // Construct the run manager and set the initialization classes
  G4RunManager* runmgr = new G4RunManager();

  G4VModularPhysicsList* physics_list = new FTFP_BERT_HP();
  physics_list->ReplacePhysics(new G4EmStandardPhysics_option4());
  runmgr->SetUserInitialization(physics_list);

  runmgr->SetUserInitialization(new DetectorConstruction());

  runmgr->SetUserAction(new PrimaryGeneration());

  runmgr->SetUserAction(new SteppingAction());

  // Initialize visualization
  G4VisManager* vismgr = new G4VisExecutive();
  vismgr->Initialize();

  // Get the pointer to the User Interface manager
  G4UImanager* uimgr = G4UImanager::GetUIpointer();


  std::cout<<"Writing ntuples "<<std::endl;                                                                                                   
  // Activate score ntuple writer                                                                                                             
  // The Root output type (Root) is selected in Analysis.hh.                                                                                  
  // The verbose level can be also set via UI commands                                                                                        
  // /score/ntuple/writerVerbose level                                                                                                        
  // /score/writerFileName filename                                                                                                           
  G4TScoreNtupleWriter<G4AnalysisManager> scoreNtupleWriter;                                                                                  
  scoreNtupleWriter.SetVerboseLevel(1);  
  
  // Process macro or start UI session
  //
  if (!ui) {
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    uimgr->ApplyCommand(command+fileName);
  }
  else {
    // interactive mode
    uimgr->ApplyCommand("/control/execute init_vis.mac");
    ui->SessionStart();
    delete ui;
  }

  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted
  // in the main() program.

  delete vismgr;
  delete runmgr;
}
