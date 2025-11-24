// Problem: CF 1136 A - Nastya Is Reading a Book
// https://codeforces.com/contest/1136/problem/A

/*
 * Problem: A. Nastya Is Reading a Book
 * Algorithms/Techniques: Simulation
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 *
 * Nastya is reading a book with n chapters. Each chapter has a range of pages.
 * She marks the first unread page as k. We need to count how many chapters are
 * either not started or partially read (i.e., not fully completed).
 */

#include <cstdio>
#include <vector>
int main() {
  long n;
  scanf("%ld", &n);
  std::vector<long> a(n);  // Store the ending page of each chapter
  for (long p = 0; p < n; p++) {
    long x, y;
    scanf("%ld %ld", &x, &y);
    a[p] = y;  // Store the end page of chapter p
  }
  long k;
  scanf("%ld", &k);
  long cnt(0);
  for (long p = 0; p < n; p++) {
    cnt += (a[p] >= k);  // Count chapters where ending page >= k (not fully read)
  }
  printf("%ld\n", cnt);
  return 0;
}


// https://github.com/VaHiX/codeForces/