//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// PrimaryGenerator.cc
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include "PrimaryGenerator.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"

//------------------------------------------------------------------------------
  PrimaryGenerator::PrimaryGenerator()
  : fpParticleGPS(0)
//------------------------------------------------------------------------------
{
  fpParticleGPS = new G4GeneralParticleSource();
}

//------------------------------------------------------------------------------
  PrimaryGenerator::~PrimaryGenerator()
//------------------------------------------------------------------------------
{
  delete fpParticleGPS;
}

//------------------------------------------------------------------------------
  void PrimaryGenerator::GeneratePrimaries(G4Event* anEvent)
//------------------------------------------------------------------------------
{
  fpParticleGPS->GeneratePrimaryVertex(anEvent);
}
