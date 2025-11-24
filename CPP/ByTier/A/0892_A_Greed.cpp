// Problem: CF 892 A - Greed
// https://codeforces.com/contest/892/problem/A

/*
Purpose: Determine if all cola from n cans can be poured into exactly 2 cans.
Algorithms/Techniques: Greedy approach to find the two largest capacities and check if their sum is at least the total volume.

Time Complexity: O(n) - single pass through the arrays to compute total volume and find two maximum capacities.
Space Complexity: O(1) - only a few variables used regardless of input size.

Input: 
- n (number of cans)
- Array a of n integers representing remaining cola in each can
- Array b of n integers representing capacity of each can

Output:
- "YES" if all cola can fit into two cans, "NO" otherwise
*/
#include <cstdio>
typedef long long ll;
int main() {
  long n;
  scanf("%ld", &n);
  ll vol(0), bs(0), bm(0); // vol: total volume, bs: second largest capacity, bm: largest capacity
  for (long p = 0; p < n; p++) {
    ll a;
    scanf("%lld", &a);
    vol += a; // accumulate total volume of cola
  }
  for (long p = 0; p < n; p++) {
    ll b;
    scanf("%lld", &b);
    if (b >= bm) {
      bs = bm;  // update second largest before updating largest
      bm = b;
    } else if (b >= bs) {
      bs = b;   // update second largest if b is smaller than bm but larger than bs
    }
  }
  puts(vol <= (bs + bm) ? "YES" : "NO"); // check if total volume fits in two largest cans
  return 0;
}


// https://github.com/VaHiX/CodeForces/