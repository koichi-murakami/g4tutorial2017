#ifndef StackingAction_H
#define StackingAction_H 1

#include "globals.hh"
#include "G4UserStackingAction.hh"


class StackingAction : public G4UserStackingAction
{
  public:
    StackingAction();
    virtual ~StackingAction();

  public:
    virtual G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track* aTrack);
    virtual void NewStage();
    virtual void PrepareNewEvent();

  private:
    G4int fScintiCounter;
    G4int fCerenCounter;
    G4int fOpAbsorpCounter;
};


#endif
