// Problem: CF 1020 B - Badge
// https://codeforces.com/contest/1020/problem/B

/*
B. Badge
Algorithm: Simulation of a directed graph traversal to find the first node that is visited twice in a path starting from each node.
Time Complexity: O(n^2) in worst case due to nested loops, but often much better in practice due to early termination.
Space Complexity: O(n) for the arrays p and t.

The problem simulates a process where a teacher follows a chain of accusations until a student is revisited.
We track for each starting student 'a', which student gets the second hole (i.e., is visited twice).
This is essentially finding the first repeated node in a path starting from every node.
*/
#include <iostream>
int a, i, j, n, p[1005], t[1005]; // a: current starting student, i: loop counter, j: current student in chain, n: number of students, p[]: accusation mapping, t[]: tracking visited students
int main() {
  for (std::cin >> n; i++ < n;) // Read all p values into array p
    std::cin >> p[i];
  for (; a++ < n; std::cout << j << ' ') // For each starting student from 1 to n
    for (j = a; t[j] < a; j = p[j]) // Traverse chain until a student is revisited (t[j] >= a)
      t[j] = a; // Mark j as visited in this traversal
}


// https://github.com/VaHiX/codeForces/