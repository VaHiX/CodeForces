/*
 * Problem URL : https://codeforces.com/contest/1120/problem/A
 * Submit Date : 2025-09-02
 */

#include<bits/stdc++.h>
using namespace std;
const int MAXA=5e6;
int m,n,k,s,x,l,r,si[MAXA],bo[MAXA],siz[MAXA],a[MAXA],tot;
int check(int l,int r){
    //printf("%d %d\n",l,r);
    l-=(l-1)%k;
    if(r-l+1>n+k) return 0;
    int ans=r-l+1-k;
    if(ans<0) ans=0;
    printf("%d\n",ans);
    for(int i=l;i<=r;i++){
	if(ans==0) break;
	if(si[a[i]]>0) si[a[i]]--;
	else ans--,printf("%d ",i);
    }
    exit(0);
}
int main(){
    scanf("%d%d%d%d",&m,&k,&n,&s);
    n=m-n*k;
    for(int i=1;i<=m;i++) scanf("%d",&a[i]);
    for(int i=1;i<=s;i++){
	scanf("%d",&x);
	bo[x]=1;
	siz[x]++;
	si[x]++;
	tot++;
    }
    r=0;l=0;
    while(r<=m&&tot>0){
	r++;
	if(bo[a[r]]){
	    siz[a[r]]--;
	    if(siz[a[r]]>=0) tot--;
	}
    }
    while(l<=m){
	l++;
	if(bo[a[l]]){
	    if(siz[a[l]]==0) break;
	    siz[a[l]]++;
	}
    }
    if(l<=m&&r<=m) check(l,r);
    while(r<m&&l<m){
	r++;
	while(a[r]!=a[l]&&r<=m){
	    if(bo[a[r]]) siz[a[r]]--;
	    r++;
	}
	l++;
	while((!(bo[a[l]]&&siz[a[l]]==0)&&l<=m)){
	    if(bo[a[l]])
		siz[a[l]]++;
	    l++;
	}
	if(l>m||r>m) break;
	check(l,r);
    }
    printf("-1");
}
