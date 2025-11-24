# Problem: CF 1894 C - Anonymous Informant
# https://codeforces.com/contest/1894/problem/C

"""
Algorithm: Simulation with cycle detection
Time Complexity: O(min(n, k)) per test case
Space Complexity: O(1)

The problem involves determining whether a given array b can be obtained 
from some initial array a through k operations, where each operation 
consists of choosing a fixed point x (a[x] == x) and cyclically shifting 
the array left by x positions. 

The solution simulates the reverse process: starting from the end of array b,
we trace back how the array would have looked before each operation. 
If we encounter a value greater than n at any point, it's invalid since 
fixed points must be within [1, n]. Also, if we go out of bounds during 
simulation, we wrap around using modular arithmetic.
"""

List = list


class Solution:
    def cf(self):
        n, k = map(int, input().split())
        b = list(map(int, input().split()))
        # If maximum element is <= n, it's possible that all elements 
        # could have been valid fixed points
        if max(b) <= n:
            print("Yes")
        else:
            ans = "Yes"
            ind = n  # Start from the last index
            # Simulate for min(n, k) steps, as after n steps we 
            # would've completed a full cycle
            for _ in range(min(n, k)):
                # If the value at current index exceeds n, it's invalid
                if b[ind - 1] > n:
                    ans = "No"
                    break
                # Move backward by the value at current position
                ind -= b[ind - 1]
                # Wrap around if needed
                if ind < 0:
                    ind += n
            print(ans)


t = int(input())
for i in range(t):
    res = Solution().cf()


# https://github.com/VaHiX/CodeForces/