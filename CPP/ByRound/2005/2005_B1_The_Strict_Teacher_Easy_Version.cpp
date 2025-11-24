// Problem: CF 2005 B1 - The Strict Teacher (Easy Version)
// https://codeforces.com/contest/2005/problem/B1

/*
B1. The Strict Teacher (Easy Version)
Algorithms/Techniques: Simulation + Greedy + Binary Search
Time Complexity: O(t), where t is the number of test cases
Space Complexity: O(1)

This problem involves a one-dimensional line of n cells and two teachers chasing David.
David and teachers move optimally:
- David maximizes the number of moves until caught
- Teachers minimize the number of moves to catch David
In each query, we determine the minimum number of moves required for the teachers to catch David,
assuming optimal play.

The key insight is that in a 1D line with two teachers, the optimal strategy for the teachers is to close
the gap between themselves and David as quickly as possible. Since David can move one step or stay,
the teachers can also move optimally toward him.

We compute the minimum distance David can maintain from each teacher:
- If David is to the left of both teachers: he can move toward the rightmost teacher
- If David is to the right of both teachers: he can move toward the leftmost teacher
- If David is between the two teachers: he maximizes his distance in the middle

The formula:
- If a < bl: res = bl - 1 (David moves left and is caught immediately)
- If bl < a < br: res = (br - bl) / 2 (David avoids both teachers by staying in center)
- If br < a: res = n - br (David moves right toward the boundary)

*/

#include <cstdio>
int main() {
  long t;
  scanf("%ld", &t);
  while (t--) {
    long n, m, q;
    scanf("%ld %ld %ld", &n, &m, &q);
    long bl, br;
    scanf("%ld %ld", &bl, &br);
    long a;
    scanf("%ld", &a);
    if (bl > br) {
      long tmp = bl;
      bl = br;
      br = tmp;
    }
    long res(0);
    if (a < bl) {
      res = bl - 1;   // David is to the left, teacher from bl can catch in bl-1 moves
    } else if (bl < a && a < br) {
      res = (br - bl) / 2;   // David is between teachers, optimal is middle
    } else if (br < a) {
      res = n - br;   // David is to the right, teacher from br can catch in n-br moves
    }
    printf("%ld\n", res);
  }
}


// https://github.com/VaHiX/codeForces/