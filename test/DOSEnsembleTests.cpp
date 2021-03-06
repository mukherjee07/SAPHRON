#include "../src/Simulation/DOSSimulation.h"
#include "../src/DensityOfStates/WangLandauOP.h"
#include "../src/ForceFields/ForceFieldManager.h"
#include "../src/ForceFields/LebwohlLasherFF.h"
#include "../src/Moves/MoveManager.h"
#include "../src/Moves/DirectorRotateMove.h"
#include "../src/Particles/Particle.h"
#include "../src/Observers/DLMFileObserver.h"
#include "../src/Worlds/World.h"
#include "../src/Worlds/WorldManager.h"
#include "gtest/gtest.h"

using namespace SAPHRON;

TEST(DOSSimulation, DefaultBehavior)
{
	/*double n = 20;
	// Initialize world.
	World world(n, n, n, 1.0, 1.0);
	Particle site1({0, 0, 0}, {1.0, 0, 0}, "E1");
	world.PackWorld({&site1}, {1.0});

	// Initialize forcefields.
	LebwohlLasherFF ff(1.0, 0);
	ForceFieldManager ffm;
	ffm.AddNonBondedForceField("E1", "E1", ff);

	// Initialize moves.
	DirectorRotateMove move1(33);
	MoveManager mm;
	mm.AddMove(&move1);

	// Initialize observer.
	SimFlags flags;
	flags.simulation_on();
	flags.histogram_on();
	flags.world_on();

	DLMFileObserver co("test", flags, 1000);

	// Initialize histogram. 
	Histogram hist(-1.8*n*n*n, 0.3*n*n*n, 7000);

	// Initialize Wang-Landau order parameter. 
	WangLandauOP op(hist);

	// World manager 
	WorldManager wm;
	wm.AddWorld(&world);

	DOSSimulation ensemble(&wm, &ffm, &mm, &op, &hist);
	ensemble.AddObserver(&co);
	ensemble.Run(20);*/
}