# Problem: CF 2146 C - Wrong Binary Search
# https://codeforces.com/contest/2146/problem/C

# Flowerbox describing the code purpose, algorithms, time and space complexity
"""
C. Wrong Binary Search

Problem Overview:
We are given a binary string s of length n. We need to construct a permutation p of size n such that:
- An integer i is "stable" if find(i) always returns a position j where p[j] == i, regardless of how the mid-point m is chosen during binary search.
- The integer i is stable if and only if s[i] == '1'.

Algorithm:
The approach uses the concept of constructing intervals based on the positions of '1's in the string.
The key idea is that for all elements in a contiguous interval to be stable, the permutation must ensure that any query to an element in that interval will always return it correctly under binary search logic.
This leads to arranging elements so that "stable" regions have elements placed such that the binary search behavior matches constraints.

Time Complexity: O(n) - Linear time for each test case due to scanning string and building answer array.
Space Complexity: O(n) - For storing input, intermediate arrays, and output.
"""

for _ in range(int(input())):
    n = int(input())
    s = input()
    s1 = "1" + s + "1"  # Add sentinel '1' at both ends to simplify boundary conditions
    
    # If there exists "101" pattern, then no valid permutation exists
    if "101" in s1:
        print("NO")
        continue
    else:
        print("YES")
    
    # Append a sentinel '1' at the end of string to make indexing consistent 
    s = s + "1"
    
    # Initialize answer array with zeros
    ans = [0] * (n + 1)
    last = -1  # Last index where a '1' was encountered
    
    # Traverse through extended string to assign values in the permutation
    for i in range(n + 1):
        if s[i] == "1":  # When we hit a '1', it denotes the end of some interval
            ans[i] = i + 1  # Assign value at this position as index + 1 (1-based)
            cur = i  # Current index to use in reverse assignment
            
            # Go back from last '1' to current one, updating values in reverse order
            for j in range(last + 1, i):
                ans[j] = cur  # Assign decreasing values
                cur -= 1  # Decrement counter
            
            last = i  # Update last position where '1' was hit
    
    # Print only first n elements of the result (excluding sentinel)
    print(*ans[:n])


# https://github.com/VaHiX/CodeForces/