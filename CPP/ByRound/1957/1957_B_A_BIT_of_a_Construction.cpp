// Problem: CF 1957 B - A BIT of a Construction
// https://codeforces.com/contest/1957/problem/B

/*
 * Problem: Construct a sequence of n non-negative integers summing to k
 *          such that the number of 1s in the binary representation of 
 *          their bitwise OR is maximized.
 *
 * Algorithm:
 * - If k == 1, output the single value n.
 * - Otherwise, determine if n is a power of 2.
 *   - If not, split n into two parts and fill the rest with zeros.
 *   - If yes, use a specific construction to maximize the number of 1-bits in OR.
 *
 * Time Complexity: O(log n) per test case
 * Space Complexity: O(1) excluding input/output
 */
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
#define inf 1000000007
#define pi 3.141592653589793238462643383279502884197169399
#define gcd __gcd
#define max3(a, b, c) max(max(a, b), c)
#define min3(a, b, c) min(min(a, b), c)
#define PYES cout << "YES\n"
#define PNO cout << "NO\n"
const int N = 1e7;
#define vi vector<int>
typedef long long ll;
template <typename T>
ostream &operator<<(ostream &output, const vector<T> &data) {
  for (const T &x : data)
    output << x << " ";
  return output;
}
template <typename T> istream &operator>>(istream &input, vector<T> &data) {
  for (auto &item : data) {
    input >> item;
  }
  return input;
}
vector<int> form_v(int n) {
  vector<int> v(n);
  for (int i = 0; i < n; i++) {
    cin >> v[i];
  }
  return v;
}
void sol() {
  ll n, k;
  cin >> k >> n;  // Read k first, then n (note: this order seems reversed in input parsing)
  ll check = 0;
  ll temp = n;
  if (k == 1) {
    cout << n << "\n";
    return;
  }
  // Check if n is a power of 2
  while (n != 0) {
    if (n % 2 == 0) {
      check = 1;
    }
    n >>= 1;
  }
  n = temp;
  if (check == 0) {
    // n is a power of 2
    cout << n << " ";
    for (int i = 1; i < k; i++) {
      cout << "0 ";
    }
  } else {
    // n is not a power of 2
    temp = 0;
    ll temp2 = n;
    int i = 0;
    // Build a number with all bits set up to the highest bit of n
    while (n != 1) {
      temp <<= 1;
      temp += 1;
      n /= 2;
    }
    // Output temp and diff between n and temp
    cout << temp << " " << temp2 - temp << " ";
    for (int i = 2; i < k; i++) {
      cout << "0 ";
    }
  }
  cout << "\n";
}
int main() {
#define int long long
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int t = 1;
  cin >> t;
  for (int i = 0; i < t; i++) {
    sol();
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/