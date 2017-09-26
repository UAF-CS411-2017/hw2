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
		return (this->west <= other.west && this->east >= other.east) || (this->west >= other.west && this->east <= other.east);
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

// struct Node {
// 	Node(Node parent, Bridge obj): parent(parent), obj(obj) {}
// 	Node(Bridge obj): parent(NULL), obj(obj) {}

// 	void addChild(const Bridge & bridge) {
// 		this->children.push_back(bridge);
// 	}

// 	const int getLargestWeight() {
// 		if(this->children.size() == 0)
// 			return this->obj.weight;
// 		else {
// 			auto weight  = 0;

// 			for(auto bridge : this->children) {
// 				auto childWeight = bridge.getLargestWeight();

// 				if(childWeight > weight)
// 					weight = childWeight;
// 			}

// 			return this->obj.weight + weight;
// 		}
// 	}

// 	Node parent;
// 	Bridge obj;
// 	vector<const Bridge &> children;
// };

const int addWeights(const vector<Bridge> & bridges) {
	int weight = 0;

	for(auto bridge : bridges)
		weight += bridge.weight;

	return weight;
}

const vector<vector<Bridge>> getAllSubsets(const vector<Bridge> & bridges/*, const int & index*/) {
	vector<vector<Bridge>> allSubsets;
	
	for(auto i = 0; i < bridges.size(); i++) {
		allSubsets.push_back(vector<Bridge>({bridges[i]}));
		vector<Bridge> subset({bridges[i]});

		for(auto j = i + 1; j < bridges.size(); j++) {
			auto bridge = bridges[j];

			if(!bridge.crosses(subset) && !bridge.connectsToSameCity(subset)) {
				subset.push_back(bridges[j]);
				allSubsets.push_back(subset);
			}
		}
	}

	return allSubsets;
}

const int findLargestWeight(const vector<Bridge> & bridges, const int & index) {
	return 0;
	if(index == bridges.size() - 1)
		return bridges[index].weight;

	int subsetWeight = findLargestWeight(bridges, index + 1);
	int weight = bridges[index].weight + subsetWeight;

	return (weight > subsetWeight ? weight:subsetWeight);

	//					OLD CODE

	// for(auto i = index + 1; i < bridges.size(); i++) {
	// 	Bridge bridge = bridges[i];
	// 	cout << bridge.toString();
	// 	if(!bridge.crosses(matches) && !bridge.connectsToSameCity(matches))
	// 		matches.push_back(bridge);
	// }

	// int weight = addWeights(matches);
	// otherWeight = findLargestWeight(bridges, index + 1);

	// return (weight > otherWeight ? weight:otherWeight);
}

const int build(const int & w, const int & e, const vector<vector<int>> & cbs) {
	vector<Bridge> bridges;
	vector<Bridge> searched;
	for(auto i = 0; i < cbs.size(); i ++) {
		Bridge newBridge(i, cbs[i][0], cbs[i][1], cbs[i][2]);
		bridges.push_back(newBridge);
		// cout << newBridge.toString() << endl;
	}

	auto subsets = getAllSubsets(bridges);
	// auto winningSubset = subsets[0];
	auto weight = 0;

	for(auto subset : subsets) {
		auto newWeight = addWeights(subset);
		if(newWeight > weight) {
			weight = newWeight;
			// winningSubset = subset;
		}
	}

	// cout << Bridge::toString(winningSubset) << endl;

	return weight;
	
	return findLargestWeight(bridges, 0);
	// return findLargestFromNode(bridges, searched, 0);
}

#endif
