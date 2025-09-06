/*
 * Problem URL : https://codeforces.com/contest/2037/problem/G
 * Submit Date : 2025-09-05
 */

#include <cstdio>
#include <vector>
 
const int N=1048576,mod=998244353;
 
std::vector<int> d[N];
 
int pr[N/5],u[N],pc;bool vis[N];
 
void sev(){
	for(int i=2,nx;i<N;++i){
		if(!vis[i]) pr[++pc]=i,u[i]=1,d[i].push_back(i);
		for(int j=1;j<=pc&&(nx=i*pr[j])<N;++j){
			vis[nx]=1;d[nx]=d[i];
			if(i%pr[j]==0) break;
			u[nx]=-u[i];d[nx].push_back(pr[j]);
			for(int f:d[i]) d[nx].push_back(f*pr[j]);
		}
	}
}
 
int f[N];
 
int main()
{
	sev();int n;scanf("%d",&n);bool fst=1;while(n--){
		int x,s=fst;fst=0;scanf("%d",&x);
		for(int y:d[x]) s=((s+u[y]*f[y])%mod+mod)%mod;
		for(int y:d[x]) (f[y]+=s)%=mod;
		if(!n) return printf("%d",s),0;
	}
}