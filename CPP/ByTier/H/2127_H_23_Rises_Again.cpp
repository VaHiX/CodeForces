/*
 * Problem URL : https://codeforces.com/problemset/problem/2127/H
 * Submit Date : 2025-08-14
 */

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ld long double
#define ar array

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template <typename T> using oset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define vt vector
#define pb push_back
#define all(c) (c).begin(), (c).end()
#define sz(x) (int)(x).size()

#define F_OR(i, a, b, s) for (int i=(a); (s)>0?i<(b):i>(b); i+=(s))
#define F_OR1(e) F_OR(i, 0, e, 1)
#define F_OR2(i, e) F_OR(i, 0, e, 1)
#define F_OR3(i, b, e) F_OR(i, b, e, 1)
#define F_OR4(i, b, e, s) F_OR(i, b, e, s)
#define GET5(a, b, c, d, e, ...) e
#define F_ORC(...) GET5(__VA_ARGS__, F_OR4, F_OR3, F_OR2, F_OR1)
#define FOR(...) F_ORC(__VA_ARGS__)(__VA_ARGS__)
#define EACH(x, a) for (auto& x: a)

template<class T> bool umin(T& a, const T& b) { return b<a?a=b, 1:0; }
template<class T> bool umax(T& a, const T& b) { return a<b?a=b, 1:0; } 

ll FIRSTTRUE(function<bool(ll)> f, ll lb, ll rb) { while(lb<rb){ ll mb=(lb+rb)/2; f(mb)?rb=mb:lb=mb+1; } return lb; }
ll LASTTRUE(function<bool(ll)> f, ll lb, ll rb) { while(lb<rb){ ll mb=(lb+rb+1)/2; f(mb)?lb=mb:rb=mb-1; } return lb; }

template<class A> void read(vt<A>& v);
template<class A, size_t S> void read(ar<A, S>& a);
template<class T> void read(T& x) { cin >> x; }
void read(double& d) { string t; read(t); d=stod(t); }
void read(long double& d) { string t; read(t); d=stold(t); }
template<class H, class... T> void read(H& h, T&... t) { read(h); read(t...); }
template<class A> void read(vt<A>& x) { EACH(a, x) read(a); }
template<class A, size_t S> void read(array<A, S>& x) { EACH(a, x) read(a); }

string to_string(char c) { return string(1, c); }
string to_string(bool b) { return b?"true":"false"; }
string to_string(const char* s) { return string(s); }
string to_string(string s) { return s; }
string to_string(vt<bool> v) { string res; FOR(sz(v)) res+=char('0'+v[i]); return res; }
template<size_t S> string to_string(bitset<S> b) { string res; FOR(S) res+=char('0'+b[i]); return res; }
template<class T> string to_string(T v) { bool f=1; string res; EACH(x, v){ if(!f) res+=' '; f=0; res+=to_string(x);} return res; }

template<class A> void write(A x) { cout << to_string(x); }
template<class H, class... T> void write(const H& h, const T&... t) { write(h); write(t...); }
void print() { write("\n"); }
template<class H, class... T> void print(const H& h, const T&... t) { write(h); if(sizeof...(t)) write(' '); print(t...); }

void DBG() { cerr << "]" << endl; }
template<class H, class... T> void DBG(H h, T... t) { cerr << to_string(h); if(sizeof...(t)) cerr << ", "; DBG(t...); }
#ifdef _DEBUG
#define dbg(...) cerr << "LINE(" << __LINE__ << ") -> [" << #__VA_ARGS__ << "]: [", DBG(__VA_ARGS__)
#else
#define dbg(...) 0
#endif

template<class T> void offset(ll o, T& x) { x+=o; }
template<class T> void offset(ll o, vt<T>& x) { EACH(a, x) offset(o, a); }
template<class T, size_t S> void offset(ll o, ar<T, S>& x) { EACH(a, x) offset(o, a); }

mt19937 mt_rng(chrono::steady_clock::now().time_since_epoch().count());
ll randint(ll a, ll b) { return uniform_int_distribution<ll>(a, b)(mt_rng); }

template<class T, class U> void vti(vt<T> &v, U x, size_t n) { v=vt<T>(n, x); }
template<class T, class U> void vti(vt<T> &v, U x, size_t n, size_t m...) { v=vt<T>(n); EACH(a, v) vti(a, x, m); }

const int d4i[4]={-1, 0, 1, 0}, d4j[4]={0, 1, 0, -1};
const int d8i[8]={-1, -1, 0, 1, 1, 1, 0, -1}, d8j[8]={0, 1, 1, 1, 0, -1, -1, -1};

struct Edge{int u,v;};
int n,m;
vt<Edge> E;
vt<vt<int>> inc;
vt<char> active;
vt<int> degRem, capv;
int bestAns, curSel;
struct Op{ int type, e, u, v; };
vt<Op> ops;

inline void remove_edge(int e){
	if(!active[e]) return;
	active[e]=0;
	int u=E[e].u, v=E[e].v;
	degRem[u]--; degRem[v]--;
	ops.pb({0,e,u,v});
}
inline void select_edge(int e){
	if(!active[e]) return;
	int u=E[e].u, v=E[e].v;
	active[e]=0;
	degRem[u]--; degRem[v]--;
	capv[u]--; capv[v]--;
	curSel++;
	ops.pb({1,e,u,v});
}
inline void undo_to(int mark){
	while((int)ops.size()>mark){
		auto o=ops.back(); ops.pop_back();
		if(o.type==0){
			active[o.e]=1;
			degRem[o.u]++; degRem[o.v]++;
		}else{
			active[o.e]=1;
			degRem[o.u]++; degRem[o.v]++;
			capv[o.u]++; capv[o.v]++;
			curSel--;
		}
	}
}
inline void propagate(){
	deque<int> q;
	vt<char> inq(n,0);
	FOR(i,0,n){
		if(capv[i]==0 || degRem[i]<=capv[i]){ q.pb(i); inq[i]=1; }
	}
	while(!q.empty()){
		int v=q.front(); q.pop_front(); inq[v]=0;
		if(capv[v]==0){
			vt<int> es;
			EACH(e, inc[v]) if(active[e]) es.pb(e);
			EACH(e, es){
				int u=E[e].u^E[e].v^v;
				remove_edge(e);
				if(!inq[u]){ if(capv[u]==0 || degRem[u]<=capv[u]){ q.pb(u); inq[u]=1; } }
			}
		}
		if(degRem[v] && degRem[v]<=capv[v]){
			vt<int> es;
			EACH(e, inc[v]) if(active[e]) es.pb(e);
			EACH(e, es){
				int u=E[e].u^E[e].v^v;
				if(capv[v]>0 && capv[u]>0 && active[e]){
					select_edge(e);
					if(!inq[u]){ if(capv[u]==0 || degRem[u]<=capv[u]){ q.pb(u); inq[u]=1; } }
				}
			}
		}
	}
}
inline int upper_bound_edges(){
	ll s=0; int rem=0;
	FOR(v,0,n) s += min(capv[v], degRem[v]);
	FOR(e,0,m) if(active[e]) rem++;
	int ub = curSel + min(rem, (int)(s/2));
	return ub;
}
void dfs(){
	propagate();
	if(curSel>bestAns) bestAns=curSel;
	int ub=upper_bound_edges();
	if(ub<=bestAns) return;

	int pick=-1, bestScore=-1;
	FOR(e,0,m) if(active[e]){
		int u=E[e].u, v=E[e].v;
		if(capv[u]==0 || capv[v]==0) continue;
		int score = (degRem[u]-capv[u]>0) + (degRem[v]-capv[v]>0);
		if(score>bestScore){ bestScore=score; pick=e; if(score==2) break; }
	}
	if(pick==-1) return;

	int mark=sz(ops);

	select_edge(pick);
	dfs();
	undo_to(mark);

	remove_edge(pick);
	dfs();
	undo_to(mark);
}

void solve() {
	read(n,m);
	E.assign(m,{});
	inc.assign(n,{});
	FOR(i,0,m){
		int u,v; read(u,v); --u;--v;
		E[i]={u,v};
		inc[u].pb(i); inc[v].pb(i);
	}
	active.assign(m,1);
	degRem.assign(n,0);
	capv.assign(n,2);
	FOR(v,0,n) degRem[v]=sz(inc[v]);
	bestAns=0; curSel=0; ops.clear();
	dfs();
	print(bestAns);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int t=1;
	read(t);
	FOR(t) {
		solve();
	}
}
