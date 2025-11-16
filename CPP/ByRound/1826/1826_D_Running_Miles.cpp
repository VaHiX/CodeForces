// Problem: CF 1826 D - Running Miles
// https://codeforces.com/contest/1826/problem/D

/*
Purpose: 
This code solves the problem of finding the maximum value of sum of beauty of three most beautiful sights in a jogging path, minus the distance of the path. 
It uses a technique that precomputes prefix and suffix maximum values with adjusted indices to efficiently compute the result for all valid ranges [l, r].

Algorithms/Techniques:
- Prefix and suffix maximum computation with modified values to account for distance effect
- Sliding window approach with optimized handling for three top beauties

Time Complexity:
O(n) - The algorithm makes a linear traversal of the array for prefix/suffix computation and another for final answer calculation.

Space Complexity:
O(n) - Extra space is used for arrays P and S of size n to store prefix and suffix maxima.
*/

#include <algorithm>
#include <cstdio>
using namespace std;
typedef long long ll;
const int N = 1e5 + 10;
int A[N], P[N], S[N];

void task() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    P[i] = S[i] = -N;  // Initialize prefix and suffix arrays with a small value
    scanf("%d", A + i);  // Read beauty values
  }
  for (int i = 0; i < n; ++i) {
    P[i] = A[i] + i;  // Prefix value: beauty at index i plus its position (to adjust for distance)
    S[n - i - 1] = A[n - i - 1] - (n - i - 1);  // Suffix value: beauty at index (n - i - 1) minus its position
    if (i != 0) {
      P[i] = max(P[i], P[i - 1]);  // Maintain prefix maximum
      S[n - i - 1] = max(S[n - i - 1], S[n - i]);  // Maintain suffix maximum
    }
  }
  int ans = 0;
  for (int i = 1; i < n - 1; ++i) {
    // For each middle point i, combine prefix max (before i), current value A[i], and suffix max (after i)
    ans = max(ans, P[i - 1] + A[i] + S[i + 1]);
  }
  printf("%d\n", ans);
  return;
}

int main() {
  int t;
  scanf("%d", &t);
  for (t; t; --t)
    task();
  return 0;
}


// https://github.com/VaHiX/CodeForces/