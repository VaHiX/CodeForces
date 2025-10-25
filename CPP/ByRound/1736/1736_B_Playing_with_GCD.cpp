// Problem: CF 1736 B - Playing with GCD
// https://codeforces.com/contest/1736/problem/B

/*
B. Playing with GCD

Problem Description:
Given an array 'a' of length n, determine if there exists an array 'b' of length n+1 such that 
for all i, a[i] = gcd(b[i], b[i+1]).

Approach:
- For each element in the array, check if it divides the GCD of its neighboring elements.
- This condition must hold for all middle elements (i.e., from index 1 to n-2).
- Use Euclidean algorithm for computing GCD.

Time Complexity: O(n * log(max(a))) - Each GCD computation takes O(log(min(a[i], a[j]))) time,
and we do this for each of the n elements in worst case.

Space Complexity: O(n) - We store the input array of size n.

Algorithm:
1. Read number of test cases t.
2. For each test case:
   - Read array length n and elements.
   - Check if the condition holds for all middle elements.
     Specifically, for every index p from 1 to n-2, verify:
       a[p] divides gcd(a[p-1], a[p+1])
   - Print YES if all conditions satisfied, otherwise NO.

*/

#include <cstdio>
#include <vector>
long gcd(long a, long b) { return b ? gcd(b, a % b) : a; }
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    bool res(true);
    // Loop through indices from 1 to n-2, checking if current element divides gcd of neighbors
    for (long p = 1; res && p + 1 < n; p++) {
      if (a[p] % gcd(a[p - 1], a[p + 1])) {  // If remainder is non-zero, condition fails
        res = false;
      }
    }
    puts(res ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/