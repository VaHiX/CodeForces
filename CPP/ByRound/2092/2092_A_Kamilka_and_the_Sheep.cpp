// Problem: CF 2092 A - Kamilka and the Sheep
// https://codeforces.com/contest/2092/problem/A

/*
Problem: A. Kamilka and the Sheep

Description:
Kamilka has n sheep with distinct beauty levels. She can choose a non-negative integer d and feed each sheep d bunches of grass,
increasing their beauty by d. Then, she chooses exactly two sheep and takes them to the mountains. The pleasure from this walk
is gcd(x, y), where x and y are the updated beauty levels of the chosen sheep. Find the maximum possible pleasure.

Algorithms/Techniques:
- For each test case, we process the array of beauty values.
- Since adding a constant d to all elements does not affect which pair gives the maximum GCD, 
  the key idea is to consider how different pairs of numbers behave under GCD operations.
- However, since the problem allows choosing any non-negative integer d, and we want to maximize the GCD,
  a better observation is that increasing all values by the same amount d does not change relationships;
  thus, for a fixed pair of elements, the gcd can be computed directly.
- But in fact, for maximizing GCD, one should realize that choosing an appropriate value of d will help
  increase two selected elements to have the highest possible GCD.

Complexity Analysis:
Time Complexity: O(n) per test case, where n is the number of sheep.
Space Complexity: O(1), only using a constant amount of extra memory.

*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n;
    scanf("%ld", &n);
    long mn(1e9), mx(0); // Initialize minimum and maximum values
    for (long p = 0; p < n; p++) {
      long a;
      scanf("%ld", &a);
      mn = (mn < a ? mn : a); // Update minimum value
      mx = (mx > a ? mx : a); // Update maximum value
    }
    printf("%ld\n", mx - mn); // Output the difference between max and min
  }
}


// https://github.com/VaHiX/codeForces/