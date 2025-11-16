# Problem: CF 1748 F - Circular Xor Reversal
# https://codeforces.com/contest/1748/problem/F

"""
Algorithm: Circular Xor Reversal
Purpose: Reverse an array where each element is initially 2^i, using XOR operations.
Technique: 
- Use a multi-swap strategy to reverse the array.
- The approach involves:
  1. Performing a series of operations to rotate elements towards their correct positions.
  2. Using a helper function `multiswap` to perform a sequence of swaps and XOR operations.
- Time Complexity: O(n^2) in worst case due to multiple nested loops for generating operations.
- Space Complexity: O(n) for storing the operations.

The algorithm ensures that the XOR operations on indices simulate the reversal process.
"""

n = int(input())
ops = []


def multiswap(i, j):
    # Helper function to generate operations for swapping elements in a range
    assert i < j

    m = j - i
    for end in range(m):
        # Add operations in reverse order for the first part
        ops.extend(range(i + end, i + m - end)[::-1])
        # Add operations in normal order for the second part
        ops.extend(range(i + end + 1, i + m - end))
    # Add final part of operations
    ops.extend(range(i, i + (m - 2) // 2 + 1))


# Perform multiswap operations to reverse the array
multiswap(0, n - 1)
if n % 2:
    # For odd n, perform an additional multiswap
    multiswap((n + 1) // 2 - n, (n - 3) // 2)
else:
    # For even n, perform another multiswap
    multiswap(n // 2 - n, n // 2 - 1)
multiswap(0, n - 1)

# Output the number of operations and the indices used
print(len(ops))
print(*[v % n for v in ops])


# https://github.com/VaHiX/CodeForces/