# Problem: CF 1912 A - Accumulator Apex
# https://codeforces.com/contest/1912/problem/A

"""
Code Purpose:
This code solves the "Accumulator Apex" game problem where Allyn starts with an accumulator value x and k lists of integers.
The goal is to maximize x by selecting elements from lists (from left to right) such that at each step, the resulting x remains non-negative.

Approach:
- For each list, compress consecutive positive/negative numbers into segments.
- Use a greedy algorithm with prioritization based on minimum prefix sum.
- Maintain a priority queue of valid operations sorted by minimum prefix sum (descending).
- Iterate through operations and select those that increase the final accumulator value while maintaining non-negativity.

Time Complexity: O(N log N) where N is the total number of elements across all lists (due to sorting)
Space Complexity: O(N) for storing compressed lists and intermediate data structures

Algorithms/Techniques:
- Segment compression
- Greedy selection with prefix sum tracking
- Priority-based decision making
"""

from sys import maxsize, stdin, stdout


def solve():
    x, k = map(int, stdin.buffer.readline().decode().split())
    filtered = list()
    for i in range(k):
        nums = compress(map(int, stdin.buffer.readline().decode().split()))
        sigma = 0
        MIN = maxsize
        for num in nums:
            sigma += num
            MIN = min(MIN, sigma)
            if sigma > 0:  # Only consider segments that result in positive sums
                filtered.append([MIN, sigma, i])
    filtered.sort(key=lambda item: item[0], reverse=True)  # Sort by minimum prefix sum descending
    i = 0
    memo = [0] * k
    while i < len(filtered) and x + filtered[i][0] >= 0:
        if filtered[i][1] > memo[filtered[i][2]]:  # If this segment improves previous selection
            x -= memo[filtered[i][2]]
            memo[filtered[i][2]] = filtered[i][1]
            x += filtered[i][1]
        i += 1
    return x


def compress(nums):
    next(iter(nums))  # Skip length, consume it
    result = [next(iter(nums))]  # First element
    for num in nums:
        if num >= 0 and result[-1] >= 0:
            result[-1] += num  # Merge consecutive positives
        else:
            result.append(num)
    return result


def main():
    stdout.write(f"{solve()}\n")


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/codeForces/