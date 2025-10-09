/*
 * Problem URL : https://codeforces.com/problemset/problem/1200/A
 * Submit Date : 2025-08-21
 */

#import <ios>
char a[100002], b[11], *A = a, i, j = 9;
main() {
  for (gets(gets(a) + 1); *A++; i = 0, j = 9)
    while (*A == 'L'   ? b[i] ? ++i : !++b[i]
             : *A == 'R' ? b[j] ? j-- : !++b[j]
             : *A ? b[*A - '0'] = 0
           : i == 10   ? puts(b)
                       : b[i++] += 48)
      ;
}