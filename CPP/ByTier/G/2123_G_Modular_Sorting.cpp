/*
 * Problem URL : https://codeforces.com/problemset/problem/2123/G
 * Submit Date : 2025-08-14
 */

#include<bits/stdc++.h>
#pragma GCC optimize("O3")
#define N 500005
#define M 205
using namespace std;
int n,m,q,cnt,a[N],c[M],to[N],d[N];
void solve()
{
	cin>>n>>m>>q;
	for(int i=1;i<=cnt;i++) to[d[i]]=0;
	cnt=0;
	for(int i=1;i<=n;i++) cin>>a[i];
	while(q--)
	{
		int op,x,y;
		cin>>op>>x;
		if(op==1)
		{
			cin>>y;
			for(int i=1;i<=cnt;i++)
			{
				if(x>1) if(a[x-1]%d[i]>a[x]%d[i]) c[i]--;
				if(x<n) if(a[x]%d[i]>a[x+1]%d[i]) c[i]--;
				if(x>1) if(a[x-1]%d[i]>y%d[i]) c[i]++;
				if(x<n) if(y%d[i]>a[x+1]%d[i]) c[i]++;
			}
			a[x]=y;
		}
		else
		{
			int num=__gcd(m,x),len=m/num;
			if(!to[num])
			{
				to[num]=++cnt;
				d[cnt]=num;
				c[cnt]=1;
				for(int i=2;i<=n;i++) if(a[i-1]%d[cnt]>a[i]%d[cnt]) c[cnt]++;
			}
			if(c[to[num]]<=len) cout<<"YES\n";
			else if(c[to[num]]==len+1)
			{
				if(a[n]%d[to[num]]<m%num) cout<<"YES\n";
				else cout<<"NO\n";
			}
			else cout<<"NO\n";
		}
	}
	return;
}
int main()
{
	ios::sync_with_stdio(0);
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
}