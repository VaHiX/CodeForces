// Problem: CF 2132 C1 - The Cunning Seller (easy version)
// https://codeforces.com/contest/2132/problem/C1

/*
C1. The Cunning Seller (easy version)

Algorithms/Techniques: Dynamic Programming with Base-3 Number System

Time Complexity: O(log n) per test case
Space Complexity: O(1)

The problem involves finding the minimum cost to buy exactly 'n' watermelons using deals.
Each deal allows buying 3^x watermelons for 3^(x+1) + x * 3^(x-1) coins.
This solution uses a greedy approach in base-3 representation of the number n,
where each digit determines how many deals of that power to use.

For example:
Deal A (x=0): 1 watermelon → 3 coins
Deal B (x=1): 3 watermelons → 10 coins
Deal C (x=2): 9 watermelons → 36 coins
And so on...

The idea is to express n in base 3 and calculate the cost by considering
each digit's contribution as a number of complete deals or a combination of
deals needed to make up that part.
*/

#include <iostream>

using namespace std;
#define int long long
int T;
signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  cin >> T;
  while (T--) {
    int n, ans = 0, i = 0, s = 1;
    cin >> n;
    while (n) {
      // For each base-3 digit, calculate cost based on the number of deals needed
      ans += n % 3 * (s * 3 + s / 3 * i);  // Cost calculation for current digit
      n /= 3;  // Move to next digit in base-3 representation
      i++;     // Increment deal index
      s *= 3;  // Update power of 3 for next iteration
    }
    cout << ans << "\n";
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/