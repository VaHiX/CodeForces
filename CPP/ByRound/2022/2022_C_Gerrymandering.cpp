/*
 * Problem URL : https://codeforces.com/contest/2022/problem/C
 * Submit Date : 2025-09-10
 */

#include<bits/stdc++.h>
using namespace std;
int t,n,f[100005],i,j;
char c[2][100005];
int ck(int xa,int ya,int xb,int yb,int xc,int yc){
	int res=0;
	if(c[ya][xa]=='A')res++;
	if(c[yb][xb]=='A')res++;
	if(c[yc][xc]=='A')res++;
	if(res>=2)return 1;
	return 0;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>t;
	while(t--){
		cin>>n;
		for(i=0;i<=1;i++)for(j=1;j<=n;j++)cin>>c[i][j];
		for(i=1;i<=n;i++)f[i]=0;
		for(i=1;i<=n;i++){
			j=i+(i+1)%3-1;
			if(i>=3)f[i]=f[i-3]+ck(i-2,0,i-1,0,i,0)+ck(j-2,1,j-1,1,j,1);
			if(i%3==0)f[i]=max(f[i],max(f[i-2]+ck(i-1,0,i,0,i,1),f[i-1]+ck(i,0,i-1,1,i,1)));
			else if(i%3==1)f[i]=max(f[i],f[i-1]+ck(i,0,i,1,i+1,1));
			else f[i]=max(f[i],f[i-2]+ck(i-1,0,i,0,i-1,1));
		}
		cout<<f[n]<<"\n";
	}
	return 0;
}

