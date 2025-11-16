// Problem: CF 1884 B - Haunted House
// https://codeforces.com/contest/1884/problem/B

/*
B. Haunted House
Algorithms/Techniques: Simulation, Prefix Sum
Time Complexity: O(n) per test case
Space Complexity: O(n) for the vector storing counts

The problem asks to find the minimum number of adjacent swaps required to make a binary number divisible by 2^i for each i from 1 to n.
For a number to be divisible by 2^i, its last i bits must form a number divisible by 2^i, which means the last i bits must all be zero.
So we need to move all the '1's in the last i positions to the right so they end up at the end (as trailing zeros).
This can be done by counting how many 1s are there in each prefix of the string and using prefix sums for efficient calculation.
*/

#include <iostream>
#include <vector>
#include <string>

typedef long long ll;
int main() {
  std::ios_base::sync_with_stdio(false);
  ll t;
  std::cin >> t;
  while (t--) {
    ll n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    std::vector<ll> v; // Stores count of '1's from right to left
    ll cur(0);
    for (ll p = n - 1; p >= 0; p--) {
      if (s[p] == '1') {
        ++cur;
      } else {
        v.push_back(cur); // Push current count of 1s seen so far from the right
      }
    }
    // Compute prefix sum to get total number of operations needed for each i
    for (ll p = 1; p < v.size(); p++) {
      v[p] += v[p - 1];
    }
    // Output result for each i from 1 to n
    for (ll p = 0; p < n; p++) {
      std::cout << (p < v.size() ? v[p] : -1) << " ";
    }
    std::cout << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/