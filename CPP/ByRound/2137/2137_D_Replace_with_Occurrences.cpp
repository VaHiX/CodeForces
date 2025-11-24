// Problem: CF 2137 D - Replace with Occurrences
// https://codeforces.com/contest/2137/problem/D

/*
D. Replace with Occurrences

Purpose:
This code determines whether there exists an array a of size n such that for each element b[i], 
the count of occurrences of a[i] in the array equals b[i]. If such an array exists, it constructs one.
The solution uses grouping by frequency and assigning unique identifiers to groups.

Algorithms/Techniques:
- Hash map to group indices by their values
- Greedy assignment of identifiers based on grouping by frequency

Time Complexity:
O(n) average case, where n is the size of input array. Each element is processed once and hash map operations are amortized O(1).

Space Complexity:
O(n) for storing the array elements and auxiliary structures (hash map and result vector).
*/

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int T;
  cin >> T;
  while (T--) {
    int x;
    cin >> x;
    vector<int> y(x);
    for (int i = 0; i < x; i++)
      cin >> y[i];
    unordered_map<int, vector<int>> z;
    for (int i = 0; i < x; i++)
      z[y[i]].push_back(i);
    vector<int> w(x, -1);
    int p = 1, q = 1;
    for (auto u = z.begin(); u != z.end(); ++u) {
      int v = u->first;
      auto &r = u->second;
      if ((int)r.size() % v) { // Check if the count of occurrences is divisible by the value itself
        q = 0;
        break;
      }
      for (int i = 0; i < (int)r.size(); i += v) { // Assign identifiers in batches
        for (int j = 0; j < v; j++)
          w[r[i + j]] = p; // Assign same identifier to group of indices
        p++;
      }
    }
    if (!q)
      cout << "-1\n";
    else {
      for (int i = 0; i < x; i++)
        cout << w[i] << " ";
      cout << "\n";
    }
  }
}


// https://github.com/VaHiX/codeForces/