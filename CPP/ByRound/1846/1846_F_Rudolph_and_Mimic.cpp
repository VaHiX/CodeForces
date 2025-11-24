// Problem: CF 1846 F - Rudolph and Mimic
// https://codeforces.com/contest/1846/problem/F

/*
Algorithm/Technique: 
This solution uses a strategy to identify a mimic among n objects by removing objects in stages, 
using the fact that the mimic cannot remain the same object for more than two stages. 
The algorithm compares object counts before and after removal to detect which object type is not 
consistent with the original distribution, thereby identifying a potential mimic candidate.

Time Complexity: O(n) per test case, as we process each element a constant number of times.
Space Complexity: O(n) for storing the object types in the array and auxiliary structures.
*/

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
using pii = pair<int, int>;
const int MAX = 2e5 + 1;
int a, n, t, v[201], hm[10], f[10];
;
void testcase() {
  cin >> n;
  for (int i = 1; i <= 9; i++) {
    hm[i] = 0;
    f[i] = 0;
  }
  for (int i = 1; i <= n; i++) {
    cin >> v[i];
    hm[v[i]]++; // Count occurrences of each type
    f[v[i]]++;  // Store initial counts
  }
  cout << '-' << ' ' << 0 << endl; // First removal: remove 0 objects
  for (int i = 1; i <= 9; i++) {
    hm[i] = 0; // Reset count for second stage
  }
  for (int i = 1; i <= n; i++) {
    cin >> v[i];
    hm[v[i]]++; // Count occurrences after first removal
  }
  vector<int> aux; // Vector to store indices to remove
  int to = 0; // Type of object to detect
  for (int i = 1; i <= 9; i++) {
    if (f[i] < hm[i]) { // If count of some type increased, it could be the mimic
      to = i;
      for (int j = 1; j <= n; j++) {
        if (v[j] != i) { // Collect indices of objects that are not of type 'i'
          aux.push_back(j);
        }
      }
      break;
    }
  }
  if (to) {
    // If a type was found with increased count, proceed to remove those indices
  } else {
    // If no such type found, try again by removing 0 objects
    cout << '-' << ' ' << 0 << endl;
    for (int i = 1; i <= 9; i++) {
      hm[i] = 0;
    }
    for (int i = 1; i <= n; i++) {
      cin >> v[i];
      hm[v[i]]++;
    }
    for (int i = 1; i <= 9; i++) {
      if (f[i] < hm[i]) {
        to = i;
        for (int j = 1; j <= n; j++) {
          if (v[j] != i) {
            aux.push_back(j);
          }
        }
        break;
      }
    }
  }
  cout << '-' << ' ' << aux.size() << ' ';
  n -= aux.size(); // Update number of remaining objects
  for (int i = 1; i <= (int)aux.size(); i++) {
    cout << aux[i - 1] << ' '; // Output indices of objects to remove
  }
  cout << endl;
  int ind = 0; // Index of the actual mimic
  while (1) {
    for (int i = 1; i <= n; i++) {
      cin >> v[i];
      if (v[i] != to) // The mimic can't be of type 'to' anymore due to transformation rules
        ind = i;
    }
    if (ind) {
      cout << '!' << ' ' << ind << endl; // Output the index of the mimic
      return;
    }
    cout << '-' << ' ' << 0 << endl; // Continue with another removal
  }
}
signed main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  cin >> t;
  while (t--)
    testcase();
  return 0;
}


// https://github.com/VaHiX/CodeForces/