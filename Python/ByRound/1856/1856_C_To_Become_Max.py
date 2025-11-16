# Problem: CF 1856 C - To Become Max
# https://codeforces.com/contest/1856/problem/C

"""
Algorithm: Binary Search on Answer + Prefix Sum + Triangular Number Calculation
Time Complexity: O(n * log(n) * log(max_val + n)) where n is length of array and max_val is max element
Space Complexity: O(n) for prefix sum array

This solution uses binary search on the answer to find the maximum possible value of the array.
For each candidate maximum value, it checks if it's achievable within k operations using
prefix sums and triangular number calculations to efficiently compute required steps.
"""

t = int(input())


def build_stats(arr):
    # Build prefix sum array for efficient range sum queries
    prefix_sum = [None for _ in range(len(arr))]
    for i in range(len(arr)):
        prefix_sum[i] = arr[i] + (prefix_sum[i - 1] if i > 0 else 0)
    return prefix_sum, max(arr)


def triangle_number(n: int):
    # Calculate triangular number: 1 + 2 + ... + n = n*(n+1)/2
    if n == 0:
        return 0
    return n * (n + 1) // 2


def compute_required_steps(
    left_val: int,
    right_val: int,
    start_idx: int,
    end_idx: int,
    prefix_sum: list[int],
    arr: list[int],
):
    # Compute number of operations needed to make subarray [start_idx, end_idx] all equal to right_val
    # Use triangular numbers to calculate how much we would increment
    triangle_left = triangle_number(left_val)
    triangle_right = triangle_number(right_val - 1)
    all_block_count = triangle_left - triangle_right  # Total increments needed
    existing_block_count = prefix_sum[end_idx] - (
        prefix_sum[start_idx - 1] if start_idx > 0 else 0
    )  # Current sum of elements in the range
    return (
        all_block_count
        - existing_block_count
        + (arr[end_idx] - right_val if arr[end_idx] > right_val else 0)
    )


def test_candidate_max(
    candidate_max: int, k: int, prefix_count: list[int], arr: list[int]
):
    # Check if candidate_max is achievable with at most k operations
    start_idx = 0
    end_idx = 0
    left_val = candidate_max
    right_val = candidate_max
    while start_idx < len(arr):
        # Extend window from left until we can form a valid sequence
        while end_idx < len(arr) - 1 and right_val > 0 and right_val > arr[end_idx]:
            end_idx += 1
            right_val -= 1
        # If we reached the end but still need more values
        if end_idx == len(arr) - 1 and right_val > arr[end_idx]:
            return False
        # Compute required steps for current window [start_idx, end_idx]
        steps = compute_required_steps(
            left_val, right_val, start_idx, end_idx, prefix_count, arr
        )
        if steps <= k:
            return True
        start_idx += 1
        right_val += 1  # Move to next possible configuration
    return False


def search_for_max(
    low_val: int, high_val: int, k: int, prefix_sum: list[int], arr: list[int]
):
    # Binary search on maximum possible value
    if low_val == high_val:
        if test_candidate_max(low_val, k, prefix_sum, arr):
            return low_val
        else:
            return -1
    elif high_val - low_val == 1:
        if test_candidate_max(high_val, k, prefix_sum, arr):
            return high_val
        elif test_candidate_max(low_val, k, prefix_sum, arr):
            return low_val
        else:
            return -1
    candidate_max = (low_val + high_val) // 2
    test_result = test_candidate_max(candidate_max, k, prefix_sum, arr)
    if test_result:
        return search_for_max(candidate_max, high_val, k, prefix_sum, arr)
    else:
        return search_for_max(low_val, candidate_max - 1, k, prefix_sum, arr)


def func():
    n, k = map(int, input().split())
    arr = list(map(int, input().split()))
    prefix_sum, max_val = build_stats(arr)
    return search_for_max(max_val, max_val + n, k, prefix_sum, arr)


for _ in range(t):
    print(func())


# https://github.com/VaHiX/CodeForces/