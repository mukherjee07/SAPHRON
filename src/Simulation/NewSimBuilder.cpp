#include "NewSimBuilder.h"

using namespace std;

namespace SAPHRON
{
	int DumpErrorsToConsole(const vector<string>& msgs, int notw)
	{
		cout << setw(notw) << right << "\033[1;31mError(s)! See below.\033[0m\n";
		for(auto& msg : msgs)
				cout << " * " << msg << "\n";
		return -1;
	}

	void DumpNoticesToConsole(const vector<string>& msgs, string prefix, int notw)
	{
		cout << setw(notw) << right << "\033[32mOK!\033[0m\n";
		if(msgs.size() == 0)
			return;
		
		for(auto& msg : msgs)
			cout << prefix << " * " << msg << "\n";
	}

	bool NewSimBuilder::BuildSimulation(istream& is)
	{
		Json::Reader reader;
		Json::Value root;
		vector<string> notices;

		// Parse JSON.
		cerr << setw(_msgw) << left << " > Validating JSON...";
		if(!reader.parse(is, root))
		{
			DumpErrorsToConsole({reader.getFormattedErrorMessages()}, _notw);
			return false;
		}
		cout << setw(_notw) << right << "\033[32mOK!\033[0m\n";

		// Build world(s).
		cerr << setw(_msgw) << left << " > Building world(s)...";
		for(auto& jworld : root["worlds"])
		{
			try{
				auto* world = World::Build(jworld);
				_worlds.push_back(world);

				// Print notices.
				notices.push_back("Built world \"" + world->GetStringID() + "\".");
				auto dim = world->GetBoxVectors();
				notices.push_back("Setting size to [" +  
					to_string(dim[0]) + ", " + 
					to_string(dim[1]) + ", " + 
					to_string(dim[2]) + "] \u212B.");
				
				notices.push_back("Setting neighbor list radius to " + 
					to_string(world->GetNeighborRadius()) + 
					" \u212B.");

				notices.push_back("Setting seed to " + 
					to_string(world->GetSeed()) + ".");

				// Make sure some particles were initialized.
				if(world->GetParticleCount() == 0)
				{
					DumpErrorsToConsole({"No particles have been specified."}, _notw);
					return false;
				}

				// Write particle species notices.
				auto& slist = Particle::GetSpeciesList();
				for(auto& s : world->GetComposition())
					notices.push_back("Initialized " + to_string(s.second) + 
							  " particle(s) of type \"" + slist[s.first] + "\".");
				
			} catch(BuildException& e) {
				DumpErrorsToConsole(e.GetErrors(), _notw);
				return false;
			} catch(exception& e) {
				DumpErrorsToConsole({e.what()}, _notw);
				return false;
			}
		}

		if(_worlds.size() == 0)
		{
			DumpErrorsToConsole({"No worlds have been specified."}, _notw);
			return false;
		}
		DumpNoticesToConsole(notices, "",_notw);
		notices.clear();

		// Build forcefield(s).
		cerr << setw(_msgw) << left << " > Building forcefield(s)...";
		try{
			ForceField::BuildForceFields(
					root.get("forcefields", Json::arrayValue), 
					&_ffm, 
					_forcefields);
		} catch(BuildException& e) {
			DumpErrorsToConsole(e.GetErrors(), _notw);
			return false;
		} catch(exception& e) {
			DumpErrorsToConsole({e.what()}, _notw);
			return false;
		}

		// Make sure we've created forcefields.
		if(_forcefields.size() == 0)
		{
			DumpErrorsToConsole({"No forcefields have been specified."}, _notw);
			return false;
		}

		//TODO: ADD FORCEFIELD INITIALIZATION MESSAGE
		DumpNoticesToConsole(notices, "",_notw);
		notices.clear();

		// Build move(s).
		cerr << setw(_msgw) << left << " > Building move(s)...";
		try{
			Move::BuildMoves(root.get("moves", Json::arrayValue), &_mm, _moves);
		} catch(BuildException& e) {
			DumpErrorsToConsole(e.GetErrors(), _notw);
			return false;
		} catch(exception& e) {
			DumpErrorsToConsole({e.what()}, _notw);
			return false;
		}

		// Make sure we've created moves.
		if(_moves.size() == 0)
		{
			DumpErrorsToConsole({"No moves have been specified."}, _notw);
			return false;
		}


		DumpNoticesToConsole(notices, "",_notw);
		notices.clear();

		return true;
	}
}