// Problem: CF 1847 B - Hamon Odyssey
// https://codeforces.com/contest/1847/problem/B

/*
B. Hamon Odyssey

Purpose:
This code solves the problem of dividing a sequence of vampire strengths into contiguous groups such that:
- Each vampire belongs to exactly one group.
- The sum of the "strengths" (bitwise AND of all elements in a group) is minimized.
- Among all ways to achieve the minimum sum, we maximize the number of groups.

Algorithm:
The approach uses a greedy method:
1. Start from the first element.
2. Keep extending the current group by performing bitwise AND with each new element.
3. If at any point the current AND becomes zero, it means we can start a new group (since 0 is the smallest possible AND value).
4. After processing all elements, check if there's a remaining group that hasn't contributed to the count yet.

Time Complexity: O(n) per test case, where n is the number of vampires.
Space Complexity: O(1), as only a few variables are used regardless of input size.

*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long cur;
    scanf("%ld", &cur);
    long cnt(0); // Count of groups formed
    for (long p = 1; p < n; p++) { // Iterate through remaining elements
      long x;
      scanf("%ld", &x);
      if (!cur) { // If previous AND result is zero, start a new group
        ++cnt;
        cur = x; // Reset current to the new value
      } else {
        cur &= x; // Continue extending the current group by ANDing with new element
      }
    }
    cnt += (!cur);   // Add one more group if last group wasn't counted (i.e., if cur is 0)
    cnt += (!cnt);   // If no groups were formed, we still have to make at least one group
    printf("%ld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/