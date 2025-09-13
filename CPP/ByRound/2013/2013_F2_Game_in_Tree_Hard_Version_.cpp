/*
 * Problem URL : https://codeforces.com/contest/2013/problem/F2
 * Submit Date : 2025-09-12
 */

#include <bits/stdc++.h>
#define fi first
#define se second
#define pb push_back
using namespace std;

const int N = 200010, SZ = (1 << 18) + 5;
static char buf[SZ], *bgn = buf, *til = buf;
char getc() {
    if(bgn == til)  bgn = buf, til = buf + fread(buf, 1, SZ, stdin);
    return bgn == til ? EOF : *bgn++;
}
template<typename T>
void read(T &x) {
    char ch = getc();  T fh = 0;   x = 0;
    while(ch < '0' || ch > '9')    fh |= (ch == '-'), ch = getc();
    while(ch >= '0' && ch <= '9')   x = x * 10 + ch - '0', ch = getc();
    x = fh ? -x : x;
}
template<typename Type, typename... argc>
void read(Type &x, argc &...args)   {read(x), read(args...);}
int n, u, v, mx[N], mx2[N], pmx[N], dep[N], book[N], fa[N], ans[N], toa[N], tob[N];
vector<int> edge[N], lin, tmp, tmp2;
void dfs(int x, int fath) {
    fa[x] = fath, dep[x] = dep[fath] + 1;
    for(int y : edge[x])    if(y != fa[x])  dfs(y, x);
}
void Dfs(int x) {
    mx[x] = mx2[x] = 0;
    for(int y : edge[x]) {
        if(y == fa[x])  continue;
        Dfs(y), mx2[x] = max(mx2[x], mx2[y] + 1);
        if(!book[y])    mx[x] = max(mx[x], mx[y] + 1);
    }
}
struct STable {
    int mx[20][N], n, val[N];
    void init() {
        //  for(int j = 0; j <= 17; ++j) 
        //     for(int i = 0; i + (1 << j) - 1 <= n; ++i)  mx[j][i] = -N;
        for(int i = 1; i <= n; ++i) mx[0][i] = val[i];
        for(int j = 1; j <= 17; ++j) 
            for(int i = 1; i + (1 << j) - 1 <= n; ++i)  mx[j][i] = max(mx[j - 1][i], mx[j - 1][i + (1 << (j - 1))]);
    }
    int query(int l, int r) {
        if(l > r)   return -N;
        int v = __lg(r - l + 1);
        return max(mx[v][l], mx[v][r - (1 << v) + 1]);
    }
}st, st2;
struct segtree {
    int cov[N << 2], col[N << 2];
    int ls(int x)   {return x << 1;}
    int rs(int x)   {return x << 1 | 1;}
    void upd(int x, int val)    {col[x] = cov[x] = val;}
    void pushdown(int x)    {if(cov[x] != 0)    upd(ls(x), cov[x]), upd(rs(x), cov[x]), cov[x] = 0;}
    void build(int l, int r, int p) {
        cov[p] = col[p] = 0;
        if(l == r)  return;
        int mid = (l + r) >> 1;
        build(l, mid, ls(p)), build(mid + 1, r, rs(p));
    }
    void update(int l, int r, int val, int nl, int nr, int p) {        
        if(l > r)   return;
        if(l <= nl && nr <= r)  return upd(p, val);
        int mid = (nl + nr) >> 1;   pushdown(p);
        if(mid >= l)    update(l, r, val, nl, mid, ls(p));
        if(mid < r) update(l, r, val, mid + 1, nr, rs(p));
    }
    void get(int l, int r, int p, int *tmp) {
        if(l == r)  return tmp[l] = col[p] > 0 ? col[p] : tmp[l], void();
        int mid = (l + r) >> 1; pushdown(p);
        get(l, mid, ls(p), tmp), get(mid + 1, r, rs(p), tmp);
    }
}tra, trb;
void work(int u, int dth) {
    if(dep[u] < dth)    return;
    int nw = u; lin.clear(), lin.pb(0);
    for(int i = 1; i <= n; ++i) book[i] = 0, toa[i] = N, tob[i] = -N;
    while(nw)   lin.pb(nw), book[nw] = 1, nw = fa[nw];
    reverse(lin.begin() + 1, lin.end());
    Dfs(1);
    int m = lin.size() - 1;
    for(int i = 1; i <= m; ++i)  st.val[i] = mx[lin[i]] - i, st2.val[i] = mx[lin[i]] + i - 1;
    st.n = st2.n = m, st.init(), st2.init();
    // cerr << st.query(3, 3) + 4 << " " << mx[lin[3]] << " " << st.val[3] << "\n";
    tra.build(1, m, 1), trb.build(1, m, 1);
    for(int i = m / 2; i > 1; --i) {
        int l = i + i - 1, r = m;
        while(l < r) {
            int mid = (l + r + 1) >> 1;
            if(mx[lin[i]] + i - 1 > st.query(i + 1, mid - i + 1) + mid)   l = mid;
            else    r = mid - 1;
        }
        // cerr << i << " : " << l << "\n";
        tra.update(i + i, l, i, 1, m, 1);
    }
    for(int i = 3; i <= m; ++i) {
        int l = i, r = min(i + i - 3, m) + 1;
        while(l < r) {
            int mid = (l + r) >> 1;
            if(mx[lin[i]] + mid - i >= st2.query(mid - i + 2, i - 1))   r = mid;
            else    l = mid + 1;
        }
        // cerr << i << " : " << r << "\n";
        trb.update(r, min(i + i - 3, m), i, 1, m, 1);
    }
    tra.get(1, m, 1, toa), trb.get(1, m, 1, tob);
    // cerr << u << " " << dth << "\n";
    // for(int i = 1; i <= m; ++i) cerr << toa[i] << " ";
    // cerr << "\n";
    // for(int i = 1; i <= m; ++i) cerr << tob[i] << " ";
    // cerr << "\n";
    for(int i = dth; i <= m; ++i) {
        int x = lin[i];
        if(mx[1] > max(mx2[x], st.query(2, i) + i))  ans[x] = 1;
        else if(mx2[x] >= st2.query(2, i - 1))  ans[x] = 2;
        else {
            if(toa[i] == N && tob[i] == -N)  ans[x] = (i & 1) ? 1 : 2;
            else    ans[x] = toa[i] - 1 <= i - tob[i] ? 1 : 2;
        }
    }
}   
void clear() {
    tmp.clear(), tmp2.clear();
    for(int i = 1; i <= n; ++i) ans[i] = 0, edge[i].clear();
}
void mian() {
    // static int T = 0;
    read(n), clear();
    for(int i = 1; i < n; ++i)  read(u, v), edge[u].pb(v), edge[v].pb(u);
    read(u, v), dfs(1, 0);
    int x = u, y = v;
    while(dep[x] > dep[v])  tmp.pb(x), x = fa[x];
    while(dep[y] > dep[u])  tmp2.pb(y), y = fa[y];
    while(x != y)   tmp.pb(x), tmp2.pb(y), x = fa[x], y = fa[y];
    // cerr << x << " " << y << "\n";
    tmp.pb(x), work(u, dep[x]), work(v, dep[x] + 1);
    for(int i = int(tmp2.size()) - 1; i >= 0; --i)  tmp.pb(tmp2[i]);
    for(int x : tmp) {
        // ++T;
        // if(n < 11)   
            puts(ans[x] == 1 ? "Alice" : "Bob");
        // else if(T == 14816) {
        //     printf("%d\n", n);
        //     for(int i = 1; i <= n; ++i)
        //         for(int j : edge[i])    if(i < j)   printf("%d %d\n", i, j);
        //     printf("%d %d\n", u, v);
        // }
    }   
}
int main() {
    #ifdef Kelly
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
        freopen("err.txt", "w", stderr);
    #endif
    int T = 1;  read(T);
    while(T--)  mian();
    return 0;
}