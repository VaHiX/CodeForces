# Problem: CF 1899 C - Yarik and Array
# https://codeforces.com/contest/1899/problem/C

"""
Algorithm: Dynamic Programming with Kadane's Algorithm adaptation
Technique: Modified maximum subarray sum where we enforce alternating parity constraint

Time Complexity: O(n) - Single pass through the array
Space Complexity: O(1) - Only using a few variables for tracking

The algorithm maintains a running maximum subarray sum where adjacent elements have different parities.
When a number with the same parity as the previous one is encountered, we start a new subarray from that number.
Otherwise, we extend the current subarray by adding the current number to it.
"""

import sys


def solution(arr):
    n = len(arr)
    max_out = arr[0]  # Initialize global maximum with first element
    curr_max_out = arr[0]  # Initialize current subarray maximum
    last_in_arr_parity = arr[0] % 2  # Store parity (0 for even, 1 for odd) of last included element
    for i in range(1, n):
        curr_num = arr[i]
        # Check if current number has same parity as the last included number
        if last_in_arr_parity == (curr_num % 2):
            # If same parity, start a new subarray from current number
            curr_max_out = curr_num
        else:
            # If different parity, extend current subarray
            if curr_max_out < 0:
                # If current subarray sum is negative, start fresh
                curr_max_out = curr_num
            else:
                # Otherwise, add current number to existing subarray
                curr_max_out += curr_num
            # Update the parity of the last included number
            last_in_arr_parity = curr_num % 2
        # Update global maximum
        max_out = max(max_out, curr_max_out)
    return max_out


numbers = []
for i, line in enumerate(sys.stdin):
    if i == 0:
        continue
    if i % 2 == 0:
        lst = list(int(x) for x in line.strip().split())
        numbers.append(lst)
for arr in numbers:
    print(solution(arr))


# https://github.com/VaHiX/CodeForces/