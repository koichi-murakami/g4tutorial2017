//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// SensitiveVolume.cc
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "SensitiveVolume.hh"
#include "G4TouchableHistory.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4ParticleDefinition.hh"
#include "G4HCofThisEvent.hh"
#include "G4RunManager.hh"
#include "Analysis.hh"

//------------------------------------------------------------------------------
  SensitiveVolume::SensitiveVolume(G4String name)
  : G4VSensitiveDetector(name)
//------------------------------------------------------------------------------
{}

//------------------------------------------------------------------------------
  SensitiveVolume::~SensitiveVolume()
//------------------------------------------------------------------------------
{}

//------------------------------------------------------------------------------
  void SensitiveVolume::Initialize(G4HCofThisEvent*)
//------------------------------------------------------------------------------
{
    sum_eDep = 0.;
    no_Step = 0;
}

//------------------------------------------------------------------------------
  void SensitiveVolume::EndOfEvent(G4HCofThisEvent*)
//------------------------------------------------------------------------------
{
   G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
   analysisManager->FillH1(2, sum_eDep);
   G4cout << ">>>>>  EnfOfEvent sum_eDep = "<< sum_eDep << G4endl;
}

//------------------------------------------------------------------------------
  G4bool SensitiveVolume::ProcessHits(G4Step* aStep, G4TouchableHistory*)
//------------------------------------------------------------------------------
{

//   G4cout << "=== SenstiveVolume-ProcessHits: Output of Information ===" << G4endl;

   G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

    
// energy deposit in this step and its accumulation over steps
    G4double edep = aStep->GetTotalEnergyDeposit();
    sum_eDep = sum_eDep + edep;
  
    
  
// Retrieve information from the track object
   G4int nTrack = aStep->GetTrack()->GetParentID();
   G4int nStep  = aStep->GetTrack()->GetCurrentStepNumber();
   G4String particleName = aStep->GetTrack()->GetDefinition()->GetParticleName();

if(aStep->GetTrack()->GetTrackStatus()!=fAlive) return false;
// Primary track is picked up
 //   if (nTrack != 1) return false;
      no_Step = no_Step + 1;    
    /*
   G4cout << "  Track Number: " << nTrack << G4endl;
   G4cout << "  Step  Number: " << nStep << G4endl;
*/
   G4cout << " multiplicity = " << no_Step << "  Particle: " << particleName << G4endl;


// Get PreStepPoint and TouchableHandle objects
   G4StepPoint* preStepPoint=aStep->GetPreStepPoint();
   G4TouchableHandle theTouchable = preStepPoint->GetTouchableHandle();

  // Touchable infomation: Start position of the current step
  G4ThreeVector position_World = preStepPoint->GetPosition();
  G4ThreeVector position_Local = theTouchable->GetHistory()
                                  -> GetTopTransform().TransformPoint(position_World);



// Touchable information: Volume name and copy# at the current step
  G4String volumeName = theTouchable->GetVolume()->GetName();
  G4int copyNo = theTouchable->GetCopyNumber();

  G4String motherVolumeName;
  G4int motherCopyNo;
  if (volumeName != "LogVol_PixElmt" ) {
     motherVolumeName = theTouchable->GetVolume(1)->GetName();
     motherCopyNo = theTouchable->GetCopyNumber(1);
  } 
  else {
     motherVolumeName = "None";
     motherCopyNo = 0;
  }

  G4cout << " ******  Pixel ID and energy loss accumulated ******************"<< G4endl;
  G4cout << "  Volume = " << volumeName 
         << " , CopyNo = "   << copyNo 
         << " :: Mother Volume = " << motherVolumeName
         << " ,  CopyNo= " << motherCopyNo << " :: sum_eDep =  " << sum_eDep <<G4endl;
  G4cout << " ******  Entry point  coordinates**************"<< G4endl;
  G4cout << "  World(x,y,z): " 
         << position_World.x() << ", " << position_World.y() << ", " 
         << position_World.z()  
         << "::  Local(x,y,z): " 
         << position_Local.x() << ", " << position_Local.y() << ", " 
         << position_Local.z() << G4endl; 
  G4cout << " ******  end of this pixel *******************************************"<< G4endl;

// a primary track with non-zero energy deposition is registerd
 //   if ( edep==0. ) return false;

    analysisManager->FillH1(1,motherCopyNo);
    analysisManager->FillH1(0,copyNo);
    analysisManager->FillH2(0,position_World.x(), position_World.y());
  
    analysisManager->FillNtupleIColumn(0, motherCopyNo);
    analysisManager->FillNtupleIColumn(1, copyNo);
    analysisManager->AddNtupleRow();
// accumulation of energy loss pixel by pixel   
//   G4cout  << "  in pixel ID = " <<motherCopyNo << " , "<< copyNo<< "  sum_eDep  " << sum_eDep <<G4endl;
   
  return true;
}






