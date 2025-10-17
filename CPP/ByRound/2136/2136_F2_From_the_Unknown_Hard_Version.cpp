// Problem: CF 2136 F2 - From the Unknown (Hard Version)
// https://codeforces.com/contest/2136/problem/F2

/*
F2. From the Unknown (Hard Version)
Algorithms/Techniques: Binary search with adaptive queries, interactive problem solving

Time Complexity: O(log W) per test case, where W <= 10^5
Space Complexity: O(1) excluding input/output buffers

This is an interactive problem to determine the unknown width parameter W of the RiOI Editor.
The approach uses two queries:
1. First query to determine if W is small or large (by checking with a batch of words of fixed length)
2. Second query to binary search in a narrowed range for exact value of W

*/

#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

// Function to query the editor with an article
int q(const vector<int> &a) {
  int n = a.size();
  if (n == 0) {
    return 1;
  }
  if (n < 0 || n > 100000) {
    return 0;
  }
  cout << "? " << n;
  for (int x : a) {
    cout << " " << x;
  }
  cout << endl;
  int r;
  cin >> r;
  if (r == -1) {
    exit(0);
  }
  return r;
}

// Solve function to determine value of W
void solve() {
  const int N = 11343; // A large number of words used in first query
  const int B = 116;   // Base length for words in first query
  const int WMAX = 100000;
  
  vector<int> a1(N, B); // First article with many words of same length
  int r1 = q(a1);       // Query first article
  
  if (r1 == 0) {
    // If editor cannot display first article, all words are larger than W
    int m = B * B; // Total length in second article
    vector<int> a2(m, 1); // Article with many small words
    int r2 = q(a2);       // Query second article to find W
    int w = (m - 1) / (r2 - 1); // Calculate W from results
    cout << "! " << w << endl;
  } else {
    // If editor can display first article, we narrow down the range for W
    int kL = (N - 1) / r1 + 1;   // Lower bound estimate of k (number of words that fit in one line)
    int kH = (r1 == 1) ? WMAX : (N - 1) / (r1 - 1); // Upper bound estimate
    
    int L = kL * B;              // Left boundary of W range
    int R = min(WMAX, (kH + 1) * B - 1); // Right boundary of W range

    if (L == R) {
      cout << "! " << L << endl;
      return;
    }
    
    // Prepare a second article for binary search in the narrowed range
    vector<int> a2;
    a2.reserve(2 * (R - L));     // Reserve space for efficient memory usage
    
    // Constructing second query to narrow down W
    for (int x = 1; x <= R - L; ++x) {
      a2.push_back(L);   // First part of pair: fixed start value
      a2.push_back(x);   // Second part of pair: increasing small values
    }
    
    int r2 = q(a2);   // Query second article
    int W = 2 * R - L - r2; // Compute final W based on results
    
    cout << "! " << W << endl;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/