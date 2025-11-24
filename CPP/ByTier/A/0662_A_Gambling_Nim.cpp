// Problem: CF 662 A - Gambling Nim
// https://codeforces.com/contest/662/problem/A

/*
 * Problem: Gambling Nim
 * 
 * Purpose: 
 *   Calculate the probability that Petya (first player) wins in the "Gambling Nim" game.
 *   In this variant, each card has two values, and one side is chosen randomly per card.
 *   The resulting sequence of values forms piles of stones for the Nim game.
 *   Both players play optimally.
 * 
 * Algorithm:
 *   - Uses bit manipulation and Grundy numbers (Nimbers) concepts.
 *   - For each card, we compute the XOR difference between the two sides.
 *   - Maintains a set of distinct XOR differences (stored in vector b).
 *   - Reduces the set using the process similar to Gaussian elimination on binary vectors.
 *   - Finally, determine whether the total XOR of all "b" values is zero.
 *   - If it's not zero, Petya wins with probability 1.
 *   - If it's zero and the size of reduced basis is less than 63, it's 50% probability.
 *   - Special case handling for full basis (63 bits used).
 * 
 * Time Complexity: O(n * log(max_value)) where n is number of cards
 * Space Complexity: O(n) for storing the reduced basis vector b
 * 
 * Techniques:
 *   - XOR-based operations
 *   - Gaussian elimination on binary vectors
 *   - Bit manipulation
 *   - Grundy number / Nimber calculation
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
#define ll unsigned long long
vector<ll> b; // Stores the reduced basis of differences
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int n;
  cin >> n;
  ll c = 0; // Tracks the cumulative XOR of all chosen sides
  while (n--) {
    ll a, t;
    cin >> a >> t;
    a ^= t;         // Compute difference between sides of the card
    c ^= t;         // Update total XOR of chosen sides (assumes t is the chosen side)
    for (auto &x : b)
      a = min(a, x ^ a); // Reduce a using existing basis elements
    if (a) // If after reduction a is not zero, it's a new independent element
      b.push_back(a);
  }
  for (auto &x : b)
    c = min(c, c ^ x); // Reduce the final c using the basis
  if (c) { // If final c is non-zero, Petya wins with probability 1
    cout << "1/1";
    return 0;
  }
  n = b.size(); // Size of the reduced basis
  if (n == 63)  // Special case: all 63 bits are used
    cout << "223372036854775807/223372036854775808";
  else          // General case: probability depends on number of basis elements
    cout << ((1LL << n) - 1) << "/" << (1LL << n);
}


// https://github.com/VaHiX/CodeForces/