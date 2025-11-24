// Problem: CF 524 A - Возможно, вы знаете этих людей?
// https://codeforces.com/contest/524/problem/A

#include <algorithm>
#include <iostream>
#include <map>
#include <utility>
#include <vector>

using namespace std;
int main() {
  int m, k;
  cin >> m >> k;
  int g[m], q[m];
  for (int i = 0; i < m; i++)
    cin >> g[i] >> q[i];
  map<int, int> sp; // Map to store unique user IDs and their indices
  vector<int> x; // Vector to store user IDs in sorted order
  for (int i = 0; i < m; i++) {
    sp[g[i]] = sp[q[i]] = 1; // Mark users as present
  }
  for (map<int, int>::iterator t = sp.begin(); t != sp.end(); t++) {
    t->second = x.size(); // Assign index to each user
    x.push_back(t->first); // Store user ID in sorted order
  }
  int n = x.size(); // Total number of unique users
  vector<vector<int>> gq(n); // Adjacency list for graph representation
  for (int i = 0; i < m; i++) {
    gq[sp[g[i]]].push_back(sp[q[i]]); // Add friend relationship
    gq[sp[q[i]]].push_back(sp[g[i]]); // Since friendship is symmetric
  }
  for (int i = 0; i < n; i++) {
    vector<bool> b(n); // Boolean vector to mark friends of current user
    for (int g : gq[i])
      b[g] = 1; // Mark friends of current user
    vector<int> pd; // Vector to store potential friends
    for (int j = 0; j < n; j++) {
      if (j != i && !b[j]) { // If j is not current user and not a friend
        int c = 0; // Count of common friends
        for (int g : gq[j])
          c += b[g]; // Count how many friends of j are also friends of current user
        // Check if common friends meet the threshold percentage
        if (c * 100 >= k * gq[i].size()) {
          pd.push_back(x[j]); // Add to potential friends
        }
      }
    }
    cout << x[i] << ": "; // Print user ID
    cout << pd.size(); // Print number of potential friends
    for (int t : pd)
      cout << ' ' << t; // Print potential friends
    cout << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/