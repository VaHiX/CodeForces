# Problem: CF 1969 C - Minimizing the Sum
# https://codeforces.com/contest/1969/problem/C

"""
Algorithm: Dynamic Programming with Optimization
Approach: 
- For each position and number of operations, we compute the minimum sum ending at that position.
- We maintain a DP table `f[i][j]` where `i` is the index in the array and `j` is the number of operations used.
- At each step, we consider all possible previous positions from which we can perform operations to minimize the sum.
- For every possible group of operations (up to `j` operations), we calculate the minimum value in that group and update the DP state.

Time Complexity: O(n * k^2) where n is the length of array and k is the maximum number of operations.
Space Complexity: O(n * k) for the DP table.

This solution is optimized for the constraints where sum of n over test cases is at most 3 * 10^5.
"""
def solve() -> None:
    n, k = map(int, input().split())
    arr = [int(x) for x in input().split()]
    # Initialize DP table where f[i][j] represents the minimum sum up to index i using j operations
    f = [[0] * (k + 1) for _ in range(n + 1)]
    for i, num in enumerate(arr):
        for j in range(k + 1):
            # Default case: do not perform any operation at current index
            f[i + 1][j] = f[i][j] + arr[i]
            # Try all possible previous positions to apply operations
            mn = arr[i]
            for t in range(1, min(j, i) + 1):
                mn = min(mn, arr[i - t])
                # Update the minimum sum by considering t operations from i-t to i
                f[i + 1][j] = min(f[i + 1][j], f[i - t][j - t] + mn * (t + 1))
    print(f[n][k])


for _ in range(int(input())):
    solve()


# https://github.com/VaHiX/CodeForces/