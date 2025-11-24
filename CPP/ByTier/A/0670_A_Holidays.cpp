// Problem: CF 670 A - Holidays
// https://codeforces.com/contest/670/problem/A

/*
 * Code Purpose: 
 *   This program calculates the minimum and maximum possible number of 
 *   days off in a Martian year, given that a Martian year has n days and 
 *   the Martian week consists of 5 work days followed by 2 days off.
 * 
 * Algorithm:
 *   - A complete Martian week (7 days) always contains exactly 2 days off.
 *   - For a year of n days, we compute how many complete weeks fit in n,
 *     and then examine the remainder (n % 7) to determine how many additional
 *     days off are possible in the partial week.
 *   - Minimum days off: Assign the remainder days to work days where possible,
 *     minimizing extra days off.
 *   - Maximum days off: Assign the remainder days to days off where possible,
 *     maximizing extra days off.
 * 
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 */

#include <iostream>

typedef long long int ll;
#define max2(a, b) ((a < b) ? b : a)
#define max3(a, b, c) max2(max2(a, b), c)
#define min2(a, b) ((a > b) ? b : a)
#define min3(a, b, c) min2(min2(a, b), c)
using namespace std;

int main() {
  ll n;
  cin >> n;
  
  // If n is divisible by 7, all weeks are complete, so days off = 2 * (n / 7)
  if (n % 7 == 0)
    cout << (n / 7) * 2 << " " << (n / 7) * 2 << endl;
  else {
    // Determine the remainder of days after complete weeks
    ll remainder = n % 7;
    
    // If remainder >= 6, we can add 1 or 2 extra days off
    if (n % 7 >= 6)
      cout << (2 * (n / 7)) + 1 << " " << (2 * (n / 7)) + 2;
    // If 2 <= remainder <= 5, we can add up to 2 extra days off
    else if (n % 7 <= 5 && n % 7 >= 2)
      cout << (n / 7) * 2 << " " << (2 * (n / 7)) + 2;
    // If remainder < 2, we can add at most 1 extra day off
    else if (n % 7 < 2)
      cout << (n / 7) * 2 << " " << (2 * (n / 7)) + 1;
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/