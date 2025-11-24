// Problem: CF 1765 E - Exchange
// https://codeforces.com/contest/1765/problem/E

/*
E. Exchange

Algorithms/Techniques: Greedy approach with mathematical optimization

Time Complexity: O(t), where t is the number of test cases
Space Complexity: O(1)

The problem involves finding the minimum number of gold coins (quests) Monocarp needs to complete 
to obtain at least n silver coins. He can either:
- Sell 1 gold coin for 'a' silver coins
- Buy 1 gold coin for 'b' silver coins

We decide whether to buy or sell based on the ratio of a and b:
- If a <= b, it's better to just complete enough quests to get enough silver, 
  so we compute ceil(n / a) which is (n + a - 1) / a.
- Otherwise, if a > b, we trade optimally: buy one gold coin for 'b' silver, 
  sell it for 'a' silver, gaining (a - b) silver. So we complete only 1 quest.

*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, a, b;
    scanf("%ld %ld %ld", &n, &a, &b);
    printf("%ld\n", a <= b ? ((n + a - 1) / a) : 1); // If selling is not more profitable than buying, then just do it directly; else, only 1 quest needed
  }
}


// https://github.com/VaHiX/codeForces/