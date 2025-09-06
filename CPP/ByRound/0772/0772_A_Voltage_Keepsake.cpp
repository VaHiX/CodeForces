/*
 * Problem URL : https://codeforces.com/contest/772/problem/A
 * Submit Date : 2025-09-04
 */

#include<cstdio>
const int N=100005;
long long s;
int n,p,a[N],b[N],i;
double l,m,r,x,y,t;
int main(){
	scanf("%d%d",&n,&p);
	for(i=1;i<=n;++i)scanf("%d%d",a+i,b+i),s+=a[i];
	if(s<=p)return puts("-1"),0;l=0;r=1e18;
	for(;r-l>1e-7;){
		m=(l+r)/2;x=m*p;
		for(i=1;i<=n;++i){
			t=b[i]*1.0/a[i];
			if(t<m)x-=(m-t)*a[i];
			if(x<0)break;
		}
		if(i>n)l=m;
			else r=m;
	}
	printf("%.5f\n",l);
	return 0;
}