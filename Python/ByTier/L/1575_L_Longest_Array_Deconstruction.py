# Problem: CF 1575 L - Longest Array Deconstruction
# https://codeforces.com/contest/1575/problem/L

"""
Algorithm: Longest Array Deconstruction
Purpose: Given a sequence, find the maximum number of indices where a_i == i after removing some elements.
Technique: 
    - Use greedy approach with binary search to compute LIS (Longest Increasing Subsequence).
    - For each valid element (a[i] > i), we consider it as a candidate for building an increasing subsequence.
    - The problem reduces to finding the length of the longest increasing subsequence among such candidates.

Time Complexity: O(n log n)
Space Complexity: O(n)

This uses a modified version of the Longest Increasing Subsequence algorithm using binary search
to efficiently track the smallest tail of increasing subsequences.
"""

def length_of_lis(a):
    if not a:
        return 0
    n = len(a)
    tails = [0] * n  # Array to store the smallest tail element for each length
    size = 0         # Current size of the LIS
    for num in a:
        left, right = 0, size  # Binary search bounds
        while left < right:
            mid = (left + right) // 2
            if tails[mid] < num:
                left = mid + 1
            else:
                right = mid
        tails[left] = num   # Place num at the correct position in tails
        size = max(size, left + 1)  # Update the maximum length achieved
    return size


def solution(n: int, a: list[int]) -> int:
    index = [[] for _ in range(n)]  # Group elements based on (i - a[i])
    for i, num in enumerate(a):
        i += 1  # Convert to 1-based indexing
        if not num > i:  # Only consider values where a[i] > i
            index[i - num].append(num)
    flattened_index = [element for sublist in index for element in sublist]  # Flatten all groups
    if not flattened_index:
        return 0
    # Return the length of the longest increasing subsequence among valid elements
    return length_of_lis(flattened_index)


if __name__ == "__main__":
    n = int(input())
    a = list(map(int, input().split()))
    print(solution(n, a))


# https://github.com/VaHiX/codeForces/