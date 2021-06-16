
#ifndef SOLVER_H
#define SOLVER_H
#include <bits/stdc++.h>
using namespace std;
#include "io-handle.h"

void construct_solution(vector<ll> G,vector<NODE>& arr,vector<ll>& solution,ll remwt,vector<ll>& order,
map<string,ll>& addr_to_id,vector<vector<ll>>& ancestor,map<pair<vector<ll>,ll>,ll>& dp);

ll memoized(vector<ll> G,vector<NODE>& arr,vector<ll>& solution,ll remwt,vector<ll>& order,
map<string,ll>& addr_to_id,vector<vector<ll>>& ancestor,map<pair<vector<ll>,ll>,ll>& dp);

ll greedy1(ll maxwt,vector<NODE>& arr,vector<NODE>& sorted,vector<vector<ll>>& ancestor,map<string,ll>& addr_to_id,
ll target,vector<ll>& order);
ll greedy2(ll maxwt,vector<NODE>& arr,vector<ll>& order,vector<vector<ll>>& ancestor,
map<string,ll>& addr_to_id,ll target);
ll greedy3(ll maxwt,vector<NODE>& arr,map<string,ll>& addr_to_id,vector<vector<ll>>& ancestor,ll target,vector<ll>& order);
ll greedy4(ll maxwt,vector<NODE>& sorted,vector<NODE>& arr,map<string,ll>& addr_to_id,vector<vector<ll>>& ancestor,ll target,vector<ll>& order);

#endif