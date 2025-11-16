// Problem: CF 1019 A - Elections
// https://codeforces.com/contest/1019/problem/A

/*
 * Problem: Elections
 * Algorithm: Greedy + Priority Queue + Sorting
 * Time Complexity: O(n log n + m * k * log k) where k is average group size
 * Space Complexity: O(n + m^2)
 *
 * Description:
 * Given n voters and m parties, each voter has a preferred party and cost to change vote.
 * Party 1 (United Party) wants to win by getting more votes than any other party.
 * We use greedy approach to minimize cost:
 * - Keep existing supporters of party 1
 * - For other parties, sort their voters by cost (ascending)
 * - Use priority queue to track cheapest voters to buy for each possible win scenario
 * - Try all possible numbers of additional votes needed for party 1 to win
 */

#include <stddef.h>
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
vector<int> v1[3001], v2[3001];
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  long long int i, j, n, m, p, c, sum = 0, k = 0, l, total, ans = 1e16;
  priority_queue<long long int> Q;
  cin >> n >> m;
  // Read input data and group voters by their preferred party
  for (i = 0; i < n; i++) {
    cin >> p >> c;
    v1[p].push_back(c);
    if (p != 1)
      sum += c; // Add cost of votes from non-party-1 voters to sum
  }
  // Sort each party's voters by cost to buy their vote (ascending order)
  for (i = 2; i <= m; i++) {
    sort(v1[i].begin(), v1[i].end());
    // Reverse-sort into v2 for easier access to highest-cost voters first
    for (j = v1[i].size(); j--;)
      v2[v1[i].size() - j - 1].push_back(v1[i][j]);
  }
  total = n - v1[1].size(); // Total voters from parties other than 1
  // Try all possible number of extra votes party 1 needs to win (from 0 to total)
  for (i = 0; i <= n - v1[1].size(); i++) {
    l = i + v1[1].size() - 1;
    if ((l < 0) && (m > 1))
      continue;
    // Adjust k pointer to include voters in current window
    for (; k < l; k++) {
      for (j = v2[k].size(); j--;)
        sum -= v2[k][j], Q.push(-v2[k][j]), total--; // Remove from total and add to PQ
    }
    // If we have more required votes than current, remove from PQ
    for (; total < i; total++)
      sum -= Q.top(), Q.pop(); 
    ans = min(ans, sum);
  }
  cout << ans << endl;
  return 0;
}


// https://github.com/VaHiX/codeForces/