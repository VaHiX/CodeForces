// Problem: CF 488 B - Candy Boxes
// https://codeforces.com/contest/488/problem/B

/*
Algorithm: Brute-force search with mathematical constraints
Approach:
- Given n candies in boxes, we need to find 4-n missing values such that
  the arithmetic mean, median, and range are all equal.
- For 4 numbers a1 ≤ a2 ≤ a3 ≤ a4:
    - Arithmetic mean = (a1 + a2 + a3 + a4) / 4
    - Median = (a2 + a3) / 2
    - Range = a4 - a1
- Let the common value be M. Then:
    - a1 + a2 + a3 + a4 = 4 * M
    - a2 + a3 = 2 * M
    - a4 - a1 = M
- From these equations, we derive relationships:
    - Let a1 = a, then a4 = a + M, a2 + a3 = 2 * M
    - So a1 + a2 + a3 + a4 = a + (2*M) + (a + M) = 2*a + 3*M = 4*M ⇒ a = M/2
    - Thus, a1 = M/2, a4 = 3*M/2
    - Also from a1 + a4 = M, a2 + a3 = 2*M
    - With one of a2, a3 fixed as b, other becomes (2*M - b)
    - Therefore, we can represent the sequence as: [M/2, b, 2*M - b, 3*M/2]
    - So we iterate over possible M values and b values to generate valid quadruples.

Time Complexity: O(N^2) where N = 1507, effectively O(1) due to small N
Space Complexity: O(1) - only storing a few vectors and constants
*/

#include <algorithm>
#include <cstdio>
#include <vector>
int main() {
  const int N = 1507;
  int n;
  scanf("%d", &n);
  std::vector<int> g;
  for (int p = 0; p < n; p++) {
    int x;
    scanf("%d", &x);
    g.push_back(x);
  }
  sort(g.begin(), g.end());
  bool possible(false);
  std::vector<int> v, w;
  // Iterate through possible values for M/2 (a1) to determine valid combinations
  for (int a = 1; 3 * a <= N; a++) {
    if (possible) {
      break;
    }
    // Try all valid b values that could be a2 in our derived sequence [a, b, 2*M - b, 3*a]
    for (int b = a; b <= 2 * a; b++) {
      // Construct the candidate sequence based on derived formulas
      std::vector<int> s;
      s.push_back(a);
      s.push_back(b);
      s.push_back(4 * a - b);
      s.push_back(3 * a);
      std::vector<int> w(4);
      // Find elements in s that are NOT in g (i.e., missing elements)
      std::vector<int>::iterator it = std::set_difference(
          s.begin(), s.end(), g.begin(), g.end(), w.begin());
      w.resize(it - w.begin());
      if (w.size() == 4 - n) {
        possible = true;
        v = w;
        break;
      }
    }
  }
  if (possible) {
    puts("YES");
    for (int p = 0; p < v.size(); p++) {
      printf("%d\n", v[p]);
    }
  } else {
    puts("NO");
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/