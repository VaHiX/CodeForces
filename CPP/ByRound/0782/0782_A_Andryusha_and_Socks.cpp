/*
 * Problem URL : https://codeforces.com/problemset/problem/782/A
 * Submit Date : 2025-08-14
 */

#include<cstdio>
int n,t,a[200000],c,m;
main(){
	scanf("%d",&n);
	n<<=1;
	while(n--){
		scanf("%d",&t);
		c+=a[t]?-1:1;
		m=m>c?m:c;
		a[t]^=1;
	}
	printf("%d",m);
}