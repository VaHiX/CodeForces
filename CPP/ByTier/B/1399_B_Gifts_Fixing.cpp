// Problem: CF 1399 B - Gifts Fixing
// https://codeforces.com/contest/1399/problem/B

/*
B. Gifts Fixing
time limit per test
1 second
memory limit per test
256 megabytes
input
standard input
output
standard output

You have n gifts and you want to give all of them to children. Of course, you don't want to offend anyone, so all gifts should be equal between each other. The i-th gift consists of a_i candies and b_i oranges.
During one move, you can choose some gift 1 <= i <= n and do one of the following operations:
 
 eat exactly one candy from this gift (decrease a_i by one); 
 eat exactly one orange from this gift (decrease b_i by one); 
 eat exactly one candy and exactly one orange from this gift (decrease both a_i and b_i by one). 
Of course, you can not eat a candy or orange if it's not present in the gift (so neither a_i nor b_i can become less than zero).
As said above, all gifts should be equal. This means that after some sequence of moves the following two conditions should be satisfied: a_1 = a_2 = ... = a_n and b_1 = b_2 = ... = b_n (and a_i equals b_i is not necessary).
Your task is to find the minimum number of moves required to equalize all the given gifts.

Algorithms/Techniques:
Greedy approach. For each gift, we determine how many candies and oranges we need to reduce to reach the minimum values across all gifts.
We then compute the difference in terms of moves needed to bring every gift down to those minimums.

Time Complexity: O(n) per test case
Space Complexity: O(n) for storing the arrays

*/

#include <cstdio>
#include <vector>
typedef long long ll;

int main() {
  ll t;
  scanf("%lld", &t);
  while (t--) {
    ll n;
    scanf("%lld", &n);
    ll mina(1e9 + 7), minb(1e9 + 7); // Initialize minimum values for candies and oranges
    std::vector<ll> a(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &a[p]);
      mina = (mina < a[p]) ? mina : a[p]; // Find minimum number of candies
    }
    std::vector<ll> b(n);
    for (ll p = 0; p < n; p++) {
      scanf("%lld", &b[p]);
      minb = (minb < b[p]) ? minb : b[p]; // Find minimum number of oranges
    }
    ll cnt(0);
    for (ll p = 0; p < n; p++) {
      ll x = a[p] - mina; // Excess candies in this gift compared to the minimum
      ll y = b[p] - minb; // Excess oranges in this gift compared to the minimum
      cnt += (x > y) ? x : y; // Add the larger of the two differences, since that's how many operations are needed for either type of excess
    }
    printf("%lld\n", cnt);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/