// Problem: CF 1762 A - Divide and Conquer
// https://codeforces.com/contest/1762/problem/A

/*
 * Problem: Make Array Good with Minimum Operations
 *
 * Algorithm/Techniques:
 *   - Bit manipulation and greedy approach
 *   - For each number, compute how many times we need to divide by 2 until it becomes odd
 *   - If sum of original array is even, no operations needed
 *   - Otherwise, find the minimum number of operations required for any element to make total sum even
 *
 * Time Complexity:
 *   - O(n * log(max(a_i))) where n is the size of array and max(a_i) is the maximum element in array
 *   - For each element, we perform at most log(a_i) divisions
 *
 * Space Complexity:
 *   - O(1) - only using a constant amount of extra space
 */

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long s(0), mn(1000); // s: sum of odd numbers, mn: minimum number of divisions needed
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      s += (x % 2); // count number of odd elements in the array
      if (x % 2) {   // if x is odd, count how many times we need to divide by 2 until it becomes even
        long cnt(0);
        while (x % 2) { // keep dividing by 2 while x is odd
          x /= 2;
          ++cnt; // count how many times we divided
        }
        mn = (mn < cnt) ? mn : cnt; // update minimum divisions needed for odd numbers
      } else {       // if x is even, count how many trailing zeros in binary representation
        long cnt(0);
        while (x % 2 == 0) { // keep dividing by 2 while x is even
          x /= 2;
          ++cnt; // count how many times we divided
        }
        mn = (mn < cnt) ? mn : cnt; // update minimum divisions needed for even numbers
      }
    }
    printf("%ld\n", s % 2 ? mn : 0); // if sum is odd, return minimum operations to make it even; otherwise 0
  }
}


// https://github.com/VaHiX/codeForces/