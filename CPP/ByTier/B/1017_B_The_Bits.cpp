// Problem: CF 1017 B - The Bits
// https://codeforces.com/contest/1017/problem/B

/*
B. The Bits
Algorithms/Techniques: Counting, bit manipulation

Time Complexity: O(n)
Space Complexity: O(1)

Given two binary strings a and b of length n, we need to count the number of ways to swap two bits in a 
such that the bitwise OR of a and b changes. The key insight is to track the combinations of bits in a and b 
that lead to OR changes when swapped.

We classify pairs (a[i], b[i]) into four categories:
- cnt[0][0]: a[i] = 0, b[i] = 0
- cnt[1][0]: a[i] = 1, b[i] = 0
- cnt[0][1]: a[i] = 0, b[i] = 1
- cnt[1][1]: a[i] = 1, b[i] = 1

For each pair (a[i], b[i]) to affect the OR result when swapped:
  - If we swap two bits in a and it changes the OR, then we are looking for such swaps that lead different OR.

We only need to count swaps where:
- One bit is 0 and other is 1 in a, which when swapped with a 0 or 1 from b leads to a change in OR.
The formula considers combinations such that after swapping, the OR of a and b changes.

The total number of valid swaps is computed using combinatorics based on how many times
such pairs occur in the strings.
*/
#include <stdio.h>
#include <iostream>

#define ll long long
#define db double
#define N 100100
using namespace std;
ll n, m, ans, sum, ca, cb, cnt[2][2];
char a[N], b[N];
int main() {
  int i, j;
  cin >> n;
  scanf("%s%s", a + 1, b + 1);
  for (i = 1; i <= n; i++) {
    cnt[a[i] - '0'][b[i] - '0']++; // Count occurrences of each (a[i], b[i]) pair
  }
  cout << cnt[0][0] * (cnt[1][0] + cnt[1][1]) + cnt[1][0] * (cnt[0][1]); // Compute result based on combinations
}


// https://github.com/VaHiX/codeForces/