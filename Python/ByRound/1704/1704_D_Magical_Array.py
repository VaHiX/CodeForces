# Problem: CF 1704 D - Magical Array
# https://codeforces.com/contest/1704/problem/D

"""
Algorithm: Magical Array
Purpose: Determine the special array and count of operation 2 used on it.
Techniques: 
- Use prefix sums to detect the pattern of operations.
- For each array, compute a checksum using a specific formula that encodes the effect of operations.
- The array with the maximal checksum is the special array.
- The difference between max and min checksums gives the number of operation 2 used.

Time Complexity: O(n * m)
Space Complexity: O(n)
"""

t = int(input())
for _ in range(t):
    n, m = [int(i) for i in input().split()]
    a = []
    for _ in range(n):
        y = input().split()
        # Compute a weighted sum where weight is the index (0-based)
        # This captures the pattern of how operations affect array elements
        k = sum([i * int(y[i]) for i in range(m)])
        a.append(k)
    # Find the index of the maximum checksum (special array)
    # The difference between max and min gives the number of operation 2
    print(a.index(max(a)) + 1, max(a) - min(a))


# https://github.com/VaHiX/CodeForces/