// Problem: CF 1515 A - Phoenix and Gold
// https://codeforces.com/contest/1515/problem/A

#include <cstdio>
#include <vector>
/*
 * Problem: Phoenix and Gold
 * 
 * Algorithm/Technique:
 * - Greedy approach to avoid prefix sum equal to x
 * - We process elements one by one, and keep track of current sum.
 * - If adding an element makes the sum equal to x, we defer it and store it temporarily.
 * - After processing all elements, if the total sum equals x, it is impossible to arrange.
 * - Otherwise, we output the arrangement.
 *
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, x;
    scanf("%ld %ld", &n, &x);
    std::vector<long> w;
    long s(0), rem(-1); // s is current sum, rem stores the element that would cause a conflict if added now
    for (long p = 0; p < n; p++) {
      long a;
      scanf("%ld", &a);
      if (s + a == x) {
        // If adding 'a' makes sum equal to x, store it temporarily
        if (rem > 0) {
          // If we already have a deferred element, add it to the result and update sum
          s += rem;
          w.push_back(rem);
        }
        rem = a; // defer 'a' for now
      } else {
        // Add 'a' to the result and update sum
        w.push_back(a);
        s += a;
      }
    }
    if (rem > 0) {
      // Add the deferred element to the end
      s += rem;
      w.push_back(rem);
    }
    if (s == x) {
      // If total sum equals x, no valid arrangement possible
      puts("NO");
    } else {
      // Print valid arrangement
      puts("YES");
      for (long p = 0; p < w.size(); p++) {
        printf("%ld ", w[p]);
      }
      puts("");
    }
  }
}

// https://github.com/VaHiX/CodeForces/