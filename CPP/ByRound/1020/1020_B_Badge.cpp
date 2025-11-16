// Problem: CF 1020 B - Badge
// https://codeforces.com/contest/1020/problem/B

#include <iostream>
// Flowerbox describing the code purpose, algorithms, time and space complexity
/*
 * Problem: Badge
 * Purpose: For each student 'a', determine the student who will receive a second hole in their badge
 *          when the teacher starts with 'a' and follows the chain of accusations until a student
 *          is revisited.
 * Algorithm: Simulation using a visited array 't' to track which starting student 'a' has visited
 *            each student 'j'. When a student is revisited (t[j] >= a), that student is the answer.
 * Time Complexity: O(n^2) in worst case due to nested loops, but typically much faster in practice
 * Space Complexity: O(n) for arrays 'p' and 't'
 */

int a, i, j, n, p[1005], t[1005];
int main() {
  // Read input values into array 'p'
  for (std::cin >> n; i++ < n;)
    std::cin >> p[i];
  
  // For each starting student 'a' from 1 to n
  for (; a++ < n; std::cout << j << ' ')
    // Simulate the process starting from student 'a'
    for (j = a; t[j] < a; j = p[j])
      // Mark current student 'j' as visited by starting student 'a'
      t[j] = a;
}


// https://github.com/VaHiX/CodeForces/