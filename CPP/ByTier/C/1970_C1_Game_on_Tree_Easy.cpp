// Problem: CF 1970 C1 - Game on Tree (Easy)
// https://codeforces.com/contest/1970/problem/C1

/*
Algorithm/Techniques: 
- The problem is modeled as a path (since the tree has exactly two leaves, it's essentially a linear array).
- The key insight is that the game is a simple turn-based game on a path.
- The winner is determined by the parity (odd/even) of the distance from the starting node to the nearest leaf.
- If the total number of nodes in the tree is even, then Ron wins immediately (since he starts first).
- Otherwise, we calculate the number of steps from the starting node to the nearest leaf. If this number is even, Hermione wins; otherwise Ron wins.

Time Complexity: O(n) - We process each node at most once when building the adjacency list and traversing to a leaf.
Space Complexity: O(n) - For storing the adjacency list representation of the tree.
*/

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;
#define ll long long
#define all(x) x.begin(), x.end()
#define sz(x) (ll) x.size()
const int INF = 1e18;
const int MOD = 1e9 + 7;
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  int n, t;
  cin >> n >> t;
  if (n % 2 == 0) { // If number of nodes is even, Ron wins immediately
    cout << "Ron";
    return 0;
  }
  int index;
  vector<int> arr(n + 1, -1); // Adjacency list stored in a vector (simplified for path)
  for (int i = 0; i < n - 1; i++) {
    cin >> index;
    cin >> arr[index]; // Reading edges and building a simple linked list for path traversal
  }
  int snode;
  cin >> snode;
  int count = 0; // Distance from start node to leaf
  int next = arr[snode]; // Move to next node in the path (following the tree structure)
  while (next != -1) { // Traverse until reaching a leaf (marked by -1)
    count++;
    next = arr[next];
  }
  if (count % 2 == 0) // Even distance => Hermione wins
    cout << "Hermione";
  else // Odd distance => Ron wins
    cout << "Ron";
  return 0;
}


// https://github.com/VaHiX/CodeForces/