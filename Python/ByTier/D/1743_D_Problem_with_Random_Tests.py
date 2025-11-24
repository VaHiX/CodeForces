# Problem: CF 1743 D - Problem with Random Tests
# https://codeforces.com/contest/1743/problem/D

"""
Maximum OR of Two Substrings

Algorithm: 
- The key insight is that we want to maximize the bitwise OR of two substrings.
- A brute-force solution checking all pairs of substrings would be too slow.
- However, observe that for a given number n, we can compute the maximum OR
  by trying all possible ways to set bits in n.
- The approach is to use bit manipulation techniques to find the maximum OR
  by checking how many bits we can set in the result.

Time Complexity: O(1) - Since we iterate only a fixed number of times (up to 8),
                     which is independent of input size.
Space Complexity: O(1) - Only a few variables are used, constant space.
"""

input()
n = int(input(), 2)  # Convert binary string to integer
m = n                # Initialize maximum with the number itself
for i in range(1, 9):  # Try shifting by 1 to 8 bits
    m = max(m, n | n >> i)  # Compute OR with shifted version and update maximum
print(bin(m)[2:])  # Print result in binary without '0b' prefix


# https://github.com/VaHiX/CodeForces/