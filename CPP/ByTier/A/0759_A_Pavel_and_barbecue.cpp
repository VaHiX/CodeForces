/*
 * Problem URL : https://codeforces.com/contest/759/problem/A
 * Submit Date : 2025-09-04
 */

#include<cstdio>
#include<algorithm>
using namespace std;
int ans,n,i,j,p[200005],vis[200005],b[200005],cnt;
int main()
{
    ans=0;
    cnt=0;
	scanf("%d",&n);
	for(i=1;i<=n;i++)scanf("%d",&p[i]);
	for(i=1;i<=n;i++)
	{
		scanf("%d",&b[i]);
		if(b[i]==1)cnt++;
	}
	if(cnt%2==1)ans=0;
	else ans=1;
	cnt=0;
    for(i=1;i<=n;i++)
	{
		if(!vis[i])
		{
			cnt++;
			for(j=i;!vis[j];j=p[j])vis[j]=1;
		}
	}
	if(cnt>1)ans+=cnt;
	printf("%d",ans);
}