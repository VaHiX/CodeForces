/*
 * Problem URL : https://codeforces.com/contest/2009/problem/G1
 * Submit Date : 2025-09-13
 */

#include<iostream>
using namespace std;
const int maxn=4e5+5;
int t,n,k,q,a[maxn],p[maxn],l,r;
int b[maxn],c[maxn],nmax;
int find(int x){
	for(int i=x-1;i;i--)
		if(c[i])return i;
	return 0;
}
void add(int x){
	c[b[x]]--;c[++b[x]]++;
	if(b[x]>nmax)nmax=b[x];
}
void del(int x){
	c[b[x]]--;c[b[x]-1]++;	
	if(b[x]==nmax&&!c[b[x]])
		nmax=find(b[x]);b[x]--;
}
int main(){
	scanf("%d",&t); 
	while(t--){
		scanf("%d%d%d",&n,&k,&q);
		for(int i=1;i<=2*n;i++)
			b[i]=c[i]=0;nmax=0;c[0]=2*n;
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
			a[i]=a[i]-i+n;
		}
		for(int i=1;i<=k;i++)add(a[i]);
		p[k]=k-nmax;
		for(int i=k+1;i<=n;i++){
			add(a[i]);del(a[i-k]);
			p[i]=k-nmax;
		}
		while(q--){
			scanf("%d%d",&l,&r);
			printf("%d\n",p[r]);
		}
	}
	return 0;
}