/*
 * Problem URL : https://codeforces.com/problemset/submit
 * Submit Date : 2025-08-24
 */

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const char chr[] = "0123456789abcdef";
const int I0 = 65520, ZERO = 256 << 4, ONE = 257 << 4, INF = 65535;

int program[4096];

int main() {
  int n;
  scanf("%d", &n);

  program[256] = 0, program[257] = 65535;
  for (int a = 0; a < 16; a++) {
    int Z = a * 16;
    program[Z] = I0 + a, program[Z + 1] = (Z + 6) * 16 + 2,
    program[Z + 2] = Z + 4;
    program[Z + 4] = 0, program[Z + 5] = 0, program[Z + 6] = Z + 8;
    program[Z + 8] = 0, program[Z + 9] = 0, program[Z + 10] = Z + 16;
    program[Z + 12] = ZERO, program[Z + 13] = I0, program[Z + 14] = INF;

    if (a == 15) {
      program[Z + 8] = ONE, program[Z + 9] = I0, program[Z + 10] = INF;
    }

    int b = (n >> a) & 1;
    if (b)
      for (int c = Z + 8; c < Z + 12; c++)
        swap(program[c], program[c + 4]);
  }

  /// print
  for (int i = 0; i <= 300; i++) {
    string s;
    int x = program[i];
    for (int turn = 0; turn < 4; turn++)
      s.push_back(chr[x & 15]), x >>= 4;
    reverse(s.begin(), s.end());
    cout << s << ' ';
  }
}
