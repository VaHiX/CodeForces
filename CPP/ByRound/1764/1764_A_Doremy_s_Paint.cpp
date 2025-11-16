// Problem: CF 1764 A - Doremy's Paint
// https://codeforces.com/contest/1764/problem/A

/*
Purpose: 
This code solves the problem of finding a subarray [l, r] such that the value of (r - l - c(l, r)) is maximized, 
where c(l, r) is the number of distinct elements in the subarray. The approach used is to observe that 
the maximum value of (r - l - c(l, r)) is achieved when the entire array is considered (l=1, r=n), 
as it maximizes the difference between the length of the subarray and the number of distinct elements.

Algorithms/Techniques: 
- Greedy approach by observing the structure of the problem
- Constant time selection of l=1, r=n for all test cases

Time Complexity: O(n) where n is the total number of elements across all test cases.
Space Complexity: O(1) - only using a constant amount of extra space.

*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    // Read the array elements but do not store them - they are not needed for the solution
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
    }
    // Output the optimal l and r as 1 and n respectively for every test case
    printf("1 %ld\n", n);
  }
}


// https://github.com/VaHiX/CodeForces/