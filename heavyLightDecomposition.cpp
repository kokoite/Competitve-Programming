#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+100;
#define left vxoibdo
#define right iaoaboizd
typedef long long ll;
ll clk =0;
ll left[N],right[N],color[N],index_in_chain[N],sze[N],height[N],parent[N],cost[N];
#define all(v) v.begin(),v.end()

vector<int>tree[N];
unordered_map<int,vector<int>>chains;
unordered_map<int,vector<ll>>segmentTree;

void dfs(int node,int par)
{
	clk++;
	left[node]= clk;
	for(auto nde:tree[node])
	{
		if(nde == par)
		{
			continue;
		}
		dfs(nde,node);
	}
	right[node] = clk;
}
void dfs1(int node,int par)
{
	sze[node]=1;
	for(auto nde:tree[node])
	{
		if(nde == par)
		{
			continue;
		}
		parent[nde]= node;
		height[nde] = height[node]+1;
		dfs1(nde,node);
		sze[node]+=sze[nde];
	}
}


vector<tuple<ll,ll,ll>> printAllChain(int x,int y)
{
	vector<tuple<ll,ll,ll>>segmentA,segmentB;
	//
	while(1)
	{
		if(color[x] == color[y])
		{
			segmentA.push_back({color[x],x,y});
			break;
		}
		else
		{
			if(height[color[x]]>height[color[y]])
			{
				segmentA.push_back({color[x],x,color[x]});
				segmentA.push_back({-1,color[x],parent[color[x]]});
				x = parent[color[x]];
			}
			else
			{
				segmentB.push_back({color[y],color[y],y});
				segmentB.push_back({-1,parent[color[y]],color[y]});
				y = parent[color[y]];
			}
		}
	}
	reverse(all(segmentB));
	for(auto it:segmentB)
	{
		segmentA.push_back(it);
	}
	return segmentA;
}

void hld(int node,int par)
{
	int best =-1;
	for(auto nde:tree[node])
	{
		if(nde == par)
		{
			continue;
		}
	if(best == -1 || sze[nde]>sze[best])
	{
		best = nde;
	}
	}
	if(best == -1)
	{
		return;
	}
	color[best] = color[node];
	index_in_chain[best] = index_in_chain[node]+1;
	chains[color[node]].push_back(best);
	hld(best,node);
	for(auto nde:tree[node])
	{
		if(nde == par || nde == best)
		{
			continue;
		}
		color[nde] = nde;
		index_in_chain[nde] = 0;
		chains[nde].push_back(nde);
		hld(nde,node);

	}
}
void build(int col)
{
	for(int i=chains[col].size()-1;i>=1;i--)
	{
		int left = 2*i,right=2*i +1;
		segmentTree[col][i] = max(segmentTree[col][left],segmentTree[col][right]); 
	}
}
void update(int col,int index,ll value)
{
	index+=chains[col].size();
	segmentTree[col][index] = value;
	while(index>1)
	{
		index = index>>1;
		int left = 2*index;
		int right = left +1;
		segmentTree[col][index] = max(segmentTree[col][left],segmentTree[col][right]);
	}
	return;
}
ll sum(int col,int l,int r)
{
	
	l+=chains[col].size();
	r+=chains[col].size();
	if(l>r)
	{
		swap(l,r);
	}	
	ll s=0;
	while(l<=r)
	{
		if(l&1)
		{	
			s = max(s,segmentTree[col][l]);
			l++;
		}
		if(r%2 ==0)
		{
			s = max(s,segmentTree[col][r]);
			
			r--;
		}
		l = (l>>1);
		r = (r>>1);
	}
	return s;
}
int main()
{
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
	int n,q;
	cin>>n>>q;
	int i;
	for(i=1;i<=n;i++)
	{
		cin>>cost[i];
	}
	for(i=0;i<n-1;i++)
	{
		int first,second;
		cin>>first>>second;
		tree[first].push_back(second);
		tree[second].push_back(first);
	}
	dfs1(1,0);
	color[1]=1;
	index_in_chain[1] = 0;
	chains[1].push_back(1);
	hld(1,0);

	for(i=1;i<=n;i++)
	{
		if(chains[i].size()>0)
		{
			// cout<<i<<" ";
			segmentTree[i].resize((2*(chains[i].size())) +1);
			for(int j=0;j<chains[i].size();j++)
			{
				segmentTree[i][j+chains[i].size()] = cost[chains[i][j]];
			}
			build(color[i]);
		}
	}
	while(q--)
	{
		int type;
		cin>>type;
		if(type == 1)
		{
			ll node,value;
			cin>>node>>value;
			update(color[node],index_in_chain[node],value);
		}
		else
		{
			int node1,node2;
			cin>>node1>>node2;
			// cout<<node1<<" "<<node2<<endl;
			vector<tuple<ll,ll,ll>>v = printAllChain(node1,node2);
			ll ans = 0;
			for(auto it:v)
			{
				ll a,b,c;
				tie(a,b,c) = it;
				if(a!=-1)
				{
					ans = max(ans,sum(a,index_in_chain[b],index_in_chain[c]));
				}

				
			}
			cout<<ans<<" ";
		}
	}
	
}