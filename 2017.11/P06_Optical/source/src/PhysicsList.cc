//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// PhysicsList.cc　　P04_PhysicsList/source/src/PhysicsList.hh にOpticalPhotonプロセスを追加
// 
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "PhysicsList.hh"
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4OpticalPhysics.hh"
#include "G4OpticalProcessIndex.hh"

//------------------------------------------------------------------------------
  PhysicsList::PhysicsList()
  : G4VModularPhysicsList() 
//------------------------------------------------------------------------------
{

// Default physics
   RegisterPhysics(new G4DecayPhysics());

// Radioactive decay
   RegisterPhysics(new G4RadioactiveDecayPhysics());

// EM physics
   RegisterPhysics(new G4EmStandardPhysics());


// Optical Photon physics 追加

 G4OpticalPhysics* opticalPhysics = new G4OpticalPhysics();
  RegisterPhysics( opticalPhysics );


  opticalPhysics->SetScintillationYieldFactor(1.0);
  opticalPhysics->SetScintillationExcitationRatio(0.0);

  opticalPhysics->SetMaxNumPhotonsPerStep(100);
  opticalPhysics->SetMaxBetaChangePerStep(10.0);

  opticalPhysics->SetTrackSecondariesFirst(kCerenkov,true);
  opticalPhysics->SetTrackSecondariesFirst(kScintillation,true);

}

//------------------------------------------------------------------------------
  PhysicsList::~PhysicsList()
//------------------------------------------------------------------------------
{}

//------------------------------------------------------------------------------
  void PhysicsList::SetCuts()
//------------------------------------------------------------------------------
{
    G4VUserPhysicsList::SetCuts();
}

