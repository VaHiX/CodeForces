// Problem: CF 1806 A - Walking Master
// https://codeforces.com/contest/1806/problem/A

/*
Problem: Walking Master
Time Complexity: O(1) per test case
Space Complexity: O(1)

Algorithms/Techniques: 
- Greedy approach with mathematical analysis of moves
- Uses the fact that in one move, we can either go (x+1,y+1) or (x-1,y)
- The minimum number of moves depends on the difference in x and y coordinates,
  and checking if such a path is even possible.

Key insight:
- From (a,b) to (c,d), the required change in x-coordinate is (c - a) and in y is (d - b).
- Each move can increase y by 1 (going right-up) or decrease x by 1 (going left).
- The minimum moves are calculated based on how much vertical distance can be covered
  by diagonal moves, then adding the horizontal adjustment needed.

*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long a, b, c, d;
    scanf("%ld %ld %ld %ld", &a, &b, &c, &d);
    // Check if it's impossible to reach destination
    // If vertical distance is too large or not enough horizontal movement to cover difference
    if ((b > d) || ((d - b) < (c - a))) {
      puts("-1");
      continue;
    }
    // Calculate minimum moves:
    // 2*(d-b) accounts for diagonal moves needed to cover vertical distance
    // (a-c) is the horizontal offset we must adjust after moving diagonally
    long res = 2 * (d - b) + (a - c);
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/