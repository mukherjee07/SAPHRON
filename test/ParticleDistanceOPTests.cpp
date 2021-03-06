#include "../src/DensityOfStates/ParticleDistanceOP.h"
#include "../src/Particles/Particle.h"
#include "../src/Worlds/World.h"
#include "../src/Utils/Histogram.h"
#include "gtest/gtest.h"

using namespace SAPHRON;

TEST(ParticleDistanceOP, DefaultBehavior)
{
	World world(10., 10., 10., 1.0, 1.0);

	Particle s1({-1, 1, 0}, {0.0, 0.0, 0.0}, "S1");
	Particle s2({-1, -1, 0}, {0.0, 0.0, 0.0}, "S1");
	Particle s3({1, -1, 0}, {0.0, 0.0, 0.0}, "S1");
	Particle s4({1, 1, 0}, {0.0, 0.0, 0.0}, "S1");

	Histogram hist(0, 10, 200);
	ParticleDistanceOP op(hist, {&s1, &s2}, {&s3, &s4});
	ASSERT_EQ(2.0, op.EvaluateOrderParameter(world));
}