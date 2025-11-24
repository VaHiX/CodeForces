// Problem: CF 1426 A - Floor Number
// https://codeforces.com/contest/1426/problem/A

/*
Problem: A. Floor Number
Algorithms/Techniques: Mathematical computation, ceiling function simulation

Time Complexity: O(t), where t is the number of test cases
Space Complexity: O(1)

Vasya goes to visit his classmate Petya. Vasya knows that Petya's apartment number is n. 
There is only one entrance in Petya's house and the distribution of apartments is the following: 
the first floor contains 2 apartments, every other floor contains x apartments each. 
Apartments are numbered starting from one, from the first floor. 

The task is to find the number of floor on which Petya lives.
*/
#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, x;
    scanf("%ld %ld", &n, &x);
    if (n <= 2) {
      puts("1"); // If apartment number is 1 or 2, Petya lives on the first floor
    } else {
      // Calculate the floor number after the first floor
      // (n - 2 + x - 1) / x computes how many full floors of x apartments are needed
      // Adding 1 accounts for the first floor
      printf("%ld\n", 1 + (n - 2 + x - 1) / x);
    }
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/