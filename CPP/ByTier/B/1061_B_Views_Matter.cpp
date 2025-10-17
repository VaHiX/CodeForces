/*
 * Problem URL : https://codeforces.com/contest/1061/problem/B
 * Submit Date : 2025-09-11
 */

#include<bits/stdc++.h>
using namespace std;
const int maxn=100005;
int a[maxn];
int main(){
	int n,s,f=1;
	long long sum=0;
	scanf("%d%d",&n,&s);
	for(int i=0;i<n;i++){
		scanf("%d",&a[i]);
		sum+=a[i];
	}
	sort(a,a+n);
	for(int i=1;i<n;i++){
		if(a[i]>f)
		f++;
	}
	printf("%lld\n",sum-(a[n-1]+n-f));
}
