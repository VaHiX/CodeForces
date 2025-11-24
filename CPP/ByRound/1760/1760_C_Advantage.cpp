// Problem: CF 1760 C - Advantage
// https://codeforces.com/contest/1760/problem/C

/*
C. Advantage
Algorithm: For each element in the array, we need to compute the difference between that element and the maximum element in the array excluding itself.
Approach:
1. For each test case, find the two largest elements (mxa and mxb) in the array.
2. For each element, if it equals the maximum element (mxa), subtract the second largest (mxb).
   Otherwise, subtract the maximum (mxa).
Time Complexity: O(n) per test case
Space Complexity: O(n) for storing the vector
*/
#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    std::vector<long> v(n);
    long mxa(0), mxb(0);  // mxa = max element, mxb = second max element
    for (long p = 0; p < n; p++) {
      scanf("%ld", &v[p]);
      if (v[p] >= mxa) {   // Update both max and second max
        mxb = mxa;
        mxa = v[p];
      } else if (v[p] > mxb) {  // Update only second max
        mxb = v[p];
      }
    }
    for (long p = 0; p < n; p++) {
      printf("%ld ", v[p] - ((v[p] == mxa) ? mxb : mxa));  // Subtract appropriate max
    }
    puts("");
  }
}


// https://github.com/VaHiX/codeForces/