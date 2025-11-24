// Problem: CF 678 B - The Same Calendar
// https://codeforces.com/contest/678/problem/B

#include <cstdio>
bool isLeap(int n) {
  return (n % 400 == 0) || ((n % 4 == 0) && (n % 100 != 0));
}
int main() {
  long y;
  scanf("%ld", &y);
  long next = y;
  int diff(0);
  while (true) {
    diff += 1 + isLeap(next); // Increment by 1 day for regular year, 2 for leap year
    ++next; // Move to the next year
    if (diff % 7 == 0 && isLeap(next) == isLeap(y)) { // If days of week align and leap status matches
      break;
    }
  }
  printf("%ld\n", next);
  return 0;
}

// https://github.com/VaHiX/codeForces/