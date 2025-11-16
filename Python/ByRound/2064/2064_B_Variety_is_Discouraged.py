# Problem: CF 2064 B - Variety is Discouraged
# https://codeforces.com/contest/2064/problem/B

# ==============================================================================
# Problem: B. Variety is Discouraged
# Purpose: Maximize the score of an array after removing at most one contiguous subarray.
#          Score = length - number of distinct elements.
# Algorithms/Techniques:
#   - Two-pointer technique with frequency counting
#   - Sliding window to find optimal subarray to remove
# Time Complexity: O(n) per test case
# Space Complexity: O(n) for frequency array and input parsing
# ==============================================================================

for s in [*open(0)][2::2]:  # Read every second line starting from index 2 (skip t, n)
    n = len(a := [*map(int, s.split())])  # Convert current line to list of integers
    m = [0] * n  # Frequency array to track occurrences of each value (1 to n)
    for i in a:  # Count frequency of each element
        m[i - 1] += 1  # Adjust index to 0-based

    b = l = 0  # b = max segment length, l = start of current segment being considered
    r = [0, 0]  # r[0], r[1] = bounds of best subarray to delete
    
    for i in range(n):  # Iterate through all elements
        if m[a[i] - 1] != 1:  # If the element's count > 1 (i.e., it is repeated)
            l = i + 1  # Update start of potential segment with repeated elements
        elif b < i - l + 1:  # If current segment length is larger than best so far
            b = i - l + 1  # Update max length
            r = [l, i]  # Update bounds of segment to remove

    if b:  # If there was a valid segment found (non-zero length)
        print(r[0] + 1, r[1] + 1)  # Print in 1-based indexing
    else:
        print(0)  # No removal needed or impossible to improve score


# https://github.com/VaHiX/codeForces/