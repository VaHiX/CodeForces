// Problem: CF 2120 A - Square of Rectangles
// https://codeforces.com/contest/2120/problem/A

/*
Problem: Arrange three rectangles to form a square
Algorithms/Techniques: Brute force checking of all possible arrangements
Time Complexity: O(1) - constant time due to fixed number of checks and small input constraints
Space Complexity: O(1) - only using a constant amount of extra space

Aryan is an ardent lover of squares but a hater of rectangles. Harshith gives him three rectangles 
with given dimensions. Aryan wants to arrange these rectangles to form a square without overlapping,
and rotations are not allowed.

Input format:
- t test cases
- For each case: l1 b1 l2 b2 l3 b3 (rectangles' dimensions)
- Rectangles are already sorted: l3 <= l2 <= l1 and b3 <= b2 <= b1

Output:
- "YES" if rectangles can form a square, "NO" otherwise
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long l1, b1, l2, b2, l3, b3;
    scanf("%ld %ld %ld %ld %ld %ld", &l1, &b1, &l2, &b2, &l3, &b3);
    bool ans(false);
    
    // Check arrangement 1: All rectangles aligned along one side to form a square
    if (l1 + l2 + l3 == b1 && b1 == b2 && b2 == b3) {
      ans = true;
    } else if (l2 + l3 == l1 && b2 == b3 && b1 + b2 == l1) {
      // Check arrangement 2: Two rectangles stacked vertically, third next to them
      ans = true;
    } else if (b1 + b2 + b3 == l1 && l1 == l2 && l2 == l3) {
      // Check arrangement 3: All rectangles aligned horizontally
      ans = true;
    } else if (b2 + b3 == b1 && l2 == l3 && l1 + l2 == b1) {
      // Check arrangement 4: Two rectangles stacked horizontally, third above them
      ans = true;
    }
    
    puts(ans ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/