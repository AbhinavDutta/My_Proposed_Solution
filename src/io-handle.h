#ifndef IO_HANDLE_H
#define IO_HANDLE_H
#define ll long long int
#include <bits/stdc++.h>
using namespace std;
typedef struct nodes
{
    string address;
    ll weight; ll fee;
    vector<ll> children;  
    vector<ll> parent;
}NODE;
ll getID();
void reset(NODE& node);
void parseInput(vector<NODE>& arr,map<string,ll>& addr_to_id);
void map_address(map<string,ll>& addr_to_id,vector<NODE>& arr,ll& copy);
void displayOutput(vector<NODE>& arr,vector<ll>& solution,vector<ll>& order);

#endif