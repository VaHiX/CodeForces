// Problem: CF 1662 N - Drone Photo
// https://codeforces.com/contest/1662/problem/N

/*
Problem: N. Drone Photo
Algorithm: Count valid axis-aligned rectangle configurations where two younger contestants hold one pole and two older contestants hold another, such that the poles do not cross.

Time Complexity: O(n^2)
Space Complexity: O(n^2)

Approach:
- The code iterates through all values from 1 to n*n in increasing order.
- For each value, it finds its position (row, col).
- It uses counters l[.] and c[.] to track how many elements have been processed in each row and column so far.
- For each element, it counts how many previously processed elements are in the same row or column - these can form valid rectangles.
- The count of valid rectangles is computed using the formula based on total pairs and invalid ones.

Variables:
- v[i][j]: ages of contestants at position (i,j)
- poz[i]: stores position of contestant with age i
- l[i], c[i]: counters for number of elements in row/column i already processed
- t: cumulative count of valid rectangles formed so far
- nrd: total possible rectangles = n*n*(n-1)*(n-1)/4
- drp: valid rectangles that are "good", i.e., non-crossing
- drb: invalid rectangles, i.e., crossing poles

Key Insight:
The condition that poles don't cross is equivalent to checking if elements at positions (r1,c1) and (r2,c2) form a valid rectangle (i.e., r1 != r2 and c1 != c2) such that the smaller ages are in one pair and larger ages in another, making the configuration valid.
*/

#include <iostream>
using namespace std;
long long nrd, t, drp, drb;
int n, i, j, v[1501][1501];
struct pozitie {
  int l, c;
};
pozitie poz[2250001]; // Array to store positions of elements with ages from 1 to n*n
int l[1501], c[1501]; // Counters for number of elements seen in each row and column

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cin >> n;
  // Read input matrix
  for (i = 1; i <= n; i++) {
    for (j = 1; j <= n; j++) {
      cin >> v[i][j];
      poz[v[i][j]] = {i, j}; // Store position of each age value
    }
  }

  // Process all ages from 1 to n*n in increasing order
  for (i = 1; i <= n * n; i++) {
    // t counts valid pairs: number of elements already processed that lie in same row or column as current element
    t += l[poz[i].l] * c[poz[i].c];
    l[poz[i].l]++; // Increment row counter
    c[poz[i].c]++; // Increment column counter
  }

  // Total possible arrangements that can form rectangles with the given constraints
  nrd = 1ll * n * n * (n - 1) * (n - 1) / 4;

  // Subtract invalid cases from total to get valid ones
  drp = t - nrd; // Invalid configurations (crossing poles)
  drb = nrd - drp; // Valid configurations (non-crossing poles)

  cout << drb;
  return 0;
}


// https://github.com/VaHiX/codeForces/