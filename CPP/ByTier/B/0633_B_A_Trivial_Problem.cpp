// Problem: CF 633 B - A Trivial Problem
// https://codeforces.com/contest/633/problem/B

/*
B. A Trivial Problem
time limit per test
2 seconds
memory limit per test
256 megabytes
input
standard input
output
standard output
Mr. Santa asks all the great programmers of the world to solve a trivial problem. He gives them an integer 
m
 and asks for the number of positive integers 
n
, such that the factorial of 
n
 ends with exactly 
m
 zeroes. Are you among those great programmers who can solve this problem?

Algorithm: 
- For each n, compute the number of trailing zeros in n! by counting factors of 5.
- Use a while loop to find all n such that trailing zeros equal m.
- Time complexity: O(n * log n), where n is up to 100000 * 5 = 500000 (worst case)
- Space complexity: O(k), where k is the number of valid n values (at most 5)

*/

#include <iostream>
#include <vector>
int main() {
  const int M = 100000;
  int m;
  std::cin >> m;
  std::vector<long> res; // Store all valid n values
  long n(0); // current number being checked
  long f(0); // number of trailing zeros in n!
  while (f <= m) { // Continue while f is less than or equal to m
    long x = ++n; // Increment n and store in x
    f = 0; // Reset f for new calculation
    while (x > 0) { // Count factors of 5 in x!
      f += (x / 5); // Add number of multiples of 5
      x /= 5; // Move to next power of 5
    }
    if (f == m) { // If trailing zeros match required count
      res.push_back(n); // Add n to result list
    }
  }
  std::cout << res.size() << std::endl; // Print number of valid n values
  for (int p = 0; p < res.size(); p++) { // Print all valid n values
    std::cout << res[p] << " ";
  }
  std::cout << std::endl;
  return 0;
}


// https://github.com/VaHiX/codeForces/