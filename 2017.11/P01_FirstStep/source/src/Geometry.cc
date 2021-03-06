//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Geometry.cc
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "Geometry.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4VPhysicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4NistManager.hh"
#include "G4VisAttributes.hh"
#include "G4SystemOfUnits.hh"

//------------------------------------------------------------------------------
  Geometry::Geometry() {}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
  Geometry::~Geometry() {}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
  G4VPhysicalVolume* Geometry::Construct()
//------------------------------------------------------------------------------
{
// Get pointer to 'Material Manager'
   G4NistManager* materi_Man = G4NistManager::Instance();

// Define 'World Volume'
   // Define the shape of solid
   G4double leng_X_World = 2.0*m;         // X-full-length of world 
   G4double leng_Y_World = 2.0*m;         // Y-full-length of world 
   G4double leng_Z_World = 2.0*m;         // Z-full-length of world 
   G4Box* solid_World = 
     new G4Box("Solid_World", leng_X_World/2.0, leng_Y_World/2.0, leng_Z_World/2.0);

   // Define logical volume
   G4Material* materi_World = materi_Man->FindOrBuildMaterial("G4_AIR");
   G4LogicalVolume* logVol_World = 
     new G4LogicalVolume(solid_World, materi_World, "LogVol_World");
   logVol_World->SetVisAttributes (G4VisAttributes::Invisible);

   // Placement of logical volume
   G4int copyNum_World = 0;               // Set ID number of world
   G4PVPlacement* physVol_World  = 
     new G4PVPlacement(G4Transform3D(), "PhysVol_World", logVol_World, 0, 
                       false, copyNum_World);

// Define 'Water Box'
   // Define the shape of solid
   G4double leng_X_WaterBox = 10.0*cm;     // X-full-length of water box 
   G4double leng_Y_WaterBox = 10.0*cm;     // Y-full-length of water box 
   G4double leng_Z_WaterBox =  4.0*cm;     // Z-full-length of water box 
   G4Box* solid_WaterBox = 
     new G4Box( "Solid_WaterBox", leng_X_WaterBox/2.0, leng_Y_WaterBox/2.0, leng_Z_WaterBox/2.0 );

   // Define logical volume
   G4Material* materi_WaterBox = materi_Man->FindOrBuildMaterial("G4_WATER");
   G4LogicalVolume* logVol_WaterBox = 
     new G4LogicalVolume( solid_WaterBox, materi_WaterBox, "LogVol_WaterBox", 0, 0, 0 );

   // Placement of logical volume
   G4double pos_X_LogV = 0.0*cm;           // X-location LogV 
   G4double pos_Y_LogV = 0.0*cm;           // Y-location LogV
   G4double pos_Z_LogV = 0.0*cm;           // Z-location LogV
   G4ThreeVector threeVect_LogV = G4ThreeVector(pos_X_LogV, pos_Y_LogV, pos_Z_LogV);
   G4RotationMatrix rotMtrx_LogV = G4RotationMatrix();
   G4Transform3D trans3D_LogV = G4Transform3D(rotMtrx_LogV, threeVect_LogV);

   G4int copyNum_LogV = 1000;                // Set ID number of LogV
   new G4PVPlacement(trans3D_LogV, "PhysVol_WaterBox", logVol_WaterBox, physVol_World, 
                     false, copyNum_LogV);

// Return the physical world
   return physVol_World;
}
