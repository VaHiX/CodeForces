// Problem: CF 976 B - Lara Croft and the New Game
// https://codeforces.com/contest/976/problem/B

/*
Purpose: Determine Lara Croft's current position in a dungeon after moving k steps in a predefined snake-like pattern.
Algorithm: 
  - The dungeon is traversed in a snake-like fashion:
    - Go down from (1,1) to (n,1)
    - Then move right to (n, m), then up one step to (n-1, m), then left to (n-1, 1)
    - Repeat until all cells are visited.
  - The path is treated as a series of segments:
    - First segment: go down the leftmost column (n steps)
    - Then each subsequent segment: move right or left in a snake pattern
    - Each "row" of snake has (m - 1) cells, except possibly the last.
Time Complexity: O(1) - Constant time calculation
Space Complexity: O(1) - Only a few variables are used
*/

#include <cstdio>
typedef long long ll;
ll n, m, k, x, y;
int main() {
  ll n, m, k;
  scanf("%lld %lld %lld", &n, &m, &k);
  if (k < n) {
    // If k is less than n, Lara is still moving down the leftmost column
    printf("%lld 1\n", k + 1);
  } else {
    // Subtract the steps used in the first column
    k -= n;
    // Determine which "row" in the snake pattern we're on
    ll x = k / (m - 1);
    // Adjust the row number based on the snake direction
    x = n - x;
    // Determine column within that "row"
    ll y = k % (m - 1);
    // Adjust column depending on snake direction (zigzag)
    if (x % 2) {
      // Going left: reverse the column
      y = m - y;
    } else {
      // Going right: shift by 2 to align with the grid
      y += 2;
    }
    printf("%lld %lld\n", x, y);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/