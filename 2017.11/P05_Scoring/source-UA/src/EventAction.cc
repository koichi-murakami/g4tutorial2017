
#include "EventAction.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"

#include "G4UnitsTable.hh"
#include "Analysis.hh"
#include "Randomize.hh"
#include <iomanip>


EventAction::EventAction()
 : G4UserEventAction() 
{}


EventAction::~EventAction()
{}

void EventAction::BeginOfEventAction(const G4Event* /*event*/)
{
    for(G4int i=0; i<noBGO;i++){
        sum_eDep[i] = 0.;
    }
}

void EventAction::EndOfEventAction(const G4Event* /*event*/)
{
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    G4double sum_BGO = 0.;
    for(G4int i=0; i<noBGO; i++){
        GetSum(i);
        //G4cout << "sum_eDep["<<i+1000 << "] = "<< GetSum(i)<<G4endl;
        analysisManager->FillH1(i+1, GetSum(i));   //H1 id = 1 ~ 20
        
        sum_BGO = sum_BGO + GetSum(i);
    }
    G4cout << "全てのBGOでのエネルギー付与 : "<< sum_BGO <<G4endl;
    analysisManager->FillH1(21, sum_BGO);
}

