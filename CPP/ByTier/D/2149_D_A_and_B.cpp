// Problem: CF 2149 D - A and B
// https://codeforces.com/contest/2149/problem/D

/*
Problem: Minimize swaps to make all characters of one type form a single continuous block.
Algorithms/Techniques: Two-pointer technique, greedy approach, median minimization.
Time Complexity: O(n) per test case, where n is the length of the string.
Space Complexity: O(n) for storing indices of characters.

Approach:
- For each character type ('a' and 'b'), find all positions where that character occurs.
- Compute the minimum number of swaps needed to gather all occurrences of a character into a continuous block.
- To compute this, we use the fact that placing characters optimally is achieved by aligning them around the median position.
- This minimizes the total distance that each character needs to be moved.
*/

#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;
typedef long long ll;
string s;
int n;
vector<int> ve, ve1;

// Function to calculate minimum swaps needed to gather all 'tar' characters into a continuous block
ll make(string s, char tar) {
  ve.clear(); // Clear previous indices
  ve1.clear(); // Clear previous adjusted indices
  for (int i = 0; i < n; i++) {
    if (s[i] == tar)
      ve.push_back(i); // Store indices of target character
  }
  int m = ve.size();
  if (m == 0)
    return 0; // No target characters present

  // Calculate adjusted positions based on index shift to align optimally
  for (int i = 0; i < m; i++)
    ve1.push_back(ve[i] - i);

  int mid = ve1[m / 2]; // Find median of adjusted indices
  long long r = 0;
  for (int i = 0; i < m; i++) {
    r += abs(mid - ve[i]); // Sum up total moves needed
    mid++;
  }
  return r;
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    cin >> n;
    cin >> s;
    ll z1 = make(s, 'a'); // Minimum swaps for all 'a's to form block
    ll z2 = make(s, 'b'); // Minimum swaps for all 'b's to form block
    cout << min(z1, z2) << endl; // Output minimum of both options
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/