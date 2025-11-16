// Problem: CF 2072 B - Having Been a Treasurer in the Past, I Help Goblins Deceive
// https://codeforces.com/contest/2072/problem/B

/*
B. Having Been a Treasurer in the Past, I Help Goblins Deceive

Purpose:
This program determines the maximum number of subsequences "-_-" that can be formed 
from a given string of '-' and '_' characters by optimally rearranging them.

Algorithm:
- Count the number of '-' (a) and '_' (b) characters.
- To form "subsequences" "-_-", we need:
  - One '-' character at the beginning,
  - One '_' character in the middle,
  - One '-' character at the end.
- The optimal arrangement is to place all '-' characters first, followed by all '_' 
  characters, then all remaining '-' characters (i.e., "--...__...--...").
- To count such subsequences:
  - For each middle '_', we can choose one '-' from those before it and one '-' from those after it.
  - The number of ways to form "-_-" using the first i '-' characters and j '_' characters
    and remaining k '-' characters is: 
      (number of choices for first '-' in prefix) * (number of '_' in middle section) * (choices for second '-' in suffix).
- For a sequence like: ---___---, we can use the formula:
   b * (a / 2) * ((a + 1) / 2), 
   where we divide total '-' into two parts and compute combinations accordingly.

Time Complexity: O(n) per test case
Space Complexity: O(1)

*/

#include <stddef.h>
#include <iostream>
#include <string>

int main() {
  std::ios_base::sync_with_stdio(false);  // Improves I/O speed
  long t;
  std::cin >> t;
  while (t--) {
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    long long a(0), b(0);
    for (size_t p = 0; p < s.size(); p++) {
      a += (s[p] == '-');  // Count total '-' characters
      b += (s[p] == '_');  // Count total '_' characters
    }
    long long ans = b * (a / 2) * ((a + 1) / 2);  // Compute maximum subsequences using derived formula
    std::cout << ans << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/