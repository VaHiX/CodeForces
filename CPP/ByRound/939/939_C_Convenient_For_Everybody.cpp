/*
 * Problem URL : https://codeforces.com/problemset/problem/939/C
 * Submit Date : 2025-08-15
 */

#include <stdio.h>
__int64 n,a[200005],d[200005],mn,val,s,e,ans;
int main()
{
	scanf("%I64d",&n);
	for (int i=1;i<=n;i++)
	{
		scanf("%I64d",&a[i]);
		a[n+i]=a[i];
	}
	scanf("%d %d",&s,&e);
	e--;
	for (int i=1;i<=2*n;i++)
	{
		d[i]=d[i-1]+a[i];
	}
	for (int i=1;i<=n;i++)
	{
		val=d[n+e-i+1]-d[n+s-1-i+1];
		if (mn<val)
		{
			mn=val;
			ans=i;
		}
	}
	printf("%I64d\n",ans);
	return 0;
}
