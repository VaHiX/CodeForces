/*
 * Problem URL : https://codeforces.com/contest/2007/problem/D
 * Submit Date : 2025-09-13
 */

#include<stdio.h>
#include<algorithm>
const int N=200005;

int T,n,m;
int c[2],d[N];
char s[N];

signed main(){
	int i,u,v;
	scanf("%d",&T);
	
	while(T--){
		scanf("%d",&n);
		
		for(i=1;i<=n;i++) d[i]=0;
		for(i=1;i<n;i++){
			scanf("%d%d",&u,&v);
			d[u]++,d[v]++;
		}
		
		scanf("%s",s+1);
		c[0]=c[1]=m=v=0;
		
		for(i=2;i<=n;i++) if(d[i]==1){
			if(s[i]=='?') m++;
			else c[s[i]^48]++;
		}else if(s[i]=='?') v^=1;
		
		if(s[1]=='?'){
			if(c[0]^c[1])
				printf("%d\n",m/2+std::max(c[0],c[1]));
			else
				printf("%d\n",m/2+c[0]+(m&v));
		}else
			printf("%d\n",(m+1)/2+c[s[1]^49]);
	}
	
	return 0;
}
