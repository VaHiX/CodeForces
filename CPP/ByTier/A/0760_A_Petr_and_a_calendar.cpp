// Problem: CF 760 A - Petr and a calendar
// https://codeforces.com/contest/760/problem/A

/*
Purpose: This program calculates the number of columns needed for a calendar table based on the month and the weekday of the first day of that month.
         The calendar has rows for weekdays (Monday to Sunday) and columns for weeks.

Algorithm:
- Adjust the starting day to be Sunday-based for easier calculation.
- Based on the month, determine how many days are in that month.
- Count how many weeks (columns) are required by iterating from the first day to the end of the month,
  incrementing by 7 days (one week).
  
Time Complexity: O(1) - The number of iterations is bounded and does not depend on input size.
Space Complexity: O(1) - Only a constant amount of space is used.

Techniques:
- Case analysis based on month (28, 30, or 31 days)
- Loop-based column counting with step of 7
*/

#include <iostream>

using namespace std;
#define ll long long
#define endl "\n"
#define input cin >>
#define output cout <<
#define pb push_back
void fastIO() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
}
void solve() {
  int m, d;
  cin >> m >> d;
  d = 7 - d + 1; // Convert to Sunday-based indexing (1 = Sunday)
  if (m == 2) { // February has 28 days
    int cnt = 1;
    for (int i = d; i < 28; i += 7) // Iterate through the days, increment by 7
      cnt++;
    cout << cnt << endl;
  } else if (m == 4 || m == 6 || m == 9 || m == 11) { // April, June, September, November have 30 days
    int cnt = 1;
    for (int i = d; i < 30; i += 7) // Iterate through the days, increment by 7
      cnt++;
    cout << cnt << endl;
  } else { // All other months have 31 days
    int cnt = 1;
    for (int i = d; i < 31; i += 7) // Iterate through the days, increment by 7
      cnt++;
    cout << cnt << endl;
  }
}
int main() {
  fastIO();
  solve();
  return 0;
}


// https://github.com/VaHiX/CodeForces/