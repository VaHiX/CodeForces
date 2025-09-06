/*
 * Problem URL : https://codeforces.com/contest/1019/problem/A
 * Submit Date : 2025-09-02
 */

#include<bits/stdc++.h>
using namespace std;
vector<int> v1[3001],v2[3001];
int main()
{
ios_base::sync_with_stdio(false);
cin.tie(NULL);
long long int i,j,n,m,p,c,sum=0,k=0,l,total,ans=1e16;
priority_queue<long long int>Q;
cin>>n>>m;
	for(i=0;i<n;i++)
	{
	cin>>p>>c;
	v1[p].push_back(c);
		if(p!=1)
		sum+=c;
	}
	for(i=2;i<=m;i++)
	{
	sort(v1[i].begin(),v1[i].end());
		for(j=v1[i].size();j--;)v2[v1[i].size()-j-1].push_back(v1[i][j]);
	}
total=n-v1[1].size();
	for(i=0;i<=n-v1[1].size();i++)
	{
	l=i+v1[1].size()-1;
		if((l<0)&&(m>1))
		continue;
		for(;k<l;k++)
		{
			for(j=v2[k].size();j--;)sum-=v2[k][j],Q.push(-v2[k][j]),total--;
		}
		for(;total<i;total++)
		sum-=Q.top(),Q.pop();
	ans=min(ans,sum);
	}	
cout<<ans<<endl;
return 0;
}		
	
