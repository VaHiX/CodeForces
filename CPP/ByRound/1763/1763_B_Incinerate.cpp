// Problem: CF 1763 B - Incinerate
// https://codeforces.com/contest/1763/problem/B

/*
Purpose: Determine if Genos can kill all monsters using his Incineration Cannon.
         Each attack reduces all monster health by k, then k is reduced by
         the power of the weakest remaining monster.
         
Algorithms/Techniques: 
    - Sorting monsters by power (first element of pair)
    - Greedily simulate attacks, updating k after each attack
    - Track total health reduced and compare to monster health

Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for storing monster data
*/

#include <algorithm>
#include <iostream>
#include <utility>

using namespace std;

int main() {
  int t, n, k, i, h;
  cin >> t;
  while (t--) {
    cin >> n >> k;
    pair<int, int> a[n]; // pair: power (first), health (second)
    for (i = 0; i < n; i++)
      cin >> a[i].second; // read health values
    for (i = 0; i < n; i++)
      cin >> a[i].first;  // read power values
    sort(a, a + n);        // sort monsters by power (ascending)
    h = 0;                 // total health reduced so far
    for (i = 0; i < n && k > 0;) {
      h += k;              // apply attack to all monsters
      while (a[i].second <= h && i < n)  // skip monsters already dead
        i++;
      k -= a[i].first;     // reduce k by weakest monster's power
    }
    if (i == n)
      cout << "YES" << '\n';
    else
      cout << "NO" << '\n';
  }
}


// https://github.com/VaHiX/CodeForces/