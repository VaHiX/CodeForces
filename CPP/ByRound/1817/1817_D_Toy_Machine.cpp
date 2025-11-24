// Problem: CF 1817 D - Toy Machine
// https://codeforces.com/contest/1817/problem/D

/*
 * Problem: D. Toy Machine
 * 
 * Algorithm/Technique:
 * - Simulation-based approach to move a specific toy to the leftmost cell in the top row.
 * - Uses a sequence of moves (L, R, U, D) to manipulate toy positions.
 * - The solution constructs a path by carefully moving toys to the left, then back to the desired position.
 * 
 * Time Complexity: O(n)
 *   - The algorithm iterates through the number of cells (n) a few times, but in a linear fashion.
 *   - Each loop contributes at most O(n) operations.
 * 
 * Space Complexity: O(n)
 *   - The output string s stores the sequence of moves, which can be up to O(n) characters long.
 */

#include <stdlib.h>
#include <iostream>
#include <string>

using namespace std;
int a, b, c, d, e, i, j, ii, jj, zx, xc, K;
string s;

// Function to print the result and exit
void print() {
  cout << s;
  exit(0);
}

// Function to perform the main simulation logic after initial moves
void solve(int K) {
  while (K > 1) {
    K--;
    s += "DRUL";  // Append sequence of moves to shift toys
  }
  print();
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  cin >> a >> K;  // Read n and k

  // If k is in the left half, move left first to bring it closer
  if (K < (a + 1) / 2) {
    s += "L";
    solve(K);
  }

  // Move right to ensure the toy is in the right part of the row
  s += "R";
  while (K < a - 2) {
    K++;
    s += "DLUR";  // Move toy right by pushing it down and right
  }

  // Final adjustment to position the toy correctly
  s += "DRU";

  // Additional moves to adjust the toy position
  for (i = 1; i <= a / 2 + 5; i++) {
    s += "RDRU";  // Repeated right-down-up moves to stabilize
  }

  // Adjust the position of the K-th toy
  K = (a + 1) / 2 - 1;
  s += "LUL";
  solve(K);

  return 0;
}


// https://github.com/VaHiX/CodeForces/