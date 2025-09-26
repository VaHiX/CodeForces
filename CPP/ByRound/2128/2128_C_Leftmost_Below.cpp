// Problem: CF 2128 C - Leftmost Below
// https://codeforces.com/contest/2128/problem/C

/*
C. Leftmost Below
Time Complexity: O(n) per test case
Space Complexity: O(1)

Algorithm/Techniques: Greedy approach with reverse analysis

The problem involves determining whether a target array can be reached by performing specific operations on an initially zero array.
Each operation selects a value x > minimum element in current array,
then finds the leftmost position i such that a[i] < x (and all previous elements are >= x),
then increments a[i] by x.

Key insight:
We simulate the reverse process. For each element from right to left:
- If the current element is less than the minimum seen so far divided by 2 + 1, it's impossible.
- Update the running minimum to be the smaller of itself and current element.
This greedy approach ensures we maintain valid states throughout the sequence.

*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long mn(1e9 + 7); // Initialize minimum with a large value
    bool ans(true);
    while (n--) {
      long b;
      scanf("%ld", &b);
      if (mn < b / 2 + 1) {   // Check if current element is too small to be valid
        ans = false;
      }
      mn = (mn < b ? mn : b); // Update the running minimum
    }
    puts(ans ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/