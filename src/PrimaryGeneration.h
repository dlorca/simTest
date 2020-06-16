// -----------------------------------------------------------------------------
//  nanoDotCal | PrimaryGeneration.h
//
//  Class for the definition of the primary generation action.
//   * Author: David Lorca
//   * Creation date: 05 - Feb - 2020
// -----------------------------------------------------------------------------

#ifndef PRIMARY_GENERATION_H
#define PRIMARY_GENERATION_H

#include <G4VUserPrimaryGeneratorAction.hh>
#include "globals.hh"

class G4ParticleDefinition;

class G4GeneralParticleSource;

class PrimaryGeneration: public G4VUserPrimaryGeneratorAction
{
public:
  PrimaryGeneration();
  virtual ~PrimaryGeneration();
  virtual void GeneratePrimaries(G4Event*);

 private:
  G4GeneralParticleSource* particleSource; // GPS
  
};

#endif
