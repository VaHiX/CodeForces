/*
 * Problem URL : https://codeforces.com/problemset/problem/1221/C
 * Submit Date : 2025-08-15
 */

#include <bits/stdc++.h>
using namespace std;
int a,b,c,T;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d %d %d",&a,&b,&c);
			printf("%d\n",min({a,b,(a+b+c)/3}));
	}
}