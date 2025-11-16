// Problem: CF 2072 C - Creating Keys for StORages Has Become My Main Skill
// https://codeforces.com/contest/2072/problem/C

/*
C. Creating Keys for StORages Has Become My Main Skill
===============================================
Problem: Given n and x, construct an array of length n such that:
- The bitwise OR of all elements equals x.
- The MEX (minimum excludant) of the array is maximized.
    
Algorithm:
- Try to fill the array with consecutive integers starting from 0 as long as the OR doesn't exceed x.
- If we cannot use all positions (because OR grows too fast), then put x at the last position to make sure that OR equals x.

Time Complexity: O(n) per test case
Space Complexity: O(n)

*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, x;
    scanf("%ld %ld", &n, &x);
    std::vector<long> v(n);
    long cx(0); // cumulative OR of elements processed so far
    for (size_t p = 0; p < n; p++) {
      cx |= p; // OR with current index to see if we can include it without exceeding x
      if ((cx | x) > x) { // if adding x would exceed the target, stop early
        break;
      }
      v[p] = p; // assign current index to array element
    }
    if (cx != x) { // if final OR is not exactly x, fix it by setting last element to x
      v.back() = x;
    }
    for (size_t p = 0; p < n; p++) {
      printf("%ld ", v[p]);
    }
    puts("");
  }
}


// https://github.com/VaHiX/codeForces/