// Problem: CF 1741 G - Kirill and Company
// https://codeforces.com/contest/1741/problem/G

/*
Algorithm: 
This problem involves finding the minimum number of friends without cars who must walk to their homes in a graph. 
We use BFS to compute shortest distances from vertex 1 to all other vertices. 
For each permutation of friends without cars, we simulate assigning these friends to car-carrying friends such that 
the car-carrying friend can drive the shortest path to each friend's home. 
We use a backtracking-like recursion (`fil`) to check if a car-carrying friend can take a friend without a car.
Time Complexity: O(f! * n + m) where f is the number of friends without cars. In worst case, f <= 6, so f! is small.
Space Complexity: O(n + m) for storing the graph and auxiliary arrays.
*/

#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;
vector<int> H, ord; // H stores count of friends at each vertex, ord stores BFS distances
vector<vector<int>> gr; // adjacency list representation of graph
int ans;

// Function to determine if a friend at vertex x can be picked up by a friend with a car
// Returns true if the friend can be taken, and decrements H[x] if so
bool fil(int x) {
  if (H[x]) { // if a friend is at vertex x
    H[x]--; // decrement the count
    return 1; // we picked him up
  }
  // Traverse neighbors in BFS order
  for (auto y : gr[x]) {
    if (ord[y] <= ord[x]) // if neighbor is not on shortest path away from root
      continue;
    if (fil(y)) // recursively try to pick up friend at y
      return 1;
  }
  return 0; // could not pick up any friend
}

// Function to simulate assignment for a given permutation of friends without cars
void fi(vector<int> per) {
  int cu = per.size(); // number of friends without cars
  for (auto x : per) { // for each such friend
    if (fil(x)) { // try to assign a car-carrying friend to pick him up
      H[x]++; // if assigned, increment back the count of friends at that vertex
      cu--; // reduce the number of friends still needing a ride
    }
  }
  ans = min(ans, cu); // update minimum number of friends who must walk
}

void solve() {
  int n, m;
  cin >> n >> m;
  ans = 10; // initialize answer to a large number
  gr.clear();
  gr.resize(n);
  H.clear();
  H.resize(n, 0); // initialize friends count at each vertex to 0
  ord.clear();
  ord.resize(n, -1); // initialize order array to -1 (unvisited)
  for (int i = 0; i < m; ++i) {
    int a, b;
    cin >> a >> b;
    a--, b--; // convert vertex indices to 0-based
    gr[a].push_back(b);
    gr[b].push_back(a); // add edges to adjacency list
  }
  
  // BFS to compute shortest distances from vertex 1 (0-indexed)
  queue<pair<int, int>> Q;
  Q.emplace(0, 0);
  while (Q.size()) {
    int d = Q.front().second; // depth (distance)
    int u = Q.front().first;  // vertex
    Q.pop();
    if (ord[u] != -1) // if already visited, skip
      continue;
    ord[u] = d; // store depth
    for (auto y : gr[u]) // for all neighbors
      Q.emplace(y, d + 1); // add to queue with incremented depth
  }
  
  int f;
  cin >> f;
  vector<int> INI; // original friend counts
  vector<int> person(f); // indices of friends' homes
  for (int i = 0; i < f; ++i) {
    int x;
    cin >> x;
    x--; // convert to 0-based
    person[i] = x;
    H[x]++; // increment count of friends at this home
  }
  INI = H; // save original friend count for each vertex

  int k;
  cin >> k;
  vector<int> per(k); // indices of friends without cars (in original list)
  for (auto &x : per) {
    cin >> x;
    x = person[x - 1]; // get their home vertex
    H[x]--; // reduce count because they'll be picked up
  }
  
  INI = H; // save updated friend counts
  sort(per.begin(), per.end()); // sort permutations to handle all
  do {
    H = INI;
    fi(per); // evaluate permutation
  } while (next_permutation(per.begin(), per.end())); // go through all permutations
  
  cout << ans << '\n'; // print minimum number of friends who must walk
}

int main() {
  int t;
  cin >> t;
  while (t--)
    solve(); // process each test case
}


// https://github.com/VaHiX/CodeForces/