#pragma GCC optimize(2, 3, "Ofast")
#include"bits/stdc++.h"
using namespace std;
typedef long long ll;
const ll INF = 1e18  + 100 ;
const ll NINF = -INF; 
const int inf  = 1e9 + 7;
const int MOD = 998244353;
const int mod = 1000000007;
const int ninf = -mod;
#define pb push_back
#define vi vector<int>
#define all(a) a.begin(),a.end()
#define allr(a) a.rbegin(),a.rend()
#define pii pair<int,int>
#define pll pair<ll,ll>
#define mems(a) memset(a,0,sizeof a)
#define revsort(a) sort(allr(a))
#define vll vector<ll>
#define vpll vector<pll>
#define vpii vector<pii>
#define nl "\n"
#define flush cout<<endl
#define sz(a) a.size()
#define ln(a) a.length()
#define rev(a) reverse(all(a))
#define dbg cout<<"All is well"<<endl
#define debugPrime cout<<"HeHeHeHe"<<endl
#define vvl vector<vll>
#define vvi vector<vi>
#define vvpi vector<vpii>
#define vvpl vector<vpll>
#define ret return
ll mul(ll a,ll b,ll mod)
{
    return ((a%mod) * (b%mod))%mod;
}
ll tri(ll a,ll b,ll c,ll mod)
{
    return mul(mul(a,b,mod),c,mod);
}
ll binPow(ll a, ll b,ll mod)
{
    if(b == 0)
        return 1;
    ll ans = binPow(a,b/2,mod);
    if(b & 1)
    {
        return tri(ans,ans,a,mod);
    }
    return mul(ans,ans,mod);
}
void __print(int x) {cerr << x;}
void __print(long x) {cerr << x;}
void __print(long long x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}
template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}
#ifndef ONLINE_JUDGE
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define debug(x...)
#endif
template<typename T1, typename T2> void ckmin(T1 &a, T2 b) { if (a > b) a = b; }
template<typename T1, typename T2> void ckmax(T1 &a, T2 b) { if (a < b) a = b; }
const int N  = 2e5;
vi tree[N],a(N),deleted(N),sze(N),cent[N],par(N),lvl(N);
int n,dist[(int)log2(N)][N];
void dfs1(int node,int prev)
{
    sze[node]=1;
    n++;
    for(auto nde:tree[node])
    {
        if(nde == prev || deleted[nde])
        {
            continue;
        }
        dfs1(nde,node);
        sze[node] += sze[nde]; 
    }
}
int find_centroid(int node,int prev)
{
    for(auto nde:tree[node])
    {
        if(nde == prev || deleted[nde])
            continue;
        if(sze[nde] > n/2)
            return find_centroid(nde,node);
    }
    return node;
}
void dfs2(int node,int prev,int level)
{
    for(auto nde:tree[node])
    {
        if(nde == prev)
            continue;
        dist[level][nde] = min(a[nde],dist[level][node]);
        dfs2(nde,node,level);
    }
}
void add_edge(int node,int prev)
{
    par[node] = prev;
    lvl[node] = lvl[prev] + 1;
    dist[lvl[node]][node] = a[node]; 
}
void dfs(int node,int prev)
{   
    n=0;
    dfs1(node,prev);
    int centroid = find_centroid(node,prev);
    deleted[centroid]=1;
    add_edge(centroid,prev);
    dfs2(centroid,centroid,lvl[centroid]);
    for(auto nde:tree[centroid])
    {
        if(deleted[nde])
            continue;
        dfs(nde,centroid);
    }
}
int lca(int node1,int node2)
{
    while(node1 != node2)
    {
        if(lvl[node1] > lvl[node2])
        {
            node1 = par[node1];
        }
        else
        {
            node2 = par[node2];
        }
    }
    return node1;
}
void solve()
{
    int i,j,n,q;
    cin>>n >> q;
    a.resize(n+1);
    sze.resize(n+1);
    par.resize(n+1);
    for(i=1;i<=n;i++)
    {
        cin>>a[i];
    }
    for(i=1;i<n;i++)
    {
        int first,second;
        cin>>first>>second;
        tree[first].pb(second);
        tree[second].pb(first);
    }
    dfs(1,0);
    while(q--)
    {
        int node1,node2;
        cin>>node1  >> node2;
        int lc =lca(node1,node2);
        int ans = min(dist[lvl[lc]][node1],dist[lvl[lc]][node2]);
        cout << ans << nl;
    }

}
int main()
{ 
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(0);
    int t=1;
    // cin>>t;
    while(t--)
    {
        solve();
    }
}  