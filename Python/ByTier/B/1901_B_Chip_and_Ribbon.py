# Problem: CF 1901 B - Chip and Ribbon
# https://codeforces.com/contest/1901/problem/B

"""
Algorithm: Greedy approach to minimize teleportations.
Time Complexity: O(n) per test case, where n is the length of the array.
Space Complexity: O(1), only using a few variables for computation.

The key insight is that we start at the first cell and must place the chip such that 
the final counts match the given array. We can move the chip rightward or teleport it 
to any position. The optimal strategy is to teleport the chip only when necessary.
If the current cell needs more counts than the previous, we must teleport and move to
reach that level. The difference in counts tells us how many teleports are needed.
"""

def solve():
    n = int(input())
    arr = list(map(int, input().split()))
    ans = arr[0] - 1  # We need to teleport to start at cell 1 and add 1 count to it
    for i in range(1, n):
        # If current cell needs more count than previous, we must teleport
        # and move to reach that level
        if arr[i] > arr[i - 1]:
            ans += arr[i] - arr[i - 1]
    print(ans)


if __name__ == "__main__":
    for _ in range(int(input())):
        solve()


# https://github.com/VaHiX/CodeForces/