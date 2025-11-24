// Problem: CF 1046 A - AI robots
// https://codeforces.com/contest/1046/problem/A

/*
 * Problem: AI robots
 * Task: Count pairs of robots that can see each other and have similar IQs (difference <= K)
 * Algorithms/Techniques:
 *   - Coordinate compression
 *   - 2D range counting with Binary Indexed Tree (Fenwick Tree)
 *   - Divide and Conquer on sorted array
 * 
 * Time Complexity: O(N log N)
 * Space Complexity: O(N)
 */

#include <stdlib.h>
#include <algorithm>
#include <iostream>

#define ll long long
#define endl '\n'
#define rep(i, l, r) for (int i = l; i <= r; i++)
#define per(i, r, l) for (int i = r; i >= l; i--)
const int MX = 3e5 + 7;
const int mod = 1e9 + 7;
using namespace std;

// Fast modular exponentiation
ll qpow(ll a, ll b, ll MOD = mod) {
  for (ll ans = 1;; a = a * a % MOD, b >>= 1) {
    if (b & 1)
      ans = ans * a % MOD;
    if (!b)
      return ans;
  }
}

// Modular inverse using Fermat's little theorem
ll inv(ll a, ll MOD = mod) { return qpow(a, MOD - 2, MOD); }

// Greatest common multiple (not used in current code)
ll __gcm(ll a, ll b) { return a * b / __gcd(a, b); }

// Binary Indexed Tree for range queries and updates
ll cnt[MX], ans = 0;

// Robot data structure
int X[MX], K, dq[MX];

// Update BIT at position pos with value x
void upd(int x, int pos) {
  for (; pos < MX; pos += pos & -pos) {
    cnt[pos] += x;
  }
}

// Get prefix sum up to position pos
int get_sum(int pos) {
  ll sum = 0;
  while (pos) {
    sum += cnt[pos];
    pos -= pos & -pos;
  }
  return sum;
}

struct node {
  int x, r, q, L, R;
  void get() {
    cin >> x >> r >> q;
    L = 0, R = 0;
  }
} p[MX];

// Sort by radius in descending order
bool cmp(node a, node b) { return a.r > b.r; }

// Sort by IQ in descending order
bool cmp1(node a, node b) { return a.q > b.q; }

// Divide and conquer function to count valid pairs
void Dic(int l, int r) {
  if (l == r)
    return;
  int mid = l + r >> 1;
  Dic(l, mid);
  Dic(mid + 1, r);
  int lt = 0, rt = 0;
  for (int i = mid + 1, j = l; i <= r; i++) {
    // Move j forward while difference exceeds K
    while (j <= mid && p[j].q - p[i].q > K)
      j++;
    // Add elements within K range to deque and update BIT
    while (j <= mid && abs(p[j].q - p[i].q) <= K) {
      dq[rt++] = j;
      upd(1, p[j].x);
      j++;
    }
    // Remove elements that are now out of range from BIT
    while (lt < rt && abs(p[dq[lt]].q - p[i].q) > K) {
      upd(-1, p[dq[lt]].x);
      lt++;
    }
    // Count valid pairs using BIT
    ans += get_sum(p[i].R) - get_sum(p[i].L - 1);
  }
  // Clean up the remaining elements in deque from BIT
  for (int j = lt; j < rt; j++) {
    upd(-1, p[dq[j]].x);
  }
  // Merge sorted ranges by IQ
  inplace_merge(p + l, p + mid + 1, p + r + 1, cmp1);
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  int n;
  cin >> n >> K;
  int top = 0;
  
  // Read input and prepare coordinates for compression
  for (int i = 1; i <= n; i++) {
    p[i].get();
    X[++top] = p[i].x;
    X[++top] = p[i].x + p[i].r;
    X[++top] = p[i].x - p[i].r;
  }
  
  // Sort and compress coordinates
  sort(X + 1, X + top + 1);
  top = unique(X + 1, X + top + 1) - X - 1;
  
  // Map original coordinates to compressed ones
  for (int i = 1; i <= n; i++) {
    p[i].L = lower_bound(X + 1, X + top + 1, p[i].x - p[i].r) - X;
    p[i].R = lower_bound(X + 1, X + top + 1, p[i].x + p[i].r) - X;
    p[i].x = lower_bound(X + 1, X + top + 1, p[i].x) - X;
  }
  
  // Sort robots by radius in descending order
  sort(p + 1, p + n + 1, cmp);
  Dic(1, n);
  cout << ans << endl;
}


// https://github.com/VaHiX/codeForces/