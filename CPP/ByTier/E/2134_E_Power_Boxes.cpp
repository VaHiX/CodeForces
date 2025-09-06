/*
 * Problem URL : https://codeforces.com/contest/2134/problem/E
 * Submit Date : 2025-08-30
 */

#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1005;
int t,n,ans[N],id[N],f[N],x,lst,res;
int T(int x){
	cout<<"throw "<<x<<endl;
	cin>>res;
	return res;
}
void S(int x){
	cout<<"swap "<<x<<endl;
	swap(id[x],id[x+1]);
}
void A(){
	cout<<"! ";
	for(int i=1;i<=n;i++)cout<<ans[i]<<" ";
	cout<<endl;
}
void query(int i){
	x=T(i);
	if(2+f[i+2]==x)ans[id[i]]=1;
	else ans[id[i]]=2;
}
void solve(int i,int F){
	query(i+F);
	S(i);
	query(i+F);
}
signed main(){
	cin>>t;
	while(t--){
		cin>>n;
		for(int i=1;i<=n;i++)id[i]=i;
		lst=n+1;
		f[n+1]=f[n+2]=0;
		for(int i=n-1;i>=1;i-=2){
			if(lst==n+1)solve(i,0);
			else{
				if(ans[id[lst]]==1)solve(i,1);
				else solve(i,0);
			}
			f[i+1]=f[i+1+ans[id[i+1]]]+1;
			f[i]=f[i+ans[id[i]]]+1;
			if(ans[i]==1||ans[i+1]==1)lst=i;
		}
		if(n&1){
			if(lst==n+1){
				S(1);
				query(2);
			}
			else{
				if(ans[id[lst]]==2){
					S(lst);
					for(int i=lst+1;i>=2;i--)f[i]=f[i+ans[id[i]]]+1;
				}
				query(1);
			}
		}
		A();
	}
	return 0;
}