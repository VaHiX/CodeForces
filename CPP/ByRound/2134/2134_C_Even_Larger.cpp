/*
 * Problem URL : https://codeforces.com/contest/2134/problem/C
 * Submit Date : 2025-08-30
 */

#include<bits/stdc++.h>
using namespace std;
const int N=200005;
int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	long long t,n,a[N],i,x,ans;
	cin>>t;
	while(t--){
		cin>>n;
		for(i=1;i<=n;i++)
			cin>>a[i];
		a[n+1]=0;
		ans=0;
		for(i=2;i<=n;i+=2){
			x=max(a[i-1]+a[i+1]-a[i],0LL);
			ans+=x;
			a[i+1]-=x;
			if(a[i+1]<0){
				a[i-1]+=a[i+1];
				a[i+1]=0;
			}
		}
		cout<<ans<<'\n';
	}
}
