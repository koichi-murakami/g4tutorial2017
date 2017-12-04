
#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4ParticleGun.hh"
#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"


class G4Event;
class PrimaryGeneratorMessenger;


class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    PrimaryGeneratorAction();
    virtual ~PrimaryGeneratorAction();

  public:
    virtual void GeneratePrimaries(G4Event*);
    G4ParticleGun* GetParticleGun() { return fParticleGun; }
    void SetOptPhotonPolar();
    void SetOptPhotonPolar(G4double);

  private:
    G4ParticleGun* fParticleGun;
    PrimaryGeneratorMessenger* fGunMessenger;
};


#endif /*PrimaryGeneratorAction_h*/
