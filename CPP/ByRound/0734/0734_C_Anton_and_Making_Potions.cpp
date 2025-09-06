/*
 * Problem URL : https://codeforces.com/contest/734/problem/C
 * Submit Date : 2025-09-02
 */

#include <stdio.h>
#include <algorithm>
using namespace std;

int main(){
	long long n,m,k,x,s;
	scanf("%lld%lld%lld%lld%lld",&n,&m,&k,&x,&s);
	long long min = n * x;
	long long a[m+1],b[m+1],c[k+1],d[k+1];
	a[0] = x;
	b[0] = 0;
	c[0] = d[0] = 0;
	for(int i=1;i<=m;i++) scanf("%lld",&a[i]);
	for(int i=1;i<=m;i++) scanf("%lld",&b[i]);
	for(int i=1;i<=k;i++) scanf("%lld",&c[i]);
	for(int i=1;i<=k;i++) scanf("%lld",&d[i]);
	for(int i=0;i<=m;i++){
		if(b[i] > s) continue;
		int j = upper_bound(d,d+k+1,s-b[i]) - d - 1;
		long long temp = (n - c[j]) * a[i];
		if(temp < min) min = temp;
	}
	printf("%lld",min);
	return 0;
}