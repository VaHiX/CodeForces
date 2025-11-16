// Problem: CF 1712 E2 - LCM Sum (hard version)
// https://codeforces.com/contest/1712/problem/E2

/*
 * Problem: E2. LCM Sum (hard version)
 * Purpose: Count the number of triplets (i, j, k) such that l <= i < j < k <= r and lcm(i, j, k) >= i + j + k.
 * 
 * Algorithm:
 * - Uses inclusion-exclusion principle with a sieve-like approach.
 * - For each number i, maintain a count of how many numbers are divisible by i.
 * - For each query [l, r], compute total triplets minus invalid ones.
 * - Invalid triplets are those where lcm(i,j,k) < i + j + k.
 * - This is optimized using a Fenwick Tree to efficiently query counts.
 * 
 * Time Complexity: O(N log N + T), where N = 2e5 and T is number of test cases.
 * Space Complexity: O(N), for arrays and vectors.
 */

#include <algorithm>
#include <iostream>
#include <vector>

#define int long long
#define endl '\n'
using namespace std;

const int N = 2e5 + 10;

int n, l, r, cnt[N], t[N], ans[N];
vector<int> id[N], v[N];

// Fenwick Tree update operation
void add(int x, int d) {
  for (; x < N; x += x & -x) { // Add delta to all ancestors
    t[x] += d;
  }
}

// Fenwick Tree query operation
int ask(int x) {
  int s = 0;
  for (; x; x ^= x & -x) { // Sum from root to x
    s += t[x];
  }
  return s;
}

// Helper function to compute combination C(n, 3) = n * (n - 1) * (n - 2) / 6
int js(int a) { return a * (a - 1) * (a - 2) / 6; }

// Helper function to compute length of range [l, r]
int len(int l, int r) { return l <= r ? r - l + 1 : 0; }

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> l >> r;
    ans[i] = js(r - l + 1); // Total triplets in range [l, r]
    // Subtract invalid triplets based on divisibility conditions
    ans[i] -= len((l + 2) / 3, r / 6); // Rule 1: lcm < sum when divisible by 3
    ans[i] -= len((l + 5) / 6, r / 15); // Rule 2: lcm < sum when divisible by 6
    id[l].push_back(i); // Store query indices
    v[l].push_back(r); // Store query right bounds
  }

  // Process from largest to smallest number - sieve style
  for (int i = N - 1; i >= 1; --i) {
    // Propagate counts via sieve (for all multiples of i)
    for (int j = i << 1; j < N; j += i) {
      add(j, cnt[j]++);
    }
    // Process queries at this point
    for (int j = 0; j < id[i].size(); ++j) {
      ans[id[i][j]] -= ask(v[i][j]) - ask(i - 1); // Count valid triplets within range
    }
  }

  for (int i = 1; i <= n; ++i) {
    cout << ans[i] << endl; // Output result for each test case
  }

  return 0;
}


// https://github.com/VaHiX/CodeForces/