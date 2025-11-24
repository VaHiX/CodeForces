// Problem: CF 2164 C - Dungeon
// https://codeforces.com/contest/2164/problem/C

/*
Algorithm/Techniques: Greedy + Priority Queue + Sorting
Time Complexity: O(n log n + m log m)
Space Complexity: O(n + m)

This solution uses a greedy approach to maximize the number of monsters killed.
- Sort monsters by their health values (ascending).
- Use a min-heap (priority queue) to always try to kill the weakest monster possible with the weakest available sword.
- When a monster is killed, we may gain a new sword with increased damage.
- For monsters that do not grant new swords (c[i] == 0), we process them greedily.
- After initial processing, we attempt to assign remaining swords to remaining monsters.
*/

#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;
const int N = 200005;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int t, n, m, i, a[N], f[N], x;
  pair<int, int> bc[N];
  cin >> t;
  while (t--) {
    cin >> n >> m;
    for (i = 1; i <= n; i++)
      cin >> a[i];
    for (i = 1; i <= m; i++)
      cin >> bc[i].first;  // monster health
    for (i = 1; i <= m; i++)
      cin >> bc[i].second; // c[i] - damage of new sword if obtained
    sort(bc + 1, bc + m + 1); // sort monsters by health
    priority_queue<int, vector<int>, greater<int>> pq; // min-heap of sword damages
    for (i = 1; i <= n; i++)
      pq.push(a[i]);
    for (i = 1; i <= m; i++)
      f[i] = 0; // flags to mark if monster is killed
    vector<int> z; // swords that couldn't be used for monster with c[i] > 0
    i = 1;
    while (!pq.empty()) {
      // Skip monsters without new sword (c[i] == 0)
      while (i <= m && bc[i].second == 0)
        i++;
      x = pq.top();
      pq.pop();
      if (i > m)
        z.push_back(x); // No more monsters with c[i] > 0, so store sword
      else if (bc[i].first > x)
        z.push_back(x); // Sword too weak for monster
      else {
        f[i] = 1; // Mark monster as killed
        x = max(x, bc[i].second); // New sword damage
        pq.push(x); // Add new sword to available swords
        i++; // Move to next monster
      }
    }
    i = 1;
    // Assign remaining swords to remaining monsters
    for (auto e : z) {
      while (i <= m && f[i] == 1)
        i++;
      if (e >= bc[i].first)
        f[i] = 1; // Assign sword to monster if sufficient
    }
    x = 0;
    for (i = 1; i <= m; i++)
      x += f[i]; // Count total monsters killed
    cout << x << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/