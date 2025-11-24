// Problem: CF 2073 H - Secret Lilies and Roses
// https://codeforces.com/contest/2073/problem/H

/*
Secret Lilies and Roses
Input file: standard input
Output file: standard output
Time limit: 2 seconds
Memory limit: 1024 megabytes

Task:
Given n flowers arranged in a line, each being either a lily or a rose, find an integer k such that the number of lilies among the leftmost k flowers (l_k) equals the number of roses among the rightmost n - k flowers (r_k).

Approach:
1. Use binary search to locate the boundary where l_k = r_k.
   - For a given mid-point, determine if enough lilies have been seen to satisfy the equation l_k = r_k using type queries.
2. Once we identify a candidate k (with some margin), perform multiply queries around this point to compute l_{k-1}, l_k, and l_{k+1} for accurate computation.

Algorithms:
- Binary search on the answer (for finding k)
- Type queries to identify flower types
- Multiply queries to evaluate l_k * r_k

Time Complexity: O(log n) per test case due to binary search and a few multiply queries.
Space Complexity: O(1) - only using constant extra space.

*/

#include <iostream>
#include <string>

using namespace std;
using ll = long long;
#define rep(i, a, b) for (int i = (int)(a); i < (int)(b); i++)
#define all(p) p.begin(), p.end()
void solve();
int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  rep(i, 0, t) solve();
}

void solve() {
  int n;
  cin >> n;
  // Initialize binary search bounds: rose is leftmost (invalid), lily is rightmost (valid)
  int rose = 0, lily = n + 1;
  while (lily - rose > 1) {
    int m = (lily + rose) / 2;
    cout << "type " << m << endl;   // Query type of flower at position m
    string res;
    cin >> res;
    if (res == "lily")
      lily = m;   // Update upper bound since it's a lily
    else
      rose = m;   // Update lower bound since it's a rose
  }

  // Lambda function to perform multiply query and return result
  auto f = [&](int ind) -> int {
    if (ind <= 0 || n <= ind)  // Bounds check for invalid indices
      return 0;
    cout << "multi " << ind << endl;   // Perform multiply query at index ind
    int res;
    cin >> res;
    return res;
  };

  // Find the exact value using three consecutive multiply queries around mid point
  int mid = rose;
  int A = f(mid - 1);   // l_{mid-1}
  int B = f(mid);       // l_{mid}
  int C = f(mid + 1);   // l_{mid+1}

  // We compute the result as: (l_{mid+1} - l_{mid}) + mid - (l_{mid} - l_{mid-1})
  int ans = C - B + mid - (A - B);
  cout << "answer " << ans << endl;
}


// https://github.com/VaHiX/codeForces/