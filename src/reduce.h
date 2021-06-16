#ifndef REDUCE_H
#define REDUCE_H
#include <bits/stdc++.h>
#include "io-handle.h"
using namespace std;
void reduce(vector<NODE>& arr,vector<ll>& taken,ll maxwt,map<string,ll>& addr_to_id,
vector<ll>& order,vector<vector<ll>>& ancestor,vector<NODE>& sorted);
#endif