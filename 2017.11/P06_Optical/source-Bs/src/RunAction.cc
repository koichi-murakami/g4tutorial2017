#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4ParticleMomentum.hh"

RunAction::RunAction(PrimaryGeneratorAction* kin)
 : G4UserRunAction(), primary(kin)
{;}

RunAction::~RunAction()
{;}

void RunAction::BeginOfRunAction(const G4Run* aRun)
{
     G4cout << "ラン番号 " << aRun->GetRunID()<< " 開始   " ;

    fp = fopen("Brewster.csv", "a");
   
    fEvents = 0;
    polWave = "--";
}

void RunAction::EndOfRunAction(const G4Run* aRun)
{
    G4int noOfEvents = aRun->GetNumberOfEvent();

    G4ParticleGun* gun = primary->GetParticleGun();
    G4ParticleMomentum direction = gun->GetParticleMomentumDirection();
    G4double incAngle = 57.29578*std::atan(direction.y()/direction.x());
    G4ThreeVector polar = gun->GetParticlePolarization();
    
    if(polar.z()==0){polWave="P";}
    if(polar.z()==1){polWave="S";}
    G4double reflRate = 100. * fEvents/noOfEvents;
    // CSV ファイル出力　ファイル安全策なし
    fprintf (fp, "%e %s %e \n", incAngle, " , ", reflRate);
    //G4cout <<" , "<< incAngle<<","<<reflRate <<G4endl;
    //テキスト出力
    G4cout << "イベント数： " << noOfEvents  <<"  "<< polWave<<"偏光  入射角, "<< incAngle<< ", 反射率 , "<<reflRate<< G4endl;
}

