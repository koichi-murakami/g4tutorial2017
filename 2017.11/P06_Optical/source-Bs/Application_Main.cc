//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Geant4 Application: Tutorial course for Hep/Medicine Users: 2016.11.29 @Sendai
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"
#include "PhysicsList.hh"

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "FTFP_BERT.hh"

//-------------------------------------------------------------------------------
  int main( int argc, char** argv )
//-------------------------------------------------------------------------------
{
   // ============= [ Setting up the application environment ] =================
      G4String nameMainMacro = "GlobalSetup.mac";   // Initialization  macros
      G4String macroFile;
   // ==========================================================================

    if ( argc != 3 ) {
        G4cout << " Usage: application -m macroFile" <<G4endl;
        return 1;
    }
    if      ( G4String(argv[1]) == "-m" ) macroFile   = argv[2];

// Construct the default run manager
   G4RunManager* runManager = new G4RunManager;

// Set up mandatory user initialization: Geometry
   runManager->SetUserInitialization( new DetectorConstruction() );

// Set up mandatory user initialization: Physics-List
   runManager->SetUserInitialization( new PhysicsList() );

// Set up user initialization: User Actions
   runManager->SetUserInitialization( new ActionInitialization() );

// Initialize G4 kernel
   runManager->Initialize();

// Create visualization environment
   G4VisManager* visManager = new G4VisExecutive;
   visManager->Initialize();

// Start interactive session
   G4UImanager*   uiManager = G4UImanager::GetUIpointer();

    if ( macroFile.size() ) {
        // Batch mode
        G4String command = "/control/execute ";
        uiManager->ApplyCommand(command+macroFile);
    }
    else
    {
   G4UIExecutive* uiExec    = new G4UIExecutive(argc, argv);
   uiManager->ApplyCommand("/control/execute " + nameMainMacro);
   uiExec->SessionStart();

// Job termination
   delete uiExec;
    }
   delete visManager;
   delete runManager;

   return 0;
}
