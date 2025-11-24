// Problem: CF 501 A - Contest
// https://codeforces.com/contest/501/problem/A

/*
 * Code Purpose:
 *   This program determines the winner of a Codeforces contest between Misha and Vasya
 *   based on the points they earned from solving one problem each.
 *   Points are calculated with a time-based penalty.
 *
 * Algorithm/Techniques:
 *   - For each participant, the score is computed as the maximum of two values:
 *     1. A fixed reduction: (3 * points) / 10
 *     2. A time-based penalty: points - (points * time_delay) / 250
 *   - The participant with higher score wins; if equal, it's a tie.
 *
 * Time Complexity: O(1)
 *   - The computation involves only a constant number of arithmetic operations.
 *
 * Space Complexity: O(1)
 *   - Only a fixed amount of space is used for storing variables.
 */

#include <algorithm>
#include <iostream>

typedef long long int ll;
using namespace std;

int main() {
  ll a, b, c, d;      // a, b: points for problems; c, d: time delays in minutes
  ll misha, vasya;    // scores for Misha and Vasya
  cin >> a >> b >> c >> d;

  // Compute Misha's score: max of fixed reduction and time-penalized score
  misha = max((3 * a) / 10, (a - ((a * c) / 250)));

  // Compute Vasya's score: max of fixed reduction and time-penalized score
  vasya = max((3 * b) / 10, (b - ((b * d) / 250)));

  // Compare scores and output result
  if (misha > vasya)
    cout << "Misha";
  else if (misha < vasya)
    cout << "Vasya";
  else
    cout << "Tie";

  return 0;
}


// https://github.com/VaHiX/CodeForces/