
#include "RunAction.hh"
#include "Analysis.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"



RunAction::RunAction()
 : G4UserRunAction()
{
    // Get analysis manager
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    G4cout << "Using " << analysisManager->GetType() << G4endl;
    analysisManager->SetActivation(true);

    // Create directories
    //analysisManager->SetHistoDirectoryName("histograms");
    //analysisManager->SetNtupleDirectoryName("ntuple");
    analysisManager->SetVerboseLevel(1);
    //analysisManager->SetFirstHistoId(1);
    analysisManager->SetFileName("Pixel");
    //analysisManager->SetHistoDirectoryName("histo");
    // Book histograms, ntuple
    //
    
    // Creating histograms
//H1
    G4int id = analysisManager->CreateH1("h1:0","CopyNumber", 336, 1, 336, "none");
	//analysisManager->SetH1Activation(id, false);
     id = analysisManager->CreateH1("h1:1","MotherCopyNumber", 80, 1, 80, "none");
	//analysisManager->SetH1Activation(id, false);
     id = analysisManager->CreateH1("h1:2","sum_eDep", 100, 0., 5.*MeV);
	analysisManager->SetH1Activation(id, false);
// H2
     G4int id2 = analysisManager->CreateH2("h2:0","world_x vs y", 200, -10.*mm, 10*mm, 200,  -10*mm, 10*mm);
	analysisManager->SetH2Activation(id2, false);
 

    // Creating ntuple
    //
    analysisManager->CreateNtuple("Pixel", "motherCopy Number copyNumber");
    analysisManager->CreateNtupleIColumn("motherCopyNumber");
    analysisManager->CreateNtupleIColumn("copyNumber");
    analysisManager->FinishNtuple();

 }



RunAction::~RunAction()
{
  delete G4AnalysisManager::Instance();  
}



void RunAction::BeginOfRunAction(const G4Run* /*run*/)
{ 
    
  // Get analysis manager
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  // Open an output file
  //
  // G4String fileName = "Pixel";
  analysisManager->OpenFile();
    //G4cout << "File " << fileName << " Open" <<G4endl;
    
}



void RunAction::EndOfRunAction(const G4Run* /*run*/)
{
  // print histogram statistics
  //
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  // save histograms & ntuple
  //
  analysisManager->Write();
  analysisManager->CloseFile();


}
