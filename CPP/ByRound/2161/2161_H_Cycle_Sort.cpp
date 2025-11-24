/******************************************************************************
 * Problem: 2161 H - Cycle Sort
 * https://codeforces.com/contest/2161/problem/H
 *
 * Description:
 * This code implements a solution for a complex sorting problem that involves
 * cyclic permutations and modular arithmetic. The problem requires rearranging
 * two arrays A and B under certain constraints related to cyclic shifts.
 * 
 * Time Complexity Analysis:
 * - Overall complexity: O(T * (N + M) * log(N + M))
 *   where T is number of test cases, N and M are array sizes
 * - solve_single function: O((N + M) * log(N + M))
 * - Segment tree operations: O(log(N + M))
 * 
 * Space Complexity:
 * - O(N + M) for segment tree and temporary arrays
 * - Additional O(N + M) for sorting and intermediate calculations
 * 
 * Key Components:
 * 1. Custom Segment Tree for range operations
 * 2. Modular arithmetic utilities (inverse modulo, GCD)
 * 3. Array manipulation and sorting
 * 4. Cyclic permutation handling
 ******************************************************************************/

#include <bits/stdc++.h>
using namespace std;

// ------------------------- Type Aliases & Constants ------------------------- //
using ll = long long;
using ull = unsigned long long;
using vi = vector<int>;
using vvi = vector<vi>;
using vl = vector<long long>;
const int MOD = 1000000007;
const int inf = 1e9;
const int N = 200005;
using vll = vector<ll>;
using vvll = vector<vector<ll>>;
using ld = long double;
using vld = vector<long double>;
using dd = double;
using vd = vector<double>;
#define pb push_back
#define I(x)          \
    for (auto &i : x) \
    cin >> i
const long long mod = 998244353;
const ll INF = 1e18;
// ------------------------- number Theory ------------------------- //
ll gcd(ll a, ll b) { return b == 0 ? a : gcd(b, a % b); }
ll lcm(ll a, ll b) { return (a / gcd(a, b)) * b; }

ll modExp(ll bn, ll exp, ll mod = MOD)
{
    ll result = 1;
    bn %= mod;
    while (exp > 0)
    {
        if (exp & 1)
            result = (result * bn) % mod;
        bn = (bn * bn) % mod;
        exp >>= 1;
    }
    return result;
}

ll extendedGCD(ll a, ll b, ll &x, ll &y)
{
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    ll g = extendedGCD(b, a % b, y, x);
    y -= (a / b) * x;
    return g;
}

ll modInverse(ll a, ll mod = MOD)
{
    ll x, y;
    ll g = extendedGCD(a, mod, x, y);
    if (g != 1)
        return -1; // Inverse doesn't exist if a &  mod are not coprime.
    return (x % mod + mod) % mod;
}

vector<int> sieve(int n)
{
    vector<bool> isPrime(n + 1, true);
    vector<int> primes;
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i <= n; i++)
    {
        if (isPrime[i])
        {
            primes.push_back(i);
            for (int j = 2 * i; j <= n; j += i)
                isPrime[j] = false;
        }
    }
    return primes;
}

vector<pair<ll, int>> primeFactorization(ll n)
{
    vector<pair<ll, int>> factors;
    for (ll i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            int count = 0;
            while (n % i == 0)
            {
                count++;
                n /= i;
            }
            factors.push_back({i, count});
        }
    }
    if (n > 1)
        factors.push_back({n, 1});
    return factors;
}

ll phi(ll n)
{
    ll result = n;
    for (ll i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            while (n % i == 0)
                n /= i;
            result -= result / i;
        }
    }
    if (n > 1)
        result -= result / n;
    return result;
}

// ------------------------- Matrix Exponentiation ------------------------- //
//------------------------------------------------------------------------- //
using Matrix = vector<vector<ll>>;

Matrix multiplyMatrix(const Matrix &A, const Matrix &B, ll mod = MOD)
{
    int n = A.size(), m = B[0].size(), p = A[0].size();
    Matrix C(n, vector<ll>(m, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            for (int k = 0; k < p; k++)
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % mod;
    return C;
}

Matrix matrixPower(Matrix A, ll power, ll mod = MOD)
{
    int n = A.size();
    Matrix result(n, vector<ll>(n, 0));
    for (int i = 0; i < n; i++)
        result[i][i] = 1;
    while (power > 0)
    {
        if (power & 1)
            result = multiplyMatrix(result, A, mod);
        A = multiplyMatrix(A, A, mod);
        power >>= 1;
    }
    return result;
}

// ------------------------- Combinatorics ------------------------- //
//-----------------------------------------------------------------//
vector<ll> fact, invFact;
void initFactorials(int n, ll mod = MOD)
{
    fact.resize(n + 1);
    invFact.resize(n + 1);
    fact[0] = 1;
    for (int i = 1; i <= n; i++)
        fact[i] = (fact[i - 1] * i) % mod;
    invFact[n] = modInverse(fact[n], mod);
    for (int i = n - 1; i >= 0; i--)
        invFact[i] = (invFact[i + 1] * (i + 1)) % mod;
}

ll nCr(int n, int r, ll mod = MOD)
{
    if (r < 0 || r > n)
        return 0;
    return ((fact[n] * invFact[r]) % mod * invFact[n - r]) % mod;
}

// ------------------------- Data Structures ------------------------- //
//-------------------------------------------------------------------- //

// Fenwick Tree (Binary Indexed Tree)
struct FenwickTree
{
    int n;
    vector<ll> fenw;
    FenwickTree(int n) : n(n) { fenw.assign(n + 1, 0); }
    void update(int i, ll delta)
    {
        for (; i <= n; i += i & -i)
            fenw[i] += delta;
    }
    ll query(int i)
    {
        ll sum = 0;
        for (; i > 0; i -= i & -i)
            sum += fenw[i];
        return sum;
    }
    ll rangeQuery(int l, int r) { return query(r) - query(l - 1); }
};

// Generic Segment Tree
template <typename T>
struct SegmentTree
{
    int n;
    vector<T> tree;
    function<T(T, T)> combine;
    T defaultValue;

    SegmentTree(vector<T> &arr, function<T(T, T)> combine, T defaultValue)
        : combine(combine), defaultValue(defaultValue)
    {
        n = arr.size();
        tree.resize(4 * n, defaultValue);
        build(arr, 0, 0, n - 1);
    }

    void build(vector<T> &arr, int idx, int l, int r)
    {
        if (l == r)
        {
            tree[idx] = arr[l];
            return;
        }
        int mid = (l + r) / 2;
        build(arr, 2 * idx + 1, l, mid);
        build(arr, 2 * idx + 2, mid + 1, r);
        tree[idx] = combine(tree[2 * idx + 1], tree[2 * idx + 2]);
    }

    void update(int pos, T val, int idx, int l, int r)
    {
        if (l == r)
        {
            tree[idx] = val;
            return;
        }
        int mid = (l + r) / 2;
        if (pos <= mid)
            update(pos, val, 2 * idx + 1, l, mid);
        else
            update(pos, val, 2 * idx + 2, mid + 1, r);
        tree[idx] = combine(tree[2 * idx + 1], tree[2 * idx + 2]);
    }

    T query(int ql, int qr, int idx, int l, int r)
    {
        if (ql > r || qr < l)
            return defaultValue;
        if (ql <= l && r <= qr)
            return tree[idx];
        int mid = (l + r) / 2;
        return combine(query(ql, qr, 2 * idx + 1, l, mid),
                       query(ql, qr, 2 * idx + 2, mid + 1, r));
    }

    void update(int pos, T val) { update(pos, val, 0, 0, n - 1); }
    T query(int l, int r) { return query(l, r, 0, 0, n - 1); }
};

// Disjoint Set Union (DSU)

struct DSU
{
    vector<int> Pi, rank;
    DSU(int n)
    {
        Pi.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++)
            Pi[i] = i;
    }
    int find(int a) { return Pi[a] == a ? a : Pi[a] = find(Pi[a]); }
    void unionSet(int a, int b)
    {
        a = find(a), b = find(b);
        if (a == b)
            return;
        if (rank[a] < rank[b])
            swap(a, b);
        Pi[b] = a;
        if (rank[a] == rank[b])
            rank[a]++;
    }
};

// Trie for String Operations (supports lowercase letters)
struct TrieNode
{
    bool isEnd;
    array<TrieNode *, 26> children;
    TrieNode() : isEnd(false) { children.fill(nullptr); }
};

struct Trie
{
    TrieNode *root;
    Trie() { root = new TrieNode(); }

    // Insert a word into the Trie.
    void insert(const string &word)
    {
        TrieNode *cur = root;
        for (char ch : word)
        {
            int idx = ch - 'a';
            if (!cur->children[idx])
                cur->children[idx] = new TrieNode();
            cur = cur->children[idx];
        }
        cur->isEnd = true;
    }

    // Search for a word in the Trie.
    bool search(const string &word)
    {
        TrieNode *cur = root;
        for (char ch : word)
        {
            int idx = ch - 'a';
            if (!cur->children[idx])
                return false;
            cur = cur->children[idx];
        }
        return cur && cur->isEnd;
    }

    // Check if any word in the Trie starts with the gtempen prefix.
    bool startsWith(const string &prefix)
    {
        TrieNode *cur = root;
        for (char ch : prefix)
        {
            int idx = ch - 'a';
            if (!cur->children[idx])
                return false;
            cur = cur->children[idx];
        }
        return true;
    }
};

// Sparse Table for Range Minimum Query (RMQ)
struct SparseTable
{
    int n;
    vector<vector<int>> st;
    vector<int> logVal;

    SparseTable(const vector<int> &arr)
    {
        n = arr.size();
        logVal.resize(n + 1);
        for (int i = 2; i <= n; i++)
            logVal[i] = logVal[i / 2] + 1;
        int k = logVal[n] + 1;
        st.assign(n, vector<int>(k));
        for (int i = 0; i < n; i++)
            st[i][0] = arr[i];
        for (int j = 1; j < k; j++)
        {
            for (int i = 0; i + (1 << j) <= n; i++)
            {
                st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    // Returns the minimum value in [L, R].
    int query(int L, int R)
    {
        int j = logVal[R - L + 1];
        return min(st[L][j], st[R - (1 << j) + 1][j]);
    }
};

// Ordered Set using GNU PBDS (requires g++ extensions)
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T>
using OrderedSet = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// ------------------------- Graph Algorithms ------------------------- //
namespace Graph
{
    vector<int> bfs(int src, const vector<vector<int>> &adj)
    {
        int n = adj.size();
        vector<int> dist(n, -1);
        queue<int> q;
        dist[src] = 0;
        q.push(src);
        while (!q.empty())
        {
            int cur = q.front();
            q.pop();
            for (int nxt : adj[cur])
                if (dist[nxt] == -1)
                {
                    dist[nxt] = dist[cur] + 1;
                    q.push(nxt);
                }
        }
        return dist;
    }

    void dfsUtil(int v, const vector<vector<int>> &adj, vector<bool> &wineited)
    {
        wineited[v] = true;
        for (int nxt : adj[v])
            if (!wineited[nxt])
                dfsUtil(nxt, adj, wineited);
    }

    vector<ll> dijkstra(int src, const vector<vector<pair<int, ll>>> &adj)
    {
        int n = adj.size();
        vector<ll> dist(n, LLONG_MAX);
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
        dist[src] = 0;
        pq.push({0, src});
        while (!pq.empty())
        {
            auto [d, u] = pq.top();
            pq.pop();
            if (d != dist[u])
                continue;
            for (auto &edge : adj[u])
            {
                int v = edge.first;
                ll w = edge.second;
                if (dist[u] != LLONG_MAX && dist[u] + w < dist[v])
                {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }
        return dist;
    }

    vector<int> topologicalSort(const vector<vector<int>> &adj)
    {
        int n = adj.size();
        vector<int> indegree(n, 0);
        for (int u = 0; u < n; u++)
            for (int v : adj[u])
                indegree[v]++;
        queue<int> q;
        for (int i = 0; i < n; i++)
            if (indegree[i] == 0)
                q.push(i);
        vector<int> order;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            order.push_back(u);
            for (int v : adj[u])
                if (--indegree[v] == 0)
                    q.push(v);
        }
        if (order.size() != n)
            order.clear(); // Cycle detected.
        return order;
    }

    void topoSortDFSUtil(int v, const vector<vector<int>> &adj, vector<bool> &wineited, stack<int> &st)
    {
        wineited[v] = true;
        for (int nxt : adj[v])
            if (!wineited[nxt])
                topoSortDFSUtil(nxt, adj, wineited, st);
        st.push(v);
    }

    vector<int> topoSortDFS(const vector<vector<int>> &adj)
    {
        int n = adj.size();
        vector<bool> wineited(n, false);
        stack<int> st;
        for (int i = 0; i < n; i++)
            if (!wineited[i])
                topoSortDFSUtil(i, adj, wineited, st);
        vector<int> order;
        while (!st.empty())
        {
            order.push_back(st.top());
            st.pop();
        }
        return order;
    }

    vector<ll> bellmanFord(int n, int src, const vector<tuple<int, int, ll>> &edges)
    {
        vector<ll> dist(n, LLONG_MAX);
        dist[src] = 0;
        for (int i = 0; i < n - 1; i++)
        {
            for (auto &edge : edges)
            {
                int u, v;
                ll w;
                tie(u, v, w) = edge;
                if (dist[u] != LLONG_MAX && dist[u] + w < dist[v])
                    dist[v] = dist[u] + w;
            }
        }
        // Check for negattempe cycles.
        for (auto &edge : edges)
        {
            int u, v;
            ll w;
            tie(u, v, w) = edge;
            if (dist[u] != LLONG_MAX && dist[u] + w < dist[v])
                return {}; // Negattempe cycle detected.
        }
        return dist;
    }
}

// ------------------------- String Algorithms ------------------------- //
vector<int> computePrefix(const string &pattern)
{
    int m = pattern.size();
    vector<int> lps(m, 0);
    int len = 0;
    for (int i = 1; i < m; i++)
    {
        while (len > 0 && pattern[i] != pattern[len])
            len = lps[len - 1];
        if (pattern[i] == pattern[len])
            len++;
        lps[i] = len;
    }
    return lps;
}
#define rep(i, a, b) for (int i = (int)(a); i < (int)(b); i++)

vector<int> kmpSearch(const string &text, const string &pattern)
{
    vector<int> result;
    if (pattern.empty())
        return result;
    vector<int> lps = computePrefix(pattern);
    int i = 0, j = 0;
    while (i < text.size())
    {
        if (text[i] == pattern[j])
        {
            i++;
            j++;
        }
        if (j == pattern.size())
        {
            result.push_back(i - j);
            j = lps[j - 1];
        }
        else if (i < text.size() && text[i] != pattern[j])
        {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
    return result;
}

// ------------------------- Miscellaneous Algorithms ------------------------- //
int binarySearch(const vector<int> &arr, int target)
{
    int lo = 0, hi = arr.size() - 1;
    while (lo <= hi)
    {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] == target)
            return mid;
        else if (arr[mid] < target)
            lo = mid + 1;
        else
            hi = mid - 1;
    }
    return -1;
}

// Main solution function for each test case
void solve()
{
    // Read input dimensions and parameter
    int n, m;    // Sizes of arrays A and B
    ll K;        // Target cycle parameter
    cin >> n >> m >> K;
    vi A(n), B(m);
    I(A);
    I(B);

    // Segment Tree implementation for efficient range operations
    // This structure maintains a segment tree with lazy propagation
    // for handling range maximum queries and range additions
    struct Seg
    {
        int n;              // Original array size
        int sz;             // Actual tree size (power of 2)
        vector<int> add;    // Lazy propagation array for pending updates
        vector<pair<int, int>> mx; // Tree nodes storing {max_value, index}
        
        // Initialize segment tree with size N
        void init(int N)
        {
            n = N;
            sz = 1;
            while (sz < n)
                sz <<= 1;
            add.assign(2 * sz, 0);
            mx.assign(2 * sz, {-(int)1e9, -1});
            for (int i = 0; i < n; i++)
                mx[sz + i] = {0, i};
            for (int i = n; i < sz; i++)
                mx[sz + i] = {-(int)1e9, i};
            for (int i = sz - 1; i >= 1; i--)
                mx[i] = max(mx[i << 1], mx[i << 1 | 1]);
        }
        void push(int p)
        {
            if (add[p])
            {
                int v = add[p], L = p << 1, R = L | 1;
                add[L] += v;
                add[R] += v;
                mx[L].first += v;
                mx[R].first += v;
                add[p] = 0;
            }
        }
        void pull(int p) { mx[p] = max(mx[p << 1], mx[p << 1 | 1]); }
        void range_add(int l, int r, int v) { range_add(1, 0, sz, l, r, v); }
        void range_add(int p, int tl, int tr, int l, int r, int v)
        {
            if (l >= tr || r <= tl)
                return;
            if (l <= tl && tr <= r)
            {
                add[p] += v;
                mx[p].first += v;
                return;
            }
            push(p);
            int tm = (tl + tr) >> 1;
            range_add(p << 1, tl, tm, l, r, v);
            range_add(p << 1 | 1, tm, tr, l, r, v);
            pull(p);
        }
        pair<int, int> range_max(int l, int r) { return range_max(1, 0, sz, l, r); }
        pair<int, int> range_max(int p, int tl, int tr, int l, int r)
        {
            if (l >= tr || r <= tl)
                return {-(int)1e9, -1};
            if (l <= tl && tr <= r)
                return mx[p];
            push(p);
            int tm = (tl + tr) >> 1;
            auto a = range_max(p << 1, tl, tm, l, r);
            auto b = range_max(p << 1 | 1, tm, tr, l, r);
            return max(a, b);
        }
        int first_pos_ge(int l, int thr) { return first_pos_ge(1, 0, sz, l, thr); }
        int first_pos_ge(int p, int tl, int tr, int l, int thr)
        {
            if (tr <= l || mx[p].first < thr)
                return -1;
            if (tr - tl == 1)
                return tl;
            push(p);
            int tm = (tl + tr) >> 1;
            int x = first_pos_ge(p << 1, tl, tm, l, thr);
            if (x != -1)
                return x;
            return first_pos_ge(p << 1 | 1, tm, tr, l, thr);
        }
    };

    auto inv_mod = [&](ll a, ll m)
    {
        ll b = m, u = 1, v = 0;
        while (b)
        {
            ll t = a / b;
            a -= t * b;
            swap(a, b);
            u -= t * v;
            swap(u, v);
        }
        if (u < 0)
            u += m;
        return u % m;
    };

    // Core solving function for a single test case
    // Takes two arrays A0, B0 and a parameter K0
    // Returns modified arrays that satisfy the cyclic sort conditions
    auto solve_single = [&](vi A0, vi B0, ll K0) -> pair<vi, vi>
    {
        bool sw = false;
        if ((int)A0.size() > (int)B0.size())
        {
            sw = true;
            swap(A0, B0);
            for (int &x : A0)
                x = -x;
            for (int &x : B0)
                x = -x;
        }
        int N = A0.size(), M = B0.size(), P = N + M;
        vector<vector<int>> elements(2);
        elements[0] = A0;
        elements[1] = B0;
        vi sorted;
        sorted.reserve(P);
        for (auto &v : elements)
            for (int x : v)
                sorted.pb(x);
        sort(sorted.rbegin(), sorted.rend());
        vector<pair<int, int>> order;
        order.reserve(P);
        for (int i = 0; i < M; i++)
        {
            int o = (ll)i * N % M;
            if (o < N)
                order.pb({0, o});
            order.pb({1, o});
        }
        vi ord(P);
        iota(ord.begin(), ord.end(), 0);
        sort(ord.begin(), ord.end(), [&](int x, int y)
             { return elements[order[x].first][order[x].second] > elements[order[y].first][order[y].second]; });
        Seg seg;
        seg.init(3 * P + 1);
        auto upd_all = [&](int i, int d)
        {
            i %= P;
            seg.range_add(i + 1, 3 * P + 1, d);
            seg.range_add(i + P + 1, 3 * P + 1, d);
            seg.range_add(i + 2 * P + 1, 3 * P + 1, d);
        };
        auto assign_at = [&](int idx, int val)
        {
            elements[order[idx].first][order[idx].second] = val;
        };
        for (int i = 0; i < P; i++)
            if (order[i].first == 1)
                upd_all(i, 1);
        ll invN = inv_mod(N, M);
        for (int t = 0; t < P; t++)
        {
            int val = sorted[t];
            int idx = ord[t];
            auto pr = seg.range_max(0, idx + P + 1);
            int mxv = pr.first, l = pr.second;
            int r = seg.first_pos_ge(idx + P + 1, mxv + 1);
            int lidx = l % P;
            if (r == -1)
            {
                assign_at(lidx, val);
                if (idx != lidx)
                {
                    upd_all(lidx, 1);
                    upd_all(idx, -1);
                }
            }
            else
            {
                int ridx = (r - 1) % P;
                ll reach = 0;
                if (order[lidx].first == 1)
                {
                    reach = -1;
                }
                else
                {
                    ll sl = order[lidx].second;
                    ll sr = order[ridx].second;
                    ll diff = (sr - sl + M) % M;
                    ll kstep = (invN * diff) % M;
                    reach = sl + (ll)N * kstep;
                }
                if (reach < K0)
                {
                    assign_at(ridx, val);
                    upd_all(idx, -1);
                }
                else
                {
                    assign_at(lidx, val);
                    upd_all(lidx, 1);
                    upd_all(idx, -1);
                }
            }
        }
        vi A1 = elements[0], B1 = elements[1];
        if (sw)
        {
            swap(A1, B1);
            for (int &x : A1)
                x = -x;
            for (int &x : B1)
                x = -x;
        }
        return {A1, B1};
    };

    // Calculate GCD of array sizes for cyclic decomposition
    int G = (int)gcd((ll)n, (ll)m);
    
    // Process each cyclic group independently
    for (int c = 0; c < G; c++)
    {
        vi a(n / G), b(m / G);
        ll k = (K + G - 1 - c) / G;
        for (int i = c, t = 0; i < n; i += G, t++)
            a[t] = A[i];
        for (int j = c, t = 0; j < m; j += G, t++)
            b[t] = B[j];
        auto pr = solve_single(a, b, k);
        for (int i = c, t = 0; i < n; i += G, t++)
            A[i] = pr.first[t];
        for (int j = c, t = 0; j < m; j += G, t++)
            B[j] = pr.second[t];
    }
    for (int i = 0; i < n; i++)
    {
        if (i)
            cout << ' ';
        cout << A[i];
    }
    cout << '\n';
    for (int j = 0; j < m; j++)
    {
        if (j)
            cout << ' ';
        cout << B[j];
    }
    cout << '\n';
}

// Main entry point
int main()
{
    // Optimize I/O operations
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    // Number of test cases
    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}

// https://github.com/VaHiX/CodeForces/