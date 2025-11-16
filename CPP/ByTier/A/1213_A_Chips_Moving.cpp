// Problem: CF 1213 A - Chips Moving
// https://codeforces.com/contest/1213/problem/A

/*
A. Chips Moving
Algorithms/Techniques: Greedy, Bit manipulation
Time complexity: O(n)
Space complexity: O(1)

The problem asks to move all chips to the same position with minimal cost.
Since moving by 2 units costs nothing, we only pay for moves of 1 unit.
Therefore, the key insight is that chips at even positions can be moved to any even position for free,
and chips at odd positions can be moved to any odd position for free.
We only need to pay for moving all chips to either an even or odd coordinate.

So we count how many chips are at even positions (s) and how many at odd positions (n - s).
The answer is the minimum of these two counts.

*/

#include <iostream>
#include <algorithm>

using namespace std;
int n, s, x, i;
int main() {
  for (cin >> n; i++ < n; s += x & 1)  // Read chips and count how many are at odd positions
    cin >> x;
  cout << min(s, n - s);  // Return minimum of odd or even chip counts
}


// https://github.com/VaHiX/codeForces/