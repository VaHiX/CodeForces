# Problem: CF 2094 E - Boneca Ambalabu
# https://codeforces.com/contest/2094/problem/E

"""
E. Boneca Ambalabu

Problem: Given a sequence of n integers, find the maximum value of sum of XORs (a_k ⊕ a_i) for all i in 1..n,
where k is chosen optimally from 1 to n.

Approach:
- For each bit position, count how many numbers have that bit set to 1.
- For each number a_k, compute the maximum possible sum of XORs by choosing
  the optimal bit value (0 or 1) for each bit position to maximize the contribution.
- This is done greedily from most significant bit to least significant.

Time Complexity: O(30 * n) = O(n), where n is the total number of elements across all test cases
Space Complexity: O(1) not counting input/output, O(30) for count array which is constant

Algorithms/Techniques: Bit manipulation, greedy algorithm on bit representation.
"""

for s in [*open(0)][2::2]:  # Read every second line starting from index 2 (skip t and n)
    a = [*map(int, s.split())]  # Parse the integers from current line
    c = [0] * 30  # count array for each bit position (0 to 29)
    for x in a:  # Iterate through all numbers
        for b in range(30):  # For each bit position
            c[b] += x >> b & 1  # Count how many numbers have bit b set to 1
    mx = 0
    for x in a:  # For each number, evaluate its contribution to max sum
        v = 0
        for b in range(30):  # Process each bit from most significant to least
            t = x >> b & 1  # Extract the bit at position b of current number x
            # If bit is 0, we want 1 to contribute to XOR (so use count of 1s in c[b])
            # If bit is 1, we want 0 to contribute to XOR (so use count of 0s = len(a) - c[b])
            v += (c[b] if 1 - t else len(a) - c[b]) << b
        mx = max(mx, v)  # Update global maximum
    print(mx)


# https://github.com/VaHiX/codeForces/