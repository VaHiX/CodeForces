/*
 * Problem URL : https://codeforces.com/contest/1169/problem/B
 * Submit Date : 2025-08-28
 */

#include<cstdio>
using namespace std;
int n,m,a[300005],b[300005];
bool f(int x,int y) {
	for(int i=1; i<=m; i++) {
		if(a[i]==x||a[i]==y||b[i]==x||b[i]==y) continue;
		if(y) return 0;
		return f(a[i],x)||f(b[i],x);
	}
	return 1;
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i=1; i<=m; i++)
		scanf("%d%d",&a[i],&b[i]);
	if(f(a[1],0)||f(b[1],0)) printf("YES");
		else printf("NO");
	return 0;
}