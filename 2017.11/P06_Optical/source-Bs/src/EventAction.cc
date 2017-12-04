
#include "EventAction.hh"
#include "RunAction.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"

#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include <iomanip>


EventAction::EventAction(RunAction* runAction)
 : G4UserEventAction(), fRunAction(runAction)
{}

EventAction::~EventAction()
{}

void EventAction::BeginOfEventAction(const G4Event* /*event*/)
{
    isReflective = false;
}

void EventAction::EndOfEventAction(const G4Event* /*event*/)
{  
    if(isReflective){fRunAction->CountEvent();}
}

