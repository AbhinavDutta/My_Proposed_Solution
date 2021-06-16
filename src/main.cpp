#include <bits/stdc++.h>
using namespace std;
#include "io-handle.h"
#include "util.h"
#include "reduce.h"
#include "solver.h"
int main()
{
    ll id=0;
    ll maxwt=4000000;
    map<string,ll> addr_to_id;
    map<pair<vector<ll>,ll>,ll> dp;
    vector<NODE> arr; vector<NODE> sorted;
    vector<ll> order; vector<ll> solution; vector<ll> comp;
    map_address(addr_to_id,arr,id);
    parseInput(arr,addr_to_id);
    
    ll size=arr.size();
    solution.assign(size,-1); comp.resize(size);
    vector<vector<ll>> ancestor; 
    ancestor.resize(size);
    for(ll i=0;i<size;i++)
    ancestor[i].resize(size);
    
    for(ll i=0;i<size;i++)
    {
        for(ll j=0;j<size;j++)
        {
            if(isAncestor(i,j,arr))
            ancestor[i][j]=1;
            else
            ancestor[i][j]=0;
            if(i==j)
            ancestor[i][j]=0;
        }
    }
    topologicalSort(arr,comp,addr_to_id,order,sorted,ancestor);
    reduce(arr,solution,maxwt,addr_to_id,order,ancestor,sorted);
    
    ll count=0;
    for(auto x:solution)
    {
        if(x==-1)
        count++;
    }
    if(count<=25)  //on smaller data-sets use exact dynamic programming
    {
        vector<ll> G;
        G.assign(arr.size(),1);
        memoized(G,arr,solution,maxwt,order,addr_to_id,ancestor,dp); //Dynamic porgramming
        G.assign(arr.size(),1);
        construct_solution(G,arr,solution,maxwt,order,addr_to_id,ancestor,dp);
        displayOutput(arr,solution,order);
    }
    else
    {
        ll fee1=greedy1(maxwt,arr,sorted,ancestor,addr_to_id,-1,order); //topological +fee/weight bias heuristic
        ll fee2=greedy2(maxwt,arr,order,ancestor,addr_to_id,-1); //topological heuristic
        ll fee3=greedy3(maxwt,arr,addr_to_id,ancestor,-1,order); // fee/weight heuristic
        ll fee4=greedy4(maxwt,sorted,arr,addr_to_id,ancestor,-1,order); //tree wise + fee/weight bias heuristic
        ll fee=max(fee1,max(fee2,max(fee3,fee4)));
        cout<<"fee="<<fee<<endl;
        if(fee==fee1)
        greedy1(maxwt,arr,sorted,ancestor,addr_to_id,fee,order);
        else if(fee==fee2)
        greedy2(maxwt,arr,order,ancestor,addr_to_id,fee);
        else if(fee==fee3)
        greedy3(maxwt,arr,addr_to_id,ancestor,fee,order);
        else if(fee==fee4)
        greedy4(maxwt,sorted,arr,addr_to_id,ancestor,fee,order);

    }

    return 0;

}