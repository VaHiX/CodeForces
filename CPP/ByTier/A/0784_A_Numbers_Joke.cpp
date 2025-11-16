// Problem: CF 784 A - Numbers Joke
// https://codeforces.com/contest/784/problem/A

/*
 * Code Purpose: This program outputs a specific integer from a precomputed array based on the input value.
 *               The array contains a sequence of integers related to a mathematical or recreational problem.
 * 
 * Algorithms/Techniques: Direct lookup in a precomputed array.
 * 
 * Time Complexity: O(1) - Constant time lookup.
 * Space Complexity: O(1) - Fixed size array of 50 integers, independent of input size.
 */

#include <cstdio>
int main() {
  // Precomputed array of integers corresponding to the sequence
  int v[] = {0,   4,   22,  27,  58,  85,  94,   121,  166, 202, 265,
             274, 319, 346, 355, 378, 382, 391,  438,  454, 483, 517,
             526, 535, 562, 576, 588, 627, 634,  636,  645, 648, 654,
             663, 666, 690, 706, 728, 729, 762,  778,  825, 852, 861,
             895, 913, 915, 922, 958, 985, 1086, 1111, 1165};
  int a; // Input variable
  scanf("%d", &a); // Read input value
  printf("%d\n", v[a]); // Output the corresponding value from the array
  return 0;
}


// https://github.com/VaHiX/CodeForces/