// Problem: CF 1175 A - From Hero to Zero
// https://codeforces.com/contest/1175/problem/A

/*
Problem: A. From Hero to Zero
Algorithms/Techniques: Greedy approach with base-k representation

Time Complexity: O(log_k(n)) per query
Space Complexity: O(1)

The algorithm works by converting the number n into base k and counting the steps needed.
Each digit in base k represents how many times we can divide by k before reducing by 1.
We add (digit + 1) for each digit except the last one, then subtract 1 at the end to account
for the final step to reach zero.
*/

#include <iostream>
using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) {
    long long int n, k, c = 0; // c counts total steps
    cin >> n >> k;
    while (n) {
      c += n % k + 1, n = n / k; // Add remainder + 1 steps and divide by k
    }
    cout << c - 1 << endl; // Subtract 1 to adjust for final step
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/