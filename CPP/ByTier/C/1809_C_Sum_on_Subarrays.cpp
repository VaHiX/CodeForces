// Problem: CF 1809 C - Sum on Subarrays
// https://codeforces.com/contest/1809/problem/C

/*
Purpose: This code solves the problem of constructing an array of n integers such that exactly k subarrays have positive sums.
         The rest of the subarrays have negative sums. The elements of the array are constrained to be between -1000 and 1000.

Algorithms/Techniques:
- Greedy construction approach based on mathematical reasoning about subarray sums
- Utilizes the formula for total number of subarrays: n*(n+1)/2
- Reverse logic is used when k is more than half of total subarrays to reduce computation

Time Complexity: O(n) per test case, as each test case involves a constant number of operations and loops up to n.
Space Complexity: O(1) additional space (excluding input/output), since we only use a constant amount of extra variables and do not store large data structures.
*/

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
#define ll long long
#define pii pair<int, int>
#define GETVECTOR(n)                                                           \
  for (int i = 0; i < (n); i++)                                                \
    scanf("%d ", &inp[i]);
#define CNT_LOWER(v, n)                                                        \
  (int)(lower_bound((v).begin(), (v).end(), (n)) - (v).begin())
#define CNT_UPPER(v, n)                                                        \
  (int)(upper_bound((v).begin(), (v).end(), (n)) - (v).begin())
typedef struct p3 {
  int a;
  int b;
  int c;
} p3;
bool cmp3(p3 p, p3 q) {
  if (p.a == q.a) {
    if (p.b == q.b) {
      return p.c < q.c;
    }
    return p.b < q.b;
  }
  return p.a < q.a;
}
void make_segtree(int node, int start, int end, vector<int> &segtree,
                  vector<int> &arr) {
  if (start == end) {
    segtree[node] = arr[start];
    return;
  }
  int mid = (start + end) / 2;
  make_segtree(node * 2, start, mid, segtree, arr);
  make_segtree(node * 2 + 1, mid + 1, end, segtree, arr);
  segtree[node] = segtree[node * 2] + segtree[node * 2 + 1];
  return;
}
void update(int node, int start, int end, int x, int val, vector<int> &segtree,
            vector<int> &arr) {
  if (x < start or end < x)
    return;
  if (start == end) {
    segtree[node] = val;
    return;
  }
  int mid = (start + end) / 2;
  update(2 * node, start, mid, x, val, segtree, arr);
  update(2 * node + 1, mid + 1, end, x, val, segtree, arr);
  segtree[node] = segtree[node * 2] + segtree[node * 2 + 1];
}
int query(int node, int start, int end, int l, int r, vector<int> &segtree,
          vector<int> &arr) {
  if (r < start or end < l)
    return 0;
  if (l <= start and end <= r)
    return segtree[node];
  int mid = (start + end) / 2;
  return query(node * 2, start, mid, l, r, segtree, arr) +
         query(node * 2 + 1, mid + 1, end, l, r, segtree, arr);
}
class djs {
  int n;
  vector<int> par;

public:
  djs(int n) : n(n) {
    par.resize(n);
    for (int i = 0; i < n; i++)
      par[i] = i;
  }
  int find(int v) {
    if (par[v] == v)
      return v;
    else
      return par[v] = find(par[v]);
  }
  bool Union(int x, int y) {
    int px = find(x);
    int py = find(y);
    if (px == py)
      return false;
    par[px] = py;
    return true;
  }
};
ll pow(ll a, ll x, ll m) {
  if (x == 1)
    return a % m;
  if (x == 0)
    return 1;
  ll v = pow(a, x / 2, m);
  v = v * v % m;
  if (x % 2)
    v = v * a % m;
  return v;
}
ll modInverse(ll A, ll M) {
  ll m0 = M;
  ll y = 0, x = 1;
  if (M == 1)
    return 0;
  while (A > 1) {
    ll q = A / M;
    ll t = M;
    M = A % M, A = t;
    t = y;
    y = x - q * y;
    x = t;
  }
  if (x < 0)
    x += m0;
  return x;
}
int BFS(int r, vector<int> &visited, vector<int> &dist, vector<int> &under,
        vector<vector<pii>> &GRAPH) {
  visited[r] = 1;
  int sm = 1;
  for (pii p : GRAPH[r]) {
    if (visited[p.first])
      continue;
    dist[p.first] = dist[r] + p.second;
    BFS(p.first, visited, dist, under, GRAPH);
    sm += under[p.first];
  }
}
int main() {
  int tt;
  cin >> tt;
  while (tt--) {
    int n, k;
    scanf("%d %d", &n, &k);
    int reverse = 1;
    // To reduce computation, use reverse logic if k is more than half of total subarrays
    if (k * 2 >= n * (n + 1) / 2) {
      reverse = -1;
      k = n * (n + 1) / 2 - k;
    }
    int b = 0;
    // Special cases for k=0, k=1, k=2
    if (k == 0) {
      for (int i = 0; i < n; i++)
        printf("%d ", -1 * reverse);
      printf("\n");
      continue;
    }
    if (k == 1) {
      printf("%d ", reverse);
      for (int i = 0; i < n - 1; i++)
        printf("%d ", reverse * -999);
      printf("\n");
      continue;
    }
    if (k == 2) {
      printf("%d ", reverse * 30);
      printf("%d ", reverse * -1);
      for (int i = 0; i < n - 2; i++)
        printf("%d ", reverse * -999);
      printf("\n");
      continue;
    }
    // General case
    b = 2;
    while ((b + 1) * (b + 2) / 2 <= k)
      b++;
    int t = k - b * (b + 1) / 2;
    for (int i = 0; i < t; i++)
      printf("%d ", reverse * 31);
    for (int i = t; i < b; i++)
      printf("%d ", reverse);
    if (b < n)
      printf("%d ", -1 * reverse * 30);
    for (int i = 0; i < n - b - 1; i++)
      printf("%d ", -1 * reverse * 999);
    printf("\n");
  }
}


// https://github.com/VaHiX/CodeForces/