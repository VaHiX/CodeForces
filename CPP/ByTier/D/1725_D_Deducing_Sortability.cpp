// Problem: CF 1725 D - Deducing Sortability
// https://codeforces.com/contest/1725/problem/D

/*
Code Purpose:
This code solves the problem of finding an array A of length N such that:
1. It is sortable using the given operations on elements.
2. The sum of elements is minimized.
3. Among all such arrays, lexicographically smallest one is chosen.

The solution constructs an array by working backwards from the final state,
determining values for each element based on the structure of the sorting process.

Algorithms/Techniques:
- Greedy construction of array elements to achieve minimal sum and lexicographically smallest ordering
- Binary search using lower_bound for efficient querying
- Arithmetic progression and mathematical optimization for sum calculation

Time Complexity: O(Q * log N + N) where Q is number of queries
Space Complexity: O(N) for storing the array structure
*/

#include <algorithm>
#include <iostream>

using namespace std;
using i64 = long long;
constexpr int maxn = 1e5 + 10;
int n, m, q, s[maxn], w[maxn];
i64 S;

// Function to process each query by finding the value at index p
void solve() {
  int x;
  cin >> x;
  // Find the segment where x lies using binary search
  int p = lower_bound(s + 1, s + m + 1, x) - s - 1;
  // Calculate the internal index within the segment
  int t = x - (s[p] - w[p] / 2);
  // Adjust p and t until t becomes odd (final stage of decomposition)
  while (!(t & 1))
    p++, t >>= 1;
  cout << (p + t) << '\n';
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  
  // Read input
  cin >> n >> q;
  
  // Build the initial array structure
  while (true) {
    m++;
    // Stop when remaining n can be covered by next segment
    if (n <= (m + 1) / 2)
      break;
    // Subtract from n the number of elements added so far
    n -= (m + 1) / 2;
    // Add contribution of current segment to total sum
    S += (i64)m * ((m + 1) / 2);
  }
  // Account for remaining elements
  S += (i64)n * m;
  cout << S << '\n';
  
  // Construct the working array w and cumulative sum array s
  for (int i = 1; i <= m; ++i) {
    // Assign values based on segment structure
    w[i] = m - i + (i >= m - (n - 1) * 2);
    // Compute cumulative sum s[i] of adjusted values
    s[i] = s[i - 1] + w[i] - w[i - 1] / 2;
  }
  
  // Process queries
  while (q--)
    solve();
  
  return 0;
}


// https://github.com/VaHiX/CodeForces/