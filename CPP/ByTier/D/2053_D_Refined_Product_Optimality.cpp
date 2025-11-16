// Problem: CF 2053 D - Refined Product Optimality
// https://codeforces.com/contest/2053/problem/D

/*
Purpose: Solve the problem of finding the maximum product P = ∏(min(a[i], b[i])) after optimally rearranging array b, 
         and updating the result after q modifications to either array a or b.

Algorithms/Techniques:
- Greedy strategy with sorting: To maximize the product, we sort both arrays and pair elements optimally.
- Binary search (upper_bound): To find the correct element in sorted array for updating.
- Modular exponentiation (ksm): For modular inverse using Fermat's little theorem.
- Efficient I/O: Using scanf/printf instead of cin/cout for speed.

Time Complexity: O(n log n + q * log n)
Space Complexity: O(n)

*/
#include <algorithm>
#include <stdio.h>
using namespace std;

const int p = 998244353; // Modulo value
typedef long long ll;

int a[200002], b[200002], c[200002], d[200002]; // Arrays a, b (original), and c, d (sorted copies)

// Fast modular exponentiation function to compute x^y mod p
ll ksm(ll x, ll y) {
  ll ans = 1;
  while (y) {
    if (y & 1)
      ans = ans * x % p; // Multiply result by x if y is odd
    x = x * x % p;       // Square x
    y >>= 1;             // Halve y
  }
  return ans;
}

void solve(int n, int q) {
  // Read input arrays a and b and store copies in c and d
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]), c[i] = a[i];
  for (int i = 1; i <= n; i++)
    scanf("%d", &b[i]), d[i] = b[i];

  // Sort copies for greedy pairing
  sort(c + 1, c + n + 1);
  sort(d + 1, d + n + 1);

  // Compute initial answer using sorted arrays
  ll ans = 1;
  for (int i = 1; i <= n; i++)
    ans = ans * min(c[i], d[i]) % p;
  printf("%lld ", ans);

  // Process each query
  while (q--) {
    int o, x;
    scanf("%d%d", &o, &x); // Read operation (1 for a, 2 for b) and index x

    if (o == 1) {
      // Update array a[x] and corresponding position in c
      int i = upper_bound(c + 1, c + n + 1, a[x]) - c - 1; 
      // Find where a[x] would be placed in sorted array c
      if (c[i] < d[i]) {
        // If changing a[x] makes a better pairing, update the result
        ans = ans * ksm(c[i], p - 2) % p * (c[i] + 1) % p; 
        // Revert previous contribution, add new one modulo inverse
      }
      c[i]++;
      a[x]++;
    } else {
      // Update array b[x] and corresponding position in d
      int i = upper_bound(d + 1, d + n + 1, b[x]) - d - 1; 
      // Find where b[x] would be placed in sorted array d
      if (d[i] < c[i]) {
        // If changing b[x] makes a better pairing, update the result
        ans = ans * ksm(d[i], p - 2) % p * (d[i] + 1) % p; 
        // Revert previous contribution, add new one modulo inverse
      }
      d[i]++;
      b[x]++;
    }

    printf("%lld ", ans); // Output current answer
  }
}

int main() {
  int _;
  scanf("%d", &_);
  while (_--) {
    int n, q;
    scanf("%d%d", &n, &q);
    solve(n, q);
    putchar('\n');
  }
}


// https://github.com/VaHiX/CodeForces/