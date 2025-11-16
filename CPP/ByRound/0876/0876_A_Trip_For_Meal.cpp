// Problem: CF 876 A - Trip For Meal
// https://codeforces.com/contest/876/problem/A

/*
 * Code Purpose:
 * This program calculates the minimum distance Winnie-the-Pooh must travel 
 * to have exactly 'n' meals at his friends' houses, starting from Rabbit's house.
 * 
 * The three friends (Rabbit, Owl, Eeyore) live in a triangle structure, with 
 * distances a (Rabbit-Owl), b (Rabbit-Eeyore), and c (Owl-Eeyore).
 * 
 * Winnie starts at Rabbit's house and must visit friends to eat, following 
 * the path that minimizes overall distance.
 * 
 * Algorithm:
 * - If n == 1, no travel is needed.
 * - Otherwise, we calculate the minimum distance by choosing the shorter 
 *   path between Rabbit-Owl and Rabbit-Eeyore, and then add (n-2) times the 
 *   shortest among the three paths.
 * 
 * Time Complexity: O(1) - constant time operations.
 * Space Complexity: O(1) - constant space usage.
 */

#include <cstdio>
int main() {
  long n;
  scanf("%ld", &n);
  long a, b, c;
  scanf("%ld %ld %ld", &a, &b, &c);
  if (n == 1) {
    puts("0");
  } else {
    int d = (a < b) ? a : b; // Choose the shorter path from Rabbit to either Owl or Eeyore
    long total = d + (n - 2) * ((d < c) ? d : c); // Add (n-2) times the shortest edge
    printf("%ld\n", total);
  }
  return 0;
}


// https://github.com/VaHiX/CodeForces/