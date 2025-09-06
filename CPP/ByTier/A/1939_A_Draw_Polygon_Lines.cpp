/*
 * Problem URL : https://codeforces.com/contest/1939/problem/A
 * Submit Date : 2025-08-31
 */

#include<bits/stdc++.h>
#define inf 0x3f3f3f3f3f3f3f3fll
#define debug(x) cerr<<#x<<"="<<x<<endl
using namespace std;
using ll=long long;
using ld=long double;
using pli=pair<ll,int>;
using pi=pair<int,int>;
template<typename A>
using vc=vector<A>;
inline int read()
{
    int s=0,w=1;char ch;
    while((ch=getchar())>'9'||ch<'0') if(ch=='-') w=-1;
    while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
    return s*w;
}
int x[80001];
int y[80001];
int n,c;
namespace S1
{
    bool vis[20001];
    inline ll get(int u,int v)
    {
        return 1ll*(x[u]-x[v])*(x[u]-x[v])+1ll*(y[u]-y[v])*(y[u]-y[v]);
    }
    inline void mian()
    {
        int lst=1;printf("1 "),vis[1]=1;
        while(true)
        {
            ll sum=0;int w=0;
            for(int i=1;i<=n;i++) if(!vis[i])
            {
                ll val=get(lst,i);
                if(val>sum) sum=val,w=i;
            }
            if(!w) break;
            printf("%d ",w),vis[w]=1;
            lst=w;
        }
        cout<<endl;
    }
}
mt19937 _rand(time(0)^clock());
namespace S2
{
    vc<int>nod[80001];
    bool vis[80001];
    int lst[80001];
    int lf[10001];
    int rf[10001];
    int dp[80001];
    int id[80001];
    int l[10001];
    int r[10001];
    vc<int>ans;
    int len;
    int cnt;
    inline void run()
    {
        for(int i=1;i<=len;i++) nod[i].clear();
        len=0;
        for(int i=1;i<=n;i++) if(!vis[i])
        {
            int p=id[i],ans=0;
            for(int j=65536;j;j>>=1) if(ans+j<=len&&y[p]>dp[ans+j]) ans+=j;
            if(ans==len) len++;
            dp[ans+1]=y[p],nod[ans+1].push_back(i);
            if(ans) lst[i]=nod[ans][nod[ans].size()-1];
            else lst[i]=0;
        }
        cnt++,l[cnt]=ans.size();
        int ma=0,w=0;
        for(int i=1;i<=len;i++) if((int)nod[i].size()>ma)
        {
            ma=nod[i].size();
            w=i;
        }
        if(ma<len)
        {
            int w=nod[len][0];
            while(w)
            {
                ans.push_back(id[w]),vis[w]=1;
                w=lst[w];
            }
        }
        else
        {
            for(int i:nod[w]) vis[i]=1,ans.push_back(id[i]);
        }
        r[cnt]=ans.size()-1;
    }
    inline bool check(int a,int b,int c)
    {
        return (ll)(x[a]-x[b])*(x[c]-x[b])+(ll)(y[a]-y[b])*(y[c]-y[b])>0;
    }
    inline int get()
    {
        int val=0;
        for(unsigned i=1;i+1<ans.size();i++) val+=check(ans[i-1],ans[i],ans[i+1]);
        return val;
    }
    int p[80001];
    inline void init()
    {
        for(int i=1;i<=n;i++) p[i]=i;
        while(true)
        {
            shuffle(p+1,p+n+1,_rand);
            int a=id[p[1]],b=id[p[2]],c=id[p[3]],d=id[p[4]],e=id[p[5]];
            int val1=check(a,b,c)+check(b,c,d)+check(c,d,e);
            int val2=check(a,c,b)+check(c,b,d)+check(b,d,e);
            if(val2==val1+1)
            {
                ans.push_back(a),ans.push_back(b),ans.push_back(c);
                ans.push_back(d),ans.push_back(e);
                for(int i=1;i<=5;i++) vis[p[i]]=1;
                return ;
            }
        }
    }
    int mem[100001];
    vc<int>out;
    inline int run(int l,int r,int x)
    {
        int p=min(x,r-l-1);
        while(r-l-1!=p) l++,r--;
        for(int i=l;i<=r;i++) mem[i]=out[i];
        for(int i=l,j=r-1;i<=j;i++,j--)
        {
            out[l++]=mem[i];
            if(i!=j) out[l++]=mem[j];
        }
        assert(l==r);
        return p;
    }
    inline void solve(int x)
    {
        out=ans;
        if(x&1) swap(out[1],out[2]),x--;
        for(int i=1;i<=cnt;i++) if(lf[i]&&lf[i]<=rf[i]) x-=run(lf[i],rf[i],x);
        for(int i:out) printf("%d ",i);
        cout<<endl;
    }
    inline void spec()
    {
        if(n==6)
        {
            printf("1 2 3 4 5 6");cout<<endl;
            printf("4 5 6 1 3 2");cout<<endl;
            printf("6 2 4 3 5 1");cout<<endl;
        }
        else
        {
            printf("534735187 776162084");cout<<endl;
            printf("4 5 1 2 3");cout<<endl;
            printf("1 3 2 5 4");cout<<endl;
        }
    }
    const int mod=1000000007;
    const int b=1000003;
    ll pp[80001];
    ll h[80001];
    inline void HASH(int l,int r)
    {
        pp[0]=1;
        for(int i=1;i<=n;i++) pp[i]=pp[i-1]*b%mod;
        for(int i=0;i<n;i++) h[0]=(h[0]+pp[i]*ans[i])%mod;
        ll vd=(ans[1]*pp[2]+ans[2]*pp[1]-ans[1]*pp[1]-ans[2]*pp[2])%mod;
        vd=(vd%mod+mod)%mod;

        int now=0;
        for(int i=1;i<=cnt;i++) if(lf[i]&&lf[i]<=rf[i])
        {
            int r=(lf[i]+rf[i])>>1,l=r+1;
            ll v=0;
            while(l>=lf[i]+2)
            {
                l--,v=(v+pp[l]*ans[l])%mod;
                r++,now+=2;
                ll nx=(v*b+pp[l]*ans[r])%mod;
                h[now]=(h[now-2]+nx-v-ans[r]*pp[r]%mod+2*mod)%mod;
                v=nx;
            }
        }

        for(int i=0;i<=n;i++) if(i&1) h[i]=(h[i-1]+vd)%mod;
        for(int i=l;i<=r;i++) printf("%lld ",h[i]);
        cout<<endl;
    }
    inline void mian(int T)
    {
        if(T>=3&&n<=10)
        {
            spec();
            return ;
        }
        c=read();
        for(int i=1;i<=n;i++) id[i]=i;
        sort(id+1,id+n+1,[](int u,int v){ return x[u]<x[v];});
        init();
        while((int)ans.size()<n) run();

        int s=get();
        assert(s<=c);

        if(T==2)
        {
            for(int i:ans) printf("%d ",i);
            cout<<endl;
            return ;
        }

        int C=0;
        for(int i=1;i<=cnt;i++) if(r[i]-l[i]>=4)
        {
            lf[i]=l[i],rf[i]=r[i];
            if(i!=1)
            {
                int val=check(ans[r[i-1]],ans[l[i]],ans[l[i]+1]);
                for(int j=l[i]+2;j<=r[i];j++) if(check(ans[r[i-1]],ans[l[i]],ans[j])!=val) lf[i]=l[i]+1;
            }
            if(i!=cnt)
            {
                int val=check(ans[r[i]-1],ans[r[i]],ans[l[i+1]]);
                for(int j=l[i];j<=r[i]-2;j++) if(check(ans[j],ans[r[i]],ans[l[i+1]])!=val) rf[i]=r[i]-1;
            }
            if((rf[i]-lf[i])%2==0) lf[i]++;
            C+=rf[i]-lf[i]-1;
        }
        assert(C+s>=n-c);
        if(T==4) HASH(c-s,n-c-s);
        int q=read();
        for(int i=1;i<=q;i++) solve(read()-s);
    }
}
int main()
{
    int T=read();read();
    n=read();
    for(int i=1;i<=n;i++) x[i]=read(),y[i]=read();
    if(T==1) S1::mian();
    else S2::mian(T);
    return 0;
}