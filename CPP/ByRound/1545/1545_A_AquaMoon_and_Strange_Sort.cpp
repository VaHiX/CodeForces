/*
 * Problem URL : https://codeforces.com/contest/1545/problem/A
 * Submit Date : 2025-08-31
 */

#include<bits/stdc++.h>
using namespace std;const int N=1e5+7;
int T_T,n,i,j,a[2][N];
int main(){
	for(scanf("%d",&T_T);T_T--;){
		for(scanf("%d",&n),i=1;i<=n;++i)scanf("%d",a[i&1]+(i+1)/2);
		sort(a[0]+1,a[0]+n/2+1);sort(a[1]+1,a[1]+(n+1)/2+1);
		for(j=0,i=1;i<=n;++i)if(a[i&1][(i+1)/2]<a[(i-1)&1][i/2]){
			puts("NO");j=1;break;
		}if(!j)puts("YES");
	}
}