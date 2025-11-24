# Problem: CF 2129 F1 - Top-K Tracker (Easy Version)
# https://codeforces.com/contest/2129/problem/F1

# Flowerbox:
# This code solves an interactive problem of reconstructing a hidden permutation p of {1,2,...,n}.
# It uses four types of queries to gather information about elements in the permutation,
# where each query returns top k largest values from specified positions or their positions.
# The solution is based on precomputed groups and tracking of how many times each element appears
# in different group combinations. Time complexity: O(n^2) per test case, Space complexity: O(n)
# The algorithm uses predefined sets to build a mapping that uniquely identifies positions of elements.

groups = [[] for _ in range(30)]  # Predefined groups used to identify elements
free = 0  # Counter for unique identifiers assigned to group combinations
appear = {}  # Maps sorted group tuples to their identifiers


def add(g):
    """Add a group (list of indices) to the groups structure and assign it a unique identifier."""
    global free
    for e in g:  # For each element in the group
        groups[e].append(free)  # Add identifier to this element's list
    appear[tuple(sorted(g))] = free  # Store mapping from group to its identifier
    free += 1


# Pre-populate the groups with predefined combinations used for identifying permutation positions
add([])  # Empty group
for i in range(30):
    add([i])  # Single element groups
for a in range(30):
    for b in range(a):
        add([a, b])  # Two-element groups

# Additional complex combinations (based on mathematical properties)
for i in range(10):
    for x in range(27):
        add([0, 1 + x, 1 + (x + i + 1) % 27])
for i in range(27):
    add([28, 29, 1 + i])
for i in range(2):
    for x in range(27):
        add([1 + x, 1 + (x + 1) % 27, 1 + (x + 3 + i) % 27])
for x in range(29):
    add([1 + x, 1 + (x + 2) % 29, 1 + (x + 10) % 29])

# Process each test case
for _ in range(int(input())):
    n = int(input())  # Read the size of permutation
    seen = [[] for _ in range(n)]  # Track which groups each index belongs to
    
    # For each of the 30 predefined groups, query if any entries are within the valid range
    for i in range(30):
        q = [e + 1 for e in groups[i] if e < n]  # Get actual indices in range
        if not q:
            continue
        # Send a query of type 4 with group elements
        print(4 if i == 0 else 2, len(q), *q)
        
        # Read returned elements (those are the positions of elements in the permutation that belong to this group)
        for e in [int(t) for t in input().split()]:
            seen[e - 1].append(i)  # Mark which group id corresponds to which position

    line = [0] * n  # Final output to be printed
    for i in range(n):  # For each index in the output array
        t = tuple(seen[i])  # Get sorted tuple of group identifiers
        line[i] = appear[t] + 1  # Look up the corresponding element identifier
    
    print("!", *line)  # Print final result


# https://github.com/VaHiX/codeForces/