#include "SimBuilder.h"

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

	void PrintBoldNotice(const string& notice, int msgw)
	{
		cerr << setw(msgw + 8) << left << "\033[1m" + notice + "\033[0m";
	}

	bool SimBuilder::BuildSimulation(istream& is)
	{
		Json::Reader reader;
		Json::Value root;
		vector<string> notices;

		// Parse JSON.
		PrintBoldNotice(" > Validating JSON...", _msgw);

		if(!reader.parse(is, root))
		{
			DumpErrorsToConsole({reader.getFormattedErrorMessages()}, _notw);
			return false;
		}
		cout << setw(_notw) << right << "\033[32mOK!\033[0m\n";

		// Build world(s).
		PrintBoldNotice(" > Building world(s)...", _msgw); 
		for(auto& jworld : root["worlds"])
		{
			try{
				auto* world = World::Build(jworld);
				_worlds.push_back(world);

				// Add world to world manager.
				_wm.AddWorld(world);

				// Print notices.
				notices.push_back("Building world \"" + world->GetStringID() + "\"...");
				auto dim = world->GetHMatrix();

				notices.push_back("Setting size to [" +  
					to_string(dim(0,0)) + ", " + 
					to_string(dim(1,1)) + ", " + 
					to_string(dim(2,2)) + "] \u212B.");
				
				notices.push_back("Setting neighbor list radius to " + 
					to_string(world->GetNeighborRadius()) + 
					" \u212B.");

				notices.push_back("Setting cutoff radius to " + 
					to_string(world->GetCutoffRadius()) + 
					" \u212B.");

				notices.push_back("Setting seed to " + 
					to_string(world->GetSeed()) + ".");

				notices.push_back("Setting temperature to " + 
					to_string(world->GetTemperature()) + "K.");

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
		PrintBoldNotice(" > Building forcefield(s)...", _msgw); 
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

		notices.push_back("Initialized " +  to_string(_forcefields.size()) + " forcefield(s).");

		DumpNoticesToConsole(notices, "",_notw);
		notices.clear();

		// Build move(s).
		PrintBoldNotice(" > Building move(s)...", _msgw); 
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

		for(auto& m : _moves)
			notices.push_back("Initialized " + m->GetName() + " move.");

		DumpNoticesToConsole(notices, "",_notw);
		notices.clear();

		// Build observers.
		PrintBoldNotice(" > Building observer(s)...", _msgw); 
		try{
			SimObserver::BuildObservers(root.get("observers", Json::arrayValue), _observers);
		} catch(BuildException& e) {
			DumpErrorsToConsole(e.GetErrors(), _notw);
			return false;
		} catch(exception& e) {
			DumpErrorsToConsole({e.what()}, _notw);
			return false;
		}

		// Make sure we've created at least one observer.
		if(_observers.size() == 0)
		{
			DumpErrorsToConsole({"No observers have been specified."}, _notw);
			return false;
		}

		for(auto& o : _observers)
		{
			notices.push_back("Initialized " + o->GetName() + " observer.");
			notices.push_back("Set sampling frequency to " + to_string(o->GetFrequency()) +  " sweeps.");
		}

		DumpNoticesToConsole(notices, "",_notw);
		notices.clear();

		if(root.isMember("histogram")) 
		{
			PrintBoldNotice(" > Building histogram...", _msgw); 
			try{
				_hist = Histogram::BuildHistogram(root["histogram"]);
			} catch(BuildException& e) {
				DumpErrorsToConsole(e.GetErrors(), _notw);
				return false;
			} catch(exception& e) {
				DumpErrorsToConsole({e.what()}, _notw);
				return false;
			}

			notices.push_back("Initialized histogram range [" + 
				to_string(_hist->GetMinimum()) + ", " + 
				to_string(_hist->GetMaximum()) + "].");
			notices.push_back("Created " + to_string(_hist->GetBinCount()) + " bins.");

			DumpNoticesToConsole(notices, "",_notw);
			notices.clear();
		}

		if(root.isMember("orderparameter"))
		{
			PrintBoldNotice(" > Building order parameter...", _msgw);
			try{
				_orderp = DOSOrderParameter::Build(root["orderparameter"], _hist, &_wm);
			} catch(BuildException& e) {
				DumpErrorsToConsole(e.GetErrors(), _notw);
				return false;
			} catch(exception& e) {
				DumpErrorsToConsole({e.what()}, _notw);
				return false;
			}

			DumpNoticesToConsole(notices, "",_notw);
			notices.clear();
		}

		// Build simulation.
		PrintBoldNotice(" > Building simulation...", _msgw);
		try{
			_sim = Simulation::BuildSimulation(root, &_wm, &_ffm, &_mm, _orderp, _hist);

			// Add observers.
			for(auto& o  : _observers)
				_sim->AddObserver(o);

		} catch(BuildException& e) {
			DumpErrorsToConsole(e.GetErrors(), _notw);
			return false;
		} catch(exception& e) {
			DumpErrorsToConsole({e.what()}, _notw);
			return false;
		}

		DumpNoticesToConsole(notices, "",_notw);
		notices.clear();

		return true;
	}
}