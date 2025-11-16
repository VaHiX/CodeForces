# Problem: CF 2162 A - Beautiful Average
# https://codeforces.com/contest/2162/problem/A

"""
Maximum Average Subarray
Algorithm: Greedy
Time Complexity: O(n)
Space Complexity: O(1)

The problem asks for the maximum average of any subarray in the given array.
The key insight is that the maximum average will always be achieved by a subarray
of length 1 containing the maximum element in the array. This is because if we have
any subarray with a larger average, we could always increase it by including more
of the maximum elements or by extending the subarray to include this maximum element.

Thus, the solution is simply to find the maximum element in the array.
"""

from sys import stdin as inp
from sys import stdout as out

for t in range(int(inp.readline())):
    n = int(inp.readline())
    a = list(map(int, inp.readline().split()))
    out.write(str(max(a)) + "\n")


# https://github.com/VaHiX/CodeForces/