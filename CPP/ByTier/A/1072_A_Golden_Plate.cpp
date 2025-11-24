// Problem: CF 1072 A - Golden Plate
// https://codeforces.com/contest/1072/problem/A

/*
Task: A. Golden Plate
Purpose: Compute the number of cells to be gilded on a w×h rectangle with k gilded rings, each ring being 1 cell wide and placed 2 cells apart from each other.
Algorithms/Techniques: Simulation of gilding process by calculating perimeter of nested rectangles.
Time Complexity: O(k), where k is the number of rings.
Space Complexity: O(1), only using a few variables.
*/
#include <cstdio>
#include <iostream>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n");
#define nl printf("\n");
#define N 101010
#define inf 1e18
#define sf(n) scanf("%d", &n)
#define sff(n, m) scanf("%d%d", &n, &m)
#define sfl(n) scanf("%I64d", &n)
#define sffl(n, m) scanf("%I64d%I64d", &n, &m)
#define pf(n) printf("%d", n)
#define pff(n, m) printf("%d %d", n, m)
#define pffl(n, m) printf("%I64d %I64d", n, m)
#define pfl(n) printf("%I64d", n)
#define pfs(s) printf("%s", s)
#define pb push_back
#define pp pair<int, int>
using namespace std;

int main() {
  int i, j, k;
  int n, m;
  int w, h;
  sff(w, h); // Read width and height of the plate
  sf(k);     // Read number of rings to be gilded
  int cnt = 0; // Variable to store total gilded cells
  for (i = 1; i <= k; i++) {
    // For each ring, compute its perimeter and add to count
    cnt += (w * 2 + ((h - 2) * 2));
    w -= 4; // Reduce width by 4 for next inner ring (2 cells on each side)
    h -= 4; // Reduce height by 4 for next inner ring (2 cells on each side)
  }
  pf(cnt); // Print the total number of gilded cells
  return 0;
}


// https://github.com/VaHiX/codeForces/