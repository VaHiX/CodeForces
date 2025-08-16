/*
 * Problem URL : https://codeforces.com/problemset/problem/2118/F
 * Submit Date : 2025-08-14
 */

#define ssh(x)<x>
#include ssh(bits/stdc++.h)
#define rfor(x...)for(register x)
#define rep(i,l,r)rfor(ll i=l;i<=r;i++)
#define ref(i,l,r)rfor(ll i=l;i<r;i++)
#define per(i,l,r)rfor(ll i=l;i>=r;i--)
#define rev(i,u,v)rfor(ll i=head[u],v;v=to[i],i;i=next[i])
#define rej(i,s)rfor(ll i=s;i;i=(i-1)&s)
#define re0(i,s)rfor(ll i=s,~i;i=i?(i-1)&s:-1)
#define red(i,n)rfor(ll i=n;i;i>>=1)
#define IO(x...)((*#x!='/'||#x[1])&&(*#x&&freopen(#x".in","r",stdin)&&freopen(#x".out","w",stdout),gc=fgc,pc=fpc,atexit(fout)))
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef const ll cll;
typedef const ld cld;
cll N=1e6+7,mod=1e9+7,iv2=(mod+1)/2,root=3,iz=1<<21,oz=1<<22;
char is[iz],*i1=is,*i2=is,os[oz],*o1=os,*o2=os+oz;
typedef ll aN[N];
int fgc(){
    return i1==i2&&(is==(i2=is+fread(i1=is,1,iz,stdin)))?-1:*i1++;
}
void fout(){
    fwrite(os,o1-os,1,stdout),o1=os;
}
int fpc(int c){
    if(o1==o2)fout();
    return*o1++=c;
}
int(*gc)()=getchar,(*pc)(int)=putchar,wt[126];
int readchar(int l=33,int r=126){
    if(l>r)std::swap(l,r);
    int c=gc();
    for(;c<l||c>r;c=gc()); 
    return c;
}
ll readll(){
    ll x=0,w=1;
    int c=gc();
    for(;c<48||c>57;c=gc())c-45||(w=-w);
    for(;c>47&&c<58;c=gc())x=x*10+c-48;
    return x*w;
}
void writell(cll u,int c=32){
    ll t=0;
    rfor(ull n=u<0?pc(45),-u:u;n;n/=10)wt[++t]=n%10^48;
    for(t||pc(48);t;)pc(wt[t--]);
    c&&pc(c);
}
int mygets(char*s,int c=0){
    char*t=s+1;
    while((*s=gc())<33);
    while((*t=gc())>32)t++;
    c&&(*t++=c),*t=0;
    return t-s;
}
int myputs(const char*s,int c=10){
    const char*t=s;
    while(*t)pc(*t++);
    c&&pc(c);
    return t-s+(c!=0); 
}
cll IO_res=IO(),T=readll();
aN next,to,head,tail,fail,a,b,lst,flag;
ll cnt,top;
void add(cll u,cll v){
    next[tail[u]]=++cnt,to[tail[u]=cnt]=v,next[cnt]=0;
    head[u]||(head[u]=cnt);
}
void dfs(cll u,cll c){
    if(c)a[++top]=c;
    rev(i,u,v)dfs(v,c+1);
}
void calc_str(cll n,cll m){
    (void)m;
    memset(head,cnt=0,(n+2)<<3);
    memset(tail,0,(n+2)<<3);
    memset(flag,0,(n+2)<<3);
    memset(lst,0,(m+2)<<3);
    lst[0]=n+1;
    rep(i,1,n){
        if(lst[a[i]-1])add(lst[a[i]-1],i),flag[i]=1;
        lst[a[i]]=i;
    }
    rep(i,1,n){
        if(!flag[i])add(lst[a[i]-1],i),flag[i]=1;
        lst[a[i]]=i;
    }
    top=0,dfs(n+1,0);
}
ll is_match(aN a,aN b,cll n){
    ll j=fail[1]=0;
    fail[0]=-1;
    rep(i,2,n){
        while(~j&&a[j+1]!=a[i])j=fail[j];
        fail[i]=++j;
    }
    j=0;
    rep(i,1,n){
        while(~j&&a[j+1]!=b[i])j=fail[j];
        if(++j==n)return 1;
    }
    rep(i,1,n){
        while(~j&&a[j+1]!=b[i])j=fail[j];
        if(++j==n)return 1;
    }
    return 0;
}
void calc(ll ID){
    (void)ID;
    cll n=readll(),m=readll();
    rep(i,1,n)a[i]=readll();
    calc_str(n,m),memcpy(b,a,(n+1)<<3);
    rep(i,1,n)a[i]=readll();
    calc_str(n,m);
    //rep(i,1,n)writell(b[i],i==n?10:32);
    //rep(i,1,n)writell(a[i],i==n?10:32);
    myputs(is_match(a,b,n)?"YES":"NO");
}
int main(){
    rep(i,1,T)calc(i);
    return 0;
}
