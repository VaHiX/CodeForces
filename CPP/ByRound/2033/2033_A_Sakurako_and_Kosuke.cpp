// Problem: CF 2033 A - Sakurako and Kosuke
// https://codeforces.com/contest/2033/problem/A

/*
A. Sakurako and Kosuke
time limit per test1 second
memory limit per test256 megabytes

Algorithms/Techniques: Simulation, Game Theory

The game involves two players taking turns moving a dot on a number line starting at position 0.
- Sakurako moves first (player 1) and always moves in the negative direction.
- Kosuke moves second (player 2) and always moves in the positive direction.
- On the i-th move, the player moves the dot by (2*i - 1) units in their respective direction.
- The game ends when the absolute value of the dot's position exceeds n.

Simulate the process to determine who makes the last move.
Time Complexity: O(n) per test case, as we simulate moves up to n.
Space Complexity: O(1), only using a few variables for simulation.
*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    n = (n > 0 ? n : -n); // Ensure n is positive (though input is already positive)
    puts(n % 2 ? "Kosuke" : "Sakurako"); // If n is odd, Kosuke makes the last move; else Sakurako
  }
}


// https://github.com/VaHiX/codeForces/