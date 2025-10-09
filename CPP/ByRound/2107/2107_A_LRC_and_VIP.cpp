// Problem: CF 2107 A - LRC and VIP
// https://codeforces.com/contest/2107/problem/A

/*
 * Problem: A. LRC and VIP
 * Purpose: Given an array of integers, divide it into two non-empty sequences such that 
 *          the GCD of elements in each sequence are different.
 * Algorithm: 
 *   - Find minimum and maximum values in the array.
 *   - If all elements are equal, it's impossible to split into two groups with different GCDs.
 *   - Otherwise, assign all maximum elements to one group (say 1), others to another (say 2).
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for storing the array
 */
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n);
    long mna(1e5), mxa(-1);  // Initialize min and max values
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
      mna = (mna < a[p] ? mna : a[p]);  // Update minimum
      mxa = (mxa > a[p] ? mxa : a[p]);  // Update maximum
    }
    if (mna == mxa) {  // All elements are same, impossible to split
      puts("No");
      continue;
    }
    puts("Yes");
    for (long p = 0; p < n; p++) {
      printf("%d ", a[p] == mxa ? 1 : 2);  // Assign max element to group 1, others to 2
    }
    puts("");
  }
}


// https://github.com/VaHiX/codeForces/