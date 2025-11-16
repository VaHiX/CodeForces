// Problem: CF 1843 B - Long Long
// https://codeforces.com/contest/1843/problem/B

/*
B. Long Long

Purpose:
This code solves a problem where we are given an array of integers and can perform operations to flip the signs of subarrays.
The goal is to find the maximum possible sum of the array after any number of such operations and the minimum number of operations needed to achieve that sum.

Algorithm:
- For each test case, iterate through the array and greedily count how many "flips" (operation segments) are needed.
- A flip segment begins when we encounter a negative number after having seen positive numbers (or at start).
- To maximize sum: flip all negative subarrays that do not involve zero, essentially making them positive.
- Count those flip segments to determine minimum operations.

Time Complexity: O(n), where n is the size of the array. Each element is visited once per test case.
Space Complexity: O(1), only constant extra space is used.

Input Format:
First line contains number of test cases t.
Each test case starts with n (size of array), followed by n integers.

Output Format:
For each test case, print two integers:
- Maximum possible sum after operations
- Minimum number of operations required to get that sum
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    bool pos(true);         // Tracks if the current segment is positive (i.e., we're in a positive sequence)
    long cnt(0);            // Counts number of flip operations needed
    long long total(0);     // Stores the maximum sum possible
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (x > 0) {
        pos = true;         // Marking that we're now in a positive section
        total += x;         // Add the value to our running sum (as it's positive)
      } else if (x < 0) {
        if (pos) {
          ++cnt;            // Start of a new negative segment, so increment operation count
          pos = false;      // Mark that now we're in a negative section
        }
        total -= x;         // Subtracting the negative value adds its absolute value to total
      }
    }
    printf("%lld %ld\n", total, cnt);
  }
}


// https://github.com/VaHiX/codeForces/