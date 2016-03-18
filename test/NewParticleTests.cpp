#include "../src/Particles/NewParticle.h"
#include "gtest/gtest.h"

using namespace SAPHRON;

TEST(Particle, DefaultBehavior)
{
	// Test basic methods, getters and setters.
	Site site1, site2;
	site1.position = {1, 1, 2};
	site2.position = {1, 1, 4};

	NewParticle particle(0, {&site1, &site2});

	Vector3 pos{1,1,3};
	ASSERT_EQ(pos, particle.GetPosition());
	ASSERT_EQ(0, particle.GetCharge());
	ASSERT_EQ(2.0, particle.GetMass());

	// Test positions.
	particle.SetPosition(1, {1, 1, 6});
	pos[2] = 4;
	ASSERT_EQ(pos, particle.GetPosition());

	pos = {0, 0, 0};
	particle.SetPosition(pos);
	ASSERT_EQ(pos, particle.GetPosition());
	pos = {0, 0, -2};
	ASSERT_EQ(pos, particle.GetPosition(0));
	pos = {0, 0, 2};
	ASSERT_EQ(pos, particle.GetPosition(1));

	// Test charge calculation.
	particle.SetCharge(0, 2);
	ASSERT_EQ(2, particle.GetCharge());
	ASSERT_EQ(2, particle.GetCharge(0));
	ASSERT_EQ(0, particle.GetCharge(1));

	// Test directors.
	Vector3 dir1 = {0, 0, 1};
	ASSERT_EQ(dir1, particle.GetDirector(0));
	ASSERT_EQ(dir1, particle.GetDirector(1));
	dir1 = {1, 0, 0};
	particle.SetDirector(1, dir1);
	ASSERT_EQ(dir1, particle.GetDirector(1));

	// Test mass.
	particle.SetMass(0, 3);
	particle.SetMass(1, 2);
	ASSERT_EQ(5, particle.GetMass());

	ASSERT_EQ(0, particle.GetSpecies());
	ASSERT_FALSE(particle.IsBonded(0, 0));
	ASSERT_FALSE(particle.IsBonded(0, 1));
	ASSERT_FALSE(particle.IsBonded(1, 1));
	particle.AddBond(0, 1);
	ASSERT_TRUE(particle.IsBonded(0, 1));
	ASSERT_EQ(2, particle.SiteCount());

	// Test "copy" constructor.
	std::vector<Site> sites;
	NewParticle particle2(particle, sites);

	ASSERT_EQ(particle2.GetPosition(), particle.GetPosition());
	ASSERT_EQ(particle2.GetCharge(), particle.GetCharge());
	ASSERT_EQ(particle2.GetMass(), particle.GetMass());
	ASSERT_EQ(particle2.GetSpecies(), particle.GetSpecies());
	ASSERT_EQ(particle2.GetBonds(), particle.GetBonds());
	ASSERT_EQ(particle2.SiteCount(), particle.SiteCount());

	ASSERT_EQ(site1.position, sites[0].position);
	ASSERT_EQ(site1.director, sites[0].director);
	ASSERT_EQ(site1.species, sites[0].species);
	ASSERT_EQ(site1.charge, sites[0].charge);
	ASSERT_EQ(site1.mass, sites[0].mass);

	ASSERT_EQ(site2.position, sites[1].position);
	ASSERT_EQ(site2.director, sites[1].director);
	ASSERT_EQ(site2.species, sites[1].species);
	ASSERT_EQ(site2.charge, sites[1].charge);
	ASSERT_EQ(site2.mass, sites[1].mass);
}