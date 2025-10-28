// Problem: CF 2129 C2 - Interactive RBS (Medium Version)
// https://codeforces.com/contest/2129/problem/C2

/*
C2. Interactive RBS (Medium Version)
Interactive problem to reconstruct a hidden bracket sequence of length n.
Uses binary search to find a position where a '(' occurs, then uses bit manipulation
and queries to build the full bracket sequence.

Algorithms/Techniques:
- Binary Search to locate a '(' in the sequence
- Bit Manipulation and Query-based Reconstruction
- Interactive Problem Solving with limited queries

Time Complexity: O(n * log n) - due to binary search and query processing.
Space Complexity: O(n) - for storing the final string s.

*/
#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;
const int N = 1005;
int t, n;

void ask() {
  cin >> n;
  int l = 1, r = n;
  // Binary search to find a '('
  while (l <= r) {
    int mid = l + r >> 1; // Midpoint calculation using bit shift
    printf("? %d", mid);  // Query with 'mid' indices
    for (int i = 1; i <= mid; i++) {
      printf(" %d", i);
    }
    cout << endl;
    int y;
    cin >> y;  // Get result of query
    if (y) {
      r = mid - 1;
    } else
      l = mid + 1;
  }
  // If no '(' found, adjust l to 1
  if (l == n + 1) {
    l = 1;
  }
  string s;
  // Process the sequence in chunks of 7 characters for reconstruction
  for (int i = 1; i <= n; i += 7) {
    int ll = i, rr = min(n, ll + 6);  // Determine chunk boundaries
    // Calculate a bitmask-like query structure based on chunk size
    printf("? %d", ((1 << (rr - ll + 2)) - 1) + (rr - ll));
    int num = 1;  // Counter for doubling pattern
    for (int j = 0; j < rr - ll + 1; j++) {
      for (int k = 1; k <= num; k++)
        cout << " " << i + j;  // Add indices that will form pairs
      for (int k = 1; k <= num; k++)
        cout << " " << l;      // Add index of previously found '('
      cout << " " << l;         // Additional index for pairing
      num *= 2;                 // Double the count for next iteration
    }
    cout << endl;
    int y;
    cin >> y;  // Get result from query
    // Extract bits to decide between '(' and ')' for each position
    int z = rr - ll + 1;
    for (; z; z--, y >>= 1) {  // Process bits from least significant
      if (y & 1) {
        s += "(";
      } else
        s += ")";
    }
  }
  cout << "! " << s << endl;  // Output final bracket sequence
  return;
}

int main() {
  cin >> t;
  while (t--) {
    ask();
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/