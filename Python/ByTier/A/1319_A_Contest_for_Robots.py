# Problem: CF 1319 A - Contest for Robots
# https://codeforces.com/contest/1319/problem/A

"""
Algorithm: Binary String Reachability
Time Complexity: O(n)
Space Complexity: O(1)

This problem deals with determining whether one substring of a binary string is reachable from another 
substring using specific operations. The key insight is that the operations allow us to transform 
"011" to "110" and vice versa. 

The reachability is determined by counting how many "01" and "10" patterns appear in the strings.
If we are able to transform one string to another, the number of such patterns must be consistent.

We calculate the number of transitions from 0 to 1 (s) and 1 to 0 (f) and use them to determine 
if transformation is possible.
"""

n = int(input())
r = list(map(int, input().split()))  # First binary string
b = list(map(int, input().split()))  # Second binary string
f = 0  # Count of transitions from 1 to 0
s = 0  # Count of transitions from 0 to 1
for i in range(n):
    if r[i] == 1 and b[i] == 0:
        f += 1  # Increment if we find a transition from 1 to 0
    if r[i] == 0 and b[i] == 1:
        s += 1  # Increment if we find a transition from 0 to 1
if f == 0:
    print(-1)  # No transformation possible if no 1->0 transitions
else:
    print(s // f + 1)  # Calculate the minimum number of operations needed


# https://github.com/VaHiX/CodeForces/