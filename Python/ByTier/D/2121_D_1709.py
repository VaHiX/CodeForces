# Problem: CF 2121 D - 1709
# https://codeforces.com/contest/2121/problem/D

# Purpose: Solve a sorting problem where two arrays `a` and `b` must be made increasing
#          while ensuring that for each index i, a[i] < b[i].
#          The solution uses bubble sort-like operations with additional cross-array swaps.
# Algorithms/Techniques:
#   - Bubble sort logic applied on both arrays independently (for monotonicity)
#   - Cross-swapping between elements of arrays when necessary to maintain order constraints
# Time Complexity: O(n^3) in worst case due to nested loops and potential swaps
# Space Complexity: O(n^2) for storing operations, as they're stored in list `r`

R = lambda: [*map(int, input().split())]
for _ in [0] * R()[0]:  # Process multiple test cases
    R()  # Read n but not use it directly; consumes line
    a, b = c = R(), R()  # Assign arrays to variables `a`, `b` and `c`
    r = []  # List to store operations
    j = k = 0  # j tracks array index (1-based), k for cross-swap count
    
    # Bubble sort on two arrays separately with tracking of swaps
    for l in c:  # Iterate through both arrays (a and b)
        j += 1  # Increment array counter
        for i, x in enumerate(l):  # For each element in current array
            while i and x < l[i - 1]:  # If out of order with previous element
                i -= 1  # Move index back to correct position
                r += (j, i + 1)  # Record bubble swap operation (1-based indexing)
                l[i : i + 2] = x, l[i]  # Perform actual exchange

    # Cross-swap to ensure a[i] < b[i] for all valid indices
    for x, y in zip(*c):  # Iterate over pairs (a[i], b[i])
        r += (3, k := k + 1) * (x > y)  # If a[i] > b[i], swap them (operation 3)
    
    print(len(r) // 2, *r)  # Print number of operations and the list of operations


# https://github.com/VaHiX/codeForces/