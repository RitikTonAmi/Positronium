#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4OpticalSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4GenericMessenger.hh"




// #include "detector.hh"


class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
    MyDetectorConstruction();
    ~MyDetectorConstruction();


    virtual G4VPhysicalVolume *Construct();
    void ConstructScintillator();


private:
    G4Box *solidWorld, *solidRadiator, *solidDetector, *solidScintillator, *solidAir;
    G4LogicalVolume *logicWorld, *logicRadiator, *logicDetector, *logicScintillator, *logicAir[10];
    G4VPhysicalVolume *physWorld, *physDetector, *physRadiator, *physScintillator, *physAir[10];

    G4OpticalSurface *mirrorSurface;

    G4Material *worldMat, *NaI, *Air[10];
    G4Element *Na, *I;

    void DefineMaterials();

    G4GenericMessenger *fMessenger;
    

    G4LogicalVolume *fScoringVolume;

    G4int nRows, nCols;

    G4double xWorld, yWorld, zWorld;

    G4bool isScintillator;

    // G4LogicalVolume *logicDetector;
    // virtual void ConstructSDandField();

    // G4LogicalVolume *logicScintillator;
    // virtual void ConstructScintillator();


};

#endif
