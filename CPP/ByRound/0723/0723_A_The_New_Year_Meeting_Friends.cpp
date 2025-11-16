// Problem: CF 723 A - The New Year: Meeting Friends
// https://codeforces.com/contest/723/problem/A

/*
 * Problem: A. The New Year: Meeting Friends
 * 
 * Purpose: Find the minimum total distance three friends need to travel to meet at a single point.
 * 
 * Algorithm/Technique: 
 * - Sort the positions of the three friends.
 * - The optimal meeting point is between the first and third friend (after sorting).
 * - The minimum total distance is the difference between the third and first friend's position.
 * 
 * Time Complexity: O(1) - Sorting 3 elements is constant time.
 * Space Complexity: O(1) - Only using a fixed-size array and a few variables.
 */

#include <algorithm>
#include <iostream>

using namespace std;

int main() {
  int d[3];  // Array to store the positions of the three friends
  int i, s;  // Loop index and result variable
  
  // Read the three positions
  for (i = 0; i < 3; i++)
    cin >> d[i];
  
  // Sort the positions in ascending order
  sort(d, d + 3);
  
  // The minimum total distance is the difference between the last and first position
  s = d[2] - d[0];
  
  // Output the result
  cout << s;
  
  return 0;
}


// https://github.com/VaHiX/CodeForces/