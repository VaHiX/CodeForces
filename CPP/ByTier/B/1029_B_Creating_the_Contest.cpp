// Problem: CF 1029 B - Creating the Contest
// https://codeforces.com/contest/1029/problem/B

/*
B. Creating the Contest
Algorithm: Sliding window approach to find the maximum length of a subsequence where each element 
           is at most twice the previous one.
Time Complexity: O(n)
Space Complexity: O(n)

The problem asks for the longest contest (subset of problems) such that for every problem 
except the hardest, there exists a problem with difficulty greater than current but not more than twice the current.
This can be solved by scanning the array and maintaining a count of consecutive elements
that satisfy the condition a[i+1] <= a[i] * 2. When this condition breaks, we reset the count.
*/
#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n); // Store the difficulties
  for (long p = 0; p < n; p++) {
    scanf("%ld", &a[p]);
  }
  long cnt(1), mx(1); // cnt: current sequence length, mx: maximum sequence length
  for (long p = 1; p < n; p++) {
    cnt = (a[p - 1] * 2 >= a[p]) ? (cnt + 1) : 1; // Extend or reset the count
    mx = (mx > cnt) ? mx : cnt; // Update maximum if necessary
  }
  printf("%ld\n", mx);
  return 0;
}


// https://github.com/VaHiX/codeForces/