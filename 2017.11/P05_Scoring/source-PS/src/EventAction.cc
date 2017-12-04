
#include "EventAction.hh"
#include "Analysis.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include <iomanip>


EventAction::EventAction()
 : G4UserEventAction(),
   fBGOEdepHCID(-1)        // Hit Collection ID
{}


EventAction::~EventAction()
{}
// ヒットコレクション

G4THitsMap<G4double>* 
EventAction::GetHitsCollection(G4int hcID,
                                  const G4Event* event) const
{
  G4THitsMap<G4double>* hitsCollection 
    = static_cast<G4THitsMap<G4double>*>(
        event->GetHCofThisEvent()->GetHC(hcID));
  
  if ( ! hitsCollection ) {
    G4ExceptionDescription msg;
    msg << "Cannot access hitsCollection ID " << hcID; 
    G4Exception("EventAction::GetHitsCollection()",
      "MyCode0003", FatalException, msg);
  }         

  return hitsCollection;
}    

// ヒットコレクションのマップ(G4int, G4double) のG4doubleの値とその和を得てヒストをFill

G4double EventAction::GetSum(G4THitsMap<G4double>* hitsMap) const
{
G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
G4double sumValue = 0;
G4double edep = 0.;
  std::map<G4int, G4double*>::iterator it;
  for ( it = hitsMap->GetMap()->begin(); it != hitsMap->GetMap()->end(); it++) {
    edep = *(it->second);
    sumValue += edep;
    G4int key = (it->first);
    analysisManager->FillH1(key-999, edep);
    //G4cout << "iterator : " << key << " edep: "<< edep << G4endl;
  }
  return sumValue;  
}  

// イベントの統計出力（お好みで）
void EventAction::PrintEventStatistics(
                            G4double BGOEdep) const
{
  // Print event statistics
  //
  G4cout
    << "   Absorber: total energy: " 
    << std::setw(7) << G4BestUnit(BGOEdep, "Energy Deposit") << G4endl;
}


void EventAction::BeginOfEventAction(const G4Event* /*event*/)
{}


// イベントの終わり処理
void EventAction::EndOfEventAction(const G4Event* event)
{  
// Get hist collections IDs　ヒットコレクションを取得し
  if ( fBGOEdepHCID == -1 ) {
    fBGOEdepHCID
      = G4SDManager::GetSDMpointer()->GetCollectionID("BGO/Edep");  // SD名/ソコアラー名
  }
  
  // ヒットコレクションから一イベントでのエネルギーデポとその総和を求めてヒストへ
  //
  G4double BGOEdep = GetSum(GetHitsCollection(fBGOEdepHCID, event));

  // get analysis manager
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  // fill histograms
  //  
  analysisManager->FillH1(21, BGOEdep);
  
  // fill ntuple
}  


