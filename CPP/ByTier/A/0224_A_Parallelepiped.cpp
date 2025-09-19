/*
 * Problem URL : https://codeforces.com/problemset/problem/224/A
 * Submit Date : 2025-08-09
 */

#include <cmath>
#include <iostream>

using namespace std;

int main() {
  int ab, bc, ca;
  cin >> ab >> bc >> ca;
  int a = sqrt(ab * ca / bc + 0.5);
  int b = sqrt(bc * ab / ca + 0.5);
  int c = sqrt(ca * bc / ab + 0.5);
  cout << (a + b + c) * 4 << endl;
  return 0;
}
