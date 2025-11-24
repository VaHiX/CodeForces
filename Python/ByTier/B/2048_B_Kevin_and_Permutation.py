# Problem: CF 2048 B - Kevin and Permutation
# https://codeforces.com/contest/2048/problem/B

"""
Problem: Minimize the sum of minimums of all subarrays of length k in a permutation of 1..n.

Approach:
- If k == 1, the minimum of each subarray of length 1 is just the element itself.
  To minimize sum, arrange elements in increasing order.
- Otherwise:
  - Place the smallest elements at positions that are multiples of k (starting from k-1).
    This distributes small values across subarrays such that each subarray gets a small minimum.
  - Fill remaining positions with the rest of the elements in increasing order.

Time Complexity: O(n)
Space Complexity: O(n)

Algorithms/Techniques: Greedy placement of small values to minimize subarray minimums.
"""

t = int(input())
for _ in range(t):
    n, k = map(int, input().split())
    if k == 1:
        print(" ".join(map(str, range(1, n + 1))))
        continue
    a = [-1] * n  # Initialize result array with -1
    reqd = n // k  # Number of positions we will place a small value
    index = k - 1  # Start placing from index k-1 (0-based)
    val = 1  # Start assigning values from 1
    while reqd > 0:
        a[index] = val  # Assign smallest available value to current index
        val += 1
        index += k  # Move to next position that is a multiple of k
        reqd -= 1
    for i in range(n):
        if a[i] == -1:
            a[i] = val  # Fill remaining slots with remaining values
            val += 1
    print(" ".join(map(str, a)))


# https://github.com/VaHiX/CodeForces/