// Problem: CF 1719 C - Fighting Tournament
// https://codeforces.com/contest/1719/problem/C

/*
Algorithm: Tournament Simulation with Optimization
Approach:
1. For each athlete, we simulate how many times they will win before the strongest athlete is determined.
2. We maintain a map 'm' where m[i] represents how many times athlete i can win consecutively before the strongest athlete takes over.
3. The strongest athlete will win indefinitely (represented by INT_MAX).
4. For each query, we determine how many wins the specified participant has within k rounds using precomputed values in the map.

Time Complexity: O(n + q) per test case, where n is the number of participants and q is the number of queries.
Space Complexity: O(n) for storing the array and the map.
*/

#include <limits.h>
#include <algorithm>
#include <iostream>
#include <map>

using namespace std;

int main() {
  int T;
  cin >> T;
  while (T--) {
    int n, q, x = 1;  // x keeps track of the index of the current strongest athlete
    map<int, int> m;  // m[i] stores how many consecutive wins athlete i can have
    cin >> n >> q;
    int v[n + 1];  // array to store athlete strengths
    for (int i = 1; i <= n; i++)
      cin >> v[i];
    
    // Preprocessing step to calculate how many wins each athlete can have
    for (int i = 2; i <= n; i++) {
      if (v[i] > v[x])
        x = i;
      m[x]++;  // Increment the win count for the current strongest athlete up to position i
    }
    
    // The strongest athlete can win indefinitely
    m[x] = INT_MAX;
    
    // Process queries
    for (int i = 0; i < q; i++) {
      int a, k;
      cin >> a >> k;
      
      // Adjust k based on how many rounds before athlete 'a' starts winning
      k -= max(a - 2, 0);
      
      // Output the minimum of: 
      // - k rounds remaining
      // - wins this athlete can have (precomputed)
      // - but at least 0
      cout << max(min(m[a], k), 0) << endl;
    }
  }
}


// https://github.com/VaHiX/CodeForces/