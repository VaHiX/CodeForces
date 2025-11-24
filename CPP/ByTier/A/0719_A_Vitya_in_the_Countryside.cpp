// Problem: CF 719 A - Vitya in the Countryside
// https://codeforces.com/contest/719/problem/A

/*
Purpose: Determine if the moon size will increase (UP), decrease (DOWN), or if it's undecidable (-1) based on a sequence of n consecutive observations.
The moon size follows a fixed 30-day cycle: 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0...
Algorithms/Techniques: 
  - Direct observation and comparison of the last two elements in the sequence.
  - Special handling for boundary cases (0 and 15) based on the cycle.

Time Complexity: O(n) where n is the number of days observed. 
Space Complexity: O(n) for storing the array of observed values.
*/
#include <iostream>

using namespace std;
int main() {
  int i, j, k;
  int n;
  bool f = false;
  cin >> n;
  int a[n];
  for (i = 0; i < n; i++)
    cin >> a[i];
  // If only one observation and it's not 0 or 15, we can't determine next trend
  if (n == 1 && a[n - 1] != 15 && a[n - 1] != 0) {
    cout << "-1";
    return 0;
  }
  // If current moon size is increasing and not at peak (15), next must be UP
  if (a[n - 1] > a[n - 2] && a[n - 1] != 15)
    cout << "UP";
  // If current moon size is increasing but at peak (15), next must be DOWN
  else if (a[n - 1] > a[n - 2] && a[n - 1] == 15)
    cout << "DOWN";
  // If current moon size is decreasing and not at bottom (0), next must be DOWN
  else if (a[n - 1] < a[n - 2] && a[n - 1] != 0)
    cout << "DOWN";
  // If current moon size is decreasing and at bottom (0), next must be UP
  else if (a[n - 1] < a[n - 2] && a[n - 1] == 0)
    cout << "UP";
  return 0;
}


// https://github.com/VaHiX/CodeForces/