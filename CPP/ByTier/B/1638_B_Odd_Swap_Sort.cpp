// Problem: CF 1638 B - Odd Swap Sort
// https://codeforces.com/contest/1638/problem/B

/*
B. Odd Swap Sort
Algorithm: The problem asks whether an array can be sorted using adjacent swaps only when the sum of swapped elements is odd.
This means we can only swap elements if one is even and the other is odd.
Key observation:
- Even numbers can only be swapped with odd numbers.
- So, the even numbers must appear in order among themselves (non-decreasing).
- Similarly, the odd numbers must appear in order among themselves (non-decreasing).
- We process the array by separating even and odd elements and checking if they're non-decreasing in their respective groups.

Time Complexity: O(n) per test case
Space Complexity: O(1)

Input:
Each test contains multiple test cases. The first line contains a single integer t (1 ≤ t ≤ 10^5) — the number of test cases.
The first line of each test case contains a single integer n (1 ≤ n ≤ 10^5) — the length of the array.
The second line of each test case contains n integers a_1,a_2, ..., a_n (1 ≤ a_i ≤ 10^9) — the elements of the array.

Output:
For each test case, print "Yes" or "No" depending on whether you can or cannot sort the given array.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long a(-1), b(-1); // 'a' tracks max odd number seen so far, 'b' tracks max even number seen so far
    bool res(true);
    while (n--) {
      long x;
      scanf("%ld", &x);
      if (x % 2) { // If x is odd
        if (a <= x) {
          a = x; // Update maximum odd number seen so far
        } else {
          res = false; // If current odd number is smaller than previous, not sortable
        }
      } else { // If x is even
        if (b <= x) {
          b = x; // Update maximum even number seen so far
        } else {
          res = false; // If current even number is smaller than previous, not sortable
        }
      }
    }
    puts(res ? "Yes" : "No");
  }
}


// https://github.com/VaHiX/codeForces/