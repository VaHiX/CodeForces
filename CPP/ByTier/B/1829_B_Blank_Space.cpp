// Problem: CF 1829 B - Blank Space
// https://codeforces.com/contest/1829/problem/B

/*
B. Blank Space
time limit per test1 second
memory limit per test256 megabytes

You are given a binary array a of n elements, a binary array is an array consisting only of 0s and 1s.
A blank space is a segment of consecutive elements consisting of only 0s.
Your task is to find the length of the longest blank space.

Algorithm: Linear scan with two pointers approach
Time Complexity: O(n) where n is the length of the array
Space Complexity: O(1) - only using constant extra space

Approach:
- For each test case, iterate through the array
- Track current consecutive zeros (cur) and maximum zeros seen so far (mx)
- When encountering a 1, reset current counter to 0
- When encountering a 0, increment current counter and update maximum if needed
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long cur(0), mx(0); // cur: current consecutive zeros, mx: max consecutive zeros
    for (long p = 0; p < n; p++) {
      int x;
      scanf("%d", &x);
      if (x) { // if current element is 1
        cur = 0; // reset current counter
        continue; // skip to next iteration
      }
      ++cur; // increment current consecutive zeros
      mx = (mx > cur) ? mx : cur; // update maximum if current is larger
    }
    printf("%ld\n", mx);
  }
}


// https://github.com/VaHiX/codeForces/