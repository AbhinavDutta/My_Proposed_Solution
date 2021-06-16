#include "io-handle.h"
/*** CODE FOR TOPOLOGICAL SORT AND ITS FEE/WEIGHT BIASED VARIANT *******/
void dfs(vector<NODE>& arr,ll v,vector<bool>& vis,vector<ll>& r_Order);
void exploreDFS(vector<NODE>& arr,ll v,vector<bool>& vis);
void kahn_sort(vector<NODE>& sorted);

bool cmp(NODE a, NODE b)
{
    
	if (a.fee*1.0/a.weight>b.fee*1.0/b.weight)
    return true;
    else if (a.fee*1.0/a.weight==b.fee*1.0/b.weight)
    return a.address>b.address;
    else
    return false;
    
}
void topologicalSort(vector<NODE>& arr,vector<ll>& comp,map<string,ll>& addr_to_id,vector<ll>& order,
vector<NODE>& sorted,vector<vector<ll>>& ancestor)
{
    sorted=arr;
    vector<bool> vis;
    ll sz=arr.size(); 
    vis.assign(sz,false);
    for(ll i=0;i<sz;i++)
    {
        if(!vis[i])
        dfs(arr,i,vis,order);
    }
    reverse(order.begin(),order.end());
    kahn_sort(sorted);

}
void dfs(vector<NODE>& arr,ll v,vector<bool>& vis,vector<ll>& order)
{
    vis[v]=true;
    for(auto x:arr[v].children)
    {
        if(!vis[x])
        dfs(arr,x,vis,order);
    }
    order.push_back(v);
}


bool isAncestor(ll u,ll v,vector<NODE>& arr) //is u an ancestor of v?
{
    vector<bool> vis; vis.assign(arr.size(),false);
    exploreDFS(arr,u,vis);
    return vis[v];
}
void exploreDFS(vector<NODE>& arr,ll v,vector<bool>& vis)
{
    vis[v]=true;
    for(auto x:arr[v].children)
    {
        if(!vis[x])
        exploreDFS(arr,x,vis);
    }
}

void kahn_sort(vector<NODE>& sorted)
{
    set<NODE,decltype(&cmp)> q(cmp);

    for (ll i = 0; i < (ll)sorted.size(); i++)
    {
        if (sorted[i].parent.size() == 0)
            q.insert(sorted[i]);
    }

    vector<NODE> top_order;
    map<string,ll> in_degree;
    for(ll i=0;i<(ll)sorted.size();i++)
    in_degree[sorted[i].address]=sorted[i].parent.size();

    while (!q.empty())
    {
        NODE u = *q.begin();
        q.erase(u);
        top_order.push_back(u);

        for (auto itr :u.children)
        {
            if (--in_degree[sorted[itr].address] == 0)
                q.insert(sorted[itr]);
        }
    }
    for (ll i = 0; i < (ll)sorted.size(); i++)
    {
        sorted[i]=top_order[i];
    }
    
}