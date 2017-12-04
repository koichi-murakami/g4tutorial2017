#include "SteppingAction.hh"
#include "EventAction.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4OpticalPhoton.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"

SteppingAction::SteppingAction(EventAction* eventAction)
: G4UserSteppingAction(), fEventAction(eventAction)
{   ; }

SteppingAction::~SteppingAction()
{ ; }

void SteppingAction::UserSteppingAction(const G4Step* step)
{
  
  G4StepPoint* point1 = step->GetPreStepPoint();
  G4StepPoint* point2 = step->GetPostStepPoint();
//世界の外へ出ていない時には
if (point2->GetStepStatus() == fWorldBoundary)return;
  G4Track* track = step->GetTrack();
  G4String ParticleName = track->GetDynamicParticle()->
                                 GetParticleDefinition()->GetParticleName();
//光学光子ならば
 if (ParticleName != "opticalphoton")return;
    
 
    G4double stepLen = step->GetStepLength();
    G4TouchableHandle touch1 = point1->GetTouchableHandle();
    G4TouchableHandle touch2 = point2->GetTouchableHandle();
  G4String  currVol =  touch1->GetVolume()->GetName();
  G4String  nextVol =  touch2->GetVolume()->GetName();
    
 // 全反射かどうか

        if ( stepLen>0.0){
            //G4cout<< "輸送　ステップ長 "<< stepLen<<"  "<<currVol<<" から "<<nextVol<<"  へ   " <<G4endl;
            if(nextVol=="World")track->SetTrackStatus(fStopAndKill);
        }else{
            fEventAction->SetReflective();
           //G4cout<< "反射　ステップ長 "<< stepLen<<"  momentum  "<<track->GetMomentum()<<"                    "<<currVol<<" から "<<nextVol<<"  へ   "<<G4endl;
            //track->SetTrackStatus(fStopAndKill);
        }
}
