// Problem: CF 2164 B - Even Modulo Pair
// https://codeforces.com/contest/2164/problem/B

/*
Algorithm: Even Modulo Pair
Purpose: Given a strictly increasing sequence of positive integers, find two distinct elements x and y such that x < y and y mod x is even. If no such pair exists, output -1.

Approach:
- The key insight is that if we have two numbers a and b, where a < b, then b % a is even if and only if (b % a) & 1 == 0.
- A brute-force approach checking all pairs would be too slow (O(n^2)).
- However, notice that in a sorted array, if we fix a number as x (smaller), the possible values for y (larger) can be checked up to a certain limit.
- We only need to check a few small indices (up to 30) for the outer loop since the probability of getting an even remainder increases when the numbers are closer or have small differences.
- When the difference between elements is small, we are more likely to get an even modulo result due to properties of even and odd numbers.
- For each element, we check the previous few elements, and if we find a valid pair, we output it and stop.

Time Complexity: O(n * min(n, 30)) = O(n^2) worst case, but practically faster due to the small limit on inner loop
Space Complexity: O(n) to store the input array

Techniques:
- Fast I/O using buffer
- Brute-force optimization with a small fixed limit
- Bitwise operation to check if a number is even
*/

#include <stdio.h>
#include <algorithm>

using namespace std;
typedef long long ll;
inline int readChar();
template <class T = int> inline T readInt();
template <class T> inline void writeInt(T x, char end = 0);
inline void writeChar(int x);
inline void writeWord(const char *s);
static const int buf_size = 1 << 18;
inline int getChar() {
#ifndef LOCAL
  static char buf[buf_size];
  static int len = 0, pos = 0;
  if (pos == len)
    pos = 0, len = fread(buf, 1, buf_size, stdin);
  if (pos == len)
    return -1;
  return buf[pos++];
#endif
}
inline int readChar() {
#ifndef LOCAL
  int c = getChar();
  while (c <= 32)
    c = getChar();
  return c;
#else
  char c;
  cin >> c;
  return c;
#endif
}
template <class T> inline T readInt() {
#ifndef LOCAL
  int s = 1, c = readChar();
  T x = 0;
  if (c == '-')
    s = -1, c = getChar();
  while ('0' <= c && c <= '9')
    x = x * 10 + c - '0', c = getChar();
  return s == 1 ? x : -x;
#else
  T x;
  cin >> x;
  return x;
#endif
}
static int write_pos = 0;
static char write_buf[buf_size];
inline void writeChar(int x) {
  if (write_pos == buf_size)
    fwrite(write_buf, 1, buf_size, stdout), write_pos = 0;
  write_buf[write_pos++] = x;
}
template <class T> inline void writeInt(T x, char end) {
  if (x < 0)
    writeChar('-'), x = -x;
  char s[24];
  int n = 0;
  while (x || !n)
    s[n++] = '0' + x % 10, x /= 10;
  while (n--)
    writeChar(s[n]);
  if (end)
    writeChar(end);
}
inline void writeWord(const char *s) {
  while (*s)
    writeChar(*s++);
}
struct Flusher {
  ~Flusher() {
    if (write_pos)
      fwrite(write_buf, 1, write_pos, stdout), write_pos = 0;
  }
} flusher;
int num[100000];
int main() {
  int T = readInt();
  while (T--) {
    int n = readInt();
    for (int i = 0; i < n; i++)
      num[i] = readInt();
    bool ans = 1;
    // Iterate through pairs of elements, checking small indices at a time
    for (int i = 1; i < min(n, 30) && ans; i++) {
      for (int j = 0; j < i && ans; j++) {
        // Check if the modulo is even using bitwise AND
        if ((num[i] % num[j] & 1) == 0) {
          writeInt(num[j], ' ');  // Output smaller element
          writeInt(num[i], '\n'); // Output larger element
          ans = 0; // Mark as found
        }
      }
    }
    if (ans)
      writeWord("-1\n"); // No valid pair found
  }
}


// https://github.com/VaHiX/CodeForces/