// Problem: CF 2167 E - khba Loves to Sleep!
// https://codeforces.com/contest/2167/problem/E

/*
Problem: Place k teleports on a line [0, x] to maximize the minimum time for any friend to reach the nearest teleport.

Approach:
- Use binary search on the answer to find the maximum minimum distance (ans).
- For a given minimum distance ans, calculate how many valid positions exist on the line [0,x] where we can place teleports such that each friend is at most 'ans' distance away from a teleport.
- The check function computes the number of valid teleport positions for a fixed ans and verifies if it's >= k.
- Once we have the best minimum distance, we greedily place k teleports at the optimal positions.

Time Complexity: O(n log x + k)
Space Complexity: O(n)

Algorithms/Techniques:
- Binary search on the answer
- Greedy placement of teleport positions
*/

#include <stddef.h>
#include <algorithm>
#include <functional>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vector<int>> vvi;
typedef vector<vector<ll>> vvll;
#define pb push_back
#define all(x) x.begin(), x.end()
#define fr(i, start, n) for (int i = start; i < n; i++)
template <typename T>
using reverse_priority_queue = priority_queue<T, vector<T>, greater<T>>;
const ll MOD = 1e9 + 7;

// Function to check if we can place at least k teleports such that each friend is at most 'x' distance away
int check(int x, vi &v, int k, int X) {
  int n = v.size();
  int count = 0;
  // Add valid positions from the left of first friend
  count += max(0, v[0] - x + 1);
  // Add valid positions from the right of last friend
  count += max(0, X - (v[n - 1] + x) + 1);
  // Add valid positions between consecutive friends
  for (int i = 0; i < n - 1; i++) {
    int left = v[i] + x;
    int right = v[i + 1] - x;
    count += max(0, right - left + 1);
  }
  return count >= k;
}

void solve() {
  int n, k, x;
  cin >> n >> k >> x;
  vi v(n);
  fr(i, 0, n) cin >> v[i];
  sort(all(v));
  int m = v.size();
  int start = 0, end = x;
  int ans = 0;
  // Binary search for the maximum optimal minimum distance
  while (start <= end) {
    int mid = start + (end - start) / 2;
    if (check(mid, v, k, x)) {
      start = mid + 1;
      ans = mid;
    } else
      end = mid - 1;
  }
  // If no gap is needed, place teleports at 0,1,...,k-1
  if (ans == 0) {
    for (int i = 0; i < k; i++) {
      cout << i << " ";
    }
    cout << endl;
    return;
  }
  int count = k;
  // Place teleports from the left side
  int left = v[0] - ans;
  for (int i = 0; i <= left and count; i++) {
    cout << i << " ";
    count--;
  }
  // Place teleports between friends
  for (int i = 0; i < n - 1 and count; i++) {
    int left = v[i] + ans;
    int right = v[i + 1] - ans;
    while (left <= right and count) {
      cout << left << " ";
      left++;
      count--;
    }
  }
  // Place teleports from the right side
  int right = v[n - 1] + ans;
  for (int i = right; i <= x and count; i++) {
    cout << i << " ";
    count--;
  }
  cout << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/