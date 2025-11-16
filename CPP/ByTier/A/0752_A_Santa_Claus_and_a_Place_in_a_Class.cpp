// Problem: CF 752 A - Santa Claus and a Place in a Class
// https://codeforces.com/contest/752/problem/A

/*
 * Problem: Santa Claus and a Place in a Class
 * 
 * Purpose: Given the number of lanes (n), desks per lane (m), and the place number (k),
 *          determine the lane (r), desk (d), and side (L/R) of Santa's seat.
 * 
 * Algorithm:
 *  1. Calculate which lane Santa sits in based on the place number.
 *  2. Determine which desk in that lane Santa sits in.
 *  3. Determine if Santa sits on the left or right side of the desk.
 * 
 * Time Complexity: O(1) - constant time operations
 * Space Complexity: O(1) - only a few variables used
 */

#include <iostream>

typedef long long int ll;
#define pp pair<ll, ll>
#define max2(a, b) ((a < b) ? b : a)
#define max3(a, b, c) max2(max2(a, b), c)
#define min2(a, b) ((a > b) ? b : a)
#define min3(a, b, c) min2(min2(a, b), c)
using namespace std;

int main() {
  ll i, j, k;
  ll n, m, len;
  cin >> n >> m >> k;
  
  // Determine the lane number (1-indexed)
  // Each lane has 2 * m places (2 places per desk, m desks per lane)
  // We compute the lane by dividing k by (2 * m) and rounding up
  if (k % (2 * m) == 0)
    len = (k / (2 * m));
  else
    len = (k / (2 * m)) + 1;
  
  cout << len << " ";
  
  // Determine the desk number (1-indexed)
  // We calculate the index of the desk within the lane
  ll dd;
  if (k % 2 == 0)
    dd = k / 2;  // If k is even, it's the right side of a desk
  else
    dd = (k / 2) + 1;  // If k is odd, it's the left side of a desk
  
  // Traverse to find the desk number within the lane
  j = 1;  // Current desk number within the lane (1-indexed)
  for (i = 1; i <= dd; i++) {
    if (i == dd)
      cout << j << " ";  // Output the final desk number
    
    // Advance to next desk number
    if (j == m)
      j = 1;  // Reset to first desk if we reach the last desk
    else
      j++;   // Move to next desk
  }
  
  // Determine side: 'L' if k is odd (left side), 'R' if k is even (right side)
  if (k % 2 == 0)
    cout << 'R';
  else
    cout << 'L';
  
  return 0;
}


// https://github.com/VaHiX/CodeForces/