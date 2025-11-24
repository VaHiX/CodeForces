# Problem: CF 2134 C - Even Larger
# https://codeforces.com/contest/2134/problem/C

"""
C. Even Larger

Algorithm/Technique: Greedy with backward iteration and adjustment
Time Complexity: O(n) where n is the length of the array
Space Complexity: O(n) for storing the array and auxiliary variables

The problem asks to make an array "good" by minimizing operations (each operation reduces an element by 1).
An array is good if for every subarray of length >= 2, the sum of elements at even indices (1-indexed) 
is >= sum of elements at odd indices.

Approach:
- Process elements from right to left in pairs.
- For each pair of positions (i, i+2), calculate how much we need to reduce
  to ensure that a[i] + a[i+2] >= a[i+1].
- This greedy approach reduces violations while minimizing total operations.

This works due to the nature of overlapping subarrays:
Adjusting earlier elements can help fix multiple future violations.
"""

for s in [*open(0)][2::2]:  # Read lines from input, skipping first and taking every 2nd line
    a = [0, 0] + [*map(int, s.split())]  # Convert string to int list, prepend two zeros for easier indexing
    a += [0] * (2 - len(a) % 2)  # Extend array to make its length even, pad with zeros if needed
    n = len(a)
    ans = 0  # Total operations counter
    
    # Traverse from right to left in steps of 2
    for i in range(n - 3, 1, -1):  # From n-3 down to 2 (inclusive), step by -2
        if i % 2 != 0:  # Skip odd indices since we process pairs
            continue
            
        # Calculate potential excess difference needed to make a[i] + a[i+2] >= a[i+1]
        # If it's negative, no adjustment is needed (as we take max with 0)
        ext1 = max(a[i] + a[i + 2] - a[i + 1], 0)
        # Limit how much of `ext1` can be actually deducted from a[i] (i.e., don't go below 0)
        e1 = min(ext1, a[i])
        ans += ext1  # Add to total operations
        a[i] -= e1   # Reduce a[i]
        a[i + 2] -= ext1 - e1  # Adjust remaining value from a[i+2]
    
    print(ans)


# https://github.com/VaHiX/codeForces/