// Problem: CF 1837 F - Editorial for Two
// https://codeforces.com/contest/1837/problem/F

/*
Purpose: This code solves the problem of optimally selecting k problems out of n for editorial work,
         and splitting them between Monocarp and Polycarp to minimize the maximum time taken.

Algorithms/Techniques:
- Segment tree with dynamic updates and queries
- Two pointers/sliding window approach for choosing the best split
- Sorting to find optimal problem selection based on weights

Time Complexity: O(n log n + n log(max_value)) where n is the number of problems
Space Complexity: O(n) for storing the segment trees and auxiliary arrays
*/

#include <assert.h>
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
class segtree {
private:
  struct node {
    long long s = 0;
    int cnt = 0;
    node() : s(0), cnt(0) {}
    void assign(int v) {
      if (v) {
        s = v;
        cnt = 1;
      } else {
        s = 0;
        cnt = 0;
      }
    }
    void merge(const node &a, const node &b) {
      s = a.s + b.s;
      cnt = a.cnt + b.cnt;
    }
  };
  int b;
  node *tree;

public:
  const int n;
  segtree(int _n) : n(_n) {
    assert(_n > 0);
    for (b = 1; b < n; b <<= 1)
      ;
    tree = new node[b << 1];
    for (int i = 0; i < n; i++) {
      tree[b + i] = node();
    }
    for (int i = b - 1; i > 0; i--) {
      tree[i].merge(tree[i * 2], tree[i * 2 + 1]);
    }
  }
  template <typename... M> void update(int ind, const M &...v) {
    assert(0 <= ind && ind < n);
    tree[b + ind].assign(v...);
    for (int i = (b + ind) / 2; i > 0; i >>= 1) {
      tree[i].merge(tree[i * 2], tree[i * 2 + 1]);
    }
  }
  long long query(int k) const {
    int x = 1;
    long long sum = 0;
    while (x < b) {
      const node &L = tree[x << 1];
      long long cnt_left = L.cnt;
      if (cnt_left <= k) {
        sum += L.s;
        k -= cnt_left;
        x = (x << 1) ^ 1;
      } else {
        x = (x << 1);
      }
    }
    const node &nd = tree[x];
    if (k > 0) {
      sum += nd.s;
      k -= nd.cnt;
    }
    if (k > 0) {
      return 2e18;
    }
    return sum;
  }
};
void foo() {
  int n, k;
  cin >> n >> k;
  vector<int> a(n);
  vector<pair<int, int>> values(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    values[i] = {a[i], i};
  }
  sort(values.begin(), values.end());
  vector<int> pos(n);
  for (int i = 0; i < n; i++) {
    pos[values[i].second] = i;
  }
  segtree left_st(n), right_st(n);
  for (int i = 0; i < n; i++) {
    right_st.update(pos[i], a[i]);
  }
  long long ans = 2e18;
  auto consider = [&](int L) -> pair<long long, long long> {
    const int R = k - L;
    long long sumL = left_st.query(L);
    long long sumR = right_st.query(R);
    ans = min(ans, max(sumL, sumR));
    return make_pair(sumL, sumR);
  };
  int take_left = 0;
  consider(0);
  for (int i = 0; i < n; i++) {
    left_st.update(pos[i], a[i]);
    right_st.update(pos[i], 0);
    while (take_left < k) {
      auto p = consider(take_left + 1);
      if (p.first <= p.second) {
        take_left++;
      } else {
        break;
      }
    }
    consider(take_left);
  }
  cout << ans << '\n';
}
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int cases;
  cin >> cases;
  for (int t = 1; t <= cases; t++) {
    foo();
  }
}


// https://github.com/VaHiX/CodeForces/