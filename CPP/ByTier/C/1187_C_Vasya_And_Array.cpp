/*
 * Problem URL : https://codeforces.com/contest/1187/problem/C
 * Submit Date : 2025-09-11
 */

#include<bits/stdc++.h>
using namespace std;
int n,m,x[1005],y[1005],cnt,t,l,r,a[1005];
bool num[1005];
int main(){
	cin>>n>>m;
	while(m--){
		cin>>t>>l>>r;
		if(t) for(int i=l;i<r;i++) num[i]=1;
		else{
			cnt++;x[cnt]=l;y[cnt]=r;
		}
	}
	a[1]=n;
	for(int i=2;i<=n;i++){
		if(num[i-1]) a[i]=a[i-1];
		else a[i]=a[i-1]-1;
	}
	for(int i=1;i<=cnt;i++) if(a[x[i]]==a[y[i]])
		return cout<<"NO",0;
	cout<<"YES\n";
	for(int i=1;i<=n;i++) cout<<a[i]<<" ";
}