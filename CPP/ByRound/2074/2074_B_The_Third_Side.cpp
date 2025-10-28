// Problem: CF 2074 B - The Third Side
// https://codeforces.com/contest/2074/problem/B

/*
B. The Third Side
Algorithm: Greedy approach to maximize the final element.
We are given a sequence of positive integers and we must repeatedly combine two elements 
to form a new element x such that a triangle can be formed with side lengths a[i], a[j], and x.
The key insight is to always pick the two largest available numbers, then choose x to be 
the sum of the two smaller sides minus 1 (or more precisely, we try to maximize x by choosing
it just less than the sum of other two to keep triangle inequality satisfied, but in this case,
the optimal strategy is to combine greedily and form a new element which is effectively:
s - (n - 1) where s is sum of all elements. This works because the operation essentially allows us to 
reduce n elements into 1 with maximum gain when combining optimally).

Time Complexity: O(n) per test case
Space Complexity: O(1)
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long s(0); // Sum of all elements
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      s += x; // Accumulate the total sum
    }
    printf("%ld\n", s - (n - 1)); // Output the result: sum minus (n-1)
  }
}


// https://github.com/VaHiX/codeForces/