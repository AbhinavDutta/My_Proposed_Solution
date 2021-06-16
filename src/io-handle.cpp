#include "io-handle.h"
#include <bits/stdc++.h>
using namespace std;
/********DISPLAY OUTPUT AND PARSE CSV FILE *********/
ll id=0;
void reset(NODE& node)
{
    node.address.clear();
    node.weight=-1; node.fee=-1;
    node.children.clear();
}
void equate(NODE& a,NODE& b)
{
    a.address=b.address;
    a.weight=b.weight;
    a.fee=b.fee;
}
void map_address(map<string,ll>& addr_to_id,vector<NODE>& arr,ll& copy)
{
    FILE* in=fopen("mempool.csv","r");
    char x; string curr; ll cnt=0; 
    while(fscanf(in,"%c",&x)!=EOF)
    {
        if(x=='\n')
        break;
    }
    while(fscanf(in,"%c",&x)!=EOF)
    {
        if(x==',')
        {
            if(cnt==0)
            {
                if(addr_to_id.find(curr)==addr_to_id.end())
                    addr_to_id[curr]=id++;
            }
            if(cnt==1)
            ;
            if(cnt==2)
            ;
            if(cnt>=3)
            ;
            cnt++;
            curr="";
        }
        else if(x=='\n')
        {
            cnt=0;
            curr="";
        }
        else
        curr+=x;
    }
    arr.resize(id);
    copy=id;
    fclose(in);
}
void parseInput(vector<NODE>& arr,map<string,ll>& addr_to_id)
{
    FILE* in=fopen("mempool.csv","r");
    char x; string curr; ll cnt=0; NODE node;
    while(fscanf(in,"%c",&x)!=EOF)
    {
        if(x=='\n')
        break;
    }
    while(fscanf(in,"%c",&x)!=EOF)
    {
        if(x==',')
        {
            if(cnt==0)
                node.address=curr;
            if(cnt==1)
                node.fee=stoll(curr);
            if(cnt==2)
                node.weight=stoll(curr);
            if(cnt>=3&&curr!="")
            {
                arr[addr_to_id[curr]].children.push_back(addr_to_id[node.address]);
                arr[addr_to_id[node.address]].parent.push_back(addr_to_id[curr]);
            }
            cnt++;
            curr="";
        }
        else if(x=='\n')
        {
            if(cnt>=3&&curr!="")
            {
                arr[addr_to_id[curr]].children.push_back(addr_to_id[node.address]);
                arr[addr_to_id[node.address]].parent.push_back(addr_to_id[curr]);
            }
            equate(arr[addr_to_id[node.address]],node);
            reset(node);
            cnt=0;
            curr="";
        }
        else
        curr+=x;
    }
    if(node.address!="")
    {
        equate(arr[addr_to_id[node.address]],node);
        if(curr!="")
        {
            arr[addr_to_id[curr]].children.push_back(addr_to_id[node.address]);
            arr[addr_to_id[node.address]].parent.push_back(addr_to_id[curr]);
        }
    }

    fclose(in);
}

void displayOutput(vector<NODE>& arr,vector<ll>& solution,vector<ll>& order)
{
    fstream out;
    out.open("block.txt");
    for(ll x:order)
    {
        if(solution[x]==-1)
        {
            cout<<"fail"<<endl;
            exit(0);
        }
        if(solution[x]==1)
        {
            out<<arr[x].address<<endl;
        }
    }
    out.close();
}