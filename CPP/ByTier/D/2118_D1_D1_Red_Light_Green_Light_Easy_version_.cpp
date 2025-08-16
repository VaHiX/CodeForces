/*
 * Problem URL : https://codeforces.com/problemset/problem/2118/D1
 * Submit Date : 2025-08-14
 */

#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+1;
int T,n,k,q,x,p[N],a[N],l[N],r[N],v[N][2];
map<int,int> L,R;
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>T;
	while(T--)
	{
		cin>>n>>k;
		for(int i=1;i<=n;i++)	cin>>p[i];
		for(int i=1;i<=n;i++)	cin>>a[i];
		L.clear();R.clear();
		for(int i=1;i<=n;i++)
		{
			l[i]=L[(p[i]+a[i])%k];
			L[(p[i]+a[i])%k]=i;
		}
		for(int i=n;i>=1;i--)
		{
			if(!R.count(((p[i]-a[i])%k+k)%k))	r[i]=n+1;
			else	r[i]=R[((p[i]-a[i])%k+k)%k];
			R[((p[i]-a[i])%k+k)%k]=i;
		}
		cin>>q;
		while(q--)
		{
			cin>>x;
			int pos=n+1,dir=0,yes=1;
			for(int j=n;j>=1;j--)	if(p[j]>=x&&(x+a[j])%k==p[j]%k)	pos=j;
			memset(v,0,sizeof(v));
			while(pos!=0&&pos!=n+1)
			{
				if(v[pos][dir])
				{
					cout<<"No\n";
					yes=0;
					break;
				}
				v[pos][dir]=1;
				if(dir)	pos=r[pos];
				else	pos=l[pos];
				dir^=1;
			}
			if(yes)	cout<<"Yes\n";
		}
	}
	return 0;
}