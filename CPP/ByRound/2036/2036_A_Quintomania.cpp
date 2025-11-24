// Problem: CF 2036 A - Quintomania
// https://codeforces.com/contest/2036/problem/A

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t); // Read number of melodies
  while (t--) {
    long n;
    scanf("%ld", &n); // Read number of notes in current melody
    long prev;
    scanf("%ld", &prev); // Read first note
    bool perfect(true); // Assume melody is perfect initially
    for (long p = 1; p < n; p++) { // Loop through remaining notes
      long x;
      scanf("%ld", &x); // Read next note
      long diff = x - prev; // Calculate difference between current and previous note
      if (diff < 0) {
        diff = -diff; // Make sure difference is positive
      }
      if (diff != 5 && diff != 7) { // If difference is not 5 or 7, melody is not perfect
        perfect = false;
      }
      prev = x; // Update previous note to current for next iteration
    }
    puts(perfect ? "YES" : "NO"); // Output result based on flag
  }
}

// https://github.com/VaHiX/codeForces/