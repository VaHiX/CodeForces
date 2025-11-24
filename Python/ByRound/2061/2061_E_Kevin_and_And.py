# Problem: CF 2061 E - Kevin and And
# https://codeforces.com/contest/2061/problem/E

"""
E. Kevin and And

Problem Description:
Kevin has a sequence 'a' of length n and m types of magic represented by integers 'b'. Each magic operation allows him to perform bitwise AND of an element in 'a' with a value from 'b'. The goal is to minimize the sum of elements in 'a' after at most k such operations.

Approach:
1. For each element in sequence 'a', we compute possible improvements (reductions) that can be made using subsets of magic elements.
2. We use bitmask enumeration to generate all subsets of 'b' and calculate their bitwise OR results.
3. For every possible subset size, we store the minimum possible values a[i] could reduce to when applied with those magic combinations.
4. Using dynamic programming and greedy selection on differences, compute the best 'k' improvements.

Time Complexity:
- O(2^m * n + n * m * k), where 2^m is for generating all subsets, n for processing elements, and k for selection of top k gains.

Space Complexity:
- O(2^m * n), for storing cost reductions per subset size.

"""

import io
import os

input = io.BytesIO(os.read(0, os.fstat(0).st_size)).readline


def main():
    m, n, k = map(int, input().split())  # Read n, m, k from input
    a = list(map(int, input().split()))  # Read sequence 'a'
    b = list(map(int, input().split()))  # Read magic values 'b'
    MAX = (1 << 30) - 1  # Max value for bit manipulation (2^30 - 1)
    # Flip all bits in array 'b' to simulate AND using OR and inversion
    b = [MAX - num for num in b]
    costs = [[] for _ in range(n + 1)]  # For storing bitwise OR results for subsets of different sizes

    # Recursive function to generate all subsets of 'b' and compute their OR values
    def getnext(index, pre, curr):
        if index == n:
            if len(pre) > 0:
                costs[len(pre) - 1].append(curr)
            return
        getnext(index + 1, pre, curr)
        pre.append(b[index])
        getnext(index + 1, pre, curr | b[index])
        pre.pop()

    getnext(0, [], 0)  # Start recursion

    save = []

    # For each element in 'a', evaluate how much it can reduce using combinations from 'b'
    for num in a:
        nums = [num]  # Store potential values of changing current element
        for i in range(n):
            minimum = num  # Default minimum is no change
            for sub in costs[i]:  # Go through previously calculated subset OR values
                minimum = min(minimum, (~sub) & num)  # Apply inversion and AND to get real decrease
            nums.append(minimum)
        diff = [nums[i] - nums[i + 1] for i in range(len(nums) - 1)]  # Difference between states
        save.extend(diff)  # Add all changes for this element

    save.sort(reverse=True)  # Sort differences in descending order for greedy selection
    print(sum(a) - sum(save[:k]))  # Compute final sum after applying top k improvements


T = int(input())
t = 1
while t <= T:
    main()
    t += 1


# https://github.com/VaHiX/codeForces/