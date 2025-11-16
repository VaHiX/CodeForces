// Problem: CF 1761 C - Set Construction
// https://codeforces.com/contest/1761/problem/C

/*
Purpose: This code constructs n sets A_1, A_2, ..., A_n such that the binary matrix b represents subset relationships.
         Specifically, b[i][j] = 1 if and only if A_i is a proper subset of A_j.
         The algorithm uses a greedy approach where each set is initialized with its index and then expanded
         based on the matrix entries indicating subset relationships.

Algorithms/Techniques: Graph Construction, Greedy Set Expansion
Time Complexity: O(n^2) per test case, due to reading matrix and processing each element
Space Complexity: O(n^2) for storing the sets and the matrix input

*/
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
vector<int> v[110]; // Vector to store the sets, indexed from 1 to n
int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    // Initialize each set with its own index
    for (int i = 1; i <= n; i++)
      v[i].clear(), v[i].push_back(i);
    // Read the binary matrix
    for (int i = 1; i <= n; i++) {
      string s;
      cin >> s;
      for (int j = 0; j < n; j++) {
        // If there is a 1 in the matrix, add the corresponding row index to column index set
        if (s[j] == '1')
          v[j + 1].push_back(i);
      }
    }
    // Output the constructed sets
    for (int i = 1; i <= n; i++) {
      cout << v[i].size(); // Output the size of the set
      for (int j : v[i]) // Output each element of the set
        cout << " " << j;
      cout << endl;
    }
  }
}


// https://github.com/VaHiX/CodeForces/