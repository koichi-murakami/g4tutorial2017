#include "RunAction.hh"
#include "Analysis.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"


RunAction::RunAction()
 : G4UserRunAction()
{ 
// Create analysis manager
  
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  G4cout << "Using " << analysisManager->GetType() << G4endl;

  analysisManager->SetVerboseLevel(1);
  analysisManager->SetFirstHistoId(1);        // Histo Id starts from 1 not from0

  // Book histograms, ntuple
  //
  
  // Creating histograms　　　BGO結晶20個でのエネルギー付与
    G4String Hist_Name[20]=
    {"BGO1", "BGO2", "BGO3", "BGO4", "BGO5", "BGO6", "BGO7", "BGO8", "BGO9", "BGO10",
        "BGO11", "BGO12", "BGO13", "BGO14", "BGO15", "BGO16", "BGO17", "BGO18", "BGO19", "BGO20"};

    for(G4int i=0; i<20; i++){
        analysisManager->CreateH1(Hist_Name[i],"Edep in BGO", 200, 0., 2000*MeV);
    }
    analysisManager->CreateH1("Sum","Edep Sum", 500, 0., 10000*MeV);  //総和


  // Creating ntuple
}

RunAction::~RunAction()
{
  delete G4AnalysisManager::Instance();  
}

void RunAction::BeginOfRunAction(const G4Run* /*run*/)
{
 // Get analysis manager and open an output file
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  G4String fileName = "BGO";
  analysisManager->OpenFile(fileName);
}

void RunAction::EndOfRunAction(const G4Run* /*run*/)
{
  //save histograms & ntuple
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();

}

