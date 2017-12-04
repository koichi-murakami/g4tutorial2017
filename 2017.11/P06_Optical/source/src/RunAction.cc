
#include "RunAction.hh"
#include "G4Run.hh"


RunAction::RunAction()
 : G4UserRunAction()
{;}

RunAction::~RunAction()
{;}

void RunAction::BeginOfRunAction(const G4Run* aRun)
{
  G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;
}

void RunAction::EndOfRunAction(const G4Run* aRun)
{

  G4cout << "number of event = " << aRun->GetNumberOfEvent()<< G4endl;
}

