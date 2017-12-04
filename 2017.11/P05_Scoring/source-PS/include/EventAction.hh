
#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"

#include "G4THitsMap.hh"
#include "globals.hh"

/// Event action class
///　ヒットコレクションに格納されている原始スコアラのエネルギーとその和を取りヒストクラムに書き込む


class EventAction : public G4UserEventAction
{
public:
  EventAction();
  virtual ~EventAction();

  virtual void  BeginOfEventAction(const G4Event* event);
  virtual void    EndOfEventAction(const G4Event* event);
    
private:
  // methods
  G4THitsMap<G4double>* GetHitsCollection(G4int hcID,
                                          const G4Event* event) const;
  G4double GetSum(G4THitsMap<G4double>* hitsMap) const;
  void PrintEventStatistics(G4double BGOEdep) const;
  
  // data members                   
  G4int  fBGOEdepHCID;
};
                     


#endif

    
