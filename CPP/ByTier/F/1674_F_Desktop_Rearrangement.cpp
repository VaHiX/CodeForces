// Problem: CF 1674 F - Desktop Rearrangement
// https://codeforces.com/contest/1674/problem/F

/*
Code Purpose:
This program solves the problem of rearranging icons on a desktop to make it "good" with minimum moves.
A "good" desktop means all icons form a prefix of full columns and possibly a prefix of the next column.
The solution uses a Binary Indexed Tree (Fenwick Tree) to efficiently track and update icon positions.

Algorithms/Techniques:
- Binary Indexed Tree (Fenwick Tree) for efficient prefix sum queries and updates
- Coordinate compression to map 2D coordinates to 1D array indices
- Greedy approach to calculate minimum moves needed to make desktop good

Time Complexity: O(q * log(n*m)) where q is the number of queries, n and m are dimensions of the desktop
Space Complexity: O(n*m) for the BIT and the input storage

*/
#include <iostream>
#include <string>

using namespace std;

int bit[1000001], n; // BIT array and size variable

// Function to calculate prefix sum up to index i
int sum(int i) {
  int r = 0;
  for (; i; i -= (i & -i)) // Traverse using LSB trick
    r += bit[i];
  return r;
}

// Function to update BIT at index i by value v
void upd(int i, int v) {
  for (; i <= n; i += (i & -i)) // Update using LSB trick
    bit[i] += v;
}

int main() {
  int h, w, q, c = 0, x, y; // h=rows, w=columns, q=queries, c=count of icons
  cin >> h >> w >> q;
  n = h * w + 1; // Size of BIT array
  string s;
  
  // Initialize the desktop and update BIT with initial icon positions
  for (int i = 0; i < h; i++) {
    cin >> s;
    for (int j = 0; j < w; j++)
      if (s[j] == '*') { // If icon found
        c++; // Increment icon count
        upd(j * h + i + 1, 1); // Update BIT with this position (mapped to 1D)
      }
  }
  
  // Process each query
  while (q--) {
    cin >> x >> y; // Read query coordinates (1-indexed)
    
    // Check if the position has an icon using prefix sum
    if ((sum((y - 1) * h + x) - sum((y - 1) * h + x - 1)) == 1) {
      // Icon exists at this position, so remove it
      c--;
      upd((y - 1) * h + x, -1); // Update BIT
    } else {
      // No icon exists, so add one
      c++;
      upd((y - 1) * h + x, 1); // Update BIT
    }
    
    // Calculate and print minimum moves needed
    // This is calculated as total icons minus the largest prefix of icons
    cout << c - sum(c) << endl;
  }
}


// https://github.com/VaHiX/CodeForces/