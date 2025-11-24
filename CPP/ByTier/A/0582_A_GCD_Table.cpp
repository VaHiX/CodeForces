// Problem: CF 582 A - GCD Table
// https://codeforces.com/contest/582/problem/A

/*
Purpose: Restore an array from its GCD table.
Algorithm:
- Use a map to count occurrences of each GCD value in the table.
- Process GCD values in descending order.
- For each value, if it's still available (count > 0), add it to the result array.
- Reduce the count of GCDs between this value and already added values.
- Output the reconstructed array.

Time Complexity: O(n^2 * log(max_value)) where n is the size of the array.
Space Complexity: O(n^2) for storing the map of GCD counts.

Techniques:
- Map for counting frequencies
- Reverse iteration over map to process larger values first
- GCD computation using built-in __gcd function
*/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <utility>
#include <vector>

using namespace std;
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n;
  cin >> n;
  map<int, int> arr;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= n; ++j) {
      int a;
      cin >> a;
      arr[a]++;
    }
  vector<int> sol;
  for (auto it = arr.rbegin(); it != arr.rend(); ++it) {
    while (it->second) {
      for (auto x : sol)
        arr[__gcd(x, it->first)] -= 2;
      sol.push_back(it->first);
      it->second--;
    }
  }
  for (auto x : sol)
    cout << x << ' ';
  return 0;
}


// https://github.com/VaHiX/CodeForces/