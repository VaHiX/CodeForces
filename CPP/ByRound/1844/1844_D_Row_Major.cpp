// Problem: CF 1844 D - Row Major
// https://codeforces.com/contest/1844/problem/D

/*
 * Problem: Find the string with minimum number of distinct characters
 *          such that it is not the row-major order of any bad grid.
 *
 * Approach:
 * - A bad grid is one where adjacent cells share the same character.
 * - To avoid this, we need to use a sufficient number of distinct characters.
 * - The minimum number of distinct characters required is the smallest number
 *   that does not divide n (i.e., n % k != 0).
 * - We construct a string using the first 'k' characters of the alphabet
 *   and repeat this pattern to form a string of length n.
 *
 * Time Complexity: O(n) per test case
 * Space Complexity: O(n) for storing the result string
 */

#include <stddef.h>
#include <cmath>
#include <iostream>
#include <iterator>
#include <string>

using namespace std;
#define li long int
#define lf long float
#define ld long double
#define lli long long int
#define llf long long float
#define lld long long double
#define endl "\n"
#define vlli vector<long long int>
#define it(var) var.begin(), var.end()
#define rit(var) var.rbegin(), var.rend()
#define mid(left, right) (left + (right - left) / 2)
#define fast_io                                                                \
  ios_base::sync_with_stdio(false);                                            \
  cin.tie(NULL);                                                               \
  cout.tie(NULL);
#define _print(x) cerr << #x << " = " << x << endl;
template <typename T> T _gcd(T a, T b) {
  if (a % b)
    return _gcd(b, a % b);
  return b;
}
template <typename T> T _lcm(T a, T b) { return (a * (b / _gcd(a, b))); }
template <typename T, typename... Args> auto sum(T a, Args... args) {
  return a + sum(args...);
}
template <typename T> bool comparator(pair<T, T> &a, pair<T, T> &b) {
  return (a.second < b.second);
}
const long double pi = atan2(0, -1);
string pi100 = "3."
               "141592653589793238462643383279502884197169399375105820974944592"
               "3078164062862089986280348253421170679";
void file_input_output() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
}
lli findSmallestNonFactor(lli n) {
  lli smallest = 1;
  while (true) {
    if (n % smallest != 0) {
      return smallest;
    }
    smallest++;
  }
}
int main(int argc, char const *argv[]) {
  fast_io lli t;
  cin >> t;
  while (t--) {
    lli n;
    cin >> n;
    lli distCh = findSmallestNonFactor(n); // Find smallest number that doesn't divide n
    string wind = "";
    for (lli i = 0; i < distCh; i++) {
      wind += (i + 'a'); // Build string with first 'distCh' characters
    }
    if (n <= distCh) {
      cout << wind.substr(0, n) << endl; // If n is small, just take first n chars
    } else {
      lli i = 0;
      string ans = "";
      for (i = 0; i < n - distCh; i += distCh) {
        ans += wind; // Repeat the pattern
      }
      lli p = 0;
      while (i < n) {
        ans += wind[p]; // Fill remaining positions
        p++;
        i++;
      }
      cout << ans << endl;
    }
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/