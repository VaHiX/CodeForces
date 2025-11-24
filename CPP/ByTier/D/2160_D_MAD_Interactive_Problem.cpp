// Problem: CF 2160 D - MAD Interactive Problem
// https://codeforces.com/contest/2160/problem/D

/*
Problem: D. MAD Interactive Problem
Algorithms/Techniques: Interactive problem solving using queries to determine a hidden sequence of integers from 1 to n, each appearing exactly twice.

Approach:
1. First phase: Use queries to find out which positions have elements that are duplicates (MAD > 0). For each position i, we query with increasing size k and all unused indices up to i, and if MAD returns a value > 0, we know one of those indices points to a duplicate element.
2. Second phase: Once duplicates are identified, query the remaining unknown indices to find their values by using known positions.

Time Complexity: O(n^2) in worst case due to nested loops in the first phase and second phase processing
Space Complexity: O(n) for storing used array and unknown indices

*/

#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;
#define el '\n'
#define pb push_back
#define pf push_front
#define ff first
#define ss second
#define mp make_pair
typedef long long ll;
typedef string str;
typedef vector<int> vi;
typedef pair<int, int> pi;
const int MOD = 1e9 + 7;
const int MAXN = 2e5;

void solve() {
  int n;
  cin >> n;
  int a[2 * n + 1]; // Array to store the answer
  vector<int> used(2 * n + 1, -1); // Track positions whose values are known (-1 means unknown)
  int k = 1; // Counter for queries
  int ans; // Result from query
  for (int i = 2; i <= 2 * n; i++) {
    k++; // Increment query count
    cout << "? " << k;
    for (int ind = 1; ind <= i; ind++) {
      if (used[ind] == -1) { // If position is not yet determined
        cout << " " << ind;
      }
    }
    cout << el;
    cout.flush(); // Flush output buffer
    cin >> ans; // Read result of query
    if (ans == 0) {
      continue; // No duplicate found, skip
    } else {
      used[i] = ans; // Mark the position as solved and store value
      k--; // Adjust counter since we got a result
    }
  }
  str known = " "; // String to build query for next phase
  vi unknown(n); // Vector to store positions that are yet to be determined
  int ind = 0;
  for (int i = 1; i <= 2 * n; i++) {
    if (used[i] != -1) {
      known += to_string(i) + " "; // Add known pos to string
    } else {
      unknown[ind] = i; // Mark as unknown
      ind++;
    }
  }
  for (int i = 0; i < n; i++) {
    cout << "? " << n + 1 << known << unknown[i] << el; // Query with n+1 elements to determine value
    cout.flush(); // Flush output buffer
    cin >> ans; // Read result
    used[unknown[i]] = ans; // Store the found value
  }
  cout << "! ";
  for (int i = 1; i <= 2 * n; i++) {
    cout << used[i] << " "; // Print final answer
  }
  cout << el;
  cout.flush(); // Flush output buffer
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/