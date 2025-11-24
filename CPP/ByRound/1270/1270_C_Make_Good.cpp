// Problem: CF 1270 C - Make Good
// https://codeforces.com/contest/1270/problem/C

/*
Code Purpose:
This code solves the problem of making an array "good" by appending at most 3 elements.
An array is considered good if the sum of its elements equals twice the XOR of its elements.
The approach is based on the observation that adding two specific elements (the current XOR and the sum plus XOR)
can always make the array good, leveraging mathematical properties of XOR and addition.

Algorithms/Techniques:
- Prefix sum and XOR computation
- Mathematical property: For any array, appending b and (a + b) where b is the current XOR and a is the current sum,
  results in a good array.

Time Complexity: O(n) per test case, where n is the size of the array.
Space Complexity: O(1), as only a constant amount of extra space is used.

*/
#include <stdio.h>
#include <iosfwd>

using namespace std;
#define ll long long
int T, n;
ll a, b;
int main() {
  scanf("%d", &T);
  while (T--) {
    scanf("%d", &n), a = b = 0;
    for (int i = 1, x; i <= n; ++i)
      scanf("%d", &x), a += x, b ^= x;
    printf("2\n%lld %lld\n", b, a + b);  // Append b and (a + b) to make the array good
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/