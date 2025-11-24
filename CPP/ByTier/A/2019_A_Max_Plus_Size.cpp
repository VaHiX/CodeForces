// Problem: CF 2019 A - Max Plus Size
// https://codeforces.com/contest/2019/problem/A

/*
 * Problem: Max Plus Size
 * Purpose: Given an array of positive integers, color some elements red such that no two adjacent elements are red.
 *          Score = max(red_element_value) + count_of_red_elements.
 *          Find the maximum possible score.
 * 
 * Algorithm:
 * - For each element in the array:
 *   - If index is odd (p % 2 == 1), update 'a' with max of current and previous odd-positioned values.
 *   - If index is even (p % 2 == 0), update 'b' with max of current and previous even-positioned values.
 * - Add half the array size (rounded up) to 'a' and rounded down to 'b'.
 * - Return the maximum of a and b.
 *
 * Time Complexity: O(n) where n is the length of the array
 * Space Complexity: O(1)
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long a(0), b(0); // 'a' holds max of odd indices, 'b' holds max of even indices
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (p % 2) { // odd index
        a = (a > x ? a : x); // update max among odd positions
      } else { // even index
        b = (b > x ? b : x); // update max among even positions
      }
    }
    a += (n / 2); // add count of red elements at odd indices
    b += (n + 1) / 2; // add count of red elements at even indices
    printf("%ld\n", (a > b ? a : b)); // output the maximum score
  }
}


// https://github.com/VaHiX/codeForces/