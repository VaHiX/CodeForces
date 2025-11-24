// Problem: CF 1842 D - Tenzing and His Animal Friends 
// https://codeforces.com/contest/1842/problem/D

/*
Algorithm: Greedy approach with edge relaxation
Approach:
1. Model the problem as a graph where nodes represent friends and edges represent restrictions.
2. Each restriction (u,v,y) means that exactly one of u or v can be active at a time, with a maximum combined active time of y.
3. Use a greedy method to find a feasible assignment of time slots that maximizes total time while satisfying all constraints.
4. The algorithm maintains a "used" array to track which friends are currently "active" in some subset of games.
5. Find the minimum edge (constraint) that is "unbalanced" - i.e., one endpoint is active and the other is not.
6. Assign time to this edge, update all constraints accordingly, and repeat until no more valid moves exist.
7. If no constraints are violated and all nodes are active, infinite time is possible.

Time Complexity: O(m^2 * n) - In worst case, we might process each edge multiple times, with each edge check taking O(m) time.
Space Complexity: O(m + n) - Storage for edges and used array.
*/

#include <stddef.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#define endl '\n'
using namespace std;
typedef long long ll;

void speed() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
}

const int maxn = 1e5 + 10;

struct edge {
  int v, u, x;
} edges[maxn];

struct game {
  string state;
  int play_time;
  game(string _state, int _play_time) {
    state = _state;
    play_time = _play_time;
  }
};

int n, m, used[maxn];

void solve() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    used[i] = 0;
  }
  for (int i = 1; i <= m; i++) {
    cin >> edges[i].v >> edges[i].u >> edges[i].x;
  }
  used[n] = 1; // Mark friend n as not allowed (as per problem constraints)
  string act;
  for (int i = 0; i < n; i++) {
    act.push_back('1'); // Initially all friends are in the set (except n)
  }
  act.back() = '0'; // Ensure last character (friend n) is 0
  vector<game> ans;

  while (true) {
    // Check if friend 1 is used (must be used in every set)
    if (used[1] == 1)
      break;
    bool done = true;
    // Check if all friends are used
    for (int i = 1; i <= n; i++) {
      if (used[i] == 0) {
        done = false;
        break;
      }
    }
    if (done)
      break;
    
    int min_edge = -1; // Find the edge with the minimum weight that can be used
    for (int i = 1; i <= m; i++) {
      // If one endpoint is used and other is not (edge is unbalanced)
      if (used[edges[i].v] != used[edges[i].u]) {
        if (min_edge == -1 || edges[min_edge].x > edges[i].x)
          min_edge = i;
      }
    }

    // If no valid edge, we can play infinite time
    if (min_edge == -1) {
      cout << "inf" << endl;
      return;
    }

    int val = edges[min_edge].x; // Get the value to use
    if (val > 0) {
      ans.push_back(game(act, val)); // Store this game
    }

    // Update all edges
    for (int i = 1; i <= m; i++) {
      // For unbalanced edges, reduce their weight
      if (used[edges[i].v] != used[edges[i].u])
        edges[i].x -= val;
    }

    // Mark the two endpoints of the edge as used
    if (used[edges[min_edge].v] == 0) {
      used[edges[min_edge].v] = 1;
      act[edges[min_edge].v - 1] = '0'; // Update state
    }
    if (used[edges[min_edge].u] == 0) {
      used[edges[min_edge].u] = 1;
      act[edges[min_edge].u - 1] = '0'; // Update state
    }
  }

  ll sum = 0;
  for (int i = 0; i < ans.size(); i++)
    sum = sum + (ll)(ans[i].play_time); // Calculate total play time

  cout << sum << " " << ans.size() << endl;
  for (int i = 0; i < ans.size(); i++)
    cout << ans[i].state << " " << ans[i].play_time << endl;
}

int main() {
  speed();
  solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/