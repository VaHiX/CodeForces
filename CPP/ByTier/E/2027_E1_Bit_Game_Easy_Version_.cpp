/*
 * Problem URL : https://codeforces.com/contest/2027/problem/E1
 * Submit Date : 2025-09-09
 */

#ifdef ONLINE_JUDGE
#include <bits/stdc++.h>
#else
#include "./stdc++.h"
#endif
#define fastio                                                                 \
  ios_base::sync_with_stdio(false);                                            \
  cin.tie(nullptr)
#define i64 long long
#define u64 unsigned long long
#define ld long double
#define F first
#define S second
#define MOD 1'000'000'007
#define INF 1'000'000'000
#define INFL 10'000'000'000'000'000ll
#define pi pair<int, int>
#define pi64 pair<i64, i64>
#define pb push_back
#define eb emplace_back
#ifdef ONLINE_JUDGE
#define endl '\n'
#endif
#define matrix vector<vector<int>>
#define vi vector<int>
#define vi64 vector<i64>
#define uset unordered_set
#define umap unordered_map
#define mpr make_pair
#define ALL(x) x.begin(), x.end()
#define RALL(data) data.rbegin(), data.rend()
#define TYPEMAX(type) std::numeric_limits<type>::max()
#define TYPEMIN(type) std::numeric_limits<type>::min()
#define null nullptr
using namespace std;

#ifdef ONLINE_JUDGE
class NullBuffer : public std::streambuf {
public:
  int overflow(int c) { return c; }
};
ostream logger(new NullBuffer());
#else
ostream &logger = cout;
#endif

umap<int, int> ln2;
void setup() {
  for (int i = 1, j = 0; j < 32; i <<= 1, j++) {
    ln2[i] = j;
  }
}

int ln(int x) {
  for (int i = 1; i <= 16; i <<= 1) {
    x |= x >> i;
  }
  return ln2[(x >> 1) + 1];
}

void solveMain() {
  int n;
  cin >> n;
  int ar[n], xr[n];
  for (int i = 0; i < n; i++) {
    cin >> ar[i];
  }
  for (int i = 0; i < n; i++) {
    cin >> xr[i];
  }
  int sum = 0;
  for (int i = 0; i < n; i++) {
    int a = ar[i], x = xr[i];
    int la = ln(a);
    x = x & ((1 << (la + 1)) - 1);
    if (x <= a) {
      sum ^= __builtin_popcount(x);
      continue;
    }
    int y = x;
    int lft = 0, rgt = 0, ttl = 0;
    int flag = 0;
    for (int i = la; i >= 0; i--) {
      bool ab = (a & (1 << i)) != 0, xb = (x & (1 << i)) != 0;
      if (!flag and ab and xb) {
        lft++;
      } else if (!flag and !ab and xb) {
        flag = 1, ttl++;
      } else if (flag == 1 and !ab and xb) {
        ttl++;
      } else if (flag == 1 and ab) {
        flag = 2, rgt += xb;
      } else if (flag == 2 and xb) {
        rgt++;
      }
    }
    int c = ttl == 1 and !rgt                 ? 0
            : (ttl & 1) and lft == 1 and !rgt ? ttl - 1
                                              : ttl + lft + rgt;
    sum ^= c;
  }
  cout << (sum ? "Alice" : "Bob") << endl;
}

int main() {
#ifndef ONLINE_JUDGE
  clock_t tStart = clock();
#endif
  fastio;
  int t = 1;
  cin >> t;
  setup();
  while (t--) {
    solveMain();
  }
#ifndef ONLINE_JUDGE
  printf("Time taken: %.3fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
#endif
  return 0;
}
