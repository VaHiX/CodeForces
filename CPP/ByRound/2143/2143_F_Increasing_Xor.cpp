// Problem: CF 2143 F - Increasing Xor
// https://codeforces.com/contest/2143/problem/F

/*
F. Increasing Xor
Algorithm: Using Gaussian elimination with XOR operations to maintain a basis of the subarray and determine if it can be made strictly increasing.

Time Complexity: O(n * B^2 + q) where B = 20 (bits), n is length of array, q is number of queries.
Space Complexity: O(n * B) for storage of basis vectors.

The problem allows operations of the form a_j = a_j XOR a_i where indices i and j are within a range [l,r].
We need to determine whether subarray [l,r] can be transformed into strictly increasing sequence using such operations.
This is essentially checking if we can make all elements in the subarray strictly increasing by applying XOR operations on elements within that range.

The key idea is to maintain a linear basis (Gaussian elimination style) of the current state, which allows us to know the maximum possible value we can achieve with the current set. 
If we can reach the required strictly increasing sequence, it implies the answer is YES.
*/

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
const int N = 200005;
const int B = 21;
int n, q;
int a[N];
int l, r;
int max_r[N];

void solve() {
  scanf("%d%d", &n, &q);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }
  vector<int> b(B, 0); // Basis vectors for Gaussian elimination
  vector<pair<int, int>> t; // Current set of indices with their basis bits
  for (int i = n - 1; i >= 0; i--) {
    int x = a[i];
    reverse(t.begin(), t.end()); // Reverse current set before adding new element
    t.push_back({i, 0}); // Add new element at index i with bit index 0
    reverse(t.begin(), t.end()); // Reverse back
    vector<pair<int, int>> tmp; // Temporary vector to hold updated basis elements
    b.assign(B, 0); // Reset basis vector
    
    // Process all current elements in the set with Gaussian elimination
    for (int k = 0; k < t.size(); k++) {
      int x = a[t[k].first];
      for (int j = B - 1; j >= 0; j--) {
        if ((x >> j) & 1) { // If bit j is set in x
          if (b[j]) // If basis already has an element with this bit
            x ^= b[j]; // Reduce with existing basis
          else {
            b[j] = x; // Add x to the basis
            tmp.push_back({t[k].first, j}); // Store this element with its bit index
            break;
          }
        }
      }
    }
    
    swap(t, tmp); // Update t with new basis elements
    
    bool ok = false; // Whether we can make increasing sequence
    int c = -1, ans = 0; // c tracks intermediate values
    vector<int> s; // Stores bit indices of current basis
    
    for (int j = 0; j < t.size(); j++) {
      if (c != -1) {
        int z = 0, y = 0;
        // Compute how many bits to shift and XOR with y
        for (int k = j - 1; k >= 0; k--) {
          if (t[k].second < t[j].second)
            z++; // Count how many lower bits are in a different position
          if (((c >> k) & 1) != ((y >> s[k]) & 1))
            y ^= b[s[k]];
        }
        c = ((c >> z) << (z + 1)) | (c & ((1 << z) - 1)); // Adjust c to shift bits correctly
        if ((y >> t[j].second) & 1)
          c |= 1 << z; // Add bit to c if required
      }
      
      s.push_back(t[j].second); // Add current bit to list of basis bit indices
      
      // Re-sort s in ascending order for processing later
      for (int k = (int)s.size() - 2; k >= 0; k--) {
        if (s[k] > s[k + 1])
          swap(s[k], s[k + 1]);
        else
          break;
      }
      
      // Check if we can complete the transformation
      if (j == t.size() - 1) {
        if ((1 << (j + 1)) - c - 1 < n - t[j].first) {
          ok = true; // We can transform within range
          max_r[i] = i + ans + (1 << (j + 1)) - c - 1 - 1;
          break;
        } else
          c += n - t[j].first, ans += n - t[j].first;
      } else {
        if ((1 << (j + 1)) - c - 1 < t[j + 1].first - t[j].first) {
          ok = true;
          max_r[i] = i + ans + (1 << (j + 1)) - c - 1 - 1;
          break;
        } else
          c += t[j + 1].first - t[j].first, ans += t[j + 1].first - t[j].first;
      }
    }
    
    if (!ok) // If we cannot transform
      max_r[i] = n - 1; // Set maximum reachable index as end of array
  }
  
  while (q--) {
    scanf("%d%d", &l, &r);
    l--, r--; // Convert to 0-based indexing
    
    if (max_r[l] >= r) // Check if range can be made strictly increasing
      printf("YES\n");
    else
      printf("NO\n");
  }
}

int main() {
  int yt = 1;
  cin >> yt; // Read number of test cases
  while (yt--) {
    solve(); // Process each test case
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/