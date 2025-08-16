/*
 * Problem URL : https://codeforces.com/problemset/problem/1863/H
 * Submit Date : 2025-08-14
 */

/*
Author: QAQAutoMaton
Lang: C++
Code: H.cpp
Mail: lk@qaq-am.com
Blog: https://www.qaq-am.com/
*/
#include<bits/stdc++.h>
#define debug(qaq...) fprintf(stderr,qaq)
#define DEBUG printf("Passing [%s] in LINE %d\n",__FUNCTION__,__LINE__)
#define Debug debug("Passing [%s] in LINE %d\n",__FUNCTION__,__LINE__)
#define all(x) x.begin(),x.end()
#define x first
#define y second
#define unq(a) sort(all(a)),a.erase(unique(all(a)),a.end())
using namespace std;
typedef unsigned uint;
typedef long long ll;
typedef unsigned long long ull;
typedef complex<double> cp;
typedef pair<int,int> pii;
int inf;
const double eps=1e-8;
const double pi=acos(-1.0);
template<class T,class T2>int chkmin(T &a,T2 b){return a>b?a=b,1:0;}
template<class T,class T2>int chkmax(T &a,T2 b){return a<b?a=b,1:0;}
template<class T>T sqr(T a){return a*a;}
template<class T,class T2>T mmin(T a,T2 b){return a<b?a:b;}
template<class T,class T2>T mmax(T a,T2 b){return a>b?a:b;}
template<class T>T aabs(T a){return a<0?-a:a;}
template<class T>int dcmp(T a,T b){return a>b;}
template<int *a>int cmp_a(int x,int y){return a[x]<a[y];}
template<class T>bool sort2(T &a,T &b){return a>b?swap(a,b),1:0;}
template<class T,class ...T2>T mmin(T a,T2 ...b){return mmin(a,mmin(b...));}
template<class T,class ...T2>T mmax(T a,T2 ...b){return mmax(a,mmax(b...));}
#define min mmin
#define max mmax
#define abs aabs
struct __INIT__{
	__INIT__(){
		fill((unsigned char*)&inf,(unsigned char*)&inf+sizeof(inf),0x3f);
	}
}__INIT___;
namespace io {
	const int SIZE = (1 << 21) + 1;
	char ibuf[SIZE], *iS, *iT, obuf[SIZE], *oS = obuf, *oT = oS + SIZE - 1, c, qu[55]; int f, qr;
	// getchar
	#define gc() (iS == iT ? (iT = (iS = ibuf) + fread (ibuf, 1, SIZE, stdin), (iS == iT ? EOF : *iS ++)) : *iS ++)
	// print the remaining part
	inline void flush () {
		fwrite (obuf, 1, oS - obuf, stdout);
		oS = obuf;
	}
	// putchar
	inline void putc (char x) {
		*oS ++ = x;
		if (oS == oT) flush ();
	}
	template<typename A>
	inline bool read (A &x) {
		for (f = 1, c = gc(); c < '0' || c > '9'; c = gc()) if (c == '-') f = -1;else if(c==EOF)return 0;
		for (x = 0; c <= '9' && c >= '0'; c = gc()) x = x * 10 + (c & 15); x *= f;
		return 1;
	}
	inline bool read (char &x) {
		while((x=gc())==' '||x=='\n' || x=='\r');
		return x!=EOF;
	}
	inline bool read(char *x){
		while((*x=gc())=='\n' || *x==' '||*x=='\r');
		if(*x==EOF)return 0;
		while(!(*x=='\n'||*x==' '||*x=='\r'||*x==EOF))*(++x)=gc();
		*x=0;
		return 1;
	}
	template<typename A,typename ...B>
	inline bool read(A &x,B &...y){
		return read(x)&&read(y...);
	}
	template<typename A>
	inline bool write (A x) {
		if (!x) putc ('0'); if (x < 0) putc ('-'), x = -x;
		while (x) qu[++ qr] = x % 10 + '0',  x /= 10;
		while (qr) putc (qu[qr --]);
		return 0;
	}
	inline bool write (char x) {
		putc(x);
		return 0;
	}
	inline bool write(const char *x){
		while(*x){putc(*x);++x;}
		return 0;
	}
	inline bool write(char *x){
		while(*x){putc(*x);++x;}
		return 0;
	}
	template<typename A,typename ...B>
	inline bool write(A x,B ...y){
		return write(x)||write(y...);
	}
	//no need to call flush at the end manually!
	struct Flusher_ {~Flusher_(){flush();}}io_flusher_;
}
using io :: read;
using io :: putc;
using io :: write;
const int p=998244353;
int fpm(int a,int b){
	int c=1;
	for(;b;b>>=1,a=(ll)a*a%p)if(b&1)c=(ll)c*a%p;
	return c;
}
namespace run{
	int n;
	vector<int> to[200005];
	int f[19][200005];
	int fa[200005],d[200005];
	int dfn[200005],low[200005],val[200005],t;
	void dfs(int x){
		f[0][x]=fa[x];
		dfn[x]=++t;
		val[t]=x;
		for(int i=1;i<=18;++i)f[i][x]=f[i-1][f[i-1][x]];
		for(auto i:to[x])dfs(i);
		low[x]=t;
	}
	int lca(int x,int y){
		x=val[x];y=val[y];
		if(d[x]<d[y])swap(x,y);
		for(int i=18;~i;--i)if(d[x]-(1<<i)>=d[y])x=f[i][x];
		if(x==y)return x;
		for(int i=18;~i;--i)if(f[i][x]!=f[i][y]){x=f[i][x];y=f[i][y];}
		return f[0][x];
	}

	int *s1[20000005],ov1[2000005],t1,t2,t3;
	void setv(int &a,int b){
		s1[++t1]=&a;ov1[t1]=a;a=b;
	}
	void revert1(){
		*s1[t1]=ov1[t1];--t1;
	}
	set<int> **s2[1000005],*ov2[1000005];//???
	set<int> *s3[10000005];
	int dlv[10000005];//???
	bitset<10000005>tp;
	void setv(set<int> * &a,set<int> *b){
		s2[++t2]=&a;
		ov2[t2]=a;a=b;
	}
	void revert2(){
		*s2[t2]=ov2[t2];--t2;
	}
	void Ins(set<int> *x,int y){
		s3[++t3]=x;
		dlv[t3]=y;
		tp[t3]=0;
		x->insert(y);
	}
	void Del(set<int> *x,set<int>::iterator y){
		s3[++t3]=x;
		dlv[t3]=*y;
		tp[t3]=1;
		x->erase(y);
	}
	void revert3(){
		if(tp[t3])s3[t3]->insert(dlv[t3]);
		else s3[t3]->erase(dlv[t3]);
		--t3;
	}

	int pw[200005];
	int nxt[200005];
	set<int> stv[6000005],*cur=stv;
	set<int> *nodes[200005],*oval[1<<18|5];
	int mx[1<<18|5];
	int a[200005],at[200005];
	pii cmx(-1,0);
	int less(pii a,pii b){
		if(a.x<0)return 1;
		if((!a.x)!=(!b.x))return !a.x;
		if(!a.x && !b.x)return 0;
		// a.x*2^a.y+2c<y*2^d?
		if(abs(a.y-b.y)>30)return a.y<b.y;
		int v=min(a.y,b.y);
		a.y-=v;
		b.y-=v;
		return (((ll)a.x)<<a.y) < (((ll)b.x)<<b.y);
	}
	int equal(pii a,pii b){
		// a.x*2^a.y+2c<y*2^d?

		if((!a.x)!=(!b.x))return 0;
		if(!a.x && !b.x)return 1;
		if(abs(a.y-b.y)>30)return 0;
		int v=min(a.y,b.y);
		a.y-=v;
		b.y-=v;
		return (((ll)a.x)<<a.y) == (((ll)b.x)<<b.y);
	}

	const int lim=1<<30;
	int xdp[200005];
	int merge(int x,int y){
		return x==y?(x<<1|1):(max(x,y)<<1);
	
	}
	void setval(int x,int y){
		--y;
		if(!y){
			int dx=0;
			if(mx[y]>dx){
				return;
			}
			if(mx[y]<dx){
				setv(mx[y],dx);
				setv(oval[y],++cur);	
				oval[y]->clear();
			}
			if(mx[y]==dx){
				pii mx={-inf,-inf};
				int cx=dfn[x];
				auto it=oval[y]->lower_bound(cx);
				if(it!=oval[y]->end()){
					if(*it==cx)return;
					int z=lca(cx,*it);
					chkmax(mx,pii(d[z],z));
				}
				if(it!=oval[y]->begin()){
					--it;
					int z=lca(cx,*it);
					chkmax(mx,pii(d[z],z));
				}
				Ins(oval[y],cx);
				if(mx.x<0)goto ed;
				y|=1;
				x=mx.y;
			}
		}
		if(y<=xdp[x])return;
		setv(xdp[x],y);
		while(x!=1 && y<lim){
			x=fa[x];
			setv(xdp[x],merge(xdp[to[x][0]],xdp[to[x][1]]));
			if((xdp[x]-y-y)>1)return;
			y=xdp[x];
			// dp[x]=y;
		}
		ed:;
		if(less(cmx,{y,d[x]})){
			cmx={y,d[x]};
			setv(nodes[n+1],++cur);
			setv(nxt[n+1],-1);
			nodes[n+1]->clear();
		}
		if(equal(cmx,{y,d[x]})){
			int at=n+1;
			int cx=dfn[x];
			while(1){
				pii mx={-inf,-inf};
				auto it=nodes[at]->lower_bound(cx);
				if(it!=nodes[at]->end()){
					if(*it==cx)return;
					int x=lca(cx,*it);
					if(dfn[x]==cx)return;
					chkmax(mx,pii(d[x],x));
				}
				if(it!=nodes[at]->begin()){
					--it;
					int x=lca(cx,*it);
					while(dfn[x]==*it){
						if(it==nodes[at]->begin()){
							x=-1;
							Del(nodes[at],it);
							break;
						}
						auto oit=it;
						--it;
						Del(nodes[at],oit);
						x=lca(cx,*it);
					}
					if(x!=-1)chkmax(mx,pii(d[x],x));
				}
				Ins(nodes[at],cx);
				if(mx.x>nxt[at]){
					setv(nxt[at],mx.x);
					setv(nodes[nxt[at]],++cur);
					setv(nxt[nxt[at]],-1);
				}
				if(mx.x==nxt[at]){
					cx=dfn[mx.y];
					at=nxt[at];
				}
				else return;
			}
		}
	}
	struct smt{
		vector<pii> ask;
		int ls,rs;
		smt *l,*r;
		smt(){}
		smt(int,int);
		void add(int la,int ra,pii w){
			if(la<=ls && rs<=ra){
				ask.emplace_back(w);
				return;
			}
			if(la<=l->rs)l->add(la,ra,w);
			if(r->ls<=ra)r->add(la,ra,w);
		}
		void solve(){
			pii oc=cmx;
			int ct1=t1,ct2=t2,ct3=t3;
			set<int> *ocur=cur;
			for(auto i:ask){
				setval(i.x,i.y);
			}
			if(ls==rs){
				if(cmx.x<0){
					write("0\n");
				}
				else{
					int ans=((ll)cmx.x*pw[cmx.y]+1)%p;
					for(int i=nxt[n+1];i>=0;i=nxt[i])ans=(ans+pw[i])%p;
					write(ans,'\n');
				}
			}
			else{
				l->solve();r->solve();
			}
			cmx=oc;
			cur=ocur;
			while(t1>ct1)revert1();while(t2>ct2)revert2();
			while(t3>ct3)revert3();
		}
	};
	smt node[400005],*vat=node,*rt;
	smt *newsmt(int la,int ra){
		smt *rt=vat;++vat;
		*rt=smt(la,ra);
		return rt;
	}
	smt::smt(int la,int ra){
		ls=la;rs=ra;
		ask.clear();
		if(ls==rs){
			l=r=0;return;
		}
		int mid=(ls+rs)>>1;
		l=newsmt(ls,mid);
		r=newsmt(mid+1,rs);
	}
	bool main(){
		read(n);
		cmx={-1,0};
		for(int i=1;i<=n;++i)xdp[i]=-1;
		pw[0]=1;
		for(int i=0;i<(1<<18);++i)mx[i]=-1;
		for(int i=1;i<=n;++i)pw[i]=(pw[i-1]<<1)%p;
		for(int i=0;i<=n+1;++i)nxt[i]=-1;
		for(int i=2;i<=n;++i){
			read(fa[i]);
			to[fa[i]].emplace_back(i);
			d[i]=d[fa[i]]+1;
		}
		dfs(1);
		for(int i=1;i<=n;++i){
			read(a[i]);
			at[i]=0;
		}
		int q;
		read(q);
		rt=newsmt(0,q);
		for(int i=1;i<=q;++i){
			int x,y;
			read(x,y);
			if(a[x])rt->add(at[x],i-1,{x,a[x]});
			at[x]=i;a[x]=y;
		}
		for(int i=1;i<=n;++i)if(a[i])rt->add(at[i],q,{i,a[i]});
		rt->solve();
		return 0;
	}
}
// dp[x]=(dp[ls]==dp[rs]?dp[ls]<<1):(max(dp[ls],dp[rs])<<1)-1
// 考虑所有能取到max的位置，把它们的虚树搞出来(?)
// 找到最深的合并的位置，然后只留下这些位置递归一次，给答案加上这个2^深度
// 线段树分治一下，改成仅chkmax
// 那就维护每一层这样的结构(？
// wc, 8s，那我3log了，蚌
// 看上去O(n)-O(1)lca能2log
// 不能，得set.lowerbound
// 草，修不完了
// tmd 根本过不了拍
signed main(){
#ifdef QAQAutoMaton 
	freopen("H.in","r",stdin);
	freopen("H.out","w",stdout);
#endif
	run::main();
	return 0;
}