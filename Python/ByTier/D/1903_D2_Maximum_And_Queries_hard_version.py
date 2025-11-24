# Problem: CF 1903 D2 - Maximum And Queries (hard version)
# https://codeforces.com/contest/1903/problem/D2

"""
Algorithm: Maximum And Queries (hard version)
Purpose: Given an array and multiple queries with different k values, find the maximum possible bitwise AND
         after at most k operations (each operation increments an element by 1).

Techniques:
- Bit manipulation and prefix sum
- Preprocessing to calculate the cost of achieving certain AND values
- Binary search for queries

Time Complexity: O(n * log(max(a)) + q * log(n))
Space Complexity: O(2^20) = O(1048576) 

The algorithm works by:
1. Preprocessing all possible prefix bits to determine how many operations
   are required to achieve a specific prefix
2. Using dynamic programming to accumulate costs of different bit prefixes
3. For each query, binary search on the precomputed costs to find maximum AND
"""
def II():
    return int(input())
def LII():
    return list(map(int, input().split()))
def MII():
    return map(int, input().split())
import bisect

def main():
    n, q = MII()
    nums = LII()

    # dp[i] represents the number of operations needed to make all elements 
    # have the prefix i in their binary representation
    dp = [0] * (1 << 20)
    for num in nums:
        last = -1
        cur = 0
        for j in range(19, -1, -1):
            if num >> j & 1:
                cur += 1 << j
                x = (1 << j) - (num & (1 << j) - 1)
                dp[cur] += x
                if last != -1:
                    dp[last] -= x
                last = cur

    # Accumulate dp values to get total cost for each prefix
    for j in range(19, -1, -1):
        for i in range(1 << 20):
            if i >> j & 1:
                dp[i - (1 << j)] += dp[i]

    dp[0] = 0
    for i in range(1 << 20):
        if i < len(dp) - 1:
            dp[i + 1] += dp[i]
        dp[i] = n * i - dp[i]

    # Ensure dp is monotonic decreasing
    for j in range((1 << 20) - 2, -1, -1):
        dp[j] = min(dp[j], dp[j + 1])

    # Calculate the total "deficit" (minimum operations needed to set all bits)
    v = sum((1 << 20) - x for x in nums)
    for _ in range(q):
        x = II()
        if x >= v:
            # If we have enough operations, we can set more bits
            print((1 << 20) + (x - v) // n)
        else:
            # Binary search for the maximum AND value possible
            print(bisect.bisect_right(dp, x) - 1)
    return


t = 1
for _ in range(t):
    main()


# https://github.com/VaHiX/CodeForces/