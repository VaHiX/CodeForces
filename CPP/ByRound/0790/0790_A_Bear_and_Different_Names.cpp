// Problem: CF 790 A - Bear and Different Names
// https://codeforces.com/contest/790/problem/A

/* 
 * Purpose: This program solves the "Bear and Different Names" problem.
 *          Given constraints on consecutive groups of soldiers' names,
 *          it generates a valid sequence of names such that:
 *          - Each group of k consecutive soldiers has all unique names (YES)
 *          - Or at least one name is repeated (NO)
 *          Names follow the format: First letter uppercase, rest lowercase.
 *          
 * Algorithm:
 * - Start with a base set of names using a simple pattern (like "Aa", "Ab", ..., "Az", "Ba", ...),
 *   ensuring no name is too long and all follow the naming rule.
 * - For each group described as "NO", we adjust the last soldier's name in that group
 *   to be identical to the first soldier's name, violating the uniqueness requirement.
 * 
 * Time Complexity: O(n*k) where n is number of soldiers and k is group size.
 *                  We iterate through n-k+1 groups, and for each, we may copy a name.
 * Space Complexity: O(n) for storing the names array.
 */

#include <stddef.h>
#include <iostream>
#include <string>

using namespace std;

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  int n, k;
  cin >> n >> k;
  
  // Initialize names with a simple pattern (e.g., Aa, Ab, Ac, ..., Az, Ba, ..., Zz)
  string ans[n];
  for (int i = 0; i < n; i++) {
    ans[i] = "00";                      // Initialize with two characters
    ans[i][0] = i / 26 + 'A';           // First letter: A-Z using integer division
    ans[i][1] = i % 26 + 'a';           // Second letter: a-z using modulo
  }
  
  string s;
  // Process each group description from input
  for (int i = 0; i <= n - k; i++) {
    cin >> s;
    if (s == "NO") {
      // If group is not effective, make the last soldier's name same as first soldier's name
      ans[i + k - 1] = ans[i];
    }
  }
  
  // Output all generated names
  for (string i : ans)
    cout << i << ' ';
    
  return 0;
}


// https://github.com/VaHiX/CodeForces/