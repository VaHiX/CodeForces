/*
 * Problem URL : https://codeforces.com/contest/2133/problem/E
 * Submit Date : 2025-08-30
 */

#include<bits/stdc++.h>
// #define int long long
// #define double long double
#define pii pair<int,int>
#define MP make_pair
#define F first
#define S second
using namespace std;
const int N=2e5+3;
int T,n,c[N],vis[N];
vector <int> lv;
vector <pii > op;
int Next[N<<1],ver[N<<1],head[N],tot;
void add(int x,int y){ver[++tot]=y; Next[tot]=head[x],head[x]=tot;}
void dfs1(int u,int fa){
    int cnt=0,fl=0;
    for (int i=head[u];i;i=Next[i]){
        int v=ver[i]; if (v==fa) continue;
        dfs1(v,u);
        if (c[v]==1) cnt++;
        if (c[v]==2) fl=1; 
    }
    if (!cnt) lv.emplace_back(u);
    if (cnt>=3 || fl){
        op.push_back(MP(2,u));
        op.push_back(MP(1,u));
        c[u]=3; vis[u]=1;
    }
    else if (cnt==2) c[u]=2;
    else c[u]=1;
}
void dfs2(int u){
    vis[u]=1; op.push_back(MP(1,u));
    for (int i=head[u];i;i=Next[i]){
        int v=ver[i];
        if (!vis[v] && c[v]!=3) dfs2(v);
    }
}
void Main(){
    cin>>n;
    lv.clear(); op.clear();
    tot=0; for (int i=1;i<=n;i++) head[i]=vis[i]=0;
    for (int i=1;i<n;i++){
        int u,v; cin>>u>>v;
        add(u,v); add(v,u);
    }
    dfs1(1,0);
    // for (int i=1;i<=n;i++) cout<<c[i]<<" "; cout<<"\n";
    for (auto u:lv) if (!vis[u]) dfs2(u);
    cout<<op.size()<<"\n";
    for (auto u:op) cout<<u.F<<" "<<u.S<<"\n";
}
signed main(){
//  freopen(".in","r",stdin);
//  freopen(".out","w",stdout);
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>T;
    while (T--) Main();
    return 0;
}