# Problem: CF 1775 B - Gardener and the Array
# https://codeforces.com/contest/1775/problem/B

"""
Code Purpose:
This code determines whether there exist two different subsequences in the given array such that their bitwise OR results are equal.
It uses a greedy approach based on bit manipulation and frequency counting of set bits.

Algorithms/Techniques:
- Bit counting and frequency tracking using a hash map
- Greedy check for overlapping bits between elements

Time Complexity: O(sum of k_i) where k_i is the number of set bits in c_i
Space Complexity: O(max(p_i)) where p_i are the bit positions in the input numbers

The algorithm works by:
1. For each number in the array, store its set bits in a list.
2. Count how many times each bit position appears across all numbers.
3. For each number, check if all its bits appear more than once in the entire array.
   - If yes, then there exists at least one other number that shares all these bits,
     which implies that two different subsequences will have the same OR result.
4. If no such number is found, return "NO".

"""

import sys

input = sys.stdin.readline


for _ in range(int(input())): # Process each test case
    n = int(input())
    s = {} # Dictionary to count frequency of each bit position
    m = [] # List to store bit positions for each number
    
    # Read each number's bit positions
    for i in range(n):
        m.append(list(map(int, input().split()[1:]))) # Store bit positions of current number
        for j in m[-1]: # For each bit position in current number
            s[j] = s.get(j, 0) + 1 # Increment count of that bit position
    
    # Check if there exists a number whose all bits appear more than once
    for i in range(len(m)): # For each number
        for j in m[i]: # For each bit in this number
            if s[j] <= 1: # If this bit appears only once
                break # This number doesn't qualify, check next
        else:
            # All bits in this number appear more than once
            print("Yes")
            break
    else:
        # No number qualifies
        print("No")


# https://github.com/VaHiX/CodeForces/