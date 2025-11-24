// Problem: CF 1362 B - Johnny and His Hobbies
// https://codeforces.com/contest/1362/problem/B

/*
B. Johnny and His Hobbies
time limit per test
1 second
memory limit per test
256 megabytes
input
standard input
output
standard output

Among Johnny's numerous hobbies, there are two seemingly harmless ones: applying bitwise operations and sneaking into his dad's office. As it is usually the case with small children, Johnny is unaware that combining these two activities can get him in a lot of trouble.
There is a set S containing very important numbers on his dad's desk. The minute Johnny heard about it, he decided that it's a good idea to choose a 
positive
 integer k and replace each element s of the set S with s ⊕ k (⊕ denotes the exclusive or operation). 
Help him choose such k that Johnny's dad will not see any difference after his son is done playing (i.e. Johnny will get the same set as before playing). It is possible that no such number exists. It is also possible that there are many of them. In such a case, output the smallest one. Note that the order of elements in a set doesn't matter, i.e. set {1, 2, 3} equals to set {2, 1, 3}.
Formally, find the smallest positive integer k such that {s ⊕ k | s ∈ S} = S or report that there is no such number.
For example, if S = {1, 3, 4} and k = 2, new set will be equal to {3, 1, 6}. If S = {0, 1, 2, 3} and k = 1, after playing set will stay the same.

Algorithms/Techniques: Brute force search for valid k in range [1, N) where N=1024. For each k, compute XOR of all elements in set with k and check if resulting set equals original set.

Time Complexity: O(N^2 * log N), where N = 1024; for each k in range [1,N), we perform a set operation (inserts and comparisons) on at most N elements.
Space Complexity: O(N), to store the sets and intermediate results during computation.
*/

#include <cstdio>
#include <set>
#include <functional>

int main() {
  const int N = 1024;
  int t;
  scanf("%d", &t);
  while (t--) {
    std::set<int> s;
    int n;
    scanf("%d", &n);
    for (int p = 0; p < n; p++) {
      int x;
      scanf("%d", &x);
      s.insert(x); // Insert each element of input set into the set s
    }
    int res(-1);
    for (int u = 1; u < N; u++) {
      std::set<int> w;
      for (std::set<int>::iterator it = s.begin(); it != s.end(); it++) {
        w.insert((*it) ^ u); // Compute XOR of each element in s with u and insert into w
      }
      if (s == w) {  // Check if transformed set equals original set
        res = u;
        break;
      }
    }
    printf("%d\n", res);
  }
  return 0;
}


// https://github.com/VaHiX/codeForces/