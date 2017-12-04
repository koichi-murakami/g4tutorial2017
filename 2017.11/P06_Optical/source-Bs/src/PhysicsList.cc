//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// PhysicsList.cc　　P04_PhysicsList/source/src/PhysicsList.hh にOpticalPhotonプロセスを追加
//  [Note] Based on "G4 Basic Example: B3"   
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "PhysicsList.hh"
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4OpticalPhysics.hh"
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
   RegisterPhysics(new G4OpticalPhysics());
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

