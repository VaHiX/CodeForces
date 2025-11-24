// Problem: CF 476 A - Dreamoon and Stairs
// https://codeforces.com/contest/476/problem/A

/*
Purpose: To find the minimum number of moves to climb n stairs, where each move is 1 or 2 steps,
         and the total number of moves must be a multiple of m.

Algorithm/Techniques: Greedy approach with mathematical analysis.
                      - First, we compute the best-case scenario for minimum steps (using 2-steps as much as possible).
                      - Then, we adjust the number of steps to make it a multiple of m, checking from the minimum up.
                      - If no valid number of moves is found, return -1.

Time Complexity: O(n/m) in worst case, as we might have to increment up to n/2 steps.
Space Complexity: O(1), constant extra space used.

*/
#include <iostream>

typedef long long int ll;
#define pp pair<char, ll>
#define dbg printf("in");
#define NL printf("\n");
#define S 210000
#define inf 1000000000000
using namespace std;
int main() {
  ll i, j, k;
  ll n, m;
  ll ss, s;
  cin >> n >> m;
  if (n < m) {
    cout << "-1";  // If n is smaller than m, it's impossible to have a multiple of m moves
    return 0;
  }
  if (n == m) {
    cout << n;  // If n equals m, the minimum moves is n itself (n is a multiple of m)
    return 0;
  }
  if (n % m) {  // If n is not divisible by m
    ss = n / 2 + 1;  // Start with slightly more than half moves (greedy for minimum steps)
    s = n / 2;       // Current number of 2-steps
  } else {
    ss = n / 2;  // If n is divisible by m, start with exact half moves
    s = ss;
  }
  while (s) {
    if (ss % m == 0)  // Check if current number of steps is a multiple of m
      break;
    ss++;   // Increment the total moves
    s--;    // Decrement the 2-steps count to maintain sum of steps
  }
  if (ss % m != 0)  // If no valid move count found
    cout << "-1";
  else
    cout << ss;
  return 0;
}


// https://github.com/VaHiX/CodeForces/