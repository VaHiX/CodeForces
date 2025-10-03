/*
 * Problem URL : https://codeforces.com/contest/2006/problem/F
 * Submit Date : 2025-09-13
 */

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <cstring>
#include <queue>
#include <set>
#include <map>
#include <bitset>
#include <random>
#include <ctime>
#include <chrono>
#include <iomanip>

typedef long long ll;
typedef double lf;

// #define DEBUG 1
struct IO
{
    #define MAXSIZE (1 << 20)
    #define isdigit(x) (x >= '0' && x <= '9')
    char buf[MAXSIZE], *p1, *p2;
    char pbuf[MAXSIZE], *pp;
    #if DEBUG
    #else
    IO() : p1(buf), p2(buf), pp(pbuf) {}
    ~IO() {fwrite(pbuf, 1, pp - pbuf, stdout);}
    #endif
    #define gc() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, MAXSIZE, stdin), p1 == p2) ? ' ' : *p1++)
    #define blank(x) (x == ' ' || x == '\n' || x == '\r' || x == '\t')

    template <typename T>
    void Read(T &x)
    {
        #if DEBUG
        std::cin >> x;
        #else
        bool sign = 0; char ch = gc(); x = 0;
        for (; !isdigit(ch); ch = gc())
            if (ch == '-') sign = 1;
        for (; isdigit(ch); ch = gc()) x = x * 10 + (ch ^ 48);
        if (sign) x = -x;
        #endif
    }
    void Read(char *s)
    {
        #if DEBUG
        std::cin >> s;
        #else
        char ch = gc();
        for (; blank(ch); ch = gc());
        for (; !blank(ch); ch = gc()) *s++ = ch;
        *s = 0;
        #endif
    }
    void Read(char &c) {for (c = gc(); blank(c); c = gc());}

    void Push(const char &c)
    {
        #if DEBUG
        putchar(c);
        #else
        if (pp - pbuf == MAXSIZE) fwrite(pbuf, 1, MAXSIZE, stdout), pp = pbuf;
        *pp++ = c;
        #endif
    }
    template <typename T>
    void Write(T x)
    {
        if (x < 0) x = -x, Push('-');
        static T sta[35];
        int top = 0;
        do sta[top++] = x % 10, x /= 10; while (x);
        while (top) Push(sta[--top] ^ 48);
    }
    template <typename T>
    void Write(T x, char lst) {Write(x), Push(lst);}
} IO;
#define Read(x) IO.Read(x)
#define Write(x, y) IO.Write(x, y)
#define Put(x) IO.Push(x)

using namespace std;

const int MAXN = 2e5 + 10, MAXM = 1e6 + 10, mod = 998244353;

ll fac[MAXN], inv[MAXN];
inline void add(int &x, int y) { (x += y) >= mod && (x -= mod); }

int n, m, ans, id[MAXN];
vector <int> e[MAXN];
int vis[MAXN];

inline bool Check(int u, int v)
{
    for (auto x : e[v]) vis[x] = 1;
    bool flag = 1;
    for (auto x : e[u])
        if (!vis[x]) { flag = 0; break; }
    for (auto x : e[v]) vis[x] = 0;
    return flag;
}

int cnt[MAXN];
inline int Solve1()
{
    // for (int i = 1; i <= n; i++)
    // {
    //     for (auto x : e[id[i]]) cout << x << ' '; cout << '\n';
    // }
    static int idx[MAXN];
    iota(idx + 1, idx + n + 1, 1);
    sort(idx + 1, idx + n + 1, [&](int x, int y) { return e[x].size() < e[y].size(); });
    for (int i = 1; i < n; i++)
        if (!Check(idx[i], idx[i + 1])) return 0;
    for (int i = 0; i <= n; i++) cnt[i] = 0;
    for (int i = 1; i <= n; i++) cnt[e[idx[i]].size()]++;
    int lst = 0; ll res = 1;
    for (int i = 1; i <= n; i++)
        if (cnt[i])
        {
            res = res * fac[i - lst] % mod, lst = i;
            if (i != n) res = res * fac[cnt[i]] % mod;
        }
    res = res * fac[cnt[0]] % mod;
    return res;
}

int nxt[MAXN];
inline int Solve2()
{
    ll res = 0, ori = Solve1();
    for (int i = 0; i <= n; i++) cnt[i] = 0;
    for (int i = 1; i <= n; i++) cnt[e[id[i]].size()]++;
    int lst = 0, llst = 0;
    for (int i = n; i >= 1; i--)
        if (cnt[i]) nxt[i] = lst, lst = i;
    lst = 0;
    for (int i = 1; i <= n; i++)
        if (cnt[i])
        {
            ll t = (ll)cnt[lst] * (i - lst) % mod * (cnt[lst] == 1 ? lst - llst + 1 : 1) % mod;
            res = (res + t * ori % mod * inv[cnt[lst]] % mod * inv[i - lst] % mod * (lst + 1 == i && i != n ? cnt[i] + 1 : 1)) % mod;
            t = (ll)cnt[i] * (i - lst) % mod * (cnt[i] == 1 && nxt[i] ? nxt[i] - i + 1 : 1) % mod;
            res = (res + t * ori % mod * inv[i - lst] % mod * (lst + 1 == i ? cnt[lst] + 1 : 1) % mod * (i != n ? inv[cnt[i]] : 1)) % mod;
            llst = lst, lst = i;
        }
    if (lst != n)
    {
        ll t = (ll)cnt[lst] * (n - lst) % mod * (cnt[lst] == 1 ? lst - llst + 1 : 1) % mod;
        res = (res + t * ori % mod * inv[cnt[lst]]) % mod;
    }
    return res;
}

int main()
{
    // freopen("paint.in", "r", stdin);
    // freopen("paint.out", "w", stdout);
    #if DEBUG
    #else
    ios::sync_with_stdio(0), cin.tie(0);
    #endif
    fac[0] = fac[1] = inv[0] = inv[1] = 1;
    for (int i = 2; i < MAXN; i++) fac[i] = fac[i - 1] * i % mod, inv[i] = (mod - mod / i) * inv[mod % i] % mod;
    int T;
    Read(T);
    while (T--)
    {
        Read(n), Read(m);
        for (int i = 1; i <= n; i++)
        {
            id[i] = i;
            e[i].clear();
        }
        for (int i = 1, u, v; i <= m; i++) Read(u), Read(v), e[u].push_back(v);
        sort(id + 1, id + n + 1, [&](int x, int y) { return e[x].size() < e[y].size(); });
        ans = 0;
        bool flag = 1;
        for (int i = 1; i < n; i++)
            if (!Check(id[i], id[i + 1]))
            {
                int c1 = 0, c2 = 0;
                for (auto x : e[id[i + 1]]) vis[x] = 1;
                for (auto x : e[id[i]])
                    if (!vis[x]) c1 = x;
                    else vis[x] = 0;
                for (auto x : e[id[i + 1]])
                    if (vis[x]) c2 = (c2 == 0 ? x : -1), vis[x] = 0;
                for (auto &x : e[id[i]])
                    if (x == c1) { swap(x, e[id[i]][e[id[i]].size() - 1]); break; }
                for (auto &x : e[id[i + 1]])
                    if (x == c2) { swap(x, e[id[i + 1]][e[id[i + 1]].size() - 1]); break; }
                // cout << id[i] << ' ' << id[i + 1] << ' ' << c1 << ' ' << c2 << "\n";
                // for (int i = 1; i <= n; i++)
                // {
                //     for (auto x : e[id[i]]) cout << x << ' '; cout << '\n';
                // }
                e[id[i]].pop_back(), add(ans, Solve1());
                e[id[i]].push_back(c1), e[id[i + 1]].push_back(c1), add(ans, Solve1()), e[id[i + 1]].pop_back();
                if (~c2)
                {
                    e[id[i + 1]].pop_back(), add(ans, Solve1());
                    e[id[i + 1]].push_back(c2), e[id[i]].push_back(c2), add(ans, Solve1());
                }
                flag = 0; break;
            }
        if (flag) ans = Solve2();
        cout << ans * inv[n] % mod * inv[n] % mod << '\n';
    }
    return 0;
}