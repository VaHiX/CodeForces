// Problem: CF 1980 C - Sofia and the Lost Operations
// https://codeforces.com/contest/1980/problem/C

/*
 * Problem: Sofia and the Lost Operations
 * 
 * Purpose: Determine if there exists a sequence of indices c1, c2, ..., cm 
 * such that applying m modification operations ⟨cj, dj⟩ to the original array a 
 * results in the array b.
 * 
 * Approach:
 * 1. For each position i, if a[i] != b[i], we need to ensure that b[i] appears 
 *    in the modification values d[1..m] sufficiently many times to "cover" the 
 *    mismatch.
 * 2. Count how many times each value from d[1..m] appears.
 * 3. For each position where a[i] != b[i], decrement the count of b[i] in the map.
 * 4. If any count becomes negative, the operation sequence is invalid.
 * 5. Ensure that the last operation value d[m] actually occurs in b.
 * 
 * Time Complexity: O(n + m)
 * Space Complexity: O(n + m)
 * 
 * Algorithms/Techniques:
 * - Map for counting frequencies of modification values
 * - Set for checking if last d value is present in b array
 * - Single pass over arrays to check constraints
 */
#include <iostream>
#include <map>
#include <set>

using namespace std;
int n, f, k, a[200005], b[200005], d[200005];
map<int, int> m;
set<int> s;
int main() {
  int t;
  cin >> t;
  while (t--) {
    cin >> n;
    m.clear();
    s.clear();
    for (int i = 1; i <= n; i++)
      cin >> a[i];
    for (int i = 1; i <= n; i++)
      cin >> b[i], s.insert(b[i]); // store all unique values of b
    cin >> f;
    for (int i = 1; i <= f; i++) {
      cin >> d[i];
      m[d[i]]++; // count frequency of each d value
    }
    bool ok = 1;
    for (int i = 1; i <= n; i++) {
      if (a[i] != b[i])
        m[b[i]]--; // reduce count for mismatched element
      if (m[b[i]] < 0) // if count goes negative, not enough operations
        ok = 0;
    }
    if (s.find(d[f]) == s.end()) // make sure last operation value is in b
      ok = 0;
    if (ok)
      cout << "YES" << endl;
    else
      cout << "NO" << endl;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/