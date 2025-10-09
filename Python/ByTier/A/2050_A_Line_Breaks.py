# Problem: CF 2050 A - Line Breaks
# https://codeforces.com/contest/2050/problem/A

# ==============================================================================
# Purpose: Determine the maximum number of words that can fit on the first strip
#          of length m, by sequentially adding words until the total length exceeds m.
#
# Algorithm/Techniques: Greedy approach - iterate through words and accumulate
#                       their lengths until capacity is exceeded.
#
# Time Complexity: O(n * L) where n is number of words and L is average word length
# Space Complexity: O(1) - only using a few variables to store intermediate results
# ==============================================================================

a = int(input())
for i in range(a):
    n, m = input().split()
    l = 0           # Total length of words added so far
    c = 0           # Count of words that fit
    for j in range(int(n)):
        s = input()
        l = l + len(s)      # Add current word's length to total
        if l <= int(m):     # If total length still fits in strip
            c = c + 1       # Increment word count
    print(c)


# https://github.com/VaHiX/codeForces/