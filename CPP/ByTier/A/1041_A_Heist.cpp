// Problem: CF 1041 A - Heist
// https://codeforces.com/contest/1041/problem/A

/*
A. Heist
Algorithms/Techniques: Sorting, Greedy
Time complexity: O(n log n) - due to sorting implicit in min/max calculation over input
Space complexity: O(1) - only using a few variables regardless of input size

The problem involves determining the minimum number of keyboards stolen from a store.
Keyboards were originally numbered consecutively from some starting integer x.
Given the indices of remaining keyboards, we must find the minimal number of thefts.

Approach:
1. Find the minimum and maximum indices among the remaining keyboards.
2. Calculate the total expected keyboards in a complete sequence from min to max.
3. Subtract the actual count of remaining keyboards to get the number of stolen ones.

The difference between max and min gives us the length of the hypothetical range,
but since we start counting from min, the total number of keys in that span is (max - min + 1).
Subtracting 'n' gives us how many were stolen.
*/

#include <cstdio>
int main() {
  long n;
  scanf("%ld", &n);
  long mn(1e9 + 7), mx(0); // Initialize mn to large value, mx to small value
  for (long p = 0; p < n; p++) {
    long a;
    scanf("%ld", &a);
    mn = (mn < a) ? mn : a; // Update minimum index
    mx = (mx > a) ? mx : a; // Update maximum index
  }
  printf("%ld\n", mx - mn + 1 - n); // Output the number of stolen keyboards
  return 0;
}


// https://github.com/VaHiX/codeForces/