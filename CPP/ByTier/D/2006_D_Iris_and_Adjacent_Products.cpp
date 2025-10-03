/*
 * Problem URL : https://codeforces.com/contest/2006/problem/D
 * Submit Date : 2025-09-13
 */

#include<bits/stdc++.h>
#define pb push_back
#define SZ(x) (int)(x).size()
using namespace std;
const int N=1e5+5,B=320;
int _,n,m,k,a[N],c[N],sq,o[N];
struct node{int i,l,r;}b[N];
signed main(){
	ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
	cin>>_;
	while(_--){
		cin>>n>>m>>k;sq=sqrt(k);
		sq=sq*2-(sq==k/sq);
		for(int i=1;i<=sq;i++)c[i]=0;
		for(int i=1;i<=n;i++){
			cin>>a[i];
			if(a[i]>k/a[i])a[i]=sq-k/a[i]+1;
			// cout<<a[i]<<" \n"[i==n];
		}
		for(int i=1;i<=m;i++)cin>>b[i].l>>b[i].r,b[i].i=i;
		sort(b+1,b+m+1,[](node x,node y){return
			x.l/B==y.l/B?(x.l/B&1?x.r>y.r:x.r<y.r):x.l<y.l;});
		int l=1,r=0;
		for(int i=1;i<=m;i++){
			while(l>b[i].l)c[a[--l]]++;
			while(r<b[i].r)c[a[++r]]++;
			while(l<b[i].l)c[a[l++]]--;
			while(r>b[i].r)c[a[r--]]--;
			int ans=0,sl=0,sr=0;
			for(int j=1;j*2<=sq;j++){
				sl=sl+c[j],sr=sr+c[sq-j+1];
				if(sr>sl){
					int x=(sr-sl+1)/2;
					if(((r-l+1)&1)&&sl+sr==r-l+1)x--;
					sl+=x,sr-=x,ans+=x;
				}
			}
			o[b[i].i]=ans;
		}
		for(int i=1;i<=m;i++)cout<<o[i]<<" \n"[i==m];
	}
	return 0;
}