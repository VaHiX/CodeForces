// Problem: CF 1263 D - Secret Passwords
// https://codeforces.com/contest/1263/problem/D

/*
D. Secret Passwords
time limit per test
1 second
memory limit per test
256 megabytes
input
standard input
output
standard output
One unknown hacker wants to get the admin's password of AtForces testing system, to get problems from the next contest. To achieve that, he sneaked into the administrator's office and stole a piece of paper with a list of n passwords — strings, consists of small Latin letters.
Hacker went home and started preparing to hack AtForces. He found that the system contains only passwords from the stolen list and that the system determines the equivalence of the passwords a and b as follows:

 two passwords a and b are equivalent if there is a letter, that exists in both a and b; 
 two passwords a and b are equivalent if there is a password c from the list, which is equivalent to both a and b. 
If a password is set in the system and an equivalent one is applied to access the system, then the user is accessed into the system.
For example, if the list contain passwords "a", "b", "ab", "d", then passwords "a", "b", "ab" are equivalent to each other, but the password "d" is not equivalent to any other password from list. In other words, if:

 admin's password is "b", then you can access to system by using any of this passwords: "a", "b", "ab"; 
 admin's password is "d", then you can access to system by using only "d". 
Only one
 password from the list is the admin's password from the testing system. Help hacker to calculate the minimal number of passwords, required to 
guaranteed
 access to the system. Keep in mind that the hacker does not know which password is set in the system.

Algorithm: Union-Find (Disjoint Set Union)
Time Complexity: O(N * M * α(N)) where N is number of passwords, M is average length of passwords, α is inverse Ackermann function
Space Complexity: O(N)

This solution uses a union-find data structure to group equivalent passwords together based on shared letters. 
Each character represents a node in the union-find structure. If two passwords share at least one letter, they are connected.
The final count of distinct root nodes in the union-find structure gives the minimum number of passwords needed.
*/

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

int main() {
  const long N = 26;
  long n;
  std::cin >> n;
  std::vector<long> v(N, 0);  // Union-find parent array
  for (long p = 0; p < N; p++) {
    v[p] = p;  // Initialize each element to be its own parent
  }
  std::vector<bool> w(N, 0);  // Tracks which letters appear in any password
  for (long p = 0; p < n; p++) {
    std::string x;
    std::cin >> x;
    std::vector<bool> f(N, 0);  // Flag to track letters present in current password
    for (long p = 0; p < x.size(); p++) {
      w[x[p] - 'a'] = f[x[p] - 'a'] = 1;  // Mark the letter as appearing in this password
    }
    long head;
    for (long p = 0; p < N; p++) {
      if (f[p]) {  // Find first letter that exists in current password
        head = v[p];  // Set head to root of this letter
        break;
      }
    }
    for (long p = 0; p < N; p++) {
      if (f[p]) {
        v[v[p]] = head;  // Union the parent of current letter with head 
        v[p] = head;     // Set current letter's parent to head
      }
    }
  }
  long cnt(0);
  for (long p = 0; p < N; p++) {
    cnt += w[p] * (v[p] == p);  // Count number of unique roots among letters that appear in passwords
  }
  printf("%ld\n", cnt);
  return 0;
}


// https://github.com/VaHiX/codeForces/