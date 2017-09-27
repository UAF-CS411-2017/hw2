#ifndef _CS_411_HW2_H_
#define _CS_411_HW2_H_

#include <vector>
using std::vector;

const unsigned int getMax(const vector<vector<int>> & initialSet, vector<vector<int>> & currentSet, const unsigned int index) {
	if(index < initialSet.size()) {
		auto item = initialSet[index];
		auto valid = true;

		for(auto curr : currentSet)
			if((item[0] <= curr[0] && item[1] >= curr[1]) || (item[0] >= curr[0] && item[1] <= curr[1]))
				valid = false;

		if(valid) {
			currentSet.push_back(item);
			auto withMe = getMax(initialSet, currentSet, index + 1);
			currentSet.pop_back();
			auto withoutMe = getMax(initialSet, currentSet, index + 1);

			return (withMe > withoutMe ? withMe:withoutMe);
		}
		else {
			return getMax(initialSet, currentSet, index + 1);
		}
	}
	else {
		unsigned int max = 0;
		
		for(auto item : currentSet)
			max += item[2];

		return max;
	}
}

const int build(const int & w, const int & e, const vector<vector<int>> & cbs) {
	vector<vector<int>> workingSet;

	return getMax(cbs, workingSet, 0);
}

#endif