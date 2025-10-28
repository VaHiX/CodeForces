// Problem: CF 1500 A - Going Home
// https://codeforces.com/contest/1500/problem/A

/*
Problem: A. Going Home
Purpose: Find four distinct indices in an array such that the sum of elements at two indices equals the sum of elements at the other two indices.
Algorithm: 
    - Use a hash map (simulated with arrays x[] and y[]) to store the last two indices for each possible sum.
    - Iterate over all pairs (i, j) where i < j.
    - For each sum s = a[i] + a[j], check if this sum was previously seen with two other distinct indices.
    - If yes, output the four indices.
    - Time Complexity: O(n^2)
    - Space Complexity: O(n)
*/

#include <iostream>
using namespace std;
#define For(i, l, r) for (int i = l; i <= r; i++)
#define MAXN 5000001
int N, a[MAXN], x[MAXN], y[MAXN]; // x[s] and y[s] store last two indices where sum s occurred
int main() {
  cin >> N;
  For(i, 1, N) cin >> a[i];
  For(i, 1, N) For(j, i + 1, N) {
    int s = a[i] + a[j]; // calculate current sum
    // Check if this sum was seen before and indices are all distinct
    if (x[s] && i != x[s] && i != y[s] && j != x[s] && j != y[s]) {
      cout << "YES\n" << i << ' ' << j << ' ' << x[s] << ' ' << y[s] << endl;
      return 0;
    }
    x[s] = i, y[s] = j; // update last two indices for sum s
  }
  cout << "NO\n";
  return 0;
}


// https://github.com/VaHiX/codeForces/