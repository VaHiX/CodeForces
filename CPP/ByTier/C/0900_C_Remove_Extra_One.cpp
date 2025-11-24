// Problem: CF 900 C - Remove Extra One
// https://codeforces.com/contest/900/problem/C

/*
Algorithm/Techniques: 
- The algorithm calculates the impact of removing each element on the number of records in the permutation.
- A record is an element that is greater than all previous elements in the sequence.
- We precompute the effect of removing each element by tracking the maximum and second maximum values seen so far.
- For each element, we determine how removing it affects the number of records by checking if it was the current maximum or second maximum.
- Time Complexity: O(n)
- Space Complexity: O(n)

The approach:
1. Iterate through the permutation and maintain the current maximum (mx) and second maximum (smx).
2. When a new maximum is found, we note the previous maximum as impacted (impact[mx] = -1).
3. When a new second maximum is found, we increment the impact of the current maximum.
4. After processing the entire permutation, the element with the highest impact (most detrimental removal) is chosen.
5. If multiple elements have the same impact, the smallest one is chosen due to the order of iteration.
*/

#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> impact(n + 1, 0);  // Array to store impact of removing each element
  long mx(0), smx(0), rem(1);
  for (long p = 0; p < n; p++) {
    long x;
    scanf("%ld", &x);
    if (x > mx) {
      smx = mx;           // Update second max to previous max
      mx = x;             // Update max
      impact[mx] = -1;    // Mark the old max as negatively impacted by removal
    } else if (x > smx) {
      ++impact[mx];       // Increment impact of current max due to new second max
      smx = x;            // Update second max
    }
  }
  for (long p = 1; p <= n; p++) {
    if (impact[p] > impact[rem]) {
      rem = p;            // Find element with highest impact (most negative impact means more records lost)
    }
  }
  printf("%ld\n", rem);
  return 0;
}


// https://github.com/VaHiX/CodeForces/