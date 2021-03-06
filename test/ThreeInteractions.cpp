#include "../src/ForceFields/DebyeHuckelFF.h"
#include "../src/ForceFields/FENEFF.h"
#include "../src/ForceFields/LennardJonesFF.h"
#include "../src/ForceFields/ForceFieldManager.h"
#include "../src/Particles/Particle.h"

#include "gtest/gtest.h"

using namespace SAPHRON;

TEST(ThreeInteractions, DefaultBehavior)
{
	DebyeHuckelFF ffe(0.001, {100.0});
	FENEFF ffb(2,2.5,8,10);
	LennardJonesFF ffnb(5,1.5,{100.0});

	Particle* s1 = new Particle({0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, "L1");
	s1->SetCharge(true);
	Particle* s2 = new Particle({1.5, 1.5, 0.0}, {0.0, 0.0, 0.0}, "L2");
	Particle* s3 = new Particle({3.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, "L1");
	s3->SetCharge(true);
	
	Particle* s4 = new Particle({0.0, 0.0, 2.0}, {0.0, 0.0, 0.0}, "L1");
	s4->SetCharge(true);
	Particle* s5 = new Particle({1.5, 1.5, 2.0}, {0.0, 0.0, 0.0}, "L2");
	s5->SetCharge(true);
	Particle* s6 = new Particle({3.0, 0.0, 2.0}, {0.0, 0.0, 0.0}, "L2");

	s1->AddBondedNeighbor(s2);
	s2->AddBondedNeighbor(s1);
	s2->AddBondedNeighbor(s3);
	s3->AddBondedNeighbor(s2);
	
	s4->AddBondedNeighbor(s5);
	s5->AddBondedNeighbor(s4);
	s5->AddBondedNeighbor(s6);
	s6->AddBondedNeighbor(s5);

	s1->AddNeighbor(s4);
	s1->AddNeighbor(s5);
	s1->AddNeighbor(s6);

	s2->AddNeighbor(s4);
	s2->AddNeighbor(s5);
	s2->AddNeighbor(s6);

	s3->AddNeighbor(s4);
	s3->AddNeighbor(s5);
	s3->AddNeighbor(s6);

	s4->AddNeighbor(s1);
	s4->AddNeighbor(s2);
	s4->AddNeighbor(s3);
	
	s5->AddNeighbor(s1);
	s5->AddNeighbor(s2);
	s5->AddNeighbor(s3);
	
	s6->AddNeighbor(s1);
	s6->AddNeighbor(s2);
	s6->AddNeighbor(s3);

	Particle m("M1");

	Particle m2("M2");

	m.AddNeighbor(&m2);
	m.AddChild(s1);
	m.AddChild(s2);
	m.AddChild(s3);

	m2.AddNeighbor(&m);
	m2.AddChild(s4);
	m2.AddChild(s5);
	m2.AddChild(s6);


	ForceFieldManager ffm;

	ffm.SetElectrostaticForcefield(ffe);
	
	ffm.AddNonBondedForceField("L1", "L1", ffnb);
	ffm.AddNonBondedForceField("L2", "L1", ffnb);
	ffm.AddNonBondedForceField("L2", "L2", ffnb);
	
	ffm.AddBondedForceField("L1", "L1", ffb);
	ffm.AddBondedForceField("L2", "L1", ffb);
	ffm.AddBondedForceField("L2", "L2", ffb);

	CompositionList compositions;

	// Validate test for a molecule and for a single atom
	auto NB = ffm.EvaluateEnergy(m);
	auto NB2 = ffm.EvaluateEnergy(*s1);

	ASSERT_NEAR(0.8410, NB2.energy.interelectrostatic, 1e-3);
	ASSERT_NEAR(0.332335, NB2.energy.intraelectrostatic, 1e-3);

	ASSERT_NEAR(-3.3932724443, NB2.energy.intervdw, 1e-3);
	ASSERT_NEAR(-0.3076171875, NB2.energy.intravdw, 1e-3);

	ASSERT_NEAR(56.4083121427, NB2.energy.bonded, 1e-3);

	ASSERT_NEAR(1.45935, NB.energy.interelectrostatic, 1e-3);
	ASSERT_NEAR(0.332335, NB.energy.intraelectrostatic,1e-3);

	ASSERT_NEAR(-10.4407366487, NB.energy.intervdw, 1e-3);
	ASSERT_NEAR(-0.3076171875, NB.energy.intravdw, 1e-3);
	
	ASSERT_NEAR(112.8166242855, NB.energy.bonded, 1e-3);
}
