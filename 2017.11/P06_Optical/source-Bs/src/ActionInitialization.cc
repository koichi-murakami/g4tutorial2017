
#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "EventAction.hh"
#include "RunAction.hh"
#include "SteppingAction.hh"


//

ActionInitialization::ActionInitialization()
 : G4VUserActionInitialization()
{}



ActionInitialization::~ActionInitialization()
{}


/*****
void ActionInitialization::BuildForMaster() const
{
  SetUserAction(new RunAction());
}
****/


void ActionInitialization::Build() const
{
    PrimaryGeneratorAction* primaryGen = new PrimaryGeneratorAction();
    RunAction* runAction = new RunAction(primaryGen);
    EventAction* eventAction = new EventAction(runAction);
    SteppingAction* steppingAction = new SteppingAction(eventAction);
    
    
    SetUserAction(primaryGen);
    SetUserAction(steppingAction);
    SetUserAction(eventAction);
    SetUserAction(runAction);
}





