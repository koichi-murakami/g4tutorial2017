
#include "StackingAction.hh"

#include "G4VProcess.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4Track.hh"
#include "G4ios.hh"

StackingAction::StackingAction()
  : G4UserStackingAction(),
    fScintiCounter(0), fCerenCounter(0), fOpAbsorpCounter(0)
{}

StackingAction::~StackingAction()
{}

G4ClassificationOfNewTrack
StackingAction::ClassifyNewTrack(const G4Track * aTrack)
{
  if(aTrack->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition())
  { // particle is optical photon
    if(aTrack->GetParentID()>0)
    { // particle is secondary
      if(aTrack->GetCreatorProcess()->GetProcessName() == "Scintillation")
        fScintiCounter++;
      if(aTrack->GetCreatorProcess()->GetProcessName() == "Cerenkov")
        fCerenCounter++;
      if(aTrack->GetCreatorProcess()->GetProcessName() == "OpAbsorption")
        fOpAbsorpCounter++;
    }
  }
  return fUrgent;
}


void StackingAction::NewStage()
{
  G4cout << "Scintillation photons : "
         << fScintiCounter 
         << "  Cerenkov photons : "
         << fCerenCounter 
	 << "  Optical Absorption : " << fOpAbsorpCounter << G4endl;
}



void StackingAction::PrepareNewEvent()
{
  fScintiCounter = 0;
  fCerenCounter = 0;
  fOpAbsorpCounter = 0;
}


