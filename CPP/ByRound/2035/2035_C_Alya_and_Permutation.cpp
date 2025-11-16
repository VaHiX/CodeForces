// Problem: CF 2035 C - Alya and Permutation
// https://codeforces.com/contest/2035/problem/C

#include <iostream>

using namespace std;
int main() {
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    if (n & 1) { // if n is odd
      cout << n << "\n"; // output the maximum possible k, which is n
      for (int i = 4; i < n - 1; i++) // print numbers from 4 to n-2
        cout << i << " ";
      cout << "2 1 3 " << n - 1 << " " << n << "\n"; // then append 2, 1, 3, n-1, n
    } else if (n == 6) // special case for n = 6
      cout << "7\n1 2 4 6 5 3\n"; // output k = 7 and the specific permutation
    else { // for even n > 6
      int k = 2147483648LL >> __builtin_clz(n); // find the smallest power of 2 greater than or equal to n
      cout << (k << 1) - 1 << "\n"; // output the maximum k value
      for (int i = 4; i < k - 2; i++) // print numbers from 4 to k-3
        cout << i << " ";
      for (int i = k; i < n; i++) // print numbers from k to n-1
        cout << i << " ";
      cout << "2 1 3 " << k - 2 << " " << k - 1 << " " << n << "\n"; // append the final part of the permutation
    }
  }
}


// https://github.com/VaHiX/CodeForces/