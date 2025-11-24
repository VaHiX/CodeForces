# Problem: CF 2048 C - Kevin and Binary Strings
# https://codeforces.com/contest/2048/problem/C

"""
Algorithm: Greedy approach to maximize XOR of two substrings.
Approach:
1. Identify the first '0' in the string, which indicates the start of a potential maximal XOR pattern.
2. Count how many consecutive zeros follow the first zero.
3. Based on the presence and position of zeros, determine the two substrings that give maximum XOR:
   - One substring is the whole string from start.
   - The second is optimized based on the zero pattern to maximize the XOR result.

Time Complexity: O(n), where n is the length of the string.
Space Complexity: O(n), for storing the input string.
"""

for t in range(int(input())):
    n = list(input())  # Convert string to list for easier manipulation
    r = -1  # Index of the first '0' in the string
    p = 0   # Count of consecutive zeros after the first zero
    
    # Find the first occurrence of '0'
    for i in range(len(n)):
        if n[i] == "0":
            r = i
            break
    
    # Count consecutive zeros starting from the first '0'
    for i in range(r, len(n)):
        if n[i] == "0":
            p += 1
        else:
            break
    
    # If a '0' was found, compute optimal indices for substrings
    if r != -1:
        # First substring: from start to end of string
        # Second substring: computed to maximize XOR
        print(1, len(n), max((r - p) + 1, 1), min(max(r - p, 0) + (len(n) - r), len(n)))
    else:
        # If no '0' is found, choose two single-character substrings
        print(1, len(n), 1, 1)


# https://github.com/VaHiX/CodeForces/