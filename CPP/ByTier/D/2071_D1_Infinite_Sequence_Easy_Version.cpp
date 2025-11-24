// Problem: CF 2071 D1 - Infinite Sequence (Easy Version)
// https://codeforces.com/contest/2071/problem/D1

/*
D1. Infinite Sequence (Easy Version)
Algorithm/Techniques: Recursive XOR evaluation with prefix precomputed values.
Time Complexity: O(n + t), where n is the size of input array and t is number of test cases.
Space Complexity: O(n), for storing the input array and prefix XOR array.

The sequence is defined such that for m > n:
a[m] = a[1] ^ a[2] ^ ... ^ a[⌊m/2⌋]
This is computed recursively, using a precomputed prefix XOR array to avoid recomputation.
*/

#include <iosfwd>
#include <stdio.h>
using namespace std;
using ll = long long;
const int N = 2e5 + 5;
bool a[N], pre[N]; // a stores the initial sequence, pre stores prefix XOR
int n;

// Function returns value of a[x] using recursion and prefix XOR
bool get(ll x) {
  if (x <= n)
    return a[x]; // If x is within [1, n], directly return from array
  else if (x / 2 <= n)
    return pre[x / 2]; // If half of x is in range, use prefix XOR

  bool res = pre[n]; // Initialize result with full prefix XOR

  if (!((x / 2) & 1)) // If (x/2) is even
    res ^= get(x / 2); // XOR with recursive call to get(x/2)

  if (!(n & 1)) // If n is even
    res ^= get(n + 1); // XOR with get(n+1), this handles base case for recursion

  return res;
}

void _main() {
  ll l, r;
  scanf("%d%lld%lld", &n, &l, &r);
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]), pre[i] = pre[i - 1] ^ a[i]; // Compute prefix XOR
  printf("%d\n", get(l)); // Print the value of a[l]
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--)
    _main();
  return 0;
}


// https://github.com/VaHiX/codeForces/