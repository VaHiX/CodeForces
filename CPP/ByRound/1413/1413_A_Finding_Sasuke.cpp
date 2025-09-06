/*
 * Problem URL : https://codeforces.com/contest/1413/problem/A
 * Submit Date : 2025-09-01
 */

#include<bits/stdc++.h>
using namespace std;
int t;
int n;
int a[105];
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n/2;i++){
			int a,b;
			scanf("%d%d",&a,&b);
			printf("%d %d ",-b,a);
		}
		printf("\n");
	}
	return 0;
}