# Problem: CF 1878 D - Reverse Madness
# https://codeforces.com/contest/1878/problem/D

"""
Algorithm: Reverse Madness
Purpose: Given a string and a series of operations, each operation reverses a substring based on a specific rule. The approach uses a difference array to efficiently track how many times each position is involved in a reversal operation, then processes the operations in segments to minimize the number of swaps needed.

Time Complexity: O(n + q) where n is the length of the string and q is the number of operations.
Space Complexity: O(n) for storing the string and the difference array.

Techniques Used:
- Difference array technique for efficient range updates
- Two-pointer approach to reverse segments efficiently
"""

t = int(input())
st = ""
for i in range(t):
    n, k = map(int, input().split())
    s = list(input())  # Convert string to list for in-place modifications
    l = list(map(int, input().split()))
    r = list(map(int, input().split()))
    q = int(input())
    xl = list(map(int, input().split()))
    
    # Create a difference array to count how many times each index is involved in an operation
    lst = [0] * n
    for x in xl:
        lst[x - 1] += 1  # Convert to 0-based indexing
    
    # Process each segment defined by l and r arrays
    for j in range(k):
        a1 = l[j] - 1  # Convert to 0-based indexing
        b1 = r[j] - 1  # Convert to 0-based indexing
        num = 0  # Counter for cumulative number of reversals affecting current segment
        
        # Two-pointer approach to reverse the substring
        while a1 < b1:
            num += lst[a1] + lst[b1]  # Accumulate reversal events for both ends
            if num % 2:  # If number of reversals is odd, perform swap
                s[a1], s[b1] = s[b1], s[a1]
            a1 += 1  # Move towards center from left
            b1 -= 1  # Move towards center from right
    
    st += "".join(s)  # Join the modified list back to string
    if i != t - 1:
        st += "\n"
print(st)


# https://github.com/VaHiX/CodeForces/