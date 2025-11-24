// Problem: CF 1780 A - Hayato and School
// https://codeforces.com/contest/1780/problem/A

/*
Purpose: 
This code determines whether there exist three numbers in a given array whose sum is odd. 
It uses the property that the sum of three integers is odd if and only if:
1. Exactly one of the three numbers is even, and two are odd, or
2. All three numbers are odd.

Algorithm:
- Separate the indices of odd and even numbers in the array.
- If there are at least 3 odd numbers, select any 3 of them.
- Else if there is at least one odd number and at least 2 even numbers, select one odd and two even numbers.
- Otherwise, it's impossible to form such a triplet.

Time Complexity: O(n) per test case, where n is the size of the array.
Space Complexity: O(n) for storing indices of odd and even numbers.

Techniques:
- Array traversal
- Conditional logic based on parity
- Greedy selection of elements
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> odds, evens;
    for (long p = 0; p < n; p++) {
      long x;
      scanf("%ld", &x);
      if (x % 2) {
        odds.push_back(p + 1); // Store 1-based index of odd number
      } else {
        evens.push_back(p + 1); // Store 1-based index of even number
      }
    }
    if (odds.size() >= 3) {
      puts("YES");
      printf("%ld %ld %ld\n", odds[0], odds[1], odds[2]); // Pick any 3 odds
    } else if (odds.size() > 0 && evens.size() >= 2) {
      puts("YES");
      printf("%ld %ld %ld\n", odds[0], evens[0], evens[1]); // One odd + two evens
    } else {
      puts("NO");
    }
  }
}


// https://github.com/VaHiX/CodeForces/