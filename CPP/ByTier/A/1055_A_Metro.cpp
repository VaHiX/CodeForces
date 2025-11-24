// Problem: CF 1055 A - Metro
// https://codeforces.com/contest/1055/problem/A

#include <iostream>
using namespace std;
/*
Problem: Metro
Purpose: Determine if Bob can travel from station 1 to station s using two tracks of a metro line.
         Track 1 goes from station 1 to n, track 2 goes from n to 1.
         Stations may be closed for either track.
         
Algorithms/Techniques: 
    - Simulation with conditional checks
    - Linear scan of arrays
    
Time Complexity: O(n) - single pass through the arrays
Space Complexity: O(n) - array storage for a and b

Input:
- n (number of stations), s (Alice's station)
- a[] array indicating open/closed status for track 1
- b[] array indicating open/closed status for track 2

Output:
- "YES" if Bob can reach Alice, "NO" otherwise
*/
int main() {
  int n, s, t = 0; // t tracks whether there's a valid path through middle stations
  cin >> n >> s;
  int a[n + 1], b[n + 1]; // Arrays to store track statuses (1-indexed)
  for (int i = 1; i <= n; ++i) // Read track 1 status
    cin >> a[i];
  for (int i = 1; i <= n; ++i) { // Read track 2 status and check middle stations
    cin >> b[i];
    if (i >= s && a[i] && b[i]) // If station is at or beyond Alice's station and both tracks open
      t = 1; // Mark that we can reach Alice via a valid station
  }
  if (a[1] && a[s]) // If Bob can go directly from station 1 to s on track 1
    cout << "YES";
  else if (a[1] && b[s] && t) // If Bob starts at 1, switches to track 2 at Alice's station and has valid path
    cout << "YES";
  else
    cout << "NO";
}

// https://github.com/VaHiX/codeForces/