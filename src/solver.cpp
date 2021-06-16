#include "io-handle.h"
#include "reduce.h"

/*** CONTAINS THE ALGORITHM - BOTH DYNAMIC PORGRAMMING AND GREEDY VARIANTS *****/

ll greedy1(ll maxwt,vector<NODE>& arr,vector<NODE>& sorted,vector<vector<ll>>& ancestor,map<string,ll>& addr_to_id,
ll target,vector<ll>& order);
ll greedy2(ll maxwt,vector<NODE>& arr,vector<ll>& order,vector<vector<ll>>& ancestor,
map<string,ll>& addr_to_id,ll target);
ll greedy3(ll maxwt,vector<NODE>& arr,map<string,ll>& addr_to_id,vector<vector<ll>>& ancestor,ll target,vector<ll>& order);
ll greedy4(ll maxwt,vector<NODE>& sorted,vector<NODE>& arr,map<string,ll>& addr_to_id,vector<vector<ll>>& ancestor,ll target,vector<ll>& order);

ll memoized(vector<ll> G,vector<NODE>& arr,vector<ll>& solution,ll remwt,vector<ll>& order,
map<string,ll>& addr_to_id,vector<vector<ll>>& ancestor,map<pair<vector<ll>,ll>,ll>& dp)
{
    //base cases
    ll smallest=-1;
    for(ll x:order)
    {
        if(G[x]==1)
        {
            smallest=x;
            break;
        }
    }
    pair<vector<ll>,ll> state=make_pair(G,remwt);
    if(smallest==-1)
    return dp[state]=0;

    if(dp.find(state)!=dp.end())
    return dp[state];

    
    NODE top=arr[smallest];

    vector<ll> Gl;
    vector<ll> Gr;
    Gl=G; Gr=G;
    Gl[addr_to_id[arr[smallest].address]]=0;
    Gr[addr_to_id[arr[smallest].address]]=0;
    for(ll i=0;i<(ll)arr.size();i++)
    {
        if(ancestor[addr_to_id[top.address]][i]==1||addr_to_id[top.address]==i) //i is a descendent of top
        Gr[i]=0;
    }

   
    if(solution[addr_to_id[top.address]]==-1)
    {
        
        ll ans1=0;
        if(remwt-top.weight>=0)
        ans1=memoized(Gl,arr,solution,remwt-top.weight,order,addr_to_id,ancestor,dp)+top.fee;
        ll ans2=memoized(Gr,arr,solution,remwt,order,addr_to_id,ancestor,dp);
    
        return dp[state]=max(ans1,ans2);
    }
    else if(solution[addr_to_id[top.address]]==0)
    {
        ll ans2=memoized(Gr,arr,solution,remwt,order,addr_to_id,ancestor,dp);
        return dp[state]=ans2;
    }
    else if(solution[addr_to_id[top.address]]==1)
    {
        ll ans1=0;
        if(remwt-top.weight>=0)
        ans1=memoized(Gl,arr,solution,remwt-top.weight,order,addr_to_id,ancestor,dp)+top.fee;
        return dp[state]=ans1;
    }
}
void construct_solution(vector<ll> G,vector<NODE>& arr,vector<ll>& solution,ll remwt,vector<ll>& order,
map<string,ll>& addr_to_id,vector<vector<ll>>& ancestor,map<pair<vector<ll>,ll>,ll>& dp)
{
    //base cases
    ll smallest=-1;
    for(ll x:order)
    {
        if(G[x]==1)
        {
            smallest=x;
            break;
        }
    }
    if(smallest==-1)
    return ;
    pair<vector<ll>,ll> state=make_pair(G,remwt);
    NODE top=arr[smallest];

    vector<ll> Gl;
    vector<ll> Gr;
    Gl=G; Gr=G;
    Gl[addr_to_id[arr[smallest].address]]=0;
    Gr[addr_to_id[arr[smallest].address]]=0;
    for(ll i=0;i<(ll)arr.size();i++)
    {
        if(ancestor[addr_to_id[top.address]][i]==1||addr_to_id[top.address]==i) //i is a descendent of top
        Gr[i]=0;
    }

   
    if(solution[addr_to_id[top.address]]==-1)
    {
        
        ll ans1=0;
        if(remwt-top.weight>=0)
        ans1=dp[make_pair(Gl,remwt-top.weight)]+top.fee;
        ll ans2=dp[make_pair(Gr,remwt)];
        if(ans1>ans2&&remwt-top.weight>=0)
        {
            construct_solution(Gl,arr,solution,remwt-top.weight,order,addr_to_id,ancestor,dp);
            solution[addr_to_id[top.address]]=1;
        }
        else
        {
            construct_solution(Gr,arr,solution,remwt,order,addr_to_id,ancestor,dp);
            solution[addr_to_id[top.address]]=0;
        }

       
    }
    else if(solution[addr_to_id[top.address]]==0)
    {
        construct_solution(Gr,arr,solution,remwt,order,addr_to_id,ancestor,dp);
    }
    else if(solution[addr_to_id[top.address]]==1)
    {
        if(remwt-top.weight>=0)
        construct_solution(Gl,arr,solution,remwt-top.weight,order,addr_to_id,ancestor,dp);
    }
}



//v is taken in topological order
//solution[v]=  1 -> v is taken
//              -1 -> undecided
//              0  -> v is not taken    
//G[v] = 0 (v is not in G)    or     1 (v is in G)  

bool isvalid(ll curr,vector<ll>& sol,vector<vector<ll>>& ancestor,ll size)
{
    for(ll i=0;i<size;i++)
    {
        if(ancestor[i][curr])
        {
            return (sol[i]==1);
        }
    }
    return true;
}


ll greedy1(ll maxwt,vector<NODE>& arr,vector<NODE>& sorted,vector<vector<ll>>& ancestor,
map<string,ll>& addr_to_id,ll target,vector<ll>& order)
{
    ll currwt=0; ll currfee=0;
    vector<ll> sol;
    sol.assign(arr.size(),0);
    for(auto x: sorted)
    {
        if(currwt+x.weight<=maxwt&&isvalid(addr_to_id[x.address],sol,ancestor,arr.size()))
        {
            currfee+=x.fee;
            currwt+=x.weight;
            sol[addr_to_id[x.address]]=1;
        }
    }
    if(target==currfee)
    {
        cout<<"weight="<<currwt<<endl;
        displayOutput(arr,sol,order);
    }
    return currfee;
}
ll greedy2(ll maxwt,vector<NODE>& arr,vector<ll>& order,vector<vector<ll>>& ancestor,
map<string,ll>& addr_to_id,ll target)
{
    ll currwt=0; ll currfee=0;
    vector<ll> sol;
    sol.assign(arr.size(),0);
    for(auto x: order)
    {
        if(currwt+arr[x].weight<=maxwt&&isvalid(x,sol,ancestor,arr.size()))
        {
            currfee+=arr[x].fee;
            currwt+=arr[x].weight;
            sol[x]=1;
        }
    }
    if(target==currfee)
    {
        cout<<"weight="<<currwt<<endl;
        displayOutput(arr,sol,order);
    }
    return currfee;
}
bool cmpr(NODE a,NODE b)
{
    if(a.fee*1.0/a.weight>b.fee*1.0/b.weight)
    return true;
    else if (a.fee*1.0/a.weight==b.fee*1.0/b.weight)
    return a.parent.size()<b.parent.size();
    else
    return false;
}
ll greedy3(ll maxwt,vector<NODE>& arr,map<string,ll>& addr_to_id,vector<vector<ll>>& ancestor,ll target,vector<ll>& order)
{
    vector<NODE> copy=arr; vector<ll> sol;
    sol.assign(arr.size(),0);
    ll currwt=0; ll currfee=0;
    sort(copy.begin(),copy.end(),cmpr);
    
    for(ll i=0;i<copy.size();i++)
    {
        if(currwt+copy[i].weight<=maxwt&&isvalid(addr_to_id[copy[i].address],sol,ancestor,arr.size()))
        {
            currwt+=copy[i].weight;
            currfee+=copy[i].fee;
            sol[addr_to_id[copy[i].address]]=1;
        }
    }
    if(target==currfee)
    {
        cout<<"weight="<<currwt<<endl;
        displayOutput(arr,sol,order);
    }
    return currfee;
}
ll sum(NODE v,vector<NODE>& arr)
{
    ll ans=v.weight;
    for(auto x:v.children)
    {
        ans+=sum(arr[x],arr);
    }
    return ans;
}
void selectTree(NODE v,vector<NODE>& arr,ll& currfee,ll& currwt,vector<ll>& sol,map<string,ll>& addr_to_id)
{
    currfee+=v.fee;
    currwt+=v.weight;
    if(sol[addr_to_id[v.address]]==1)
    {
        cout<<"Fail"<<endl;
        exit(0);
    }
    sol[addr_to_id[v.address]]=1;
    for(auto x:v.children)
    {
        selectTree(arr[x],arr,currfee,currwt,sol,addr_to_id);
    }
}
ll greedy4(ll maxwt,vector<NODE>& sorted,vector<NODE>& arr,map<string,ll>& addr_to_id,vector<vector<ll>>& ancestor,ll target,vector<ll>& order)
{
    ll currwt=0; ll currfee=0;
    vector<ll> sol;
    sol.assign(arr.size(),0);
    for(auto x: sorted)
    {
        if(sol[addr_to_id[x.address]]==1)
        continue;
        if(currwt+sum(x,arr)<=maxwt&&isvalid(addr_to_id[x.address],sol,ancestor,arr.size()))
        {
            selectTree(x,arr,currfee,currwt,sol,addr_to_id);
        }
    }
    if(target==currfee)
    {
        cout<<"weight="<<currwt<<endl;
        displayOutput(arr,sol,order);
    }
    return currfee;
}