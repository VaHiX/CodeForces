/*
 * Problem URL : https://codeforces.com/contest/1154/problem/E
 * Submit Date : 2025-08-30
 */

#include<bits/stdc++.h>
using namespace std;
int n,m,b[200005],a[200005],pre[200005],nxt[200005],ans[200005];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		pre[i]=i-1;nxt[i]=i+1;
		scanf("%d",&a[i]);
		b[a[i]]=i;
	}
	int id=2;
	for(int i=n;i>=1;i--){
		if(ans[b[i]]) continue;
		id=3-id;
		int k=m,l=pre[b[i]],r=nxt[b[i]];
		ans[b[i]]=id;
		while(l!=0&&k>0){k--;ans[l]=id;l=pre[l];}
		k=m;
		while(r<=n&&k>0){k--;ans[r]=id;r=nxt[r];}
		nxt[l]=r;pre[r]=l;
	}
	for(int i=1;i<=n;i++) printf("%d",ans[i]);
	return 0;
}
