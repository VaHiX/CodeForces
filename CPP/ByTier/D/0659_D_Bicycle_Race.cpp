// Problem: CF 659 D - Bicycle Race
// https://codeforces.com/contest/659/problem/D

/*
D. Bicycle Race
Algorithm: The problem requires identifying "dangerous turns" on a bicycle track.
A turn is dangerous if, by continuing straight (ignoring the turn), the rider would enter the water.
The track is a polygon defined by n+1 points, where each consecutive pair defines a straight section.
The first section goes north, and we ensure that there are no conflicting or invalid turns due to constraints.
We process all turns in a loop, checking for each turn if the turn angle leads into water.
Time Complexity: O(n), since we iterate through the turns once.
Space Complexity: O(1), only using a constant amount of extra space.
*/

#include <iostream>
int main() {
  long n;
  std::cin >> n;
  std::cout << ((n - 4) / 2) << std::endl; // Output the number of dangerous turns
  return 0;
}


// https://github.com/VaHiX/codeForces/