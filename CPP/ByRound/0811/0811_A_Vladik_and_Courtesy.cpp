// Problem: CF 811 A - Vladik and Courtesy
// https://codeforces.com/contest/811/problem/A

/*
Code Purpose:
This program determines which person (Vladik or Valera) will be the first to not have enough candies to give in a turn-based game.
The game alternates between Vladik and Valera, where each player gives away one more candy than they received in the previous turn.
The game continues until one player can't provide the required number of candies.

Algorithms/Techniques:
- Simulation of turns
- Simple iterative loop to simulate the candy exchange

Time Complexity: O(sqrt(a + b))
Space Complexity: O(1)

The loop runs approximately 2*sqrt(a + b) times in the worst case,
as the sum of first n natural numbers is n*(n+1)/2, so n ~ sqrt(2*(a+b))

*/
#include <iostream>

typedef long long int ll;
#define pp pair<ll, ll>
#define dbg printf("in");
#define NL printf("\n");
#define inf 1000000000000
#define max2(a, b) ((a < b) ? b : a)
#define max3(a, b, c) max2(max2(a, b), c)
#define min2(a, b) ((a > b) ? b : a)
#define min3(a, b, c) min2(min2(a, b), c)
using namespace std;
int main() {
  ll i, j, k;
  ll n;
  ll a, b;
  cin >> a >> b;
  i = 1;
  while (true) {
    // Vladik's turn: check if he can give i candies
    if (i > a) {
      cout << "Vladik";
      return 0;
    } else {
      a -= i;  // Subtract the candies Vladik gives
      i++;     // Increment for next turn
    }
    // Valera's turn: check if he can give i candies
    if (i > b) {
      cout << "Valera";
      return 0;
    } else {
      b -= i;  // Subtract the candies Valera gives
      i++;     // Increment for next turn
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/