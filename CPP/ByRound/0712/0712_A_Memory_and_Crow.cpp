// Problem: CF 712 A - Memory and Crow
// https://codeforces.com/contest/712/problem/A

/*
Purpose: This program reconstructs the original sequence of integers b from the given sequence a,
         where each a[i] is defined as a alternating sum starting from b[i].

Algorithms/Techniques: 
    - Reverse iteration to compute the original sequence b from the transformed sequence a.
    - Utilizes the relationship: b[i] = a[i] + a[i+1], derived from the alternating sum pattern.

Time Complexity: O(n), where n is the number of elements in the sequence.
Space Complexity: O(n), for storing the arrays a and b.

*/
#include <iostream>

using namespace std;
int main() {
  long long int n, count = 0;
  long long int i, j, k;
  cin >> n;
  long long int a[n], b[n];
  for (i = 0; i < n; i++)
    cin >> a[i];
  b[n - 1] = a[n - 1]; // Base case: last element of b equals last element of a
  for (i = n - 2; i >= 0; i--) {
    b[i] = a[i] + a[i + 1]; // Recompute b[i] from a[i] and a[i+1]
  }
  for (i = 0; i < n; i++)
    cout << b[i] << " "; // Output the reconstructed sequence b
  return 0;
}


// https://github.com/VaHiX/CodeForces/