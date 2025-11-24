// Problem: CF 1006 C - Three Parts of the Array
// https://codeforces.com/contest/1006/problem/C

/*
Algorithm: Two Pointers Technique
Time Complexity: O(n)
Space Complexity: O(1)

The problem asks to split an array into three parts such that the sum of the first and third parts are equal,
and this sum is maximized. We use a two-pointer approach:
- Left pointer (l) expands the first part.
- Right pointer (r) contracts the third part.
- We maintain running sums for the first and third parts.
- When the sums are equal, we update the answer.
- The middle part is implicitly handled by the indices not covered by l and r.

Approach:
1. Initialize left sum (L) and right sum (R).
2. Use two pointers: l from left and r from right.
3. Expand the left part by adding elements to L.
4. Contract the right part by adding elements to R, but only when L > R.
5. If L == R, update the maximum sum.
6. Continue until pointers cross or meet.
*/

#include <cstdio>
#include <iosfwd>

using namespace std;
int N, A[2 << 17];
int main() {
  scanf("%d", &N);
  for (int i = 0; i < N; i++)
    scanf("%d", &A[i]);
  long long L = 0, R = 0;
  int r = N; // Right pointer initialized to end of array
  long long ans = 0;
  for (int l = 0; l < N; l++) {
    L += A[l]; // Add current element to left sum
    while (L > R && r > 0)
      R += A[--r]; // Move right pointer left and add to right sum
    if (r <= l) // If pointers meet or cross, stop
      break;
    if (L == R) // If sums are equal, update answer
      ans = L;
  }
  printf("%lld\n", ans);
}


// https://github.com/VaHiX/CodeForces/