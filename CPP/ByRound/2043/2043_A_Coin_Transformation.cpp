// Problem: CF 2043 A - Coin Transformation
// https://codeforces.com/contest/2043/problem/A

#include <cstdio>
typedef long long ll;
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    ll nc(1); // Initialize coin count to 1 (we start with one coin)
    while (n >= 4) { // While we can still split a coin (value >= 4)
      nc *= 2;       // Double the number of coins (each split produces 2 coins)
      n /= 4;        // Reduce n to the value of each new coin (floor division by 4)
    }
    printf("%lld\n", nc); // Output maximum number of coins possible
  }
}
/*
Algorithm: Coin Transformation
Techniques: Greedy approach with mathematical transformation

Time Complexity: O(log n) per test case, as n is divided by 4 in each iteration
Space Complexity: O(1), only using a constant amount of extra space

The problem is solved by greedily splitting coins whenever possible. 
Each time we split a coin with value x > 3, we get two coins of value floor(x/4). 
This process continues until all remaining coins have value less than 4.
*/


// https://github.com/VaHiX/codeForces/