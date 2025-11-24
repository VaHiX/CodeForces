// Problem: CF 2126 C - I Will Definitely Make It
// https://codeforces.com/contest/2126/problem/C

/*
Problem: C. I Will Definitely Make It

Purpose:
This code determines whether it's possible to reach the tallest tower from a given starting tower,
while avoiding being submerged by rising water levels. Each second, the water level rises by 1,
and if the water level exceeds the current tower's height, the player dies.

Algorithms/Techniques:
- Sorting the heights to process them in ascending order
- Greedily moving to each tower in increasing order of height,
  accumulating time needed for teleportation and checking if water will overflow before arrival

Time Complexity: O(n log n) due to sorting, where n is the number of towers.
Space Complexity: O(1) additional space (excluding input storage)

*/
#include <stdint.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
#define int long long
#define fast_io                                                                \
  ios::sync_with_stdio(false);                                                 \
  cin.tie(nullptr);

void solve() {
  int n, k, height(0), time(0);
  cin >> n >> k;
  vector<int> a(n);
  for (int &x : a)
    cin >> x; // Read tower heights

  height = a[k - 1]; // Initial position is at tower k (1-indexed)
  sort(a.begin(), a.end()); // Sort towers by height in ascending order

  for (int x : a) {
    if (x > height) { // Only move to taller towers
      time += x - height; // Time needed to teleport from current height to new height
      if (time > height) { // If the accumulated time exceeds current height, water will overflow
        cout << "NO\n";
        return;
      }
      height = x; // Update current height to new tower's height
    }
  }
  cout << "YES\n"; // Successfully reached all towers without dying
}

int32_t main() {
  fast_io;
  int t = 1;
  cin >> t;
  while (t--)
    solve();
}


// https://github.com/VaHiX/codeForces/