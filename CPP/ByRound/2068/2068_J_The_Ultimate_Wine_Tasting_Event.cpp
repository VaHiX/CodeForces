// Problem: CF 2068 J - The Ultimate Wine Tasting Event
// https://codeforces.com/contest/2068/problem/J

/*
 * Problem: J. The Ultimate Wine Tasting Event
 * Purpose: Determine if it's possible to split 2n bottles (n W's and n R's) into two groups of n each,
 *          then swap the i-th bottle from each group, such that all W's end up in the first n positions.
 *
 * Algorithm:
 *   - Count total white wines 'W' in the string.
 *   - For a valid split to exist:
 *     1. Total number of W's must be even (so we can split them evenly into two groups).
 *     2. The first half of W's must appear in the first n positions of the string,
 *        and the second half must appear in the last n positions.
 *   - Time Complexity: O(n) per test case — linear scan through the string.
 *   - Space Complexity: O(1) — only using a constant amount of extra space.
 */

#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

int t, n, k, l, h;
string c;

void C() {
  cin >> n >> c;
  k = count(c.begin(), c.begin() + n, 'W'); // Count W's in first half of the string
  if (k % 2 == 0 && 
      count(c.begin(), c.begin() + k / 2, 'R') == 0 && // No R's in first k/2 positions of first half
      count(c.end() - k / 2, c.end(), 'W') == 0)     // No W's in last k/2 positions of second half
    cout << "YES\n";
  else
    cout << "NO\n";
}

int main() {
  cin >> t;
  while (t--)
    C();
  return 0;
}


// https://github.com/VaHiX/codeForces/