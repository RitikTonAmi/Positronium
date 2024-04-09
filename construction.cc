// #include "construction.hh"
// // #include "detector.hh"
// #include "G4OpticalSurface.hh"

// MyDetectorConstruction::MyDetectorConstruction()
// {}

// MyDetectorConstruction::~MyDetectorConstruction()
// {}

// G4VPhysicalVolume *MyDetectorConstruction::Construct()
// {
//     G4NistManager *nist=G4NistManager::Instance();

//     G4Material *H2 = new G4Material("H2", 0.08375*kg/m3, 1);
//     H2->AddElement(nist->FindOrBuildElement("H"), 2);

//     G4double energy[2] = {1.23984*eV/0.9, 1.23984*eV/0.2};
//     G4double rindexWorld[2] = {1.0, 1.0};
//     G4double rindexNaI[2] = {1.78, 1.78};


//     G4Material *worldMat = nist->FindOrBuildMaterial("G4_Galactic");

//     G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
//     mptWorld->AddProperty("RINDEX", energy, rindexWorld, 2);

//     G4Material *NaI = new G4Material("NaI", 3.67*g/cm3, 2);
//     NaI->AddElement(nist->FindOrBuildElement("Na"), 1);
//     NaI->AddElement(nist->FindOrBuildElement("I"), 1);

//     G4double fraction[2] = {1.0, 1.0};
//     G4double reflectivity[2] = {1.0, 1.0};

//     G4MaterialPropertiesTable *mptNaI = new G4MaterialPropertiesTable();
//     mptNaI->AddProperty("RINDEX", energy, rindexNaI, 2);
//     mptNaI->AddProperty("SCINTILLATIONCOMPONENT1", energy, fraction, 2);
//     mptNaI->AddConstProperty("SCINTILLATIONYIELD",38./keV);
//     mptNaI->AddConstProperty("RESOLUTIONSCALE",1.0);
//     mptNaI->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 250.*ns);
//     mptNaI->AddConstProperty("SCINTILLATIONYIELD1",1.);
//     NaI->SetMaterialPropertiesTable(mptNaI);

//     worldMat->SetMaterialPropertiesTable(mptWorld);

//     G4OpticalSurface *mirrorSurface = new G4OpticalSurface("mirrorSurface");

//     mirrorSurface->SetType(dielectric_metal);
//     mirrorSurface->SetFinish(ground);
//     mirrorSurface->SetModel(unified);

//     G4MaterialPropertiesTable *mptMirror = new G4MaterialPropertiesTable();
//     mptMirror->AddProperty("REFLECTIVITY", energy, reflectivity, 2);

//     mirrorSurface->SetMaterialPropertiesTable(mptMirror);

//     // World
//     G4Box *solidWorld= new G4Box("solidWorld", 0.5*m, 0.5*m, 0.5*m);
//     G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
//     G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);

//     // Target
//     G4Box *solidRadiator = new G4Box("solidRadiator", 0.3*m, 0.3*m, 0.01*m);
//     G4LogicalVolume *logicRadiator = new G4LogicalVolume(solidRadiator, H2, "logicalRadiator");
//     G4VPhysicalVolume *physRadiator = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.25*m), logicRadiator, "physRadiator", logicWorld, false, 0, true);


//     G4Box *solidScintillator = new G4Box("solidScintillator", 5*cm, 5*cm, 6*cm);
//     G4LogicalVolume *logicScintillator = new G4LogicalVolume(solidScintillator, NaI, "logicalScintillator");
//     G4LogicalSkinSurface *skin = new G4LogicalSkinSurface("skin", logicWorld, mirrorSurface);

//     G4Box *solidDetector = new G4Box("solidDetector", 1.*cm, 5.*cm, 6*cm);

//     G4LogicalVolume *logicDetector = new G4LogicalVolume(solidDetector, worldMat, "logicDetector");
    
//     for (G4int i = 0; i < 6; i++)
//     {
//         for(G4int j = 0; j < 24; j++)
//         {
//             G4Rotate3D rotZ(j*22.5*deg, G4ThreeVector(0,0,1));
//             G4Translate3D transXScint(G4ThreeVector(5./tan(22.5/2*deg)*cm+5.*cm,0*cm,-40*cm + i*15*cm));
//             G4Transform3D transformScint = (rotZ)*(transXScint);

//             G4Translate3D transXDet(G4ThreeVector(5./tan(22.5/2*deg)*cm+6.*cm + 8.*cm,0*cm,-40*cm + i*15*cm));
//             G4Transform3D transformDet = (rotZ)*(transXDet);
            
//             G4VPhysicalVolume *physScintillator = new G4PVPlacement(transformScint, logicScintillator, "physScintillator", logicWorld, false, 0 ,true);
//             G4VPhysicalVolume *physDet = new G4PVPlacement(transformDet, logicScintillator, "physDet", logicWorld, false, 0 ,true);
//             G4cout << "Det Amaan: " << physDet << G4endl;

//         }
//     }

//     return physWorld;
// }

// // void MyDetectorConstruction::ConstructSDandField()
// // {
// //     MySensitiveDetector *sensDet = new MySensitiveDetector("SensitiveDetector");

// //     logicDetector->SetSensitiveDetector(sensDet);
// // }

// SECOND ATTEMPT:
#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{

    nCols = 10;
    nRows = 10;

    fMessenger = new G4GenericMessenger(this, "/detector/", "Detector Construction");

    fMessenger->DeclareProperty("nCols", nCols, "Number of cols");
    fMessenger->DeclareProperty("nRows", nRows, "Number of rows");
    fMessenger->DeclareProperty("scintillator", isScintillator, "Construct Scintillator");

    DefineMaterials();

    isScintillator = true;

    xWorld = 40.*km;
    yWorld = 40.*km;
    zWorld = 20.*km;}

MyDetectorConstruction::~MyDetectorConstruction()
{}

void MyDetectorConstruction::DefineMaterials()
{
    G4NistManager *nist = G4NistManager::Instance();

    G4Material *worldMat = nist->FindOrBuildMaterial("G4_Galactic");

    G4Material *H2 = new G4Material("H2", 0.08375*kg/m3, 1);
    H2->AddElement(nist->FindOrBuildElement("H"), 2);


    G4double energy[2] = {1.239841939*eV/0.9 , 1.239841939*eV/0.2};
    G4double rindexWorld[2] = {1.0, 1.0};
    G4double rindexNaI[2] = {1.78, 1.78};

    G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
    mptWorld->AddProperty("RINDEX", energy, rindexWorld, 2);

    G4Element *Na = nist->FindOrBuildElement("Na");
    G4Element *I = nist->FindOrBuildElement("I");
    G4Material *NaI = new G4Material("NaI", 3.67*g/cm3, 2);
    NaI->AddElement(Na, 1);
    NaI->AddElement(I, 1);

    G4double fraction[2] = {1.0, 1.0};

    G4MaterialPropertiesTable *mptNaI = new G4MaterialPropertiesTable();
    mptNaI->AddProperty("RINDEX", energy, rindexNaI, 2);
    mptNaI->AddProperty("SCINTILLATIONCOMPONENT1", energy, fraction, 2);
    mptNaI->AddConstProperty("SCINTILLATIONYIELD",38./keV);
    mptNaI->AddConstProperty("RESOLUTIONSCALE",1.0);
    mptNaI->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 250.*ns);
    mptNaI->AddConstProperty("SCINTILLATIONYIELD1",1.);

    NaI->SetMaterialPropertiesTable(mptNaI);

    worldMat->SetMaterialPropertiesTable(mptWorld);

    G4OpticalSurface *mirrorSurface = new G4OpticalSurface("mirrorSurface");

    mirrorSurface->SetType(dielectric_metal);
    mirrorSurface->SetFinish(ground);
    mirrorSurface->SetModel(unified);

    G4double reflectivity[2] = {1.0, 1.0};

    G4MaterialPropertiesTable *mptMirror = new G4MaterialPropertiesTable();
    mptMirror->AddProperty("REFLECTIVITY", energy, reflectivity, 2);

    mirrorSurface->SetMaterialPropertiesTable(mptMirror);

}

void MyDetectorConstruction::ConstructScintillator()
{
    DefineMaterials();

    G4Box *solidScintillator = new G4Box("solidScintillator", 5*cm, 5*cm, 6*cm);

    G4LogicalVolume *logicScintillator = new G4LogicalVolume(solidScintillator, NaI, "logicalScintillator");

    G4LogicalSkinSurface *skin = new G4LogicalSkinSurface("skin", logicWorld, mirrorSurface);

    fScoringVolume = logicScintillator;

    G4Box *solidDetector = new G4Box("solidDetector", 1.*cm, 5.*cm, 6*cm);

    G4LogicalVolume *logicDetector = new G4LogicalVolume(solidDetector, worldMat, "logicDetector");

    for(G4int i = 0; i < 6; i++)
    {
        for(G4int j = 0; j < 16; j++)
        {
            G4Rotate3D rotZ(j*22.5*deg, G4ThreeVector(0,0,1));
            G4Translate3D transXScint(G4ThreeVector(5./tan(22.5/2*deg)*cm+5.*cm, 0.*cm, -40.*cm + i*15*cm));
            G4Transform3D transformScint = (rotZ)*(transXScint);

            G4Translate3D transXDet(G4ThreeVector(5./tan(22.5/2*deg)*cm+5.*cm+6.*cm, 0.*cm, -40.*cm + i*15*cm));
            G4Transform3D transformDet = (rotZ)*(transXDet);

            G4PVPlacement *physScintillator = new G4PVPlacement(transformScint, logicScintillator, "physScintillator", logicWorld, false, 0, true);

            G4PVPlacement *physDetector = new G4PVPlacement(transformDet, logicDetector, "physDetector", logicWorld, false, 0, true);
        }
    }
}


G4VPhysicalVolume *MyDetectorConstruction::Construct()
{

    
    G4Box *solidWorld = new G4Box("solidWorld", xWorld, yWorld, zWorld);

    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");

    G4PVPlacement *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);
    
    if(isScintillator)
        ConstructScintillator();

    return physWorld;
}

