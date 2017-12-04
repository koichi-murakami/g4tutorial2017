//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Geometry.cc
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "Geometry.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4VPhysicalVolume.hh"

#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4NistManager.hh"
#include "G4VisAttributes.hh"
#include "G4SystemOfUnits.hh"

#include "SensitiveVolume.hh"
#include "G4SDManager.hh"
//------------------------------------------------------------------------------
  Geometry::Geometry() {}
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
  Geometry::~Geometry() {}
//------------------------------------------------------------------------------

/////// 実装必須のConstruct()
// 最後に物理ワールドへのポインタを返す

//------------------------------------------------------------------------------
  G4VPhysicalVolume* Geometry::Construct()
//------------------------------------------------------------------------------
{
// 'Material Manager'へのポインタを取得する
   auto materi_Man = G4NistManager::Instance();

//////// 'World Volume'　を定義する
   // ステップ１　箱と寸法を定義する
   G4double leng_X_World = 2.0*m;         // X-full-length of world 
   G4double leng_Y_World = 2.0*m;         // Y-full-length of world 
   G4double leng_Z_World = 2.0*m;         // Z-full-length of world 
   auto solid_World = 
     new G4Box("Solid_World", leng_X_World/2.0, leng_Y_World/2.0, leng_Z_World/2.0);

   // ステップ２　箱を用いてlogical volume論理物体を作る
   auto materi_World = materi_Man->FindOrBuildMaterial("G4_AIR");
   auto logVol_World = 
     new G4LogicalVolume(solid_World, materi_World, "LogVol_World");
   logVol_World->SetVisAttributes (G4VisAttributes::Invisible);

   // ステップ３　logical volumeを配置する
   G4int copyNum_World = 0;               // Set ID number of world
   auto physVol_World  = 
     new G4PVPlacement(G4Transform3D(), "PhysVol_World", logVol_World, 0, 
                       false, copyNum_World);

/////// 'Pixcel Detector'の定義
// 段取りA Global Envelop　全ピクセル検出器の容れ物を用意する
   // ステップ A-１　global envelop　の箱と寸法
   G4double leng_X_PixEnvG = 16.8*mm;     // X-full-length of pixel: global envelop 
   G4double leng_Y_PixEnvG = 20.0*mm;     // Y-full-length of pixel: global envelop 
   G4double leng_Z_PixEnvG =  0.2*mm;     // Z-full-length of pixel: global envelop 
   auto solid_PixEnvG = 
     new G4Box("Solid_PixEnvG", leng_X_PixEnvG/2.0, leng_Y_PixEnvG/2.0, leng_Z_PixEnvG/2.0);

   // ステップ A-２　Define logical volume of the global envelop
   auto materi_PixEnvG = materi_Man->FindOrBuildMaterial("G4_AIR");
   auto logVol_PixEnvG = 
     new G4LogicalVolume(solid_PixEnvG, materi_PixEnvG, "LogVol_PixEnvG");
    //  論理物体に自前の可視化属性を付けるかどうかは選択できる
    //  logVol_PixEnvG->SetVisAttributes (G4VisAttributes::Visible);

   // ステップ A-３　Placement of the global envelop to the world
   G4double pos_X_LogV_PixEnvG = 0.0*cm;       // X-location LogV_PixEnvG 
   G4double pos_Y_LogV_PixEnvG = 0.0*cm;       // Y-location LogV_PixEnvG
   G4double pos_Z_LogV_PixEnvG = 0.0*cm;       // Z-location LogV_PixEnvG
   auto threeVect_LogV_PixEnvG = 
   G4ThreeVector(pos_X_LogV_PixEnvG, pos_Y_LogV_PixEnvG, pos_Z_LogV_PixEnvG);
   auto rotMtrx_LogV_PixEnvG = G4RotationMatrix();
   auto trans3D_LogV_PixEnvG = G4Transform3D(rotMtrx_LogV_PixEnvG, threeVect_LogV_PixEnvG);

   G4int copyNum_LogV_PixEnvG = 1000;                // Set ID number of LogV_PixEnvG
   new G4PVPlacement(trans3D_LogV_PixEnvG, "PhysVol_PixEnvG", logVol_PixEnvG, physVol_World, 
                     false, copyNum_LogV_PixEnvG);

// 段取りB Local Envelop (the global envelop をY軸方法へ分割)
   // ステップ B-１　Define the shape of the local envelop
   G4int nDiv_Y = 80;                                 // Number of divisions in Y-direction 
   auto leng_X_PixEnvL = leng_X_PixEnvG;          // X-full-length of pixel: local envelop 
   auto leng_Y_PixEnvL = leng_Y_PixEnvG/nDiv_Y;   // Y-full-length of pixel: local envelop 
   auto leng_Z_PixEnvL = leng_Z_PixEnvG;          // Z-full-length of pixel: local envelop 
   auto solid_PixEnvL = 
     new G4Box("Solid_PixEnvL", leng_X_PixEnvL/2.0, leng_Y_PixEnvL/2.0, leng_Z_PixEnvL/2.0);

   // ステップ B-２　Define logical volume of the local envelop
   auto materi_PixEnvL = materi_Man->FindOrBuildMaterial("G4_AIR");
   auto logVol_PixEnvL = 
     new G4LogicalVolume(solid_PixEnvL, materi_PixEnvL, "LogVol_PixEnvL");
   logVol_PixEnvL->SetVisAttributes (G4VisAttributes::Invisible);

   // ステップ B-３　the local envelop を the global envelop の中へ Replicaを使って配置する
   new G4PVReplica("PhysVol_PixEnvL", logVol_PixEnvL, logVol_PixEnvG, kYAxis,  
                   nDiv_Y, leng_Y_PixEnvL); 

// 段取りC　 Pixcel Element ( the local envelop をX軸方向へ分割)
   // ステップ C-１　Define the shape of the pixcel element
   G4int nDiv_X = 336;                                 // Number of divisions in Y-direction 
   auto leng_X_PixElmt = leng_X_PixEnvG/nDiv_X;    // X-full-length of pixel: pixcel element 
   auto leng_Y_PixElmt = leng_Y_PixEnvG/nDiv_Y;    // Y-full-length of pixel: pixcel element 
   auto leng_Z_PixElmt = leng_Z_PixEnvG;           // Z-full-length of pixel: pixcel element 
   auto solid_PixElmt = 
     new G4Box("Solid_PixElmt", leng_X_PixElmt/2.0, leng_Y_PixElmt/2.0, leng_Z_PixElmt/2.0);

   // ステップ C-２　Define logical volume of the pixcel element
   auto materi_PixElmt = materi_Man->FindOrBuildMaterial("G4_SILICON_DIOXIDE");
   auto logVol_PixElmt = 
     new G4LogicalVolume(solid_PixElmt, materi_PixElmt, "LogVol_PixElmt");
    logVol_PixElmt->SetVisAttributes (G4VisAttributes::Invisible);


   // ステップ C-３　Placement of pixcel elements to the local envelop using Replica
   new G4PVReplica("PhysVol_PixElmt", logVol_PixElmt, logVol_PixEnvL, kXAxis,  
                   nDiv_X, leng_X_PixElmt);

/////// 有感検出器

    auto aSV = new SensitiveVolume("SensitiveVolume");
    logVol_PixElmt->SetSensitiveDetector(aSV);         // Add sensitivity to the logical volume
    auto SDman = G4SDManager::GetSDMpointer();
    SDman->AddNewDetector(aSV);
/****************************************************************************************   
/////// ビームパイプ　Beam pipe
   auto material_BeamPipe = materi_Man->FindOrBuildMaterial("G4_Be");      //ベリリューム
   auto material_Vacuum = materi_Man->FindOrBuildMaterial("G4_Galactic");   // 真空

   G4double innerRadius = 5. * mm/2.0;
   G4double outerRadius = 5.3 * mm/2.0;
   G4double lengZpipe  = 1.0 * m/2.0;
   G4double twopi = 2.0 * 3.141592653589793238;

   auto  solid_InnerPipe = new G4Tubs("InnerPipe", 0., innerRadius, lengZpipe, 0., twopi);
   auto  solid_VacuumPipe = new G4Tubs("VacuumPipe", innerRadius, outerRadius,lengZpipe,  0., twopi);

   auto log_InnerPipe = new G4LogicalVolume(solid_InnerPipe, material_Vacuum, "log_InnerPipe");
   auto log_VacuumPipe = new G4LogicalVolume(solid_VacuumPipe, material_BeamPipe, "log_VacuumPipe");

   // Placement of the Beam pipe to the world
   G4double pos_X_BeamPipe = 0.0*cm;          // X-location
   G4double pos_Y_BeamPipe = 0.0*cm;          // Y-location
   G4double pos_Z_BeamPipe = -5.0*cm;       // Z-location
   auto threeVect_BeamPipe = G4ThreeVector(pos_X_BeamPipe, pos_Y_BeamPipe, pos_Z_BeamPipe);
   auto rotMtrx_BeamPipe = G4RotationMatrix();
    rotMtrx_BeamPipe.rotateX(90.*degree);
    auto trans3D_BeamPipe = G4Transform3D(rotMtrx_BeamPipe, threeVect_BeamPipe);
   
   G4int copyNum_BeamPipe = 2000;       // Set ID number
   new G4PVPlacement(trans3D_BeamPipe, "PhysVol_InnerPipe", log_InnerPipe, physVol_World, false, copyNum_BeamPipe);
   new G4PVPlacement(trans3D_BeamPipe, "PhysVol_VacuumPipe", log_VacuumPipe, physVol_World,false, copyNum_BeamPipe);
*****************************************************************************************/
    
/////// Return the physical world
   return physVol_World;
}
