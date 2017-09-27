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
	Bridge(int n, int w, int e, int we): 
		name(n), west(w), east(e), weight(we) {}

	const string toString() {
		ostringstream out;
		out << this->west << ' ' << this->east << ' ' << this->weight << endl;
		return out.str();
	}
	static const string toString(const vector<Bridge> & bridges) {
		ostringstream out;
		for(auto bridge : bridges) {
			out << bridge.name << ' ';
		}

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
		return (this->west == other.west || this->east == other.east);
	}

	const bool connectsToSameCity(const vector<Bridge> & bridges) const {
		for(auto bridge : bridges)
			if(this->connectsToSameCity(bridge))
				return true;

		return false;
	}

	const bool operator==(const Bridge & rhs) const {
		bool westEquals, eastEquals, weightEquals;

		westEquals = (this->west == rhs.west);
		eastEquals = (this->east == rhs.east);
		weightEquals = (this->weight == rhs.weight);

		return (westEquals && eastEquals && weightEquals);
	}

	const bool equals(const Bridge & rhs) const {
		bool westEquals, eastEquals, weightEquals;

		westEquals = (this->west == rhs.west);
		eastEquals = (this->east == rhs.east);
		weightEquals = (this->weight == rhs.weight);

		return (westEquals && eastEquals && weightEquals);
	}

	int name;
	int west;
	int east;
	int weight;
};

const unsigned int addWeights(const vector<Bridge> & bridges) {
	unsigned int weight = 0;

	for(auto bridge : bridges)
		weight += bridge.weight;

	return weight;
}

const unsigned int getMax(const vector<Bridge> & initialSet, vector<Bridge> & currentSet, const unsigned int index) {
	unsigned int max = 0;

	if(index < initialSet.size()) {
		auto item = initialSet[index];

		if(item.crosses(currentSet) || item.connectsToSameCity(currentSet)) {
			return getMax(initialSet, currentSet, index + 1);
		}
		else {
			currentSet.push_back(item);
			auto withMe = getMax(initialSet, currentSet, index + 1);
			currentSet.pop_back();
			auto withoutMe = getMax(initialSet, currentSet, index + 1);

			return (withMe > withoutMe ? withMe:withoutMe);
		}
	}
	else return addWeights(currentSet);
}

const int build(const int & w, const int & e, const vector<vector<int>> & cbs) {
	vector<Bridge> bridges, workingSet;
	for(auto i = 0; i < cbs.size(); i ++) {
		Bridge newBridge(i, cbs[i][0], cbs[i][1], cbs[i][2]);
		bridges.push_back(newBridge);
	}

	return getMax(bridges, workingSet, 0);
}

#endif
