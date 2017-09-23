#ifndef _CS_411_HW2_H_
#define _CS_411_HW2_H_

#include <vector>
using std::vector;
#include <iostream>
using std::cout;
using std::endl;
#include <sstream>
using std::ostringstream;
#include <string>
using std::string;

struct Bridge {
	Bridge(int w, int e, int we): 
		west(w), east(e), weight(we) {}

	const string toString() {
		ostringstream out;
		out << this->west << ' ' << this->east << ' ' << this->weight << endl;
		return out.str();
	}

	const bool crosses(const Bridge & other) {
		return (this->west < other.west && this->east > other.east) || (this->west > other.west && this->east < other.east);
	}

	const bool crosses(const vector<Bridge> & bridges) {
		for(auto bridge : bridges)
			if(this->crosses(bridge))
				return true;

		return false;
	}

	const bool connectsToSameCity(const Bridge & other) {
		if(this->west == other.west || this->east == other.east)
			return true;

		return false;
	}

	const bool connectsToSameCity(const vector<Bridge> & bridges) {
		for(auto bridge : bridges)
			if(this->connectsToSameCity(bridge))
				return true;

		return false;
	}

	int west;
	int east;
	int weight;
};

const int addWeights(const vector<Bridge> & bridges) {
	int weight = 0;

	for(auto bridge : bridges)
		weight += bridge.weight;

	return weight;
}

const int findLargestWeight(const vector<Bridge> & bridges, const int & index) {
	vector<Bridge> matches;

	if(index < bridges.size())
		matches.push_back(bridges[index]);
	else return 0;

	for(auto i = index + 1; i < bridges.size(); i++) {
		Bridge bridge = bridges[i];
		if(!bridge.crosses(matches) && !bridge.connectsToSameCity(matches))
			matches.push_back(bridge);
	}

	int weight = addWeights(matches);
	int otherWeights = findLargestWeight(bridges, index + 1);

	if(weight > otherWeights)
		return weight;
	else 
		return otherWeights;
}

const int build(const int & w, const int & e, const vector<vector<int>> & cbs) {
	vector<Bridge> bridges;
	for(auto i = 0; i < cbs.size(); i ++) {
		Bridge newBridge(cbs[i][0], cbs[i][1], cbs[i][2]);
		bridges.push_back(newBridge);
		cout << newBridge.toString();
	}
	
	return findLargestWeight(bridges, 0);
}

#endif
