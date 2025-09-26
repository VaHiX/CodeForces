/*
 * Problem URL : https://codeforces.com/contest/2018/problem/B
 * Submit Date : 2025-09-11
 */

#include<bits/stdc++.h>
using namespace std;
#define N 1050500
int a[N],L[N],R[N],c[N];
signed main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	int t;cin>>t;
	while(t--){
		int n;cin>>n;
		int ql=n+1,qr=0,tag=1,ansl=1,ansr=n;
		for(int i=1;i<=n;++i)L[i]=n+1,R[i]=0;
		for(int i=1;i<=n;++i)cin>>a[i],L[a[i]]=min(L[a[i]],i),R[a[i]]=max(R[a[i]],i),ansl=max(ansl,i-a[i]+1),ansr=min(ansr,i+a[i]-1);
		for(int i=1;i<=n;++i){
			ql=min(ql,L[i]);
			qr=max(qr,R[i]);
			if(qr-ql+1>i)tag=0;
		}	
		cout<<(ansr-ansl+1)*tag<<"\n";
	}
}