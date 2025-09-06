/*
 * Problem URL : https://codeforces.com/contest/1483/problem/A
 * Submit Date : 2025-09-01
 */

#include<bits/stdc++.h>
using namespace std;
int c[200000],d[200000],cnt[200000];
int main(){
	int t;
	scanf("%d",&t);
	while (t--){
		int n,m;
		scanf("%d%d",&n,&m);
		for (int i=1;i<=n;i++) cnt[i]=0;
		int p=0;
		for (int i=1;i<=m;i++){
			int k;
			scanf("%d%d",&k,c+i);
			cnt[c[i]]++;
			if (cnt[c[i]]>m+1>>1) p=c[i];
			if (k>1) scanf("%d",d+i);
			else d[i]=0;
			for (int j=1;j<=k-2;j++){
				int x;
				scanf("%d",&x);
			}
		}
		int q=0;
		if (p){
			q=cnt[p]-(m+1>>1);
			for (int i=1;i<=m;i++){
				if (!q) break;
				if (c[i]==p&&d[i]){
					c[i]=d[i];
					q--;
				}
			}
		}
		if (q) puts("NO");
		else{
			puts("YES");
			for (int i=1;i<=m;i++)
				printf("%d ",c[i]);
			putchar('\n');
		}
	}
	return 0;
}