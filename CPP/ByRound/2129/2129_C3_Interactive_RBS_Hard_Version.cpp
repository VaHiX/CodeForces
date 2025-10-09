// Problem: CF 2129 C3 - Interactive RBS (Hard Version)
// https://codeforces.com/contest/2129/problem/C3

/*
C3. Interactive RBS (Hard Version)
This is an interactive problem.

The task is to reconstruct a hidden bracket sequence of length n, consisting only of '(' and ')', 
using at most 100 queries. Each query allows picking k indices and returns the number of non-empty 
regular bracket substrings in the subsequence formed by those indices.

Algorithms:
- Binary search for the first '(' character using prefix queries.
- For the remaining part, uses a divide-and-conquer like approach with precomputed values to  
  determine whether each position should be '(' or ')'.

Time Complexity: O(N * log N) in the worst case due to binary searches and query cost
Space Complexity: O(N) for storing intermediate data structures

Techniques:
- Interactive problem handling with flushing output
- Use of prefix queries to determine bracket positions
- Precomputed mapping of counts and values to decode answers
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
#define ll long long
#define pb push_back
#define vi vector<int>
#define vpi vector<pair<int, int>>
#define vll vector<ll>
#define pqll priority_queue<ll>
const ll MOD = 1E9 + 7;

// Query function: sends a query to the interactor and receives result
ll query(vi entry) {
  cout << "? " << entry.size() << " ";
  for (auto x : entry)
    cout << x + 1 << " "; // Convert to 1-based indexing
  cout << "\n" << flush;
  ll r;
  cin >> r;
  return r;
}

void solve() {
  int N;
  cin >> N;
  int L, R;
  vi full;
  for (int i = 0; i < N; i++)
    full.pb(i);
  ll r = query(full); // Query entire sequence to find its structure
  if (r == 0) {       // If total number of valid substrings is zero, last bracket is ')'
    R = 0;
    L = N - 1;
  } else {
    // Do binary search to locate the first '(' by checking prefixes
    L = 0;
    R = N - 1;
    while (L != R - 1) {
      int M = (L + R) / 2;
      vi entry;
      for (int i = L; i <= M; i++)
        entry.pb(i);
      ll r = query(entry); // Query prefix [L, M]
      if (r == 0)
        L = M;       // No valid brackets here, so move right
      else
        R = M;       // Valid prefixes found, look left
    }
  }

  // Precomputed mapping tables for decoding answer bits efficiently
  vi cnt = {1, 2, 3, 5, 7, 10, 15, 21, 30, 43, 61, 87};
  vi val = {1, 3, 6, 15, 28, 55, 120, 231, 465, 946, 1891, 3828};

  vector<char> ans;
  for (int i = 0; i < N; i += 12) { // Process in chunks of 12 elements
    vi entry;
    for (int j = 0; j < 12; j++) {
      if (i + j >= N)
        break;
      // Generate appropriate queries based on precomputed mapping
      for (int k = 0; k < cnt[12 - j - 1]; k++) {
        entry.pb(i + j);
        entry.pb(R); // Always check against R (the position found to be first '(')
      }
      entry.pb(R);
    }

    ll r = query(entry); // Get combined result of all subqueries for this chunk

    int j = 11;  // Start from last element in the precomputed arrays
    while (j >= 0) {
      if (i + (12 - j - 1) >= N) { // Skip out-of-bounds
        break;
      }
      if (r >= val[j]) { // Check how much value we can subtract, which corresponds to '('
        r -= val[j];
        ans.pb('(');
      } else {
        ans.pb(')');
      }
      j--;
    }
  }
  cout << "! ";
  for (auto c : ans)
    cout << c;
  cout << "\n" << flush; // Print the final reconstructed bracket sequence
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;
  while (T--)
    solve();
}


// https://github.com/VaHiX/CodeForces/