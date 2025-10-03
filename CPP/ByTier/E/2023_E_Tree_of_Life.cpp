/*
 * Problem URL : https://codeforces.com/contest/2023/problem/E
 * Submit Date : 2025-09-10
 */

#include<bits/stdc++.h>
#ifdef ONLINE_JUDGE
	#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
	char buf[1<<21],*p1=buf,*p2=buf;
#endif
using namespace std;typedef long long ll;int read(){int num=0,f=1;char c;while(!isdigit(c=getchar()))if(c=='-')f=-1;while(isdigit(c))num=num*10+(c&15),c=getchar();return num*f;}void write(ll x,char ch=' '){int F[20],cnt=0;if(!x)putchar('0');if(x<0)putchar('-'),x=-x;while(x)F[cnt++]=x%10+'0',x/=10;while(cnt)putchar(F[--cnt]);putchar(ch);}
namespace Main
{
    const int N=500010;int n,d[N],head[N],to[N<<1],nxt[N<<1],tot,x,y,xx,yy;ll f[N],g[N],z,zz,ans;void link(int x,int y){to[++tot]=y,++d[y],nxt[tot]=head[x],head[x]=tot;}
    void dfs(int x,int Fa=0){int xx=d[x]-1;ll s=0;pair<ll,ll>mx=make_pair(0,0);for(int i=head[x];i;i=nxt[i])if(to[i]!=Fa){dfs(to[i],x);
    if(f[to[i]]<xx)yy=min(g[to[i]],(xx+1-f[to[i]])/2),f[to[i]]+=2*yy,g[to[i]]-=yy;if(f[to[i]]<xx)ans-=f[to[i]];else ans-=xx,f[to[i]]-=xx,s+=f[to[i]],mx=max(mx,{f[to[i]],g[to[i]]});g[x]+=g[to[i]]; }
    if(mx.first*2>s)s+=(g[x]-mx.second)*2,g[x]=mx.second;z=min(s/2,s-mx.first),g[x]+=z,f[x]=s+xx-2*z;}
    void main()
    {
        n=read(),memset(d,0,(n+1)<<2),memset(f,0,(n+1)<<3),memset(g,0,(n+1)<<3),memset(head,0,(n+1)<<2),ans=tot=0;for(int i=n;--i;)x=read(),y=read(),link(x,y),link(y,x);for(int i=1;i<=n;++i)ans+=d[i]*(d[i]-1ll)/2;
        dfs(1),write(ans-g[1],'\n');
    }
}
int main()
{
    const bool base=1,IO=1;int T;if(!base)T=1;else if(IO)T=read();else ios::sync_with_stdio(0),cin>>T;for(;T--;)Main::main();
    return 0;
}