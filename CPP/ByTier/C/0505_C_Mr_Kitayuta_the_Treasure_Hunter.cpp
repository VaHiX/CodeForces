/*
 * Problem URL : https://codeforces.com/contest/505/problem/C
 * Submit Date : 2025-09-05
 */

#include<bits/stdc++.h>//
using namespace std;
const int ds=305;
int n,m,p,f[30005][707],v[30005],ans;

signed main()
{
	memset(f,0x80,sizeof(f));
	ios_base::sync_with_stdio(false);
	cin>>n>>m;
	for(int i=1;i<=n;v[p]++,i++)
		cin>>p;
	ans=f[m][ds]=v[0]+v[m];
	for(int i=m+1;i<=p;i++)
		for(int j=-ds;j<=ds;j++)
		{
			if(((m+j)>0)&&((m+j)<=i))
				f[i][ds+j]=max(f[i][ds+j],max({f[i-(m+j)][ds+j],f[i-(m+j)][ds+j-1],f[i-(m+j)][ds+j+1]})+v[i]);
			ans=max(ans,f[i][ds+j]);
		}
	cout<<ans<<endl;
	return 0;
}