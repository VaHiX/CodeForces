/*
 * Problem URL : https://codeforces.com/contest/1530/problem/H
 * Submit Date : 2025-09-11
 */

#include<bits/stdc++.h>
using namespace std;
const int N=15005;
int n,ans,a[N],fl[N],fr[N],gl[N],gr[N],Cl[N],Cr[N];
void addl(int x,int k){
	for(;x;x-=x&-x)Cl[x]=min(Cl[x],k);
}
void addr(int x,int k){
	for(;x<=n;x+=x&-x)Cr[x]=max(Cr[x],k);
}
int getl(int x){
	int res=n+1;
	for(;x<=n;x+=x&-x)res=min(res,Cl[x]);
	return res;
}
int getr(int x){
	int res=0;
	for(;x;x-=x&-x)res=max(res,Cr[x]);
	return res;
}
void DP(int o){
	for(int len=o;;len++){
		int flag=0;
		for(int i=1;i<=n;i++)flag|=fl[i]<=n|fr[i]>=1;
		if(!flag){ans=max(ans,len-o);return;}
		for(int i=0;i<=n;i++)Cl[i]=n+1,Cr[i]=0;
		for(int i=n;i>=1;i--){
			if(i+1<=n)addl(a[i+1],fl[i+1]),addr(a[i+1],fr[i+1]);
			if(i+len<=n)addl(fr[i+len],a[i+len]),addr(fl[i+len],a[i+len]);
			gl[i]=getl(a[i]);gr[i]=getr(a[i]);
		}
		for(int i=1;i<=n;i++)fl[i]=gl[i],fr[i]=gr[i];
	}
}
void xxx(){
	scanf("%d",&n);ans=0;
	for(int i=1;i<=n;i++)scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)fl[i]=fr[i]=a[i];DP(2);
	for(int i=1;i<n;i++)fl[i]=n+1,fr[i]=0;
	fl[n]=fr[n]=a[n];DP(1);printf("%d\n",ans);
}
int main(){
	int T;scanf("%d",&T);while(T--)
	xxx();return 0;
}
	 	  		  	 			  		 	 	  		 		 	