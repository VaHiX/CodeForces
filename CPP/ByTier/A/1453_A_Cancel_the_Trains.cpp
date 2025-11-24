// Problem: CF 1453 A - Cancel the Trains
// https://codeforces.com/contest/1453/problem/A

/*
A. Cancel the Trains

Algorithm:
- For each test case, we are given n trains departing from the bottom and m trains departing from the left.
- Each train i from bottom starts at (i, 0) and moves to (i, T) after T minutes.
- Each train j from left starts at (0, j) and moves to (T, j) after T minutes.
- Trains crash if they are at the same (x,y) coordinate at the same time.
- So two trains crash if their paths intersect in time. This happens when:
    - Train i from bottom (i,0) and train j from left (0,j) meet at some time T.
    - Their positions: (i,T) and (T,j). For them to be equal: i=T and T=j => i=j.
- Therefore, if a train number appears in both lists (bottom and left), then those trains will crash.
- Solution: Find the number of common elements between the two sets.

Time Complexity: O(n + m)
Space Complexity: O(n + m)

*/
#include <iostream>
#include <set>

using namespace std;
int main() {
  int t, n, m, a;
  cin >> t;
  while (t--) {
    cin >> n >> m;
    set<int> z; // Set to store all train numbers
    for (int i = 0; i < n + m; ++i) {
      cin >> a;
      z.insert(a); // Insert all train numbers into the set
    }
    cout << n + m - z.size() << "\n"; // Count of duplicates = n + m - size of set
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/