# Problem: CF 2136 C - Against the Difference
# https://codeforces.com/contest/2136/problem/C

# C. Against the Difference
# Problem: Find the length of the longest neat subsequence, where a neat subsequence
# is made by concatenating blocks, where each block has all elements equal to its length.
#
# Algorithm: Dynamic programming with tracking of block structures.
# Time Complexity: O(n) per test case, as we process each element once.
# Space Complexity: O(n), for storing auxiliary arrays.

for s in [*open(0)][2::2]:
    a = s.split()
    c = [i := 0]  # Initialize cumulative max length tracker and index
    b = c + [[] for _ in a]  # b[x] will store positions where value x appears
    for x in map(int, a):  # For each element in input array
        i += 1  # Increment global index
        l = b[x]  # Get list of positions where x appeared previously
        l += (i,)  # Add current index to the list for x
        # Update cumulative max: if x <= length of block ending at i,
        # check if we can extend a block by including x
        c += (max(c[-1], x <= len(l) and x + c[l[-x] - 1]),)
    print(c[-1])


# https://github.com/VaHiX/codeForces/