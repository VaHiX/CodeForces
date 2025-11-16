// Problem: CF 2154 E - No Mind To Think
// https://codeforces.com/contest/2154/problem/E

/*
Code Purpose:
This code solves the problem of maximizing the sum of an array after performing at most k operations.
Each operation allows selecting a subsequence of odd length x and replacing all elements in it with the median of that subsequence.
The algorithm uses a combination of sorting, prefix sums, and binary search-like optimization to find the optimal strategy.

Algorithms/Techniques:
- Sorting the array to facilitate median selection
- Prefix sums for efficient range sum queries
- Optimization using a two-pointer technique to find the best x and y values (number of operations)

Time Complexity: O(N^2), where N is the size of the array. This comes from the nested loop structure.
Space Complexity: O(N), for storing the array and prefix sum arrays.

*/
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
typedef long long ll;
vector<ll> a, prefix;
int N, K;
ll eval(int x, int y) {
  int d = min(x - 1, y * K); // Calculate the number of elements that can be updated
  if (x + y > N) {
    return -1; // Invalid configuration
  } else {
    // Compute the maximum possible sum after applying x and y operations
    return prefix[N] + d * a[x] + y * a[x] -
           (prefix[x + y] - prefix[x] + prefix[d] - prefix[0]);
  }
}
void Solve() {
  ll best = 0;
  cin >> N >> K;
  a.clear();
  prefix.clear();
  a.resize(N + 1);
  prefix.resize(N + 1);
  for (int i = 1; i <= N; i++) {
    cin >> a[i];
  }
  sort(a.begin() + 1, a.begin() + N + 1); // Sort the array to simplify median computation
  for (int i = 1; i <= N; i++) {
    prefix[i] = prefix[i - 1] + a[i]; // Build prefix sum array
  }
  int r = 1;
  for (int i = 1; i <= N; i++) {
    --r;
    r = max(0, r); // Ensure r doesn't go below 0
    while (eval(i, r) < eval(i, r + 1)) { // Adjust r to find the maximum
      ++r;
    }
    best = max(best, eval(i, r)); // Update the best answer
  }
  cout << best << '\n';
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int T;
  cin >> T;
  while (T--) {
    Solve();
  }
}


// https://github.com/VaHiX/CodeForces/