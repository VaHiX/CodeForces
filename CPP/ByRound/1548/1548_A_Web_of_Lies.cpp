/*
 * Problem URL : https://codeforces.com/contest/1548/problem/A
 * Submit Date : 2025-08-31
 */

#include<stdio.h>
int x[200010];
int main()
{
	int n,m,tot;
	scanf("%d%d",&n,&m);
	int a,b,k;
	tot=n;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		if(a>b) k=a,a=b,b=k;
		x[a]++;if(x[a]==1) tot--;
	}
	int q;
	scanf("%d",&q);
	while(q--)
	{
		int f;
		scanf("%d",&f);
		if(f==1)
		{
			scanf("%d%d",&a,&b);
			if(a>b) k=a,a=b,b=k;
			x[a]++;if(x[a]==1) tot--;
		}
		if(f==2)
		{
			scanf("%d%d",&a,&b);
			if(a>b) k=a,a=b,b=k;
			x[a]--;if(x[a]==0) tot++;
		}
		if(f==3) printf("%d\n",tot);
	}
	return 0;
}