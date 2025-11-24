// Problem: CF 1686 A - Everything Everywhere All But One
// https://codeforces.com/contest/1686/problem/A

/*
Problem: A. Everything Everywhere All But One
Purpose: Determine if it's possible to make all elements of an array equal by replacing n-1 elements with their arithmetic mean.
Algorithm: 
    - For each element, check if replacing all other elements with their average results in the same value as the chosen element.
    - This is true when n * v[p] == sum of array elements.
Time Complexity: O(n) per test case
Space Complexity: O(n) for storing the array
*/
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> v(n);
    long s(0); // s holds the sum of all elements
    for (long p = 0; p < n; p++) {
      scanf("%ld", &v[p]);
      s += v[p]; // accumulate sum
    }
    bool res(false);
    for (long p = 0; !res && p < n; p++) {
      if (n * v[p] == s) { // Check if the current element can be the result after operation
        res = true;
      }
    }
    puts(res ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/