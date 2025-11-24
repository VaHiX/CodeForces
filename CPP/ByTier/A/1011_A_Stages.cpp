// Problem: CF 1011 A - Stages
// https://codeforces.com/contest/1011/problem/A

/*
 * Problem: Build a rocket with exactly k stages from n available stages,
 * such that the total weight is minimized and each consecutive stage 
 * differs by at least 2 positions in the alphabet (e.g., after 'c' we can't go to 'a', 'b', or 'c').
 * 
 * Algorithm:
 * - Sort the available stages in ascending order.
 * - Greedily select stages from left to right, ensuring that each selected stage
 *   is at least 2 positions apart (in alphabetical order) from the previously selected one.
 * - Stop when k stages are selected or it's impossible.
 *
 * Time Complexity: O(n log n) due to sorting, where n <= 50.
 * Space Complexity: O(1) if we don't count input size, otherwise O(n).
 */

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

int main() {
  int n, m;           // n = number of stages, m = number of stages to select
  string s;
  cin >> n >> m;
  cin >> s;
  
  sort(s.begin(), s.end());  // Sort stages alphabetically
  
  int l = -1, p = 0;         // l = last selected stage weight, p = total weight
  for (int i = 0; m && i < n; i++)
    if (s[i] >= l + 2)       // Check if current stage is valid (at least 2 positions after previous)
      l = s[i], p += s[i] - 'a' + 1, m -= 1;  // Update last stage, add weight, decrement count
  
  if (m)                     // If we couldn't select enough stages
    cout << -1;
  else
    cout << p;
}


// https://github.com/VaHiX/codeForces/