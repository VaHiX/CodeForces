/*
 * Problem URL : https://codeforces.com/contest/1227/problem/A
 * Submit Date : 2025-09-02
 */

#include <cstdio>
#include <cmath>
int main(){
	int tc;
	scanf("%d",&tc);
	while(tc--){
		int n;
		scanf("%d",&n);
		int lmx=0,rmi=1e9;
		while(n--){
			int l,r;
			scanf("%d %d",&l,&r);
			lmx=std::max(lmx,l);
			rmi=std::min(rmi,r);
		}
		printf("%d\n", std::max(0,lmx-rmi));
	}
}