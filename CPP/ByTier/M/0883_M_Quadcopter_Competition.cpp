// Problem: CF 883 M - Quadcopter Competition
// https://codeforces.com/contest/883/problem/M

/*
Code Purpose:
This program calculates the minimal length of a closed path a quadcopter must take to go from a starting point to a flag and return to the starting point. The path is constrained to move only vertically or horizontally (parallel to the axes), one unit per step. The flag must be strictly inside the path.

Algorithm:
The key insight is that the minimal closed path forming a cycle that contains the flag is a rectangle around the flag with an additional buffer to ensure the flag is strictly inside. The path is calculated based on Manhattan distances from the start to the flag and then expanding the path by at least one unit in all directions to meet the "strictly inside" requirement.

Time Complexity: O(1) - The solution performs a constant number of operations.
Space Complexity: O(1) - Only a constant amount of space is used.
*/

#import <bits/stdc++.h>
using namespace std;
int a, b, c, d;
int main() {
  cin >> a >> b >> c >> d; // Read starting point (a,b) and flag point (c,d)
  a = abs(a - c), b = abs(b - d); // Calculate Manhattan distance in x and y directions
  cout << 2 * (a + !a + b + !b + 2); // Output the minimal path length using derived formula
}


// https://github.com/VaHiX/CodeForces/