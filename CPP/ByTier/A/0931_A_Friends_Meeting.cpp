// Problem: CF 931 A - Friends Meeting
// https://codeforces.com/contest/931/problem/A

/*
Algorithm: Friends Meeting
Techniques: Mathematical optimization, two-pointer approach

Time Complexity: O(1)
Space Complexity: O(1)

The problem involves finding the minimum total tiredness for two friends to meet
at an integer point on a coordinate axis. Each move increases tiredness by 
1, 2, 3, ... depending on the move number. The key insight is to move towards
each other to minimize the total distance, and then calculate the optimal
tiredness using the arithmetic sum formula.

Approach:
1. Ensure a <= b by swapping if necessary.
2. Calculate distance m = b - a.
3. If m is even, they meet at the midpoint. Total tiredness = m/2 * (m/2 + 1).
4. If m is odd, they meet somewhere between a and b. 
   Compute the sum of moves for each friend to reach the meeting point.

*/
#include <iostream>
#include <utility>

typedef long long int ll;
typedef unsigned long long int ull;
#define dbg printf("in\n");
#define nl printf("\n");
#define N 100010
#define pp pair<int, int>
using namespace std;
int main() {
  int i, j, k;
  int n, m;
  int a, b;
  cin >> a >> b;
  if (a > b)
    swap(a, b); // Ensure a <= b for easier computation
  m = b - a; // Distance between the two friends
  if (m % 2 == 0) {
    m = m / 2; // Meeting point is exactly at the midpoint
    cout << (m * (m + 1)) << endl; // Sum of first m natural numbers
  } else {
    m = a + b; // Total distance from a to b is m
    k = m / 2; // Midpoint of the total distance
    j = k - a; // Moves needed for first friend to reach k
    k = b - k; // Moves needed for second friend to reach k
    cout << ((j * (j + 1)) / 2 + (k * (k + 1)) / 2) << endl; // Sum of both
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/