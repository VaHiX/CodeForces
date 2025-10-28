# Problem: CF 1864 E - Guess Game
# https://codeforces.com/contest/1864/problem/E

"""
Algorithm: Guess Game
Purpose: Calculate the expected number of turns in a guessing game between Alice and Bob,
         where they try to determine the relationship between two values a and b,
         given a OR b and their individual values.

Approach:
1. For each pair of indices (i_a, i_b), we consider all combinations of values a and b,
   where a = s[i_a], b = s[i_b].
2. We compute the number of turns required for the game to end using logic based on
   bitwise OR information.
3. Use stack-based method to efficiently calculate sum of minimums in subarrays.
4. Preprocess the sorted array to calculate contributions from equal elements.
5. Final formula combines these contributions with modular arithmetic.

Time Complexity: O(n log n) per test case due to sorting and stack operations.
Space Complexity: O(n) for storing array elements and stacks.
"""

import sys

input = sys.stdin.readline
mod = 998244353


def f(a, b):
    """
    Calculates the number of turns needed to determine the relationship between a and b
    based on the bitwise OR operation and the value of a OR b.
    Returns the number of turns.
    
    Args:
        a (int): Value of a (from s[i_a])
        b (int): Value of b (from s[i_b])
    
    Returns:
        int: Number of turns.
    """
    cnt = 0
    for i in range(30, -1, -1):  # From most significant bit to least
        if a & (1 << i) == b & (1 << i) != 0:
            cnt += 1
        elif a & (1 << i) != b & (1 << i):
            break
    return cnt


def g(arr):
    """
    Calculates the sum of minimums of all subarrays using a stack-based approach.
    
    Args:
        arr (list): Array of integers representing the number of turns needed for
                    pairs of elements that differ.
    
    Returns:
        int: Sum of minimums of subarrays.
    """
    stack = []
    sum_of_minimums = 0
    for i in range(len(arr) + 1):
        while stack and (i == len(arr) or arr[stack[-1]] >= arr[i]):
            mid = stack.pop()
            left_boundary = -1 if not stack else stack[-1]
            right_boundary = i
            count = (mid - left_boundary) * (right_boundary - mid)
            sum_of_minimums = sum_of_minimums + (count * arr[mid])
        stack.append(i)
    return sum_of_minimums


t = int(input())
for _ in range(t):
    n = int(input())
    s = sorted(list(map(int, input().split())))  # Sort the sequence
    
    # Initialize the total expected turns count
    ans = n * (n - 1) // 2  # Total number of pairs
    
    # Count and subtract duplicates
    curr = 1
    for i in range(1, n):
        if s[i] == s[i - 1]:
            curr += 1
        else:
            ans -= curr * (curr - 1) // 2
            curr = 1
    ans -= curr * (curr - 1) // 2

    l = []
    for i in range(n):
        # Add turn count for same elements (a=b case)
        ans += f(s[i], s[i]) + 1
        if i < n - 1:
            # Add turn count differences for adjacent elements
            l.append(f(s[i], s[i + 1]) + 1)
    
    # Final calculation of expected value using modular arithmetic
    ans = ((ans + 2 * g(l)) * pow(n, 2 * (mod - 2), mod)) % mod
    print(ans)


# https://github.com/VaHiX/CodeForces/