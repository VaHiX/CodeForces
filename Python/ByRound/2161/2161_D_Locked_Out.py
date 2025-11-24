# Problem: CF 2161 D - Locked Out
# https://codeforces.com/contest/2161/problem/D

"""
Algorithm: Dynamic Programming with Segment Processing
Purpose: Find minimum number of elements to remove from array to make it "good", where a good array has no two elements with difference of 1.

Approach:
- For each unique value in array, store indices where it appears.
- Use dynamic programming to keep track of minimum removals required up to each value.
- For each value, calculate the minimum removals needed considering conflicts with previous values (difference of 1).
- The DP state tracks two values:
    - dp[i]: Minimum removals if we include current value
    - dpr[i]: Minimum removals if we don't include current value

Time Complexity: O(n^2) in worst case due to nested operations, but optimized with early exits and preprocessing.
Space Complexity: O(n) for storing indices and DP arrays.

"""

def solve(n: int, A: list[int]) -> int:
    # rev[i] stores all indices where value i appears in the array
    rev = [[] for _ in range(n + 1)]
    for i in range(n):
        rev[A[i]].append(i)

    # dp[i] represents min cost to make subarray good ending at value i (including it)
    # dpr[i] represents min cost to make subarray good ending at value i (excluding it)
    dp = [n] * (n + 1)
    dpr = [n] * (n + 1)
    dp[0] = dpr[0] = 0

    for i in range(n):
        # Update dpr[i+1] with minimum of previous dp and dpr, plus number of elements at current value
        dpr[i + 1] = min(dp[i], dpr[i]) + len(rev[i + 1])
        # dp[i+1] is initialized to dpr[i] (not including current value)
        dp[i + 1] = dpr[i]
        
        base = dp[i]
        # Reverse the indices for current value to process from highest to lowest
        rev[i].reverse()

        z = len(rev[i + 1])
        best = min(z, len(rev[i]))

        ex = 0
        # For each element at i+1, check how many elements at i are before it
        for j in range(z):
            # Remove indices from rev[i] that are less than current index in rev[i+1]
            while rev[i] and rev[i][-1] < rev[i + 1][j]:
                ex += 1
                rev[i].pop()

            # Update best considering conflicting elements
            best = min(best, z - j - 1 + ex)

        # Update dp[i+1] with computed minimum
        dp[i + 1] = min(dp[i + 1], base + best)

    return min(dp[n], dpr[n])


def main():
    import sys

    input = lambda: sys.stdin.readline().rstrip()
    print = lambda s, end="\n": sys.stdout.write(str(s) + end)

    t = int(input())
    for _ in range(t):
        n = int(input())
        A = list(map(int, input().split()))
        res = solve(n, A)
        print(res)


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/