// Problem: CF 1143 B - Nirvana
// https://codeforces.com/contest/1143/problem/B

/*
B. Nirvana
Time Complexity: O(log n) - We iterate through each digit position of n
Space Complexity: O(1) - Only using a constant amount of extra space

Algorithms/Techniques: 
- Digit DP (Dynamic Programming) approach with optimization
- For each digit position, we try to decrease the digit by 1 and fill the rest with 9's
  to maximize product, while keeping the number <= n

*/
#include <cstdio>
typedef long long ll;

// Function to calculate product of all digits in a number
ll digitproduct(ll x) {
  if (x <= 0) {
    return 0;
  }
  ll prod(1); // Initialize product to 1
  while (x > 0) {
    prod *= (x % 10); // Multiply by last digit
    x /= 10; // Remove last digit
  }
  return prod;
}

int main() {
  ll n;
  scanf("%lld", &n);
  ll res = digitproduct(n); // Start with product of all digits in n
  for (ll p = 1; p <= n; p *= 10) { // Iterate through each digit position
    ll cur = (n / p) * p; // Get number with zeros from current position onwards
    ll check = digitproduct(cur - 1); // Check product of digits in cur-1 
    res = (res > check) ? res : check; // Keep maximum of current and new product
  }
  printf("%lld\n", res);
  return 0;
}


// https://github.com/VaHiX/codeForces/