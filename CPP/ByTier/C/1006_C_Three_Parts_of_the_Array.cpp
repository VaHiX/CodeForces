// Problem: CF 1006 C - Three Parts of the Array
// https://codeforces.com/contest/1006/problem/C

/*
C. Three Parts of the Array
Algorithms/Techniques: Two Pointers
Time Complexity: O(N)
Space Complexity: O(1)

Given an array, split it into three contiguous subarrays such that 
the sum of the first and third subarrays are equal and maximum possible.
Uses two pointers approach to efficiently find the optimal split points.
*/
#include <cstdio>
#include <iosfwd>

using namespace std;
int N, A[2 << 17];
int main() {
  scanf("%d", &N);
  for (int i = 0; i < N; i++)
    scanf("%d", &A[i]);
  long long L = 0, R = 0;  // L: sum of left part, R: sum of right part
  int r = N;  // Right pointer starting from end
  long long ans = 0;
  for (int l = 0; l < N; l++) {
    L += A[l];  // Extend left part by including A[l]
    while (L > R && r > 0)  // Shrink right part if needed to balance sums
      R += A[--r];  // Move right pointer left and add element to R
    if (r <= l)  // If pointers meet, stop processing
      break;
    if (L == R)  // If sums are equal, update answer
      ans = L;
  }
  printf("%lld\n", ans);
}


// https://github.com/VaHiX/codeForces/