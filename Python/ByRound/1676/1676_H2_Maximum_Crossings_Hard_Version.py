# Problem: CF 1676 H2 - Maximum Crossings (Hard Version)
# https://codeforces.com/contest/1676/problem/H2

"""
Maximum Crossings (Hard Version)

Algorithm:
- This problem is about counting the maximum number of crossings in a wiring diagram.
- The key insight is to use a Binary Indexed Tree (Fenwick Tree) to efficiently count how many wires 
  have already been placed that cross the current wire.
- For each wire from segment i to segment a[i], we count how many previous wires cross it.
- We process the array from right to left, and for each element a[i], we query how many elements 
  in the BIT are smaller than a[i]. This gives us the number of wires that cross the current wire.
- Time Complexity: O(n log n) per test case due to BIT operations.
- Space Complexity: O(n) for the BIT and input storage.

Techniques:
- Binary Indexed Tree (BIT) for efficient prefix sum and update operations.
- Reverse processing of array to compute crossings efficiently.
"""

def q(i):
    r = 0
    j = i
    # Query the prefix sum up to index i
    while i > 0:
        r += bit[i]
        i -= i & -i
    # Update the BIT at index j
    while j <= n:
        bit[j] += 1
        j += j & -j
    return r


I = lambda: int(input())
for _ in range(I()):
    n = I()

    s, bit = 0, [0] * (n + 1)
    # Process array from right to left
    for x in reversed(input().split()):
        s += q(int(x))
    print(s)


# https://github.com/VaHiX/CodeForces/