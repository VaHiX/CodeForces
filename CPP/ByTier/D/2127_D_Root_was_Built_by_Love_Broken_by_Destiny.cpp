/*
 * Problem URL : https://codeforces.com/problemset/problem/2127/D
 * Submit Date : 2025-08-14
 */

#include<bits/stdc++.h>
using namespace std;
long long n,m,l,du[1000007],T,b[1000007],a1,a2,ans,fa[1000007],ss,jc[1000007];
const long long k=1e9+7;
int main(){
	cin>>T;
	for(int u=1;u<=T;u++){
		cin>>n>>m;ans=1;jc[0]=1;ss=0;
		for(int i=1;i<=n;i++)jc[i]=jc[i-1]*i%k;
		for(int i=1;i<=n;i++)b[i]=du[i]=0;
		for(int i=1;i<=m;i++){
			scanf("%lld%lld",&a1,&a2);
			du[a1]++;du[a2]++;
			fa[a1]=a2;fa[a2]=a1;
		}
		if(m!=n-1){
			puts("0");
			continue;
		}
		if(n==2){
			puts("2");
			continue;
		}
		for(int i=1;i<=n;i++)if(du[i]==1)b[fa[i]]++;
		for(int i=1;i<=n;i++){
			ans=ans*jc[b[i]]%k;
			du[i]-=b[i];
			if(du[i]>2)ans=0;
			if(b[i])++ss;
		}
		ans=ans*2*(ss>1?2:1)%k;
		cout<<ans<<'\n'; 
	}
}