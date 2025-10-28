// Problem: CF 1165 D - Almost All Divisors
// https://codeforces.com/contest/1165/problem/D

/*
D. Almost All Divisors
Algorithm: 
    - For each test case, given a set of divisors (excluding 1 and the number itself),
      find the minimum possible number x whose divisors match the input list.
    - The key insight is that if we know all divisors except 1 and x,
      then the product of the smallest and largest divisor must be x.
    - We compute all divisors of this product and compare with given set.

Time Complexity: O(n * sqrt(max_product)) per test case, where max_product <= 10^12
Space Complexity: O(n) for storing divisors in sets.
*/

#include <iostream>
#include <set>
#include <functional>
#include <iterator>

using namespace std;

int main() {
  int T;
  cin >> T;
  while (T--) {
    int n;
    long long N;
    set<int> S, D; // S stores input divisors, D stores computed divisors
    cin >> n;
    while (n--) {
      cin >> N;
      S.insert(N); // Insert each divisor into the set
    }
    // Compute product of smallest and largest divisor - this must be our answer x
    N = (long long)*(S.begin()) * (*(S.rbegin()));
    // Find all divisors of N and store them in D
    for (int n = 2; 1LL * n * n <= N; n++)
      if (N % n == 0) {
        D.insert(n);          // Insert divisor n
        D.insert(N / n);      // Insert corresponding pair divisor
      }
    // Check if computed divisors match input divisors
    if (D == S)
      cout << N;
    else
      cout << -1;
    cout << endl;
  }
}


// https://github.com/VaHiX/codeForces/