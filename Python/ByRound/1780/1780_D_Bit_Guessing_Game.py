# Problem: CF 1780 D - Bit Guessing Game
# https://codeforces.com/contest/1780/problem/D

"""
Bit Guessing Game Solver

Algorithm:
This solution uses a greedy approach to reconstruct the hidden integer n by analyzing the number of unit bits (set bits) 
after each subtraction operation. The key insight is that subtracting a power of 2 (2^k) from n flips the k-th bit from the right.
By observing how the number of set bits changes, we can infer the presence of certain bits in the original number.

Time Complexity: O(log n) per test case, where log n is the number of bits in n (at most 30 operations).
Space Complexity: O(1), as only a constant amount of extra space is used.

Techniques:
- Bit manipulation
- Greedy reconstruction
- Binary search principles (implicitly via bit positions)

The approach works by:
1. Starting with a guess g = 1 (which corresponds to 2^0)
2. Subtracting g from the current n and checking how the number of set bits changes
3. Using the difference in set bits to infer which bit was flipped
4. Reconstructing n by setting the corresponding bits using bitwise OR
"""

for _ in range(int(input())):
    n = 0  # Resulting number being reconstructed
    prev = int(input())  # Initial count of set bits
    g = 1  # Current guess (power of 2)
    while prev != 0:
        # Subtract g from n and read new count of set bits
        nex = int(input(f"- {g}\n"))
        # Calculate the bit position that was flipped
        order = nex - prev + 1
        # Set the corresponding bit in n
        n |= 2**order
        # Update prev count and next guess
        prev -= 1
        g = 2**order
    print(f"! {n}")


# https://github.com/VaHiX/CodeForces/