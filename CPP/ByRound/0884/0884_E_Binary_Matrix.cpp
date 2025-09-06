/*
 * Problem URL : https://codeforces.com/contest/884/problem/E
 * Submit Date : 2025-09-05
 */

#include<bits/stdc++.h>
#define pb push_back
#define SZ(x) (int)((x).size())
using namespace std;
const int N=1<<14;
int n,m,f[2][N],p[N],ans;
char s[N];
inline bool V(int x){return (s[x>>2]-(s[x>>2]<65?48:55))>>(3-(x&3))&1;}
int getf(int o,int x){return x==f[o][x]?x:f[o][x]=getf(o,f[o][x]);}
signed main(){
	ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
	cin>>n>>m;memset(f[0],-1,sizeof(f[0]));
	for(int i=1,o=1;i<=n;i++,o^=1){
		cin>>s;memset(p,-1,sizeof(p));
		for(int j=0;j<m;j++){
			if(!V(j))f[o][j]=-1;
			else{
				if(!~f[!o][j])f[o][j]=j,ans++;
				else if(!~p[getf(!o,j)])p[f[!o][j]]=j,f[o][j]=j;
				else f[o][j]=getf(o,p[f[!o][j]]);
				if(j&&V(j-1)&&getf(o,j)!=getf(o,j-1))f[o][f[o][j]]=f[o][j-1],ans--;
			}
		}
	}cout<<ans<<'\n';
	return 0;
}