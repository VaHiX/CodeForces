// Problem: CF 2148 D - Destruction of the Dandelion Fields
// https://codeforces.com/contest/2148/problem/D

/*
D. Destruction of the Dandelion Fields
Algorithms/Techniques: Greedy, Sorting
Time Complexity: O(n log n) per test case due to sorting
Space Complexity: O(n) for storing odd numbers

The problem involves maximizing the number of dandelions cut by Farmer John,
who uses a lawnmower that toggles its state when visiting fields with odd 
dandelion counts. The strategy is to:
1. Collect all odd numbers (they toggle the state).
2. All even numbers contribute directly to the sum if the lawnmower is on.
3. To maximize, we sort odds and use the largest half (after sorting) to turn
   the mower on, so that the remaining smaller odds are not toggled inappropriately.
4. Then, add all evens and the sum of the larger half of odds to get the result.
*/

#include <algorithm>
#include <iostream>

using std::cin;
using std::cout;
using std::sort;

int t, n, a[200005], cnt, op;
long long sum;

int main() {
  std::ios::sync_with_stdio(false);
  cin.tie(0);
  cin >> t;
  while (t--) {
    cin >> n;
    cnt = sum = 0;
    for (int i = 1; i <= n; i++) {
      cin >> op;
      if (op & 1)  // If number is odd
        a[++cnt] = op;  // Store in array for later processing
      else
        sum += op;  // Even numbers contribute directly to the final sum
    }
    if (!cnt) {  // No odd numbers → lawnmower never turns on
      cout << 0 << '\n';
      continue;
    }
    sort(a + 1, a + cnt + 1);  // Sort odds in ascending order
    for (int i = cnt / 2 + 1; i <= cnt; i++) {  // Add the larger half of odds
      sum += a[i];
    }
    cout << sum << '\n';
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/