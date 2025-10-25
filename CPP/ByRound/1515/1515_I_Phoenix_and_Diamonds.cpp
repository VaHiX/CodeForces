/*
 * Problem URL : https://codeforces.com/contest/1515/problem/I
 * Submit Date : 2025-09-11
 */

// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
#include <bits/stdc++.h>
// #define int long long
#define i64 long long
#define pii pair <int, int> 
using namespace std;
inline int read(void) {
    int x=0,sgn=1; char ch=getchar();
    while(ch<48||57<ch) {if(ch==45)sgn=0;ch=getchar();}
    while(47<ch&&ch<58) {x=x*10+ch-48;   ch=getchar();}
    return sgn? x:-x;
}
inline i64 read64(void) {
    i64 x=0; int sgn=1; char ch=getchar();
    while(ch<48||57<ch) {if(ch==45)sgn=0;ch=getchar();}
    while(47<ch&&ch<58) {x=x*10+ch-48;   ch=getchar();}
    return sgn ? x:-x;
}
void write(i64 x) {
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
/*
    write((Ans%p+p)%p); pls
*/
const i64 inf=100000000000000000;
int n,q;
int P[200005];
struct diamond {
    int cnt,w,v,i;
} A[200005];
i64 cnt[200005];
int w[200005],v[200005];
#define lch (x<<1)
#define rch (x<<1|1)
i64 Sw[800005][19],Sv[800005][19],Mi[800005][19];
inline void calc(int x,int p) {
    for(int i=0; i<=18; ++i) {
		Sw[x][i]=Sv[x][i]=0; Mi[x][i]=inf;
		if(w[p]<(1<<i)) Sv[x][i]=1ll*cnt[p]*v[p],Sw[x][i]=1ll*cnt[p]*w[p];
		else if(w[p]<(1<<i+1)&&cnt[p]) Mi[x][i]=w[p];
	}
}
inline void pushup(int x) {
    for(int i=0; i<=18; ++i) {
        Sw[x][i]=Sw[lch][i]+Sw[rch][i];
        Sv[x][i]=Sv[lch][i]+Sv[rch][i];
        Mi[x][i]=min(Mi[lch][i],Sw[lch][i]+Mi[rch][i]);
    }
}
void build(int x,int l,int r) {
    if(l==r) return calc(x,l),void();
    int mid=(l+r)>>1;
    build(lch,l,mid);
    build(rch,mid+1,r);
    pushup(x);
}
void upd(int x,int l,int r,int p) {
    if(l==r) return calc(x,p),void();
    int mid=(l+r)>>1;
    if(p<=mid) upd(lch,l,mid,p);
    else upd(rch,mid+1,r,p);
    pushup(x);
}
i64 c; int o;
i64 qry(int x,int l,int r) {
    if(l==r) {
        int cur=min(cnt[l],c/w[l]);
        // cerr<<"brute "<<l<<' '<<cur<<endl;
        c-=1ll*cur*w[l]; while(o&&c<(1ll<<o)-1) --o;
        return 1ll*cur*v[l];
    }
    if(Sw[x][o+1]<=c) {
        // cerr<<"clear "<<o+1<<"["<<l<<' '<<r<<"]"<<Sv[x][o+1]<<endl;
        i64 res=Sv[x][o+1];
        c-=Sw[x][o+1]; while(o&&c<(1ll<<o)-1) --o;
        return res;
    }
    if(Sw[x][o]<=c&&c<Mi[x][o]) {
        i64 res=Sv[x][o];
        c-=Sw[x][o]; while(o&&c<(1ll<<o)-1) --o;
        return res;
    }
    int mid=(l+r)>>1;
	return qry(lch,l,mid)+qry(rch,mid+1,r); 
}
signed main() {
    // freopen("localinput","r",stdin);
    // freopen("localoutput","w",stdout);
    n=read(); q=read();
    for(int i=1; i<=n; ++i) A[i].cnt=read(),A[i].w=read(),A[i].v=read(),A[i].i=i;
    sort(A+1,A+n+1,[&](const diamond&A,const diamond&B){ return A.v^B.v ? A.v>B.v : A.w<B.w; });
    for(int i=1; i<=n; ++i) P[A[i].i]=i,cnt[i]=A[i].cnt,w[i]=A[i].w,v[i]=A[i].v;
    build(1,1,n);
    int t,x,k;
    int cntq=0;
    for(int T=1; T<=q; ++T) {
        t=read();
        if(t<=2) {
            k=read(); (t==2) && (k=-k); 
            x=P[read()];
            cnt[x]+=k;
            upd(1,1,n,x);
        } else {
            ++cntq;
            c=read64(); o=17; while(o&&c<(1ll<<o)-1) --o;
            write(qry(1,1,n)); puts("");
        }
    }
    // fprintf(stderr,"%.4lf\n",1.0*clock()/CLOCKS_PER_SEC);
    return 0;
}