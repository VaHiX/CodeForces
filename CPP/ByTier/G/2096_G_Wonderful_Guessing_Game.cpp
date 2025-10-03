// Problem: CF 2096 G - Wonderful Guessing Game
// https://codeforces.com/contest/2096/problem/G

/*
G. Wonderful Guessing Game
Time Complexity: O(n log n) per test case
Space Complexity: O(n) 

This problem uses a divide-and-conquer strategy to construct a set of queries that can determine 
the hidden number in the minimum possible number of queries, f(n). The strategy is based on 
recursive partitioning where each level divides the search space into three parts:
- Left segment (marked as 1)
- Middle segment (not part of any query - marked as 0)
- Right segment (marked as 2)

The algorithm builds a ternary tree-like structure and for each level, assigns elements to 
different segments based on how they should be divided. Then, it constructs k-element arrays 
with even length that split the numbers into left and right parts in order to determine
the final answer.

Key techniques:
- Ternary partitioning using recursive calls
- Encoding query structure via array markings
- Adaptive querying with precomputed responses
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#define F first
#define S second
#define all(x) x.begin(), x.end()
#define pb push_back
#define FIO                                                                    \
  ios_base::sync_with_stdio(false);                                            \
  cin.tie(0);                                                                  \
  cout.tie(0)
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
const int N = 2e5 + 7;
int a[20][N];

// Recursive function to mark the divisions in an array.
void f(int l, int r, int d) {
  if (l >= r)
    return;
  int m = (r - l + 2) / 3; // Calculate the size of left/right parts
  for (int i = l; i < l + m; i++)
    a[d][i] = 1; // Mark elements in left part as 1 (Left query)
  for (int i = r - m + 1; i <= r; i++)
    a[d][i] = 2; // Mark elements in right part as 2 (Right query)
  f(l, l + m - 1, d + 1);      // Recursively process left segment
  f(l + m, r - m, d + 1);      // Recursively process middle segment
  f(r - m + 1, r, d + 1);      // Recursively process right segment
}

void task() {
  int n;
  cin >> n;
  for (int i = 0; i < 20; i++)
    fill(a[i], a[i] + n, 0);
  int q = 0, qq = 1;
  while (qq < n)
    qq *= 3, q++; // Determine number of levels needed
  f(0, n - 1, 0);   // Start the recursive marking process

  // Sum up the markings and apply modulo 3 logic to determine final assignments
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < q; j++)
      a[q][i] += a[j][i]; // Accumulate marking levels
    a[q][i] = (3 - a[q][i] % 3) % 3; // Final mapping to 0/1/2
  }

  cout << q + 1 << endl;

  vector<int> ok(n, 1);

  // Output the constructed queries for each level of recursion
  for (int i = 0; i <= q; i++) {
    vector<int> u, v;
    for (int j = 0; j < n; j++) {
      if (a[i][j] == 1)
        u.pb(j + 1); // Collect elements belonging to left query part
      if (a[i][j] == 2)
        v.pb(j + 1); // Collect elements belonging to right query part
    }
    cout << u.size() + v.size() << " ";
    for (int x : u)
      cout << x << " ";
    for (int x : v)
      cout << x << " ";
    cout << endl;
  }

  string s;
  cin >> s; // Read the responses from Alice

  // Process responses to filter out impossible numbers
  for (int i = 0; i <= q; i++) {
    if (s[i] == 'L') {
      for (int j = 0; j < n; j++)
        if (a[i][j] != 1) // If a number doesn't belong to left part, it's invalid
          ok[j] = 0;
    } else if (s[i] == 'R') {
      for (int j = 0; j < n; j++)
        if (a[i][j] != 2) // If a number doesn't belong to right part, it's invalid
          ok[j] = 0;
    } else if (s[i] == 'N') {
      for (int j = 0; j < n; j++)
        if (a[i][j]) // If a number is in any query part, it's invalid
          ok[j] = 0;
    }
  }

  // Output the final determined number
  for (int i = 0; i < n; i++)
    if (ok[i]) {
      cout << i + 1 << endl;
      break;
    }
}

int main() {
  FIO;
  int tt;
  cin >> tt;
  while (tt--)
    task();
  return 0;
}


// https://github.com/VaHiX/codeForces/