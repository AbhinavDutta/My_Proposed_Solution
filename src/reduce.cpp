#include "io-handle.h"
#include "solver.h"
/*******TO PERFORM REDUCTION *********/
ll getWeight(vector<NODE>& arr,ll v,vector<vector<ll>>& ancestor);
ll getFee(vector<NODE>& arr,ll v,vector<vector<ll>>& ancestor,vector<ll>& solution);

void reduce(vector<NODE>& arr,vector<ll>& solution,ll maxwt,map<string,ll>& addr_to_id,
vector<ll>& order,vector<vector<ll>>& ancestor,vector<NODE>& sorted)
{
    ll fee1=greedy1(maxwt,arr,sorted,ancestor,addr_to_id,-1,order);
    ll fee2=greedy2(maxwt,arr,order,ancestor,addr_to_id,-1);
    ll fee3=greedy3(maxwt,arr,addr_to_id,ancestor,-1,order);
    ll fee4=greedy4(maxwt,sorted,arr,addr_to_id,ancestor,-1,order);
    ll fee=max(fee1,max(fee2,max(fee3,fee4)));
    for(auto x:arr)
    {
        ll weightlim=getWeight(arr,addr_to_id[x.address],ancestor);
        ll feelim=getFee(arr,addr_to_id[x.address],ancestor,solution);
        if(weightlim>maxwt)
        solution[addr_to_id[x.address]]=0;
        if(feelim<fee)
        solution[addr_to_id[x.address]]=1;
        
    }
}
ll getWeight(vector<NODE>& arr,ll v,vector<vector<ll>>& ancestor)
{
    ll ans=0;
    for(ll i=0;i<arr.size();i++)
    {
        if(i==v)
        continue;
        if(ancestor[i][v]) //i is ancestor of v
        ans+=arr[i].weight;
    }
    return ans;
}
ll getFee(vector<NODE>& arr,ll v,vector<vector<ll>>& ancestor,vector<ll>& solution)
{
    ll ans=0;
    for(ll i=0;i<arr.size();i++)
    {
        if(i==v)
        continue;
        if(ancestor[i][v]||(ancestor[i][v]==0&&ancestor[v][i]==0))  //i is not descendant of v -> i is ancestor or (i,v) -> cross
        {
            if(solution[i]!=0)
            ans+=arr[i].fee;
        }
    }
    return ans;
}