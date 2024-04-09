#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
    fParticleGun = new G4ParticleGun(1);
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
    delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
    G4ParticleTable *particleTable=G4ParticleTable::GetParticleTable();
    G4String particleName="e+";
    G4ParticleDefinition *particle=particleTable->FindParticle("e+");
    
    G4ThreeVector pos(0.,0.,-20*km);
    G4ThreeVector mom(0.,0.,1.);

    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(mom);
    fParticleGun->SetParticleMomentum(1000.*eV);
    fParticleGun->SetParticleDefinition(particle);

    fParticleGun->GeneratePrimaryVertex(anEvent);
}  
// void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
// {
//     const G4String name = "e+";
//     G4ParticleTable* pTable = G4ParticleTable::GetParticleTable();
//     G4ParticleDefinition* anInstance = pTable->FindParticle(name);

//     anInstance = new G4ParticleDefinition(
//     name, 0.510998910*MeV, 0.0*MeV, +1.*eplus, 
//                     1,                0,             0,          
//                     0,                0,             0,             
//              "lepton",               -1,             0,          -11,
//                  true,             -1.0,          NULL,
//                 false,              "e"
//                );
  
//      // Bohr Magnetron
//     G4double muB =  0.5*eplus*((6.62606896e-34 * joule*s)/(2*3.14159265358979323846))/(0.510998910*MeV/((2.99792458e+8 * m/s)*(2.99792458e+8 * m/s))) ;
    
//     anInstance->SetPDGMagneticMoment( muB * 2.* 1.0011596521859 );
    
//     G4ThreeVector pos(0.,0.,-20.*km);
//     G4ThreeVector mom(0.,0.,1.);

//     fParticleGun->SetParticlePosition(pos);
//     fParticleGun->SetParticleMomentumDirection(mom);
//     fParticleGun->SetParticleMomentum(100.*GeV);
//     fParticleGun->SetParticleDefinition(anInstance);

//     fParticleGun->GeneratePrimaryVertex(anEvent);
// }