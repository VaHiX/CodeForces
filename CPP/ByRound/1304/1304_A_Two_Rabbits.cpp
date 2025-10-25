// Problem: CF 1304 A - Two Rabbits
// https://codeforces.com/contest/1304/problem/A

/*
Problem: A. Two Rabbits
Algorithm: Mathematical simulation to determine if two rabbits moving towards each other will meet.
Time Complexity: O(t), where t is the number of test cases.
Space Complexity: O(1)

The problem involves two rabbits moving on a horizontal line:
- The taller rabbit starts at position x and moves forward by 'a' units per second.
- The shorter rabbit starts at position y and moves backward by 'b' units per second.
We need to find the time (in seconds) when they meet, or return -1 if they never do.

The mathematical approach:
Let t be the number of seconds after which they meet.
Position of taller rabbit = x + a * t
Position of shorter rabbit = y - b * t

For them to meet:
x + a * t = y - b * t
a * t + b * t = y - x
t * (a + b) = y - x
t = (y - x) / (a + b)

If (y - x) is divisible by (a + b), then t is an integer and they meet after t seconds.
Otherwise, they never meet.

Input Format:
- First line: number of test cases t
- For each test case: four integers x, y, a, b

Output Format:
- For each test case: print the time in seconds or -1 if they don't meet.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long x, y, a, b;
    scanf("%ld %ld %ld %ld\n", &x, &y, &a, &b);
    long dist = y - x;     // Distance between the rabbits
    long step = a + b;     // Combined steps per second
    printf("%ld\n", (dist % step) ? (-1) : (dist / step));  // Check divisibility and output result
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/