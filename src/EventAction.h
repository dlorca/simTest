// -----------------------------------------------------------------------------
//  nanoDotCal | EventAction.h
//
//
//   * Author: David Lorca
//   * Creation date: 05 - Feb - 2020
// -----------------------------------------------------------------------------

#ifndef EVENT_ACTION_H
#define EVENT_ACTION_H

#include <G4UserEventAction.hh>


class EventAction: public G4UserEventAction
{
public:
  EventAction();
  virtual ~EventAction();
  virtual void BeginOfEventAction(const G4Event*);
  virtual void EndOfEventAction(const G4Event*);
};

#endif
