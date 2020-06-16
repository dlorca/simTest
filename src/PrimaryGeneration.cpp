// -----------------------------------------------------------------------------
//  nanoDotCal | PrimaryGeneration.cpp
//
//  Class for the definition of the primary generation action.
//   * Author: David Lorca
//   * Creation date: 05 - Feb - 2020
// -----------------------------------------------------------------------------

#include "PrimaryGeneration.h"

#include <G4ParticleDefinition.hh>
#include <G4SystemOfUnits.hh>
#include <G4IonTable.hh>
#include <G4PrimaryParticle.hh>
#include <G4PrimaryVertex.hh>
#include <G4Event.hh>
#include "G4ParticleGun.hh"
#include "G4GeneralParticleSource.hh"
#include <G4RadioactiveDecay.hh>
#include "G4ParticleTable.hh"
#include "Randomize.hh"


PrimaryGeneration::PrimaryGeneration():
  G4VUserPrimaryGeneratorAction()
{
particleSource = new G4GeneralParticleSource();
}


PrimaryGeneration::~PrimaryGeneration()
{
}


void PrimaryGeneration::GeneratePrimaries(G4Event* event)
{

particleSource->GeneratePrimaryVertex(event);

}
