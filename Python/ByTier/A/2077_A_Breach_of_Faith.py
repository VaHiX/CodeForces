# Problem: CF 2077 A - Breach of Faith
# https://codeforces.com/contest/2077/problem/A

"""
Problem: Recover a sequence a of 2n+1 elements from a shuffled sequence b of 2n elements,
where one element was deleted from a. The sequence a must satisfy:
a[0] = a[1] - a[2] + a[3] - a[4] + ... + a[2n] - a[2n+1]

Approach:
- Sort the given array b.
- Reconstruct the sequence a by placing elements in specific positions based on the formula.
  - Even indices (0, 2, 4, ...) are filled with elements from the second half of sorted b.
  - Odd indices (1, 3, 5, ...) are filled with elements from first half of sorted b.
  - The last element is calculated as difference between sums of two halves.

Time Complexity: O(n log n) due to sorting step
Space Complexity: O(n) for storage of arrays
"""

for test_case in range(int(input())):
    n = int(input())
    b = sorted([int(_) for _ in input().split()])  # Sort the given sequence
    a = [0 for _ in range(2 * n + 1)]              # Initialize result array
    
    # Fill even positions (0, 2, 4, ...) with elements from the second half of b
    for i in range(0, n + 1):
        a[2 * i] = b[n + i - 1]
    
    # Fill odd positions (1, 3, 5, ...) with elements from the first half of b
    for i in range(0, n - 1):
        a[2 * i + 1] = b[i]
    
    # The last element is computed based on difference of sums
    a[2 * n - 1] = sum(b[n - 1 :]) - sum(b[: n - 1])
    
    print(*a)


# https://github.com/VaHiX/codeForces/