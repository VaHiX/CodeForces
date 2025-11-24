// Problem: CF 2126 B - No Casino in the Mountains
// https://codeforces.com/contest/2126/problem/B

/*
B. No Casino in the Mountains
Algorithm: Greedy approach to maximize number of valid k-day periods where all a[i] = 0,
           with mandatory 1-day break between consecutive hikes.
Time Complexity: O(n) - Each element is visited at most twice due to the i++ inside loop.
Space Complexity: O(1) - Only using a few variables for counting and tracking.

The solution uses a greedy strategy:
- Traverse array from left to right.
- Count consecutive good weather days (0s).
- When we find k consecutive good days, start a hike, increment result counter,
  and skip the next day (mandatory break).
- If we encounter a rainy day (1), reset the count of consecutive good days.

Input Format:
- First line: number of test cases t
- For each test case:
  - Line 1: n (number of days), k (hike duration)
  - Line 2: array a of size n with values 0 or 1

Output:
- For each test case, print maximum number of hikes Jean can make.
*/

#include <stdint.h>
#include <iostream>

using namespace std;
#define int long long
#define fast_io                                                                \
  ios::sync_with_stdio(false);                                                 \
  cin.tie(nullptr);

void solve() {
  int n, k, r(0), c(0), x;
  cin >> n >> k;
  for (int i = 0; i < n; i++) {
    cin >> x;
    if (x)
      c = 0;     // Reset counter when rain occurs
    else
      c++;       // Increment counter for good weather
    if (c == k) { // Found k consecutive good days
      r++;       // Increment hike count
      c = 0;     // Reset counter after starting a hike
      if (i < n - 1) { // Avoid out of bounds
        cin >> x;   // Read next day's weather to skip it (mandatory break)
        i++;       // Skip the break day in outer loop
      }
    }
  }
  cout << r << "\n";
}

int32_t main() {
  fast_io;
  int t = 1;
  cin >> t;
  while (t--)
    solve();
}


// https://github.com/VaHiX/codeForces/