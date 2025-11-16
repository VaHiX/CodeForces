// Problem: CF 706 B - Interesting drink
// https://codeforces.com/contest/706/problem/B

/*
Purpose: This program determines how many shops Vasiliy can buy "Beecola" from on each of q days,
         given that he has a certain amount of coins to spend each day.
         It uses a counting sort-like approach with a cumulative frequency array to efficiently 
         answer queries about how many shops are affordable for a given amount of money.

Algorithms/Techniques:
- Counting Sort Technique
- Cumulative Frequency Array

Time Complexity: O(N + Q + maxValue) where N is number of shops, Q is number of queries,
                 and maxValue is 100000 (as per constraints).
Space Complexity: O(maxValue) for the cumulative price array.

*/

#include <cstdio>
#include <vector>
int main() {
  const int N = 100100;  // Maximum possible price + 1 to handle all cases
  long n;
  scanf("%ld\n", &n);
  std::vector<long> cumPrices(N + 1, 0);  // Array to store cumulative count of prices <= i
  for (long p = 0; p < n; p++) {
    long x;
    scanf("%ld", &x);
    ++cumPrices[x];  // Increment count for price x
  }
  for (long p = 1; p <= N; p++) {
    cumPrices[p] += cumPrices[p - 1];  // Build cumulative sum to know how many prices <= p
  }
  long q;
  scanf("%ld\n", &q);
  while (q--) {
    long a;
    scanf("%ld\n", &a);
    printf("%ld\n", cumPrices[(a <= N) ? a : N]);  // Output cumulative count for price a
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/