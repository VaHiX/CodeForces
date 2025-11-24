// Problem: CF 483 B - Friends and Presents
// https://codeforces.com/contest/483/problem/B

/*
Algorithm: Binary Search on Answer
Approach:
We need to find the smallest number 'v' such that we can select 'cnt1' numbers for the first friend and 'cnt2' numbers for the second friend from the set {1, 2, ..., v} such that:
1. No number is shared between the two friends.
2. First friend does not like numbers divisible by x.
3. Second friend does not like numbers divisible by y.

To determine if a value 'v' works, we calculate:
- Numbers from 1 to v not divisible by x: v - v/x (first friend's available count)
- Numbers from 1 to v not divisible by y: v - v/y (second friend's available count)
- Numbers from 1 to v divisible by both x and y (i.e., by lcm(x, y)): v / (x * y)

Using inclusion-exclusion principle, total numbers not divisible by x or y:
v - v/x - v/y + v/(x*y) = v * (1 - 1/x - 1/y + 1/(x*y)) = v * (y-1) * (x-1) / (x * y)
But we directly use: v - v/x - v/y + v/(x*y)

We try all possible values of v via binary search to find minimum v where:
- Count of numbers not divisible by x >= cnt1
- Count of numbers not divisible by y >= cnt2
- Count of numbers not divisible by either x or y >= cnt1 + cnt2

Time Complexity: O(log(2e9)) = O(30) ≈ O(1)
Space Complexity: O(1)
*/

#include <cstdio>
int main() {
  long cnt1, cnt2, x, y;
  scanf("%ld %ld %ld %ld\n", &cnt1, &cnt2, &x, &y);
  long long left(0), mid(0), right(2e9);
  while (left < right) {
    mid = (left + right) / 2;
    // Check if 'mid' is sufficient to give 'cnt1' numbers to friend 1
    // and 'cnt2' numbers to friend 2, with no overlap
    if ((mid - mid / x >= cnt1) && (mid - mid / y >= cnt2) &&
        (mid - mid / (x * y) >= cnt1 + cnt2)) {
      right = mid; // If true, try smaller v
    } else {
      left = mid + 1; // If false, try larger v
    }
  }
  printf("%ld\n", right);
  return 0;
}


// https://github.com/VaHiX/CodeForces/