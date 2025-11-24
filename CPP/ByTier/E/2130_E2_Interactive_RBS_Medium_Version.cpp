// Problem: CF 2130 E2 - Interactive RBS (Medium Version)
// https://codeforces.com/contest/2130/problem/E2

/*
Interactive RBS (Medium Version)
Algorithms/Techniques: Binary search, interactive problem solving, bit manipulation
Time Complexity: O(n * log n) - The algorithm uses a binary search-like approach with at most 200 queries per test case
Space Complexity: O(n) - Space used for storing the result and intermediate variables

The code determines a hidden bracket sequence of length n.
It uses query operations to identify which positions have a '(' or ')' character,
and then reconstructs the full sequence based on these findings.
*/
#include <algorithm>
#include <iostream>
#include <utility>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;
typedef pair<LL, LL> PII;
char ans[1010];
int st[1010];

// Function to query a range of indices and determine bits
void query(int l, int r) {
  int len = 1; // Length of the current string being built for the query
  cout << '?' << ' '
       << 2 * ((1 << (r - l + 1)) - 1) + (1 << (r - l + 1)) + (r - l + 1)
       << ' ';
  // Build a series of indices to query
  for (int i = l; i <= r; i++) {
    for (int j = 1; j <= len + 1; j++)
      cout << 1 << ' '; // Add index 1 (constant) for the first part of query format
    for (int j = 1; j <= len; j++)
      cout << i << ' '; // Use the current position (i) for the second part
    len = len * 2; // Double the length (this is a specific pattern to encode information)
  }
  len = len; // Unused assignment, could be removed
  // Add final part of the query (constant values)
  for (int i = 1; i <= len; i++)
    cout << 1 << ' ';
  cout << endl;
  int que;
  cin >> que; // Read back the result from query
  // Process each bit in the result and store it in st array
  for (int i = 0; i <= 10; i++) {
    if (que >> i & 1) {
      st[l + i] = 1;
    } else
      st[l + i] = 0;
  }
}

// Function to solve the interactive problem
void solve() {
  int n;
  cin >> n; // Read length of the bracket sequence
  int l = 2; // Start from position 2 (according to the problem constraints)
  while (l <= n) {
    int r = min(l + 5, n); // Take a window of at most 6 elements
    query(l, r); // Query this range
    l = r + 1; // Move to next unprocessed segment
  }
  int ok = 0;
  // Find the first position that contains a '(' (based on st array)
  for (int i = 2; i <= n; i++) {
    if (st[i] == 1) {
      ok = 1;
      cout << '?' << ' ' << 2 << ' ' << 1 << ' ' << i << endl; // Query to determine first character
      int que;
      cin >> que; // Read result of the query
      if (que == 1) { // If result is 1, first character is '('
        ans[1] = '(';
      } else { // Otherwise it's ')'
        ans[1] = ')';
      }
      break;
    }
  }
  cout << '!' << ' ';
  // Reconstruct the full sequence based on the information gathered
  for (int i = 1; i <= n; i++) {
    if (i == 1)
      cout << ans[1]; // Output first character
    else {
      if (st[i] == 1) { // If position is marked as containing '('
        if (ans[1] == '(')
          ans[i] = ')'; // Flip the bracket character to be opposite of first one
        else
          ans[i] = '(';
      } else { // Else use same character as first one
        ans[i] = ans[1];
      }
      cout << ans[i]; // Output each character
    }
  }
  cout << endl; // Final newline to end the output
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t = 1;
  cin >> t; // Read number of test cases
  while (t--) {
    solve(); // Solve each case
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/