// Problem: CF 2084 B - MIN = GCD
// https://codeforces.com/contest/2084/problem/B

/*
B. MIN = GCD
time limit per test1 second
memory limit per test256 megabytes

Algorithm:
The problem asks whether we can rearrange the array such that there exists an index i where the minimum of the first i elements equals the GCD of the remaining elements.

Key observations:
- If such a rearrangement is possible, then for some split point i, min(a[0..i-1]) == gcd(a[i..n-1]).
- The key idea is to find the smallest element in the array. This must be the minimum value in the prefix.
- For the suffix, we consider all elements that are divisible by the minimum element and compute their GCD.
- If this GCD equals 1, then the answer is "Yes".

Approach:
1. Find the minimum element in the array.
2. For all elements divisible by the minimum element, compute their reduced values (divided by minimum).
3. Compute GCD of these reduced values.
4. If the final GCD is 1, output "Yes", otherwise "No".

Time Complexity: O(n log M), where n is the number of elements and M is the maximum value in the array (due to GCD computation).
Space Complexity: O(n) for storing the vector.

*/
#include <cstdio>
#include <vector>
typedef long long ll;

ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    std::vector<ll> v(n);
    ll idx(0), mn(1e18 + 7); // mn is initialized to a large value
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &v[p]);
      if (v[p] < mn) { // Find the index of the minimum element
        mn = v[p];
        idx = p;
      }
    }
    ll g(0); // GCD of reduced elements
    for (ll p = 0; p < n; p++) {
      if (p == idx || (v[p] % mn)) { // Skip the minimum element and non-divisible ones
        continue;
      }
      g = gcd(g, v[p] / mn); // Reduce and compute GCD
    }
    puts(g == 1 ? "Yes" : "No"); // Output based on whether GCD of reductions is 1
  }
}


// https://github.com/VaHiX/codeForces/