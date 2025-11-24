// Problem: CF 750 B - New Year and North Pole
// https://codeforces.com/contest/750/problem/B

/*
Purpose: To determine if a sequence of movements on a spherical Earth (with poles at 0 and 20000 km) adheres to specific rules:
1. Start at North Pole (0 km).
2. At North Pole, only allowed to move South.
3. At South Pole (20000 km), only allowed to move North.
4. Journey must end at North Pole (0 km).

Algorithms/Techniques: Simulation of movement along a line representing the Earth's meridian.
Time Complexity: O(n), where n is the number of movement instructions.
Space Complexity: O(n), for storing the direction and length of each move.

*/
#include <iostream>
#include <string>

typedef long long int ll;
#define pp pair<ll, ll>
#define max2(a, b) ((a < b) ? b : a)
#define max3(a, b, c) max2(max2(a, b), c)
#define min2(a, b) ((a > b) ? b : a)
#define min3(a, b, c) min2(min2(a, b), c)
using namespace std;
int main() {
  ll i, j, k;
  ll n, m;
  ll cur = 0, ew = 0; // cur represents current position on the meridian (0 = North Pole, 20000 = South Pole)
  bool f = true; // flag to indicate if the journey is valid
  cin >> n;
  string dir[n];
  ll len[n];
  for (i = 0; i < n; i++)
    cin >> len[i] >> dir[i];
  for (i = 0; i < n; i++) {
    if (cur == 0) { // if currently at North Pole
      // Only allowed to move South
      if (dir[i] == "South" && (cur + len[i]) <= 20000 && (cur + len[i]) >= 0) {
        cur += (len[i]);
      } else {
        f = false;
        break;
      }
    } else if (cur == 20000) { // if currently at South Pole
      // Only allowed to move North
      if (dir[i] == "North" && (cur - len[i]) <= 20000 && (cur - len[i]) >= 0) {
        cur -= len[i];
      } else {
        f = false;
        break;
      }
    } else { // if currently somewhere between poles
      // If moving North, check that we do not go past North Pole (0) or beyond South Pole (20000)
      if (dir[i] == "North" && (cur - len[i] > 20000 || cur - len[i] < 0)) {
        f = false;
        break;
      }
      // If moving South, check that we do not go past North Pole (0) or beyond South Pole (20000)
      if (dir[i] == "South" && (cur + len[i] > 20000 || cur + len[i] < 0)) {
        f = false;
        break;
      }
      // Perform the move in a valid direction
      if (dir[i] == "North" && (cur - len[i]) <= 20000 && (cur - len[i]) >= 0) {
        cur -= len[i];
        continue;
      } else if (dir[i] == "South" && (cur + len[i]) <= 20000 &&
                 (cur + len[i]) >= 0) {
        cur += len[i];
        continue;
      }
      // This section might never be reached due to early checks, but added for completeness
      if (dir[i] == "North" && (cur - len[i]) > 20000 && (cur - len[i]) < 0) {
        f = false;
        break;
      }
      if (dir[i] == "South" && (cur + len[i] > 20000) && (cur + len[i] < 0)) {
        f = false;
        break;
      }
    }
  }
  // Final check: journey must end at North Pole (0)
  if (cur == 0 && f == true)
    cout << "YES";
  else
    cout << "NO";
  return 0;
}


// https://github.com/VaHiX/CodeForces/