// -----------------------------------------------------------------------------
//  nanoDotCal | RunAction.h
//
//
//   * Author: David Lorca
//   * Creation date: 05 - Feb - 2020
// -----------------------------------------------------------------------------

#ifndef RUN_ACTION_H
#define RUN_ACTION_H

#include <G4UserRunAction.hh>


class RunAction: public G4UserRunAction
{
public:
  RunAction();
  virtual ~RunAction();
  virtual void BeginOfRunAction(const G4Run*);
  virtual void   EndOfRunAction(const G4Run*);
};

#endif
