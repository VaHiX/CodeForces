/*
 * Problem URL : https://codeforces.com/contest/1641/problem/A
 * Submit Date : 2025-08-31
 */

#include<bits/stdc++.h>
using namespace std;
int n,x,a[1000005];
multiset<int>mp;
int main()
{
	int i,T;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&x),mp.clear();
		for(i=1; i<=n; ++i)
		{
			scanf("%d",a+i);
		}
		sort(a+1,a+n+1);
		for(i=1; i<=n; ++i)
			if(a[i]%x==0&&mp.find(a[i]/x)!=mp.end())
				mp.erase(mp.find(a[i]/x));
			else mp.insert(a[i]);
		printf("%d\n",int(mp.size()));
	}
	return 0;
}
