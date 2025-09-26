/*
 * Problem URL : https://codeforces.com/contest/2008/problem/G
 * Submit Date : 2025-09-13
 */

#include<cstdio>
int t,n,k,d,a;
int gcd(int a,int b){return b?gcd(b,a%b):a;}
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&k),d=0;
		for(int i=0;i<n;++i)scanf("%d",&a),d=gcd(d,a);
		if(n==1)printf("%d\n",k-(a>=k));
		else if(k>1ll*(n-1)*(d-1))printf("%d\n",k+n-1);
		else a=(k+d-2)/(d-1)-1,printf("%d\n",a+k);
	}
	return 0;
}
