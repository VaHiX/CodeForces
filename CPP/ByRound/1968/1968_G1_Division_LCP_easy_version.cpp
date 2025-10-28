// Problem: CF 1968 G1 - Division + LCP (easy version)
// https://codeforces.com/contest/1968/problem/G1

/*
 * Problem: Division + LCP (easy version)
 * 
 * Purpose: Given a string and a fixed number of divisions k, find the maximum possible
 *          length of the Longest Common Prefix (LCP) of all substrings in a division.
 * 
 * Algorithm:
 *  - Use Z-algorithm to compute the Z-array for the string, which helps in efficiently
 *    finding the longest substring starting at each index that matches a prefix.
 *  - Binary search on the answer (length of LCP) to find the maximum valid length.
 *  - For a given length 'x', check if we can partition the string into exactly k
 *    substrings such that each has at least 'x' characters and they all align in
 *    prefix matching using the Z-array.
 * 
 * Time Complexity: O(n * log(n)) per test case due to binary search and Z-algorithm.
 * Space Complexity: O(n) for storing the Z-array and other auxiliary structures.
 * 
 * Techniques:
 *  - Z-algorithm for efficient substring matching.
 *  - Binary search on the result.
 *  - Greedy approach for checking valid partitions.
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#define endl "\n"
#define INF 0x7f7f7f7f
#define PII pair<int, int>
#define pb push_back
#define fi first
#define se second
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;

void solve() {
  int n, k, t;
  cin >> n >> k >> t; // Read n, k, t
  string s;
  cin >> s; // Read the input string

  // Compute Z-array for the string using the algorithm
  std::vector<int> z(n);
  z[0] = n; // The first element is always n
  int l = 0, r = 0; // Initialize left and right pointers for Z-algorithm
  for (int i = 1; i < n; i++) {
    if (i < r)
      z[i] = min(z[i - l], r - i); // Use previously computed values if possible
    while (i + z[i] < n && s[i + z[i]] == s[z[i]])
      z[i]++; // Extend match as far as possible
    if (i + z[i] > r)
      r = i + z[i], l = i; // Update the rightmost match
  }

  // Lambda function to check if it's possible to partition into k parts with LCP >= x
  auto check = [&](int x) {
    int cnt = 0; // Count of valid partitions
    for (int i = 0; i < n; i++) {
      if (z[i] >= x) { // If Z[i] >= x, then substring starting at i has prefix match of at least x
        i = i + x - 1; // Jump ahead to avoid reprocessing
        cnt++;
      }
    }
    return cnt >= k; // Return true if we can make at least k valid substrings
  };

  // Binary search on the answer
  int x = 0, y = n / k; // x = low, y = high
  while (x < y) {
    int mid = x + y + 1 >> 1; // Calculate mid (round up)
    if (check(mid))
      x = mid; // Try higher
    else
      y = mid - 1; // Try lower
  }

  cout << x << endl; // Output the maximum valid LCP
}

int main() {
  int t;
  ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> t;
  while (t--)
    solve();
}


// https://github.com/VaHiX/CodeForces/