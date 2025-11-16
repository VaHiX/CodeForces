// Problem: CF 1089 A - Alice the Fan
// https://codeforces.com/contest/1089/problem/A

/*
Purpose: 
    Solve the volleyball match score reconstruction problem where given total points scored by Team A and their opponent,
    determine the possible match score (number of sets won by each team) and the set scores that would lead to that match score.
    The match ends when one team wins 3 sets.
    The algorithm explores all possible match scores (3:x and x:3 where x=0,1,2) and tries to validate the point distribution 
    under volleyball rules for each case.

Algorithms/Techniques:
    - Brute force enumeration of match scores (3:x and x:3 for x = 0,1,2)
    - Greedy point distribution to check validity of given point totals
    - Backtracking simulation of point distribution in sets

Time Complexity: O(1) per match query - since the number of possible match scores is bounded (only 4 cases for Team A winning 0-3 sets)
Space Complexity: O(1) - fixed size arrays and variables used irrespective of input size

*/

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <utility>

using namespace std;
#define ll long long
#define ld long double
int n;
int r[20][2]; // Array to store set scores (max 5 sets)

// Function to distribute remaining points to first mb sets for Team A
int disA(int a, int b, int ma, int mb) {
  int d;
  for (int i = 0; i < mb; i++)
    d = max(0, min(a, r[i][1] - 2 - r[i][0])), r[i][0] += d, a -= d;
  return a;
}

// Function to distribute remaining points to last ma sets for Team B
int disB(int a, int b, int ma, int mb) {
  int d;
  for (int i = 0; i < ma; i++)
    d = max(0, min(b, r[i + mb][0] - 2 - r[i + mb][1])), r[i + mb][1] += d,
    b -= d;
  return b;
}

// Validates if given points a,b can be achieved for match score with ma sets won by A, mb by B
bool isPos(int a, int b, int ma, int mb) {
  if (ma != 3 && mb != 3 || ma + mb == 6) // Invalid combinations: not ending at 3-0 or 0-3 and 6 total sets
    return false;
  if (ma != 3) { // If A didn't win 3 sets, try swapping roles (swap a,b and ma,mb)
    bool ip = isPos(b, a, mb, ma);
    if (ip) {
      for (int i = 0; i < ma + mb; i++)
        swap(r[i][0], r[i][1]); // Swap scores to make result consistent
    }
    return ip;
  }
  int mas = 1000, asub = 0, mbs = 1000, bsub = 0;
  // Assign minimums to each set for B (25 points each or 15 for 5th set)
  for (int i = 0; i < mb; i++)
    r[i][0] = 0, r[i][1] = 25, b -= 25, asub += 23, mas = 23;
  // Assign minimums to each set for A (25 points each or 15 for 5th set)
  for (int i = 0; i < ma; i++)
    r[i + mb][0] = (i + mb == 4 ? 15 : 25), r[i + mb][1] = 0, a -= r[i + mb][0],
          bsub += r[i + mb][0] - 2, mbs = r[i + mb][0] - 2;
  if (a < 0 || b < 0) // Check if excess points are negative
    return false;
  // Check if points can be distributed to fit both team's requirement in the set limits
  if (a <= asub && b <= bsub) {
    a = disA(a, b, ma, mb);
    b = disB(a, b, ma, mb);
    return true;
  }
  int as, bs, d;
  as = a - mas; // Check if can fit mas extra points
  d = max(0, min(as, b));
  bs = b - d;
  as -= d;
  if (as >= 0 && bs >= 0 && as <= asub - mas && bs <= bsub) { // Can fit additional points
    r[0][0] += mas + d;
    a -= mas + d;
    r[0][1] += d;
    b -= d;
    a = disA(a, b, ma, mb);
    b = disB(a, b, ma, mb);
    return true;
  }
  bs = b - mbs; // Check if can fit mbs extra points
  d = max(0, min(bs, a));
  as = a - d;
  bs -= d;
  if (as >= 0 && bs >= 0 && as <= asub && bs <= bsub - mbs) { // Can fit additional points at end
    r[ma + mb - 1][1] += mbs + d;
    b -= mbs + d;
    r[ma + mb - 1][0] += d;
    a -= d;
    a = disA(a, b, ma, mb);
    b = disB(a, b, ma, mb);
    return true;
  }
  return false;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout << fixed << setprecision(12);
  cin >> n;
  int a, b;
  for (int i = 0; i < n; i++) {
    cin >> a >> b;
    int wa = 0, wb = 0;
    bool fs = false;
    for (int j = 3; j >= 0 && !fs; j--) // Try all possible match scores (3:x for x=0,1,2)
      for (int k = 0; k <= 3 && !fs; k++)
        wa = j, wb = k, fs = isPos(a, b, j, k);
    if (!fs)
      cout << "Impossible\n";
    else {
      cout << wa << ":" << wb << "\n";
      for (int i = 0; i < wa + wb; i++)
        cout << r[i][0] << ":" << r[i][1] << (i < wa + wb - 1 ? " " : "\n");
    }
  }
}


// https://github.com/VaHiX/CodeForces/