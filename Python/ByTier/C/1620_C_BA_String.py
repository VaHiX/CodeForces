# Problem: CF 1620 C - BA-String
# https://codeforces.com/contest/1620/problem/C

"""
Algorithm: Digit DP / Enumeration with Modular Arithmetic
Time Complexity: O(n) per testcase, where n is the length of the string
Space Complexity: O(n) for storing the grouped asterisk and 'a' segments

The solution works by grouping consecutive characters and then using a numbering system 
to determine which BA-string is the x-th lexicographically smallest. 
We process the string from right to left, grouping consecutive 'a's and '*'s. 
For each group, we calculate how many combinations are possible, and then use modular arithmetic 
to determine how many 'b's should be placed in that group to reach the x-th string.
"""

I = input
for _ in [0] * int(I()):
    n, k, x = map(int, I().split())
    x -= 1  # Convert to 0-based indexing
    p = "a"  # Previous character
    a = [[0, 0]]  # List to store groups of (a_count, star_count)
    i = 0  # Index to alternate between a and star counts
    r = ""  # Result string
    
    # Process the string from right to left
    for y in I()[::-1]:  # Reverse the string to process from right to left
        if y != p:  # If the character changes
            p = y  # Update previous character
            # Add padding zeros for the new group (if needed)
            a += [[0, 0]] * i
            i ^= 1  # Toggle index
        a[-1][i] += 1  # Increment the count of current character type
    
    # Process each group from left to right (original order)
    for u, v in a:  # u = count of 'a's, v = count of '*'s in this group
        m = k * v + 1  # Total combinations for this group (0 to k 'b's for v '*'s)
        # Choose the number of 'b's based on x and modular arithmetic
        r = x % m * "b" + u * "a" + r  # Add 'b's first, then 'a's
        x //= m  # Move to the next group's selection index
    print(r)


# https://github.com/VaHiX/CodeForces/