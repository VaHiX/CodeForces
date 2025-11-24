// Problem: CF 2124 I - Lexicographic Partition
// https://codeforces.com/contest/2124/problem/I

// Flowerbox:
// Problem: Lexicographic Partition
// Task: Given an array x, determine if there exists a permutation a such that f([a1, ..., ai]) = xi for each i.
// Algorithm: Recursive backtracking with preprocessing of element positions.
// Time Complexity: O(n log n) per test case due to sorting and recursion depth
// Space Complexity: O(n) for storage of arrays and recursion stack

#include <assert.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
#define pb push_back
typedef long long ll;
#define fi first
#define se second
#define mp make_pair
const int p = 998244353;
const int N = 2010000;

// Fast exponentiation function to compute (a^n) mod p
int qpow(int a, int n) {
  int as = 1;
  for (; n; n >>= 1) {
    if (n & 1)
      as = (ll)as * a % p;
    a = (ll)a * a % p;
  }
  return as;
}

// Store positions of each value in input array
vector<int> o[N];
int a[N]; // original input array
int ans[N]; // result array storing the permutation
int nx[N]; // next occurrence of same element (used for partitioning)

// Recursive function to build the permutation satisfying constraints
bool solve(int l, int r, int u, int v) {
  int t = a[l] + 1;  // next expected value in sequence
  if (r == l) {      // base case - single element
    ans[l] = u;
    return true;
  }
  if (a[l + 1] != t)  // if next element is not t, no valid partition exists
    return false;

  // If no more elements of type t exists in remaining range,
  // we can assign current segment as a single block and recurse
  if (nx[l + 1] > r) {
    ans[l] = v;
    return solve(l + 1, r, u, v - 1);
  }

  ans[l] = u;  // assign first element

  // Iterate through all segments starting from index l
  for (int i = l + 1; i <= r; i = nx[i]) {
    assert(a[i] == t);  // ensure current segment is correctly formed
    int j = min(nx[i] - 1, r);  // compute end of current segment
    ans[i] = u + j - l;  // assign value accordingly

    // Check if recursive call for subsegment returns correct result
    if (i < j &&
        (a[i + 1] != a[i] + 1 || (!solve(i + 1, j, u + i - l, u + j - l - 1))))
      return false;
  }
  return true;
}

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  
  int _;
  cin >> _;
  while (_--) {
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
      cin >> a[i];
    
    // Reset storage containers
    for (int i = 1; i <= n; i++)
      o[i].clear();

    // Group indices by their values
    for (int i = 1; i <= n; i++)
      o[a[i]].pb(i);

    // Set next occurrence pointers
    for (int i = 1; i <= n; i++)
      if (o[i].size()) {
        for (int j = 0; j < o[i].size() - 1; j++)
          nx[o[i][j]] = o[i][j + 1];
        nx[o[i][o[i].size() - 1]] = n + 1;
      }

    // Try to build a solution
    if (solve(1, n, 1, n)) {
      cout << "YES\n";
      for (int i = 1; i <= n; i++)
        cout << ans[i] << " ";
      cout << "\n";
    } else
      cout << "NO\n";
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/