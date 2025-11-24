// Problem: CF 1514 C - Product 1 Modulo N
// https://codeforces.com/contest/1514/problem/C

/*
C. Product 1 Modulo N
Purpose: Find the longest subsequence of [1, 2, ..., n-1] whose product is congruent to 1 modulo n.
Algorithm: 
- For each number from 1 to n-1, check if it's coprime with n (gcd(p, n) == 1)
- Include such numbers in the subsequence and compute their product modulo n
- If resulting product > 1, remove that product from the list to make the final product = 1
- Time complexity: O(n log n) due to gcd computation and loop over numbers
- Space complexity: O(n) for the boolean vector and storage of elements
*/

#include <cstdio>
#include <vector>
typedef long long ll;

// Computes greatest common divisor using Euclidean algorithm
ll gcd(ll a, ll b) { return (b == 0) ? a : gcd(b, a % b); }

int main() {
  ll n;
  scanf("%lld", &n);
  ll prod(1), cnt(0);
  std::vector<bool> a(n, 1); // Mark which numbers are included in subsequence
  
  // Loop through all numbers from 1 to n-1
  for (ll p = 1; p < n; p++) {
    ll x = gcd(p, n); // Check if p and n are coprime
    if (x > 1) {
      a[p] = 0; // Not coprime -> exclude from subsequence
    } else {
      ++cnt; // Increment count of valid elements
      prod *= p; // Multiply to current product
      prod %= n; // Keep product modulo n to prevent overflow
    }
  }
  
  // If final product > 1, remove one element whose value equals the product
  if (prod > 1) {
    --cnt; // Decrement count since we're removing an element
    a[prod] = 0; // Mark that element as excluded
  }
  
  printf("%lld\n", cnt); // Print length of subsequence
  
  // Output all remaining elements in increasing order
  for (ll p = 1; p < n; p++) {
    if (a[p] > 0) {
      printf("%lld ", p);
    }
  }
  puts(""); // New line at end
}


// https://github.com/VaHiX/codeForces/