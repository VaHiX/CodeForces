// Problem: CF 985 B - Switches and Lamps
// https://codeforces.com/contest/985/problem/B

/*
Algorithm: 
- For each lamp, count how many switches can turn it on.
- For each switch, check if removing it still allows all lamps to be turned on.
- A switch can be removed if for every lamp it controls, there's at least one other switch that can turn it on.

Time Complexity: O(n * m)
Space Complexity: O(m)

Techniques:
- Preprocessing to count lamp coverage
- Greedy check for removable switches
*/

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

int main() {
  long n, m;
  scanf("%ld %ld", &n, &m);
  std::vector<std::string> g(n);
  for (long p = 0; p < n; p++) {
    std::cin >> g[p];
  }
  std::vector<long> v(m, 0); // Count how many switches control each lamp
  for (long row = 0; row < n; row++) {
    for (long col = 0; col < m; col++) {
      v[col] += (g[row][col] == '1'); // Increment count for each lamp controlled by a switch
    }
  }
  bool possible(0); // Flag to indicate if there exists a removable switch
  for (long row = 0; row < n; row++) {
    bool rem(true); // Assume this switch can be removed
    for (long col = 0; col < m; col++) {
      if (g[row][col] == '1' && v[col] <= 1) { // If switch controls a lamp that is controlled by only this switch
        rem = false; // Cannot remove this switch
        break;
      }
    }
    if (rem) {
      possible = true; // Found a removable switch
      break;
    }
  }
  puts(possible ? "YES" : "NO");
  return 0;
}


// https://github.com/VaHiX/CodeForces/