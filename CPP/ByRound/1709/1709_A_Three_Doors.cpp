// Problem: CF 1709 A - Three Doors
// https://codeforces.com/contest/1709/problem/A

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long x;
    scanf("%ld", &x);
    long v[4] = {0}; // Array to store keys behind doors (index 1-3)
    for (long p = 1; p < 4; p++) {
      scanf("%ld", v + p); // Read the key behind each door
    }
    // Check if we can open all doors:
    // - v[x] != 0 means there's a key behind the door with number x (we can get it)
    // - v[v[x]] != 0 means that key we got leads to another door which also has a key
    puts(((v[x] != 0) && (v[v[x]] != 0)) ? "YES" : "NO");
  }
}


// https://github.com/VaHiX/codeForces/