// Problem: CF 1520 E - Arranging The Sheep
// https://codeforces.com/contest/1520/problem/E

/*
E. Arranging The Sheep
Purpose: Given a string of empty spaces '.' and sheep '*', find the minimum number of moves to align all sheep in a contiguous segment.
Algorithm: 
  - Locate all positions of sheep '*'
  - Find the median position among these sheep
  - Calculate total distance each sheep needs to move to reach their target positions,
    where targets are aligned around the median
Time Complexity: O(n) per test case, where n is the length of the string
Space Complexity: O(k) where k is the number of sheep (for storing positions)
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
    long n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    std::vector<ll> v; // Store positions of all sheep
    for (ll p = 0; p < s.size(); p++) {
      if (s[p] == '*') {
        v.push_back(p);
      }
    }
    if (v.size() <= 0) { // No sheep to move
      std::cout << "0" << std::endl;
      continue;
    }
    ll middle = v.size() / 2; // Find median position
    ll medpos = v[middle]; // Median position of sheep
    ll total(0);
    for (ll p = 0; p < v.size(); p++) {
      ll target = medpos + (p - middle); // Target position based on median
      ll dist = v[p] - target; // Distance to move
      if (dist < 0) {
        dist = -dist;
      }
      total += dist;
    }
    std::cout << total << std::endl;
  }
}


// https://github.com/VaHiX/codeForces/