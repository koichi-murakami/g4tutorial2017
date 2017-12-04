
#include "PrimaryGeneratorMessenger.hh"

#include "PrimaryGeneratorAction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4SystemOfUnits.hh"


PrimaryGeneratorMessenger::
  PrimaryGeneratorMessenger(PrimaryGeneratorAction* Gun)
  : G4UImessenger(),
    fAction(Gun)
{
  fGunDir = new G4UIdirectory("/Optical/");
  fGunDir->SetGuidance("Optical Photon polarization");

  fPolarCmd =
           new G4UIcmdWithADoubleAndUnit("/Optical/polarization",this);
  fPolarCmd->SetGuidance("Set linear polarization");
  fPolarCmd->SetGuidance("  angle w.r.t. (k,n) plane");
  fPolarCmd->SetParameterName("angle",true);
  fPolarCmd->SetUnitCategory("Angle");
  fPolarCmd->SetDefaultValue(-360.0);
  fPolarCmd->SetDefaultUnit("deg");
  fPolarCmd->AvailableForStates(G4State_Idle);
}


PrimaryGeneratorMessenger::~PrimaryGeneratorMessenger()
{
  delete fPolarCmd;
  delete fGunDir;
}


void PrimaryGeneratorMessenger::SetNewValue(
                                        G4UIcommand* command, G4String newValue)
{
  if( command == fPolarCmd ) {
      G4double angle = fPolarCmd->GetNewDoubleValue(newValue);
      if ( angle == -360.0*deg ) {
         fAction->SetOptPhotonPolar();
      } else {
         fAction->SetOptPhotonPolar(angle);
      }
  }
}


