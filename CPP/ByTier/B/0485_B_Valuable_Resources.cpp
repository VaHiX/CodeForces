// Problem: CF 485 B - Valuable Resources
// https://codeforces.com/contest/485/problem/B

/*
 * Problem: B. Valuable Resources
 * 
 * Purpose: Find the minimum area of a square city that can cover all mines.
 *          The city's sides are parallel to coordinate axes.
 * 
 * Algorithm/Techniques: 
 *   - Find the minimum and maximum x-coordinates of all mines.
 *   - Find the minimum and maximum y-coordinates of all mines.
 *   - The side length of the square is the maximum of the width and height.
 *   - The area is the square of the side length.
 * 
 * Time Complexity: O(n * log(n)) due to sorting.
 * Space Complexity: O(n) for storing the coordinates.
 */

#import <bits/stdc++.h>
using namespace std;
long long n, s, x[1005], y[1005];
int main() {
  cin >> n;
  for (int i = 0; i < n; i++)
    cin >> x[i] >> y[i];
  sort(x, x + n);    // Sort x-coordinates
  sort(y, y + n);    // Sort y-coordinates
  s = max(x[n - 1] - x[0], y[n - 1] - y[0]);  // Find the maximum extent in x or y
  cout << s * s;     // Output the area of the square
}


// https://github.com/VaHiX/CodeForces/