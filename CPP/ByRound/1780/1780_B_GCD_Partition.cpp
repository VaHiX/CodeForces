// Problem: CF 1780 B - GCD Partition
// https://codeforces.com/contest/1780/problem/B

/*
B. GCD Partition
Algorithms/Techniques: Prefix sums, GCD computation, brute-force over k partitions
Time Complexity: O(n * sqrt(max_a) + sum_n) where max_a is the maximum element in array a
Space Complexity: O(n)

The problem asks to split an array into k > 1 contiguous subarrays such that 
the GCD of their sums is maximized. We use prefix and suffix sums to quickly compute 
subarray sums. For each valid k (from 2 to n), we try all possible partitions and find 
the maximum GCD of the resulting sums.
*/
#include <cstdio>
#include <vector>
typedef long long ll;

// Function to compute greatest common divisor using Euclidean algorithm
ll gcd(ll a, ll b) { return (b == 0) ? a : gcd(b, a % b); }

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    std::vector<ll> a(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &a[p]); // Read array elements
    }
    
    // Compute prefix sums: left[p] = sum of elements from index 0 to p
    std::vector<ll> left(n);
    for (ll p = 0; p < n; p++) {
      left[p] = a[p] + (p > 0 ? left[p - 1] : 0);
    }
    
    // Compute suffix sums: right[p] = sum of elements from index p to n-1
    std::vector<ll> right(n);
    for (ll p = n - 1; p >= 0; p--) {
      right[p] = a[p] + (p + 1 < n ? right[p + 1] : 0);
    }
    
    ll res(0); // Variable to store the maximum GCD found
    
    // Try each possible split point starting from index 1
    for (ll p = 1; p < n; p++) {
      // Compute GCD of prefix sum up to p-1 and suffix sum from p onwards
      ll g = gcd(left[p - 1], right[p]);
      res = (res > g) ? res : g; // Update result if current GCD is larger
    }
    
    printf("%lld\n", res); // Print the maximum possible score
  }
}


// https://github.com/VaHiX/codeForces/