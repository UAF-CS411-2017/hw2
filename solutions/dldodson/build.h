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

	const bool crosses(const Bridge & other) const {
		return (this->west < other.west && this->east > other.east) || (this->west > other.west && this->east < other.east);
	}

	const bool crosses(const vector<Bridge> & bridges) const {
		for(auto bridge : bridges)
			if(this->crosses(bridge))
				return true;

		return false;
	}

	const bool connectsToSameCity(const Bridge & other) const {
		if(this->west == other.west || this->east == other.east)
			return true;

		return false;
	}

	const bool connectsToSameCity(const vector<Bridge> & bridges) const {
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

template <class T>
vector<vector<T>> getSubsets(const vector<T> & initialSet, vector<T> & currentSet, const unsigned int index) {
	vector<vector<T>> subsets;

	if(index >= initialSet.size())
		subsets;
	
	for(auto i = index; i < initialSet.size(); i++) {
		currentSet.push_back(initialSet[index]);
		auto newSubsets = getSubsets(initialSet, currentSet, index + 1);
		subsets.insert(subsets.end(), newSubsets.begin(), newSubsets.end());
		currentSet.pop_back();
		newSubsets = getSubsets(initialSet, currentSet, index + 1);
		subsets.insert(subsets.end(), newSubsets.begin(), newSubsets.end());
	}

	return subsets;
}

const int findLargestWeight(const vector<Bridge> & bridges, vector<Bridge> & workingSet, const int & index) {
	if(index >= bridges.size() || bridges.size() == workingSet.size())
		return 0;
	else if(index == bridges.size() - 1)
		return bridges[index].weight;
	else {
		auto weightOne = 0, weightTwo = 0;

		if(!bridges[index].crosses(workingSet) && !bridges[index].connectsToSameCity(workingSet)) {
			workingSet.push_back(bridges[index]);
			weightOne = findLargestWeight(bridges, workingSet, index + 1);
			workingSet.pop_back();
		}

		weightTwo = findLargestWeight(bridges, workingSet, index + 1);

		return (weightOne > weightTwo ? weightOne:weightTwo);
	}
}

const int build(const int & w, const int & e, const vector<vector<int>> & cbs) {
	vector<Bridge> bridges, workingSet;
	for(auto i = 0; i < cbs.size(); i ++) {
		Bridge newBridge(cbs[i][0], cbs[i][1], cbs[i][2]);
		bridges.push_back(newBridge);
		// cout << newBridge.toString();
	}

	vector<int> temp({1,2,3});
	vector<int> temp2;

	auto foo = getSubsets(temp, temp2, 0);
	for(auto f : foo) {
		for(auto b : f) {
			cout << b << ' ';
		}
		cout << endl;
	}
	
	// return findLargestWeight(bridges, workingSet, 0);
	return 0;
}

#endif
