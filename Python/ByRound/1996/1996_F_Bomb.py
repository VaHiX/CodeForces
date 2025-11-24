# Problem: CF 1996 F - Bomb
# https://codeforces.com/contest/1996/problem/F

"""
Algorithm: Binary Search + Mathematical Summation
Techniques: 
- Binary search on the answer to find the highest possible value we can achieve
- For each value, compute how many operations are needed using arithmetic sequence sum formula
- Once we know the maximum achievable value, calculate the total score using summation

Time Complexity: O(n * log(max(a))) where n is the array length and max(a) is the maximum value in array a
Space Complexity: O(1) - only using a few variables for computation, no extra space needed
"""

import sys

input = sys.stdin.readline


def count_terms_and_sum(a, b, x):
    # If a is less than x, no terms can be counted
    if a < x:
        return 0, 0
    # Compute how many terms are in the arithmetic sequence from x to a with step b
    t = (a - x) // b + 1
    # Compute the last term in the sequence
    last = a - (t - 1) * b
    # Compute sum of the arithmetic sequence
    s = t * (a + last) // 2
    return t, s


def solve():
    t = int(input())
    for _ in range(t):
        n, k = map(int, input().split())
        a = list(map(int, input().split()))
        b = list(map(int, input().split()))
        left, right = 0, max(a)
        while left < right:
            mid = (left + right + 1) // 2
            total = 0
            for i in range(n):
                if a[i] >= mid:
                    # Count how many operations needed for current a[i] to reach value `mid`
                    total += (a[i] - mid) // b[i] + 1
                    if total > k:
                        break
            if total >= k:
                # If we can perform at least k operations, try higher value
                left = mid
            else:
                # If we can't perform k operations, try lower value
                right = mid - 1
        total = 0
        total_sum = 0
        for i in range(n):
            # Compute how many terms and their sum for values >= (left + 1)
            cnt, s = count_terms_and_sum(a[i], b[i], left + 1)
            total += cnt
            total_sum += s
        # Handle remaining operations that can't be completed with full sequence
        rem = k - total
        total_sum += rem * left
        print(total_sum)


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/CodeForces/