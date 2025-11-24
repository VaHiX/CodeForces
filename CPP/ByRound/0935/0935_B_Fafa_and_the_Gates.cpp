// Problem: CF 935 B - Fafa and the Gates
// https://codeforces.com/contest/935/problem/B

/*
 * Problem: Fafa and the Gates
 * Purpose: Calculate the number of silver coins Fafa needs to pay while walking through kingdoms
 *           based on a sequence of moves. A coin is paid only when crossing from one kingdom to another.
 * 
 * Algorithm:
 * - Simulate the path of Fafa moving in the first quadrant (x >= 0, y >= 0).
 * - The wall is along the line x = y.
 * - Each move is either 'U' (up) or 'R' (right).
 * - A coin is paid if the path goes from one kingdom to another (i.e., crosses the wall x = y).
 * - The cost is incremented only when the current position (after move) is on a different kingdom
 *   than the previous kingdom (i.e., when x != y before and after moving).
 * 
 * Time Complexity: O(n) where n is the number of moves
 * Space Complexity: O(1) (we only use a few variables, no extra data structures)
 */

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n")
#define nl printf("\n");
#define N 15
#define inf 100000
#define pp pair<char, char>
using namespace std;

int main() {
  int i, j, k;
  int n, m;
  int x, y;
  int a, b;
  int x0, y0;
  string s;
  cin >> n; // Read number of moves
  cin >> s; // Read the sequence of moves
  ll cnt = 0; // Counter for the number of coins needed
  x = 0, y = 0; // Starting position (0, 0)
  
  // Initialize position after first move
  if (s[0] == 'R')
    x++; // If first move is right, increment x
  else
    y++; // If first move is up, increment y
  
  x0 = 0, y0 = 0; // Previous position initialized
  
  // Loop through the remaining moves
  for (i = 1; i < n; i++) {
    a = x, b = y; // Store current coordinates
    if (s[i] == 'R')
      a++; // Move right -> increment x
    else
      b++; // Move up -> increment y
    
    if (a == b) {
      // If we're on the wall (x == y), update previous position
      x0 = x;
      y0 = y;
      x = a;
      y = b;
    } else {
      // If we're not on the wall, check if we crossed the gate
      if (x == y) {
        // If we were on the wall and now we're not, check if the gate was visited
        if (abs(a - x0) >= 2 || abs(b - y0) >= 2)
          cnt++; // Increment coin count if we're jumping over a gate
      }
      x0 = x; // Update previous x
      y0 = y; // Update previous y
      x = a;  // Update current x
      y = b;  // Update current y
    }
  }
  printf("%I64d", cnt); // Print the final coin count
  return 0;
}


// https://github.com/VaHiX/CodeForces/