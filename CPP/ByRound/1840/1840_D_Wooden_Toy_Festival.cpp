// Problem: CF 1840 D - Wooden Toy Festival
// https://codeforces.com/contest/1840/problem/D

/*
Algorithm: Binary search on the answer with a greedy check
Techniques: 
- Sorting + Binary Search + Greedy Interval Coverage

Time Complexity: O(n log n + n log MaxValue) where MaxValue = 1e9
Space Complexity: O(n) for storing the array

The problem is to assign 3 patterns to 3 carvers such that the maximum
distance from any requested toy pattern to the closest chosen pattern is minimized.

Approach:
1. Sort the patterns.
2. Use binary search on the answer (the maximum waiting time).
3. For a given maximum waiting time k, check if we can cover all patterns
   with at most 3 intervals of length 2*k (since each carver can cover 
   a range [x-k, x+k]).
4. Use a greedy approach to count minimum intervals needed.
*/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;
typedef long long ll;
#define pb push_back
#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define lb(x, y) lower_bound(all(x), y) - begin(x)

// Check if we can cover all elements with at most 3 intervals of size 2*k
bool check(vector<int> &arr, int k) {
  int res = 0;
  for (int i = 0; i < sz(arr); i++) {
    int j = i;
    // Extend the interval as far as possible within the allowed range
    while (j + 1 < sz(arr) && arr[j + 1] - arr[i] <= k * 2)
      j++;
    res++; // Count one interval
    i = j; // Move i to the end of current interval
  }
  return res <= 3; // At most 3 intervals needed
}

// Binary search for the minimal maximum waiting time
int search(vector<int> &arr, int l, int r) {
  if (l > r)
    return -1;
  int mid = (l + r) / 2;
  if (check(arr, mid)) {
    int m = search(arr, l, mid - 1);
    if (m == -1)
      return mid;
    return m;
  }
  return search(arr, mid + 1, r);
}

void solve() {
  int N;
  cin >> N;
  vector<int> arr(N);
  for (int i = 0; i < N; i++)
    cin >> arr[i];
  sort(all(arr));
  cout << search(arr, 0, 1000000000) << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;
  for (int t = 0; t < T; t++)
    solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/