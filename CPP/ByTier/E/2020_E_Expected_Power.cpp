/*
 * Problem URL : https://codeforces.com/contest/2020/problem/E
 * Submit Date : 2025-09-10
 */

#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5,inv=285700002,mod=1e9+7;
int t,a[N],p[N],f[2][10][10][2][2],ans,n,now;
signed main(){
	scanf("%lld",&t);
	while(t--){
		scanf("%lld",&n); ans=0;
		for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
		for(int i=1;i<=n;i++) scanf("%lld",&p[i]),p[i]=p[i]*inv%mod;
		memset(f[0],0,sizeof f[0]);
		for(int i=0;i<10;i++) for(int j=0;j<10;j++) f[0][i][j][0][0]=1;
		for(int i=1;i<=n;i++){
			now=i&1; memset(f[now],0,sizeof f[now]);
			for(int j=0;j<10;j++) for(int k=0;k<10;k++) for(int u=0;u<2;u++) for(int v=0;v<2;v++)
			f[now][j][k][u][v]=(p[i]*f[now^1][j][k][u^((a[i]>>j)&1)][v^((a[i]>>k)&1)]+(1-p[i]+mod)*f[now^1][j][k][u][v])%mod;
		} 
		for(int i=0;i<10;i++) for(int j=0;j<10;j++) ans+=f[n&1][i][j][1][1]*(1<<i+j);
		printf("%lld\n",ans%mod);
	}
	return 0;
}
