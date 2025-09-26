/*
 * Problem URL : https://codeforces.com/contest/2023/problem/C
 * Submit Date : 2025-09-10
 */

#include<iostream>
#include<cstdio>
#include<queue>
using namespace std;
int n,m,k;
struct G{
	int tot,to[500005],nxt[500005],lst[500005];
	int a[500005],vi[500005],dis[500005];
	int s[1000005][2],id,cnt;
	void init(){
		tot=cnt=0;
		for(int i=1;i<=n;i+=1) vi[i]=lst[i]=0;
		return;
	}
	void add(int x,int y){
		to[++tot]=y;
		nxt[tot]=lst[x];
		lst[x]=tot;
		return;
	}
	void work(int flag){
		queue<int>q; int x,y;
		q.push(1); vi[1]=1;
		while(!q.empty()){
			x=q.front(); q.pop(); cnt+=a[x];
			for(int i=lst[x];i;i=nxt[i]){
				if(vi[y=to[i]]) continue;
				if((dis[y]=dis[x]+1)>=k) dis[y]-=k;
				vi[y]=1; q.push(y);
			}
		}
		for(int i=0;i<k;i+=1) s[i][0]=s[i][1]=0;
		for(int i=1;i<=n;i+=1) s[dis[i]][a[i]^flag]+=1;
		if(flag){
			cnt=n-cnt;
			for(int i=k+1;i>1;i-=1){
				s[i][0]=s[i-2][0];
			}
			s[1][0]=s[k+1][0];
			s[0][0]=s[k][0];
		}
		for(int i=0;i<k;i+=1){
			s[i+k][0]=s[i][0]; s[i+k][1]=s[i][1];
		}
		/*for(int i=0;i<(k<<1);i+=1){
			printf("(%d,%d) ",s[i][0],s[i][1]);
		}*/
		id=-1;
		for(int i=0,j,l;i<2*k;){
			j=i; l=i+1;
			while(s[j][0]<s[l][0]||(s[j][0]==s[l][0]&&s[j][1]<=s[l][1])){
				if(s[j][0]==s[l][0]&&s[j][1]==s[l][1]) j+=1,l+=1;
				else j=i,l+=1;
			}
			while(i<=j){
				if(i+(l-j)>=k){
					id=i; break;
				}
				i+=l-j;
			}
			if(~id) break;
		}
		//printf("%d\n",id);
		return;
	}
}G[2];
void solve(){
	scanf("%d%d",&n,&k);
	for(int k=0;k<2;k+=1){
		for(int i=1;i<=n;i+=1) scanf("%d",&G[k].a[i]);
		scanf("%d",&m); G[k].init();
		for(int i=1;i<=m;i+=1){
			int x,y; scanf("%d%d",&x,&y); G[k].add(x,y);
		}
		G[k].work(k);
	}
	if(G[0].cnt==G[1].cnt){
		if(!G[0].cnt||G[0].cnt==n) printf("YES\n");
		else{
			int flag=1;
			for(int i=0;i<k;i+=1){
				int p=G[0].id,q=G[1].id;
				if(G[0].s[p+i][0]!=G[1].s[q+i][0]) flag=0;
				if(G[0].s[p+i][1]!=G[1].s[q+i][1]) flag=0;
			}
			if(flag) printf("YES\n");
			else printf("NO\n");
		}
	}
	else printf("NO\n");
	return;
}
int main(){
	int t; scanf("%d",&t);
	while(t--) solve();
	return 0;
}
