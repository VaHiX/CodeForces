/*
 * Problem URL : https://codeforces.com/contest/1137/problem/A
 * Submit Date : 2025-09-02
 */

#include<bits/stdc++.h>
using namespace std;
pair<int,int> tmp[1010];
int n,m,a[1010][1010],num[1010][1010],mx1[1010],mx2[1010],num2[1010][1010];
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&a[i][j]);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)tmp[j]=make_pair(a[i][j],j);
		sort(tmp+1,tmp+1+m);
		int tot=0;
		for(int j=1;j<=m;j++)
		{
			if(tmp[j].first!=tmp[j-1].first)tot++;
			num[i][tmp[j].second]=tot;
		}
		mx1[i]=tot;
	}
	for(int i=1;i<=m;i++)
	{
		for(int j=1;j<=n;j++)tmp[j]=make_pair(a[j][i],j);
		sort(tmp+1,tmp+1+n);
		int tot=0;
		for(int j=1;j<=n;j++)
		{
			if(tmp[j].first!=tmp[j-1].first)tot++;
			num2[tmp[j].second][i]=tot;
		}
		mx2[i]=tot;
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			int mn=max(num[i][j],num2[i][j]);
			printf("%d ",max(mn+mx1[i]-num[i][j],mn+mx2[j]-num2[i][j]));
			//cout<<mn<<endl;
		}
		puts("");
	}
	return 0;
}
