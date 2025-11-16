// Problem: CF 1967 C - Fenwick Tree
// https://codeforces.com/contest/1967/problem/C

/*
Algorithm: Fenwick Tree Inversion using Mathematical Induction and Modular Arithmetic
Purpose: Given array b and k, compute array a such that f^k(a) = b, where f(a) is the Fenwick tree transformation.

Time Complexity: O(n * log(n)) per test case
Space Complexity: O(n) for auxiliary arrays

The approach uses the mathematical structure of the Fenwick tree and its inverse transformation.
It processes the array from right to left, using the formula:
- For each index i, compute ans[i] = cal[i]
- Then update cal[j] = cal[j] - coeff * ans[i] mod MOD, where j goes through all indices in the Fenwick tree
- The coefficient is computed iteratively using modular inverse and binomial coefficients.

The key idea is that the transformation f^k can be inverted using a similar process,
by working backwards and using the properties of the Fenwick tree structure.
*/

#include <stdio.h>
#include <iostream>

using namespace std;
const int BUF_SIZE = 1 << 20;
char in_buffer[BUF_SIZE], *ptr = in_buffer, *end_ptr = in_buffer;
char out_buffer[BUF_SIZE];
int out_idx = 0;
inline char next_char() {
  if (ptr == end_ptr) {
    int size = fread(in_buffer, 1, BUF_SIZE, stdin);
    if (size == 0)
      return EOF;
    ptr = in_buffer;
    end_ptr = in_buffer + size;
  }
  return *ptr++;
}
inline int read_int() {
  int num = 0, c;
  while ((c = next_char()) < '0' && c != EOF)
    ;
  do {
    num = (num * 10) + (c - '0');
  } while ((c = next_char()) >= '0');
  return num;
}
inline long long read_ll() {
  long long num = 0, c;
  while ((c = next_char()) < '0' && c != EOF)
    ;
  do {
    num = (num * 10) + (c - '0');
  } while ((c = next_char()) >= '0');
  return num;
}
inline void flush_output() {
  fwrite(out_buffer, 1, out_idx, stdout);
  out_idx = 0;
}
inline void write_ll(long long num) {
  if (num == 0) {
    out_buffer[out_idx++] = '0';
    out_buffer[out_idx++] = ' ';
    return;
  }
  char temp[20];
  int i = 0;
  while (num) {
    temp[i++] = (num % 10) + '0';
    num /= 10;
  }
  while (i--) {
    out_buffer[out_idx++] = temp[i];
  }
  out_buffer[out_idx++] = ' ';
  if (out_idx >= BUF_SIZE)
    flush_output();
}
inline void write_char(char c) {
  if (out_idx == BUF_SIZE)
    flush_output();
  out_buffer[out_idx++] = c;
}
long long f_out[200005];
long long cal[200005];
long long ans[200005];
long long inv[200005];
const long long MOD = 998244353;
inline int lowbit(int x) { return x & (-x); }
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  inv[1] = 1;
  for (int i = 2; i <= 200000; ++i) {
    inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
  }
  int case_num, n, k;
  case_num = read_int();
  while (case_num--) {
    n = read_int();
    k = read_int();
    for (int i = 1; i <= n; ++i) {
      f_out[i] = read_ll();
      cal[i] = f_out[i];
    }
    for (int i = 1; i <= n; ++i) {
      ans[i] = cal[i];
      long long coeff = 1, term_num = 0;
      for (int j = i; j <= n; j += lowbit(j)) {
        cal[j] = (cal[j] - coeff * ans[i] % MOD + MOD) % MOD;
        coeff = coeff * (k + term_num) % MOD * inv[term_num + 1] % MOD;
        ++term_num;
      }
    }
    for (int i = 1; i <= n; ++i) {
      write_ll(ans[i]);
    }
    out_buffer[out_idx++] = '\n';
  }
  flush_output();
  return 0;
}


// https://github.com/VaHiX/CodeForces/