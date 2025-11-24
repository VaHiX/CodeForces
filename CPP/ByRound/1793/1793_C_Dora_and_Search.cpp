// Problem: CF 1793 C - Dora and Search
// https://codeforces.com/contest/1793/problem/C

/*
C. Dora and Search
time limit per test1 second
memory limit per test256 megabytes

Algorithm: Two-pointer technique with greedy approach.
Approach:
- Use two pointers (left and right) starting from both ends of array.
- Maintain mn (minimum) and mx (maximum) values that should be present in current subsegment.
- At each step, try to "shrink" the window from either end if elements match mn or mx.
- If an element matches mn on left side or mx on right side, remove it from consideration by moving pointer.
- If no valid shrinkage is possible, break the loop.
- If after shrinking left < right, we have a valid subsegment [left+1, right+1] (1-indexed), else output -1.

Time Complexity: O(n) amortized per test case due to two pointers visiting each element at most twice.
Space Complexity: O(n) for storing the input permutation vector.

Input:
Each test consists of multiple test cases. The first line contains a single integer
t (1≤t≤10^4) — the number of test cases. Description of the test cases follows.
For each test case, the first line contains one integer
n (1≤n≤2⋅10^5) — the length of permutation.
The second line contains
n distinct integers a1,a2,…,an (1≤ai≤n) — the elements of permutation.

Output:
For each test case, output -1 if the desired subsegment does not exist.
Otherwise, output two indexes l,r such that [al,al+1,…,ar] satisfies all conditions.
If there are several solutions, then output any of them.
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    long left(0), right(n - 1), mn(1), mx(n); // Initialize pointers and min/max tracker
    while (left < right) {
      if (a[left] == mn) {        // If left element equals current minimum, move left pointer
        ++left;
        ++mn;                     // Increase expected minimum
      } else if (a[right] == mn) { // If right element equals current minimum, move right pointer
        --right;
        ++mn;                     // Increase expected minimum
      } else if (a[left] == mx) {  // If left element equals current maximum, move left pointer
        ++left;
        --mx;                     // Decrease expected maximum
      } else if (a[right] == mx) { // If right element equals current maximum, move right pointer
        --right;
        --mx;                     // Decrease expected maximum
      } else {
        break;                    // No valid shrinkage possible, exit loop
      }
    }
    if (left < right) {
      printf("%ld %ld\n", left + 1, right + 1); // Output 1-indexed indices
    } else {
      puts("-1");                 // No valid subsegment found
    }
  }
}


// https://github.com/VaHiX/codeForces/