// Problem: CF 1451 D - Circle Game
// https://codeforces.com/contest/1451/problem/D

/*
D. Circle Game
Algorithm: Mathematical game theory analysis using geometric constraints and optimal play simulation.

The problem models a turn-based game on a 2D grid where two players (Ashish and Utkarsh) take turns increasing either x or y coordinate by exactly k,
while maintaining the Euclidean distance from origin ≤ d. The player who cannot make a move loses.

Key Idea:
- The number of valid moves is bounded by the circle radius d and step size k.
- We simulate the game using an optimized formula derived from geometric and arithmetic progressions.
- A key insight is that we can bound the maximum number of moves via approximation: 
  m ≈ (d/k) / sqrt(2), which leads to computing sum of squares formula involving m.

Time Complexity: O(t), where t is number of test cases. Each case is computed in constant time.
Space Complexity: O(1), only using a few variables for computation and output.

*/
#include <iostream>
typedef long long ll;
int main() {
  std::ios_base::sync_with_stdio(false);
  ll t;
  std::cin >> t;
  const double invsqrtwo = 0.7071067812; // 1/sqrt(2), used to approximate m
  while (t--) {
    ll d, k;
    std::cin >> d >> k;
    ll m = invsqrtwo * d / k; // estimate number of moves using geometric approximation
    bool res = (k * k * (2 * m * (m + 1) + 1) <= d * d); // check if total distance constraint holds
    std::cout << (res ? "Ashish" : "Utkarsh") << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/