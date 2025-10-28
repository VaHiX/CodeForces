// Problem: CF 1279 A - New Year Garland
// https://codeforces.com/contest/1279/problem/A

/*
Problem: A. New Year Garland
Purpose: Determine if it's possible to arrange lamps of three colors (red, green, blue) 
         into a garland such that no two adjacent lamps have the same color.

Algorithms/Techniques:
- Sorting the lamp counts to identify the maximum count.
- Using mathematical condition to check if the largest group can be interspersed 
  with the other two groups without violating adjacency rules.

Time Complexity: O(1) per test case (sorting 3 elements is constant time)
Space Complexity: O(1) (only using a fixed-size vector of 3 elements)

Input:
- t (number of test cases)
- For each test case: r, g, b (counts of red, green, blue lamps)

Output:
- "Yes" if a valid garland can be made, otherwise "No"
*/

#include <algorithm>
#include <cstdio>
#include <vector>
typedef long long ll;
int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    std::vector<ll> a(3); // Store the counts of red, green, blue lamps
    for (ll p = 0; p < 3; p++) {
      scanf("%lld", &a[p]); // Read the lamp counts
    }
    sort(a.begin(), a.end()); // Sort to get max count in a[2]
    bool ans = (a[2] <= (a[0] + a[1] + a[2] + 1) / 2); // Check if largest group can be interlaced
    puts(ans ? "Yes" : "No"); // Output result
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/