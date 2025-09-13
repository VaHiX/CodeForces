/*
 * Problem URL : https://codeforces.com/contest/2021/problem/C2
 * Submit Date : 2025-09-10
 */

#include <bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int cnt,a[N],p[N],b[N],n,m,q;
set<int> s[N];
void cal(int x,int f)
{
	for(int i=x;i<=x+1;i++)
	{
		if(i==1)continue;
		int x=1e9,y=1e9;
		if(s[i].size())y=*s[i].begin();
		if(s[i-1].size())x=*s[i-1].begin();
		cnt+=(x<=y)*f;
	}
} 
void solve()
{
	cin>>n>>m>>q;
	for(int i=1;i<=n;i++)cin>>a[i],p[a[i]]=i;
	for(int i=1;i<=m;i++)
	{
		cin>>b[i],b[i]=p[b[i]];//b[i]对应 
		s[b[i]].insert(i);//存a的每个位置对应的b 
	}
	cnt=0;
	for(int i=2;i<=n;i++)
	{
		int x=1e9,y=1e9;
		if(s[i].size())y=*s[i].begin();
		if(s[i-1].size())x=*s[i-1].begin();
		cnt+=(x<=y);
	}
	if(cnt==n-1)cout<<"YA"<<'\n';
	else cout<<"TIDAK"<<'\n';
	for(int i=1;i<=q;i++)
	{
		int x,y;cin>>x>>y;
		y=p[y];
		cal(b[x],-1);
		s[b[x]].erase(x);
		cal(b[x],1);
		b[x]=y;
		cal(y,-1);
		s[y].insert(x);
		cal(y,1);
		if(cnt==n-1)cout<<"YA"<<'\n';
		else cout<<"TIDAK"<<'\n';
	}
	for(int i=1;i<=n;i++)s[i].clear();
}
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0); 
	int t;cin>>t;
	while(t--)solve();
	return 0;
} 