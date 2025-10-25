/*
 * Problem URL : https://codeforces.com/contest/2008/problem/F
 * Submit Date : 2025-09-13
 */

#include<bits/stdc++.h>
const int mod=1e9+7;
inline int qpow(int x,int y){
	static int res;res=1;
	while(y){
		if(y&1)res=1ll*res*x%mod;
		y>>=1;
		x=1ll*x*x%mod;
	}
	return res;
}
int T,n,s,ans;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&s);
		ans=0;
		for(int i=1,x;i<n;++i)
			scanf("%d",&x),ans=(ans+1ll*x*s)%mod,(s+=x)<mod?0:s-=mod;
		printf("%d\n",1ll*ans*qpow((n*(n-1ll)>>1)%mod,mod-2)%mod);
	}
	return 0;
}