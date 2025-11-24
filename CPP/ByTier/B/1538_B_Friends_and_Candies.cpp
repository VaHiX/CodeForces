// Problem: CF 1538 B - Friends and Candies
// https://codeforces.com/contest/1538/problem/B

/*
Problem: Friends and Candies
Algorithm: Greedy approach
Time Complexity: O(n) per test case
Space Complexity: O(n) for the vector storage

Given n friends with candies, we want to redistribute all candies such that 
each friend ends up with the same number of candies. We must find the minimum 
number of friends (k) whose candies are gathered and redistributed.

Approach:
1. For each test case, calculate the total sum of candies.
2. If sum is not divisible by n, return -1 as equal distribution is impossible.
3. Otherwise, compute target number of candies per friend (sum/n).
4. Count how many friends have more than target candies. 
   These excess candies can be redistributed to those with fewer.
5. Return the count of such friends, which represents minimum k.

Key points:
- If total sum % n != 0, return -1 (impossible to distribute equally)
- Otherwise, we need to collect candies from friends having more than average
- The number of such friends is our answer

Sample Input:
4
4 5 2 5    -> k=2 (friends with 5 and 5 can give 1 candy each to make all 4)
0 4        -> k=1 (friend with 4 gives 2 candies to friend with 0)
10 8 5 1 4 -> k=-1 (sum=28, 28%5 != 0)

Sample Output:
2
1
-1
0
0
*/
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n);
    long long s(0); // Total sum of candies
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
      s += a[p]; // Accumulate total candies
    }
    if (s % n) { // If we cannot distribute equally
      puts("-1");
      continue;
    }
    long num = s / n; // Target number of candies per person
    long k(0); // Count of friends with more than average candies
    for (long p = 0; p < n; p++) {
      k += (num < a[p]); // Increment if current friend has excess candies
    }
    printf("%ld\n", k); // Print minimum number of friends needed
  }
}


// https://github.com/VaHiX/codeForces/