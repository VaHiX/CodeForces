// Problem: CF 2132 C2 - The Cunning Seller (hard version)
// https://codeforces.com/contest/2132/problem/C2

/*
C2. The Cunning Seller (hard version)

Algorithms/Techniques: Greedy, Number Base Conversion, Bit Manipulation

Time Complexity: O(log n) per test case
Space Complexity: O(1)

The problem involves finding the minimum cost to buy exactly `n` watermelons using at most `k` deals.
Each deal allows buying 3^x watermelons for 3^(x+1) + x*3^(x-1) coins. 

The key insight is that we can represent `n` in base 3, and the minimum number of deals needed
is the sum of digits in base 3 representation of `n`. If this exceeds `k`, it's impossible.

We use a greedy approach to minimize cost:
- Convert n to base 3 to determine minimal deals required.
- If required deals <= k, we proceed with optimization.
- Otherwise, return -1.
- Optimize by converting some 1s and 2s to higher base 3 digits where possible, 
  effectively reducing the number of deals at a cost.

*/

#include <algorithm>
#include <iostream>

using namespace std;
using ll = long long;

// Function to calculate sum of digits in base 3 representation of n
ll g(ll n) {
  ll s = 0;
  while (n > 0) {
    s += n % 3; // Add units digit in base 3
    n /= 3;     // Move to next higher place value
  }
  return s;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int t;
  cin >> t;
  while (t--) {
    ll n, k;
    cin >> n >> k;
    
    ll mn = g(n); // Minimum number of deals needed
    
    if (k < mn) { // If we don't have enough deals
      cout << -1 << "\n";
      continue;
    }
    
    ll need = 0; // Number of "extra" moves we want to do
    
    // If n > k, we must reduce number of required deals by optimizing base 3 digits
    if (n > k)
      need = (n - k + 1) / 2;
    
    ll p = 0;      // Extra cost adjustment 
    ll cur = n;    // Current count of watermelons processed
    ll w = 1;      // Weight for current base (1, 3, 9... etc)

    // Greedily process each digit in base 3 from least significant to most
    while (need > 0 && cur >= 3) {
      ll c = cur / 3;         // Quotient when dividing by 3
      ll take = min(need, c); // Take minimum of what we need and available 
      
      p += take * w;          // Add to extra cost based on weight 
      need -= take;           // Decrease remaining needed adjustments
      cur = c;                // Move to next digit
      w *= 3;                 // Increase base for next iteration
    }

    // Base cost is 3*n and we add the optimization adjustment p
    cout << 3LL * n + p << "\n";
  }
}


// https://github.com/VaHiX/codeForces/