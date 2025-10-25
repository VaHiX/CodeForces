// Problem: CF 1877 D - Effects of Anti Pimples
// https://codeforces.com/contest/1877/problem/D

/*
 * Problem: Effects of Anti Pimples
 * 
 * Purpose: Calculate the sum of scores for all possible ways to choose black indices,
 *          where each way results in a set of black and green elements, and score is
 *          the maximum value among these elements.
 * 
 * Algorithm:
 * - For each index i, we compute the maximum value among all elements at indices that are multiples of i.
 * - This helps determine the value that would be "green" if index i is chosen as black.
 * - Then, we count how many indices have the same maximum value (in c array).
 * - Using dynamic programming, we calculate powers of 2 to represent combinations.
 * - Finally, we compute the total contribution of each value to the answer by multiplying
 *   the number of subsets that include at least one index with that value, and summing over all values.
 * 
 * Time Complexity: O(n log n)
 * Space Complexity: O(n)
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;
const int mod = 998244353;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  
  int n;
  cin >> n;
  vector<int> a(n);
  for (int &x : a) {
    cin >> x;
  }
  
  // c[i] will store how many indices have maximum value equal to i
  vector<int> c(100100);
  
  // Process each index to compute the maximum value accessible from it
  for (int i = 1; i <= n; i++) {
    for (int j = i; j <= n; j += i) {
      a[i - 1] = max(a[i - 1], a[j - 1]);  // Update maximum value at index i
    }
    c[a[i - 1]]++;  // Count how many indices have this max value
  }
  
  // Precompute powers of 2 modulo 998244353
  vector<int> p2(100100);
  p2[0] = 1;
  for (int i = 1; i <= n; i++) {
    p2[i] = (ll)p2[i - 1] * 2 % mod;
  }

  int tot = 0;  // Total count of indices processed so far
  int ans = 0;  // Final answer to be computed

  // For each possible value from 0 to 100000:
  for (int i = 0; i <= 100000; i++) {
    // Contribution = p2[tot] * (p2[c[i]] - 1) * i
    // p2[tot] = number of ways to choose black indices from indices not yet handled
    // (p2[c[i]] - 1) = number of non-empty subsets of indices with value i that can be chosen
    // i = value itself
    ans = (ans + (ll)p2[tot] * (p2[c[i]] - 1) % mod * i) % mod;
    tot += c[i];  // Increment total of processed indices
  }
  
  cout << ans;
}


// https://github.com/VaHiX/CodeForces/