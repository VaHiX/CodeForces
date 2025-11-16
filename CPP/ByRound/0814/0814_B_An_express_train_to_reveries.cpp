// Problem: CF 814 B - An express train to reveries
// https://codeforces.com/contest/814/problem/B

/*
Algorithm/Techniques: Greedy approach with map for tracking assigned colors.
Time Complexity: O(n^2) in worst case due to nested loops for finding unused color.
Space Complexity: O(n) for storing arrays and map.

The problem is to reconstruct a permutation p such that exactly one element differs
between a and p, and exactly one element differs between b and p. This means we have
two mismatches - one in sequence a and one in sequence b.

We use a greedy method:
1. First, we copy elements that match between a and b (as they must be in p).
2. Then, we check which elements in a are not yet assigned but b gives a valid color;
   or vice versa.
3. For remaining positions with no clear assignment, we assign the first unused color.
4. A map tracks which colors have been already used.
*/

#include <string.h>
#include <iostream>
#include <map>

typedef long long int ll;
#define pp pair<ll, ll>
#define dbg printf("in\n");
#define inf 1000000000000
using namespace std;
int main() {
  int i, j, k;
  int n;
  cin >> n;
  int a[n], b[n], c[n];
  map<int, bool> mp; // Tracks which colors have been assigned
  memset(c, 0, sizeof(c)); // Initialize c array to 0 (unassigned)
  for (i = 0; i < n; i++)
    cin >> a[i];
  for (i = 0; i < n; i++) {
    cin >> b[i];
    if (b[i] == a[i])
      c[i] = b[i], mp[c[i]] = 1; // If a[i] == b[i], it must be in p
  }
  // Assign elements where one sequence has a valid unassigned value
  for (i = 0; i < n; i++) {
    if (!mp[a[i]] && mp[b[i]])
      c[i] = a[i], mp[a[i]] = 1; // a[i] is unassigned but b[i] is assigned
    else if (mp[a[i]] && !mp[b[i]])
      c[i] = b[i], mp[b[i]] = 1; // b[i] is unassigned but a[i] is assigned
  }
  // Assign remaining elements to unassigned positions
  for (i = 0; i < n; i++) {
    if (!c[i]) {
      if (!mp[a[i]])
        c[i] = a[i], mp[a[i]] = 1; // Assign a[i] if not used yet
      else if (!mp[b[i]])
        c[i] = b[i], mp[b[i]] = 1; // Assign b[i] if not used yet
    }
  }
  // For any remaining unassigned positions (in theory only one), assign smallest unused color
  for (i = 0; i < n; i++) {
    if (!c[i]) {
      for (j = 1; j <= n; j++) {
        if (!mp[j]) {
          mp[j] = 1;
          c[i] = j;
          break;
        }
      }
    }
  }
  for (i = 0; i < n; i++)
    cout << c[i] << " ";
  return 0;
}


// https://github.com/VaHiX/CodeForces/