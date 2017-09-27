#ifndef _CS_411_HW2_H_
#define _CS_411_HW2_H_

#include <vector>
using std::vector;

const unsigned int getMax(const vector<vector<int>> & initialSet, vector<vector<int>> & currentSet, const unsigned int index);
const int build(const int & w, const int & e, const vector<vector<int>> & cbs);

#endif