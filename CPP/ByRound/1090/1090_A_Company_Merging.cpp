/*
 * Problem URL : https://codeforces.com/contest/1090/problem/A
 * Submit Date : 2025-08-29
 */

#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=2e5+7;

int n,a[N],b[N],mx;
ll ans;

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
		for(int j=1;j<=a[i];j++){
			int p;
			scanf("%d",&p);
			b[i]=max(b[i],p);
			mx=max(p,mx);
		}
	}
	for(int i=1;i<=n;i++) ans+=1LL*(mx-b[i])*a[i];
	cout<<ans;
} 
