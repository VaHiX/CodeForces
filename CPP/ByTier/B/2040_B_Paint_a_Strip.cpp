// Problem: CF 2040 B - Paint a Strip
// https://codeforces.com/contest/2040/problem/B

/*
B. Paint a Strip
Algorithm: Greedy approach to minimize the number of Type-1 operations.
Time Complexity: O(log n) per test case due to the while loop that doubles 'last' each time.
Space Complexity: O(1) - only using a few variables.

The problem asks for the minimum number of Type-1 operations (setting a[i]=1) 
to make all elements of an array of size n equal to 1. 

Key insight:
We can use Type-2 operations to "cover" segments of 1s, but we must start 
with at least one 1 in each segment. The greedy strategy is to find the minimal 
number of 1s such that we can cover the entire array with a sequence of Type-2 operations.

This leads to a recursive-like structure where:
- Initially, we have one 1 (cnt=1, last=1)
- Each step, we double the size of the region we can cover (last = 2 * last + 2)
- The number of Type-1 operations needed is equal to how many times we need this doubling,
  which corresponds to the depth of a binary tree-like structure.

The formula `last = 2 * last + 2` represents the minimum number of elements 
that can be covered using the current count of 1s (Type-1 operations). 
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long cnt(1), last(1);        // cnt: number of Type-1 ops, last: max elements covered so far
    while (last < n) {           // while we haven't covered the full array
      ++cnt;                     // increment operation count
      last = 2 * last + 2;       // update coverage using formula
    }
    printf("%ld\n", cnt);
  }
}


// https://github.com/VaHiX/codeForces/