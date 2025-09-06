/*
 * Problem URL : https://codeforces.com/contest/1118/problem/F1
 * Submit Date : 2025-08-29
 */

#include<bits/stdc++.h>
using namespace std;
const int N=300002;
struct node{
	int to,ne;
}e[N<<1];
int n,i,sum1,sum2,s1[N],s2[N],x,y,h[N],a[N],ans,tot;
void add(int x,int y){e[++tot]=(node){y,h[x]},h[x]=tot;}
void dfs(int u,int fa){
	s1[u]=a[u]==1,s2[u]=a[u]==2;
	for (int i=h[u],v;i;i=e[i].ne)
		if ((v=e[i].to)!=fa){
			dfs(v,u),s1[u]+=s1[v],s2[u]+=s2[v];
			if (s1[v]==sum1 && !s2[v] || s2[v]==sum2 && !s1[v]) ans++;
		}
}
int main(){
	scanf("%d",&n);
	for (i=1;i<=n;i++) scanf("%d",&a[i]),sum1+=a[i]==1,sum2+=a[i]==2;
	for (i=1;i<n;i++) scanf("%d%d",&x,&y),add(x,y),add(y,x);
	dfs(1,0);
	printf("%d",ans);
}