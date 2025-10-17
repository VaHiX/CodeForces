// Problem: CF 2147 B - Multiple Construction
// https://codeforces.com/contest/2147/problem/B

/*
B. Multiple Construction
Algorithms/Techniques: Greedy construction with specific placement pattern

Time Complexity: O(n) per test case, O(∑n) overall
Space Complexity: O(n) for output array

The solution constructs an array of length 2*n where each number from 1 to n appears exactly twice,
and the distance between the two occurrences of each number x is divisible by x.
This is achieved by placing numbers in a specific pattern:
- First, place all numbers from n down to 1
- Then place n again
- Finally, place all numbers from 1 to n-1
This ensures that for any number x, the two occurrences are positioned such that their distance
is divisible by x.
*/

#include <iostream>

using namespace std;
int main() {
  int t;
  cin >> t;
  while (t--) {
    long long n;
    cin >> n;
    // Place numbers from n down to 1
    for (int i = n; i > 0; i--) {
      cout << i << " ";
    }
    // Place n again
    cout << n << " ";
    // Place numbers from 1 to n-1
    for (int i = 1; i < n; i++) {
      cout << i << " ";
    }
    cout << endl;
  }
}


// https://github.com/VaHiX/CodeForces/