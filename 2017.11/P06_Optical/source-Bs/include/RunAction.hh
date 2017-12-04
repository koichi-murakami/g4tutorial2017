
#ifndef RunAction_h
#define RunAction_h 1

#include "globals.hh"
#include "G4UserRunAction.hh"


class G4Run;
class PrimaryGeneratorAction;

class RunAction : public G4UserRunAction
{
  public:
    RunAction(PrimaryGeneratorAction*);
    virtual ~RunAction();

  public:
    virtual void BeginOfRunAction(const G4Run* aRun);
    virtual void EndOfRunAction(const G4Run* aRun);
    void CountEvent(){fEvents +=1;};
  private:
    G4int fEvents;
    PrimaryGeneratorAction* primary;
    G4String polWave;
    FILE *fp;
};


#endif /*RunAction_h*/
