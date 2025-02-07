#pragma once
#include "SingleAgentSolver.h"

class PP
{
public:
	/////////////////////////////////////////////////////////////////////////////////////
	// stats
	double runtime = 0;
	double runtime_generate_child = 0; // runtimr of generating child nodes
	double runtime_build_CT = 0; // runtimr of building constraint table
	double runtime_build_CAT = 0; // runtime of building conflict avoidance table
	double runtime_path_finding = 0; // runtime of finding paths for single agents
	double runtime_detect_conflicts = 0;
	double runtime_preprocessing = 0; // runtime of building heuristic table for the low level

	uint64_t num_HL_expanded = 0;
	uint64_t num_HL_generated = 0;
	uint64_t num_LL_expanded = 0;
	uint64_t num_LL_generated = 0;
	uint64_t num_of_restart = 0;

	bool solution_found = false;
	int solution_cost = -2;

	PP(const Instance& instance, bool sipp, int screen);
	~PP(){}

	// Runs the algorithm until the problem is solved or time is exhausted 
	bool solve(double time_limit);
	void clearSearchEngines();

	// Save results
	void saveResults(const string &fileName, const string &instanceName) const;
    void savePaths(const string &fileName) const; // write the paths to a file
	void clear(); // used for rapid random  restart

private:
	conflict_selection conflict_seletion_rule;
    string getSolverName() const;

	int screen;
	double time_limit;
	int node_limit = MAX_NODES;
	clock_t start;
	int num_of_agents;
	int num_of_cols;
	int map_size;

    vector<int> ordered_agents;
	vector<Path*> paths;
	vector <SingleAgentSolver*> search_engines;  // used to find (single) agents' paths and mdd

    int getSumOfCosts() const;

	// print and save
	void printResults() const;

	bool validateSolution() const;
	inline int getAgentLocation(int agent_id, size_t timestep) const;

	// high level search
	void printPaths() const;
	void printAgentPath(int i) const;
};
