// Problem: CF 2129 C1 - Interactive RBS (Easy Version)
// https://codeforces.com/contest/2129/problem/C1

/*
 * Interactive RBS (Easy Version)
 * 
 * Problem Description:
 * Given a hidden bracket sequence of length n, determine the sequence using at most 550 queries.
 * Each query asks for the number of non-empty regular bracket substrings in a chosen subsequence.
 * 
 * Approach:
 * 1. First, we find the positions of the leftmost '(' and rightmost ')' by binary search.
 *    Binary search works on the indices such that we can determine whether a prefix contains
 *    a '(', which helps identify boundaries.
 * 2. Then, we reconstruct the full bracket sequence with the help of queries involving pairs of indices,
 *    determining if they form valid brackets or not based on the returned counts from the function f().
 * 
 * Time Complexity: O(n log n) - due to binary search and iterating through all positions
 * Space Complexity: O(n) - used for storing the result array s[]
 * 
 */


#include <iostream>
#include <utility>

using namespace std;
const int N = 1005;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int t, n, i, l, r, m, x, s[N];
  cin >> t;
  while (t--) {
    cin >> n;
    l = 1;           // Left boundary for binary search
    r = n;           // Right boundary for binary search
    while (r - l > 1) {  // Binary search loop to find leftmost '(' and rightmost ')'
      m = (l + r) / 2;   // Middle point
      cout << "? " << 2 * (m - l + 1);   // Query length is twice the number of elements in range [l, m]
      for (i = l; i <= m; i++)           // First part: indices from l to m
        cout << ' ' << i;
      for (i = m; i >= l; i--)           // Second part: same indices reversed
        cout << ' ' << i;
      cout << endl;
      cin >> x;     // Read response from interaction
      if (x)        // If the count of valid brackets > 0, then a '(' was found on left side
        r = m;      // Adjust right boundary to move towards left
      else          // Else, no valid pairs were formed => '(' is on the right
        l = m;      // Adjust left boundary to move towards right
    }
    cout << "? 2 " << l << ' ' << r << endl;  // Final query to distinguish between l and r as endpoints
    cin >> x;
    if (!x)     // If no valid pairs found, swap l and r to get the correct order
      swap(l, r);
    for (i = 2; i <= n; i++) {         // Reconstruct entire bracket sequence
      cout << "? 7 " << l << ' ' << i - 1 << ' ' << i << ' ' << i - 1 << ' '
           << i << ' ' << r << ' ' << r << endl;
      cin >> x;              // Read the count of valid brackets from query
      if (x == 2)            // Both positions form a parenthesis pair (either both '(' or both ')')
        s[i - 1] = s[i] = 0; // Mark as ')' for both indices
      else if (x == 1)       // Only one of the two is in an opening/closing bracket
        s[i - 1] = s[i] = 1; // Mark as '(' for both indices
      else if (x == 4) {     // Different bracket types: first one ')' and second one '('
        s[i - 1] = 0;
        s[i] = 1;
      } else {               // Case x == 3, i.e., the reverse situation of above
        s[i - 1] = 1;
        s[i] = 0;
      }
      if (i < n - 1)
        i++;   // Skip next index after processing the pair (optimization to reduce query count)
    }
    cout << "! ";     // Print the final answer tag
    for (i = 1; i <= n; i++)     // Output the constructed bracket sequence
      cout << (s[i] ? ')' : '(');
    cout << endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/