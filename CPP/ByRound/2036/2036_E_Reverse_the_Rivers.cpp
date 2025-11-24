// Problem: CF 2036 E - Reverse the Rivers
// https://codeforces.com/contest/2036/problem/E

/*
E. Reverse the Rivers
time limit per test2 seconds
memory limit per test256 megabytes

Algorithm: 
- Preprocess prefix OR values for each region across countries.
- For each query, use binary search to find valid range of countries based on conditions.
- Use lower_bound and upper_bound to efficiently determine valid index ranges.
- Time complexity: O(n*k + q*m*log(n)) where n*k <= 1e5 and sum of m <= 1e5
- Space complexity: O(n*k)

Techniques:
- Bitwise OR prefix computation
- Binary search with lower_bound/upper_bound
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
vector<int> a[100000]; // Store preprocessed prefix OR values for each region
string s; // String to store operator ('<' or '>')
int main() {
  ios::sync_with_stdio(false), cin.tie(0);
  int n, k, q, i, j, vl, r, m, cl, cr;
  cin >> n >> k >> q;
  
  // Read input values and store them in a way that allows easy access by region
  for (i = 0; i < n; i++) {
    for (j = 0; j < k; j++) {
      cin >> vl;
      a[j].push_back(vl); // Store value in region j
    }
  }
  
  // Compute prefix OR for each region across countries
  for (i = 1; i < n; i++) {
    for (j = 0; j < k; j++)
      a[j][i] |= a[j][i - 1]; // OR with previous value
  }
  
  // Process queries
  for (; q > 0; q--) {
    cin >> m;
    cl = 0; // Left boundary of valid countries (initially 0)
    cr = n; // Right boundary of valid countries (initially n)
    
    // Process each requirement in the query
    for (i = 0; i < m; i++) {
      cin >> r >> s >> vl;
      r--; // Convert to 0-indexed
      
      if (s[0] == '<') {
        // For "<", we want values strictly less than vl -> upper bound index
        cr = min(cr, (int)(lower_bound(a[r].begin(), a[r].end(), vl) - a[r].begin()));
      } else {
        // For ">", we want values strictly greater than vl -> lower bound index + 1
        cl = max(cl, (int)(upper_bound(a[r].begin(), a[r].end(), vl) - a[r].begin()));
      }
    }
    
    // Output result: if cl < cr then there's at least one valid country
    if (cl < cr)
      cout << cl + 1 << '\n'; // Return 1-indexed country number
    else
      cout << "-1\n"; // No valid country exists
  }
}


// https://github.com/VaHiX/codeForces/