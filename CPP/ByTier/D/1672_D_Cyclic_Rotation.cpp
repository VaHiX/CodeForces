// Problem: CF 1672 D - Cyclic Rotation
// https://codeforces.com/contest/1672/problem/D
 
/*
Algorithm/Techniques: Simulation with Frequency Counting
Time Complexity: O(n) per test case
Space Complexity: O(n) for the frequency array and auxiliary arrays
 
This solution simulates the transformation process by tracking the frequency of elements
in the original array 'a' and trying to match them with the target array 'b' in order.
The key idea is to process elements from array 'a' and try to advance the pointer 'lk'
to the maximum extent possible when matching elements in 'b'. If we can fully advance
'lk' to 'n', it means we can transform 'a' into 'b'.
*/
 
#include <stdio.h>
#include <iostream>
 
using namespace std;
int t, n, a[200005], b[200005], s[200005], lk;
int main() {
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
      cin >> b[i];
    }
    for (int i = 1; i <= n; i++) {
      s[i] = 0; // Reset frequency array for each test case
    }
    lk = 0; // Pointer to track progress in array 'b'
    for (int i = 1; i <= n; i++) {
      s[a[i]]++; // Increment frequency of current element in 'a'
      // While the current element in 'b' matches the element being processed,
      // and there are available elements, advance 'lk' pointer
      while (b[lk + 1] == a[i] && s[a[i]]) {
        s[a[i]]--, lk++;
      }
    }
    puts(lk == n ? "YES" : "NO"); // If all elements matched, output "YES"
  }
  return 0;
}
 
 
// https://github.com/VaHiX/CodeForces/