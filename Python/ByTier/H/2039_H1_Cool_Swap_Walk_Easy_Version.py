# Problem: CF 2039 H1 - Cool Swap Walk (Easy Version)
# https://codeforces.com/contest/2039/problem/H1

"""
Algorithm: Cool Swap Walk
Approach:
1. The goal is to sort the array using specific swap operations based on paths from (1,1) to (n,n) in an n×n grid.
2. Each path corresponds to a sequence of swaps where we only swap elements at positions (i,j) if i≠j.
3. We simulate the process by performing swaps along carefully crafted paths.
4. The strategy uses a greedy method of identifying incorrect orderings and then using path-based swaps to fix them.
5. We keep track of the starting index which helps determine how to perform swaps effectively.

Time Complexity: O(n^2) per test case due to nested loops and updates of the array during simulation.
Space Complexity: O(n) for storing the path strings and auxiliary arrays used in computation.

Techniques Used:
- Simulation of grid traversal paths with 'R' and 'D' steps.
- Array manipulation with rotation and swapping logic.
- Greedy fix for inversions using path-based swaps.
"""

for _ in range(int(input())):
    n = int(input())
    a = [*map(int, input().split())]
    out = []
    start = a.index(min(a))  # Find index of minimum element to establish base

    def performSwaps(skips):
        o = []
        skips = skips[::-1]  # Reverse skips for easier processing
        i = 0

        while i + 1 < n:
            if skips:
                if i + 1 == skips[-1]:  # If current step is marked for skipping
                    i += 2
                    skips.pop()
                    o.append("DDRR")  # Special move when skipping
                    continue

            i += 1
            o.append("DR")  # Standard step

        return o

    odd = 1
    while 1:

        # Check if array is sorted
        for i in range(n - 1):
            if a[(start + i) % n] <= a[(start + i + 1) % n]:
                continue
            break
        else:
            break  # If loop completed without breaking, array is sorted

        b = []
        swaps = []
        # Process pairs in array, checking if they need swapping
        for i in range(1, n - 1, 2):
            if a[i] <= a[i + 1] or i + 1 == start % n:
                b.append(a[i])
                b.append(a[i + 1])
                continue
            swaps.append(i)
            b.append(a[i + 1])
            b.append(a[i])

        if n % 2 == 0:
            b.append(a[-1])
        b.append(a[0])

        out.append("".join(performSwaps(swaps)))
        start -= 1
        start %= n
        a = b[:]  # Update array to new permutation

    # Append remaining DR steps to make sure all elements are properly placed
    for _ in range(start):
        out.append("DR" * (n - 1))

    print(len(out))
    for moves in out:
        print(moves)


# https://github.com/VaHiX/CodeForces/