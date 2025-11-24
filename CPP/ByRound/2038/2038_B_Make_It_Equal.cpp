// Problem: CF 2038 B - Make It Equal
// https://codeforces.com/contest/2038/problem/B

/*
B. Make It Equal
Algorithms/Techniques: Simulation with circular array operations, greedy approach to balance elements.

Time Complexity: O(n) per test case, where n is the size of the array.
Space Complexity: O(n), for storing the arrays a and b.

The problem involves making all elements of an array equal using specific operations:
- For each element a[i], we can decrease it by 2 and increase a[(i+1)%n] by 1.
- The final goal is to have all elements equal and non-negative.
- This approach simulates the process in reverse using a greedy balance mechanism.
*/

#include <algorithm>
#include <iostream>

using namespace std;
int n, c, d, k, a[200005], b[200005];
typedef long long ll;
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t;
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 0; i < n; i++) {
      cin >> a[i];
    }
    int z = 0;
    // Simulate the process until all elements become zero or negative
    while (!z) {
      z = 1;
      for (int i = 0; i < n; i++) {
        // Check if any element is still positive
        if (a[i] && a[i] + 1)
          z = 0;
        // Distribute half of current value to b[i]
        b[i] += (a[i] + 1) / 2;
        // Pass the remaining value to next element in circular array
        a[(i + 1) % n] += (a[i] + 1) / 2;
        // Flip sign of current value for tracking negative step
        a[i] = -(a[i] & 1);
      }
    }
    z = 1;
    int d = 2000000001;
    // Find minimum value and check if all elements are zero
    for (int i = 0; i < n; i++) {
      if (a[i])
        z = 0;
      d = min(d, b[i]);
    }
    long long s = 0;
    if (!z) {
      cout << "-1\n";
      goto bla;
    }
    // Calculate total operations needed by normalizing the distribution
    for (int i = 0; i < n; i++)
      s += b[i] - d;
    cout << s << "\n";
  bla:
    for (int i = 0; i < n + 3; i++)
      b[i] = 0;
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/