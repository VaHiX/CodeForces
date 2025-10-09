// Problem: CF 2136 F1 - From the Unknown (Easy Version)
// https://codeforces.com/contest/2136/problem/F1

/*
 * Problem: F1. From the Unknown (Easy Version)
 *
 * Purpose:
 *   This code attempts to determine the width parameter W of an interactive text editor
 *   by querying articles and observing how many lines they take to display.
 *
 * Algorithms/Techniques:
 *   - Binary search approach using two queries
 *   - First query checks if W >= some value (by using a large article)
 *   - Second query refines the estimate based on first result
 *
 * Time Complexity: O(1) per test case (fixed number of operations)
 * Space Complexity: O(1) (only uses constant extra space)
 */

#include <stddef.h>
#include <iostream>

#define lint long long
#define fi first
#define se second
using namespace std;
const int N = 2e5 + 5, INF = 1e9;
int mx = 100000;

void solve() {
  // First query: send a large article with all words having length 1
  cout << "? " << mx << " ";  
  for (int i = 1; i <= mx; ++i)
    cout << 1 << " ";  // Fill the article with ones (each word is 1 unit long)
  cout << endl;
  cout.flush();  // Ensure output is sent immediately

  int a;  // Number of lines returned from the first query
  cin >> a;

  if (a == 1) {
    // If it fits in one line, W must be at least mx
    cout << "! " << mx << endl;
    return;
  }

  // Calculate bounds for W based on the first query result
  int s = (mx + a - 1) / a;       // Lower bound estimation
  int t = (mx + (a - 1) - 1) / (a - 1);  // Upper bound estimation

  if (s + 1 == t) {
    // If s+1 == t, we have exact W value
    cout << "! " << s << endl;
    return;
  }

  // Second query: refine by constructing an article with carefully chosen words
  cout << "? " << (t - s - 1) * 2 << " ";  // Number of words in this query

  for (int i = 1; i <= t - s - 1; ++i) {
    cout << s << " " << i << " ";  // Send pairs of values to narrow down W
  }
  cout << endl;
  cout.flush();  // Send second query immediately

  int x;  // Lines returned from second query
  cin >> x;

  // Final answer calculation based on results of both queries
  cout << "! " << s + (t - s - 1) * 2 - x << endl;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int T = 1;
  cin >> T;
  while (T--)
    solve();
  return 0;
}


// https://github.com/VaHiX/codeForces/