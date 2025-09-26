/*
 * Problem URL : https://codeforces.com/contest/125/problem/E
 * Submit Date : 2025-09-11
 */

#include<bits/stdc++.h>
using namespace std;
double weight;
struct edge
{
	int u,v,used,id,w,flag;
	bool operator<(const edge &b)const{return w+weight*flag<b.w+weight*b.flag;}
}e[200001];
const double eps=1e-10;
int n,m,k,p[10001];
int find(int x){return p[x]==x?x:p[x]=find(p[x]);}
int count(double x,int final=0)
{
	weight=x;
	for(int i=0;i<m;i++)e[i].used=0;
	for(int i=1;i<=n;i++)p[i]=i;
	sort(e,e+m);
	int ans=0;
	for(int i=0;i<m;i++)
	{
		int x=find(e[i].u),y=find(e[i].v);
		if(x!=y&&!(final&&ans==k&&e[i].flag))
		{
			p[x]=y;
			e[i].used=1;
			if(e[i].flag)ans++;
		}
	}
	return ans;
}
int main()
{
	scanf("%d%d%d",&n,&m,&k);
	for(int i=0;i<m;i++)scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w),e[i].id=i+1,e[i].flag=(e[i].u==1||e[i].v==1);
	double l=-1e5,r=1e5+.3;
	while(l+eps<r)
	{
		double m=(l+r)/2;
		int res=count(m);
		if(res<k)r=m;
		else l=m;
		if(res==k) break;
	}
	count(l,1);
	int cnt=0,cntk=0;
	for(int i=0;i<m;i++)cnt+=e[i].used,cntk+=e[i].used*e[i].flag;
	if(cnt!=n-1||cntk!=k){puts("-1");return 0;}
	printf("%d\n",n-1);
	for(int i=0;i<m;i++)
		if(e[i].used)printf("%d ",e[i].id);
	puts("");
}
