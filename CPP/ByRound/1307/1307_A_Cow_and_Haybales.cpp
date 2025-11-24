// Problem: CF 1307 A - Cow and Haybales
// https://codeforces.com/contest/1307/problem/A

/*
A. Cow and Haybales
Algorithms/Techniques: Greedy approach, simulation of moves

Time Complexity: O(n * d) per test case, where n is number of piles and d is days
Space Complexity: O(n) for storing the array of haybales

The problem involves moving haybales from adjacent piles to pile 1 over a fixed number of days.
We use a greedy strategy: for each pile after the first, we calculate how many moves are needed 
to transfer all haybales from that pile to pile 1. We prioritize transferring haybales from 
piles closest to pile 1 first (since they require fewer moves per haybale).
*/

#include <cstdio>
#include <vector>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, d;
    scanf("%ld %ld", &n, &d);
    std::vector<long> a(n);
    for (long p = 0; p < n; p++) {
      scanf("%ld", &a[p]);
    }
    long s(a[0]); // Start with the initial amount in pile 1
    for (long p = 1; p < n; p++) {
      long x = (d / p); // Calculate maximum moves possible from pile p to pile 1
      x = (x < a[p]) ? x : a[p]; // Limit by available haybales in pile p
      d -= x * p; // Decrease remaining days by the actual number of moves made
      s += x; // Add moved haybales to pile 1
    }
    printf("%ld\n", s);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/