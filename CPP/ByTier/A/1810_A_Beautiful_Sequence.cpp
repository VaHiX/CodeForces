// Problem: CF 1810 A - Beautiful Sequence
// https://codeforces.com/contest/1810/problem/A

/*
 * Problem: Beautiful Sequence
 * 
 * Algorithm/Techniques: Greedy approach
 * 
 * Time Complexity: O(n) per test case
 * Space Complexity: O(1)
 * 
 * A sequence is good if there exists at least one i such that a[i] == i.
 * A sequence is beautiful if there exists at least one subsequence that is good.
 * 
 * Key Insight:
 * If any element in the array is less than or equal to its 1-based index,
 * then we can form a good subsequence by including that element at position p.
 * 
 * For example, if a[p] <= p, we can take the subsequence with just this element
 * which is good because a[p] = p.
 * 
 * So for each test case:
 * - Iterate through all elements of the array.
 * - Check if any element x satisfies x <= current index p (1-based).
 * - If yes, set result to true.
 * - Output YES if at least one such element exists, else NO.
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    bool res(false); // Initialize result to false
    for (long p = 1; p <= n; p++) { // Iterate from 1 to n (1-based indexing)
      long x;
      scanf("%ld", &x);
      if (x <= p) { // If current element is <= its position, subsequence is good
        res = true;
      }
    }
    puts(res ? "YES" : "NO"); // Print result
  }
}


// https://github.com/VaHiX/codeForces/