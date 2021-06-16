#ifndef UITL_H
#define UTIL_H
#include <bits/stdc++.h>
using namespace std;
#include "io-handle.h"
void topologicalSort(vector<NODE>& arr,vector<ll>& comp,map<string,ll>& addr_to_id,vector<ll>& order,
vector<NODE>& sorted,vector<vector<ll>>& ancestor);
bool isAncestor(ll u,ll v,vector<NODE>& arr) ;
#endif