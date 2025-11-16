// Problem: CF 987 C - Three displays
// https://codeforces.com/contest/987/problem/C

/*
 * Problem: Three displays
 * Algorithm: Three-pointer approach with preprocessing
 * Time Complexity: O(n^2)
 * Space Complexity: O(1)
 *
 * The algorithm finds the minimum cost of renting three displays such that
 * their font sizes are in increasing order (s_i < s_j < s_k) with indices i < j < k.
 * For each middle display j, we precompute the minimum cost of a display i < j 
 * such that s_i < s_j, and the minimum cost of a display k > j such that s_j < s_k.
 * We iterate through all possible middle displays and update the result accordingly.
 */

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
  int n;
  cin >> n;
  vector<int> s(n), c(n);
  for (int &i : s)
    cin >> i;
  for (int &i : c)
    cin >> i;
  int res = 1e9;  // Initialize result with a large value
  for (int i = 0; i < n; i++) {
    int l = 1e9;  // Minimum cost of display before i with smaller size
    for (int j = 0; j < i; j++)
      if (s[j] < s[i])
        l = min(l, c[j]);  // Update l if s[j] < s[i], keep the minimum cost
    int r = 1e9;  // Minimum cost of display after i with larger size
    for (int j = i + 1; j < n; j++)
      if (s[i] < s[j])
        r = min(r, c[j]);  // Update r if s[i] < s[j], keep the minimum cost
    res = min(res, l + c[i] + r);  // Update global minimum with current combination
  }
  if (res == 1e9)
    res = -1;  // If no valid triplet found, output -1
  cout << res << endl;
  return 0;
}


// https://github.com/VaHiX/CodeForces/