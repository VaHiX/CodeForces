// Problem: CF 2079 B - Arithmetic Exercise
// https://codeforces.com/contest/2079/problem/B

/*
 * Problem: Maximum Sum Array After Operations
 * 
 * Description:
 * Given an array a of length n initialized with zeros and m operations,
 * each operation chooses an index j and updates a[j] = x[i] - a[j].
 * Goal is to maximize the sum of elements in the array after all operations.
 * 
 * Algorithms/Techniques:
 * - Greedy approach using multiset for maintaining optimal choices
 * - Dynamic programming with optimized space and time for specific cases
 * 
 * Time Complexity: O(M log M) where M is sum of m across test cases
 * Space Complexity: O(N + M) where N is sum of n across test cases and M is sum of m
 */

#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <vector>

using namespace std;
long long inf = 2e16 + 5;

void solve2() {
  int n, m;
  cin >> n >> m;
  vector<int> a(m);
  for (int &x : a)
    cin >> x;
  reverse(a.begin(), a.end()); // Reverse to process operations in order
  vector<vector<long long>> dp(m, vector<long long>(n + 5000, -inf));
  dp[0][1] = a[0]; // Base case: first element set to its value
  for (int i = 1; i < m; ++i) {
    for (int j = 0; j <= i + 1; ++j) {
      if (j > n)
        continue;
      if (!((i + j) & 1)) // Only allow odd sum of indices
        continue;
      if (j > 0)
        dp[i][j] = dp[i - 1][j - 1] + a[i]; // Add to previous step if moving forward
      if (j < n)
        dp[i][j] = max(dp[i][j], dp[i - 1][j + 1] - a[i]); // Subtract from previous if moving backward
    }
  }
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j <= m + 1; ++j) {
      if (dp[i][j] <= -inf + 2e12) {
        cout << "--- ";
        continue;
      }
      cout << dp[i][j] << " "; // Print current DP state
    }
    cout << "\n";
  }
  cout << *max_element(dp[m - 1].begin(), dp[m - 1].end()) << "\n"; // Maximum final value
}

void solve() {
  int n, m;
  cin >> n >> m;
  vector<long long> a(m);
  for (long long &x : a)
    cin >> x;
  reverse(a.begin(), a.end()); // Process operations in reverse order
  long long ans = a[0]; // Start with initial operation applied to first element
  multiset<long long> ms; // Maintain set of changes for greedy selection
  for (int i = 1; i < m; ++i) {
    if (n % 2 == 0) { // Even array size case
      if (i & 1) { // Odd operation index - subtract from current value
        ans -= a[i];
        ms.insert(2 * a[i]); // Push twice the value to simplify balancing
      } else { // Even operation index - add or maximize using stored values
        if (!ms.size()) // No previous stored elements
          ans += a[i];
        else
          ans = max(ans + a[i], ans + *ms.rbegin() - a[i]); // Take maximum from greedy choice
        ms.insert(2 * a[i]); // Insert into multiset
        if ((int)ms.size() > n / 2) { // Maintain size limit of n/2 elements
          ms.erase(prev(ms.end())); // Remove last element
          ms.erase(ms.begin()); // Remove first element (minimum)
        } else {
          ms.erase(prev(ms.end())); // Remove largest value
        }
      }
    } else { // Odd array size case
      if (i & 1) { // Odd operation - subtract from current value
        ans -= a[i];
        ms.insert(2 * a[i]); // Insert updated element
        if ((int)ms.size() > n / 2)
          ms.erase(ms.begin()); // Remove smallest element to maintain capacity
      } else { // Even operation - add or maximize using stored values
        if (!ms.size())
          ans += a[i];
        else
          ans = max(ans + a[i], ans + *ms.rbegin() - a[i]);
        ms.insert(2 * a[i]); // Insert into multiset  
        ms.erase(prev(ms.end())); // Remove largest element
      }
    }
  }

  long long mx = ans; // Store maximum sum found so far
  vector<long long> gigachad; 
  for (long long ass : ms)
    gigachad.push_back(ass); // Extract stored values into array
  reverse(gigachad.begin(), gigachad.end()); // Reverse to process from largest
  for (long long ass : gigachad) {
    ans += ass; // Accumulate the stored gains
    mx = max(mx, ans); // Keep track of maximum overall sum
  }
  cout << mx << "\n";
}

int main() {
  int t;
  cin >> t;
  while (t--)
    solve();
}


// https://github.com/VaHiX/codeForces/