// Problem: CF 1264 A - Beautiful Regional Contest
// https://codeforces.com/contest/1264/problem/A

/*
Algorithm: Greedy approach to distribute medals
Approach:
1. Find all distinct problem counts (split points) in descending order
2. Use these split points to determine how to assign gold, silver and bronze medals
3. Try to maximize total medals (g + s + b) while satisfying all constraints
4. The core idea is to select the first few split points and then distribute s and b optimally

Time Complexity: O(n) per test case, where n is the number of participants
Space Complexity: O(n) for storing the vector of problem counts and split points

The algorithm works by:
- Identifying where problem counts change (split points)
- Using greedy selection of g, s, b from these points ensuring g < s and g < b
- Maximizing the total medal count while keeping all constraints
*/
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> v(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &v[p]);
    }
    // Add a sentinel value to simplify boundary checking
    v.push_back(v.back() - 1);
    std::vector<long> d;
    // Find all distinct problem count transitions
    for (long p = 1; p <= n; p++) {
      if (v[p - 1] > v[p]) {
        d.push_back(p);
        // Early termination if we exceed half of participants
        if (p > (n / 2)) {
          break;
        }
      }
    }
    long g(0), s(0), b(0);
    // Only proceed if we have enough distinct values to assign medals
    if (d.size() > 3) {
      // Remove one point to make space for proper assignment
      d.pop_back();
      // Assign gold medals to the first segment (g = d[0])
      g = d[0];
      // Assign silver medals to the second segment (s = d[last] - d[0])
      s = d.back() - d[0];
      // Initialize bronze medals to 0
      b = 0;
      // Try to assign remaining medals to bronze while keeping g < b
      for (long p = d.size() - 1; p > 0; p--) {
        long diff = d[p] - d[p - 1];
        if (b <= g) {
          b += diff;
          s -= diff;
        } else {
          break;
        }
      }
      // Validate that constraints are satisfied
      if (g >= s || g >= b) {
        g = s = b = 0;
      }
    }
    printf("%ld %ld %ld\n", g, s, b);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/