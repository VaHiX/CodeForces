// Problem: CF 1740 C - Bricks and Bags
// https://codeforces.com/contest/1740/problem/C

/*
Algorithm: 
The problem involves distributing n bricks into 3 bags such that each bag gets at least one brick.
After distribution, Bu Dengklek will take one brick from each bag to minimize the score.
The score is defined as |w1 - w2| + |w2 - w3|, where w1, w2, w3 are the weights of the bricks taken from the three bags respectively.
To maximize the score, Pak Chanek must choose an optimal distribution.

Key Insight:
- Since Bu Dengklek will take the bricks to minimize the score, he will pick the minimum weight brick from each bag.
- The optimal strategy for Pak Chanek is to minimize the effect of choosing the minimum brick from bags while still trying to maximize the overall score.
- After sorting the bricks, we can try different combinations by placing bricks in the middle segment into one bag and the remaining into others.
- For a sorted array of weights, we analyze potential placements that can lead to maximum possible score.

Time Complexity: O(n log n) due to sorting.
Space Complexity: O(n) for the array storage.
*/

#include <algorithm>
#include <iostream>

using namespace std;
int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    int v[n];
    for (int &i : v)
      cin >> i;
    sort(v, v + n); // Sort the bricks by weight
    int ans = 0;
    for (int i = 1; i < n - 1; ++i)
      // Calculate two potential scores for current partition
      // First: max brick from bag 1 + brick from bag 2 - 2 * brick from bag 1 (i-1)
      // Second: 2 * brick from bag 3 (i+1) - brick from bag 2 (i) - min brick from bag 1 (0)
      ans = max(
          {ans, v[n - 1] + v[i] - 2 * v[i - 1], 2 * v[i + 1] - v[i] - v[0]});
    cout << ans << endl;
  }
}


// https://github.com/VaHiX/CodeForces/