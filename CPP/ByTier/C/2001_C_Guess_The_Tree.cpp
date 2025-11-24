// Problem: CF 2001 C - Guess The Tree
// https://codeforces.com/contest/2001/problem/C

#include <iostream>

using namespace std;
int last[10010];
int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    for (int i = 2; i <= n; i++) {
      int k = 1, l;
      while (1) {
        cout << "? " << i << ' ' << k << endl;
        cin >> l;
        if (l == i) {
          last[i] = k;  // Store the parent of node i
          break;
        } else
          k = l;  // Move k to the result of query to find the path
      }
    }
    cout << "! ";
    for (int i = 2; i <= n; i++) {
      cout << last[i] << ' ' << i << ' ';  // Output edges from parent to child
    }
    cout << endl;
  }
  return 0;
}

// https://github.com/VaHiX/CodeForces/