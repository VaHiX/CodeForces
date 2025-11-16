# Problem: CF 1759 F - All Possible Digits
# https://codeforces.com/contest/1759/problem/F

"""
Algorithm: Simulation with digit manipulation
Time Complexity: O(n + p) per test case, where n is the length of the number and p is the base
Space Complexity: O(p) for storing the set of seen digits

The approach simulates the process of incrementing the number step by step,
tracking which digits are present and when all digits from 0 to p-1 are seen.
"""

for _ in range(int(input())):
    n, p = map(int, input().split())
    a = list(map(int, input().split()))
    s = set(a)  # Set to track which digits are currently present
    L = a[-1]   # Last digit of the current number

    x = L
    # Find the first missing digit by traversing backwards
    while x in s:
        x = (x - 1 + p) % p  # Move to previous digit (wrapping around)
        if x == L:  # If we loop back to the start
            break

    # If we found a gap before the last digit
    if x < L:
        a[-1] = p - 1  # Set last digit to maximum value (p-1)
        # Propagate the carry
        for i in range(n - 1, -1, -1):
            s.add((a[i] + 1) % p)  # Add the next digit
            if (a[i] + 1) != p:    # If we didn't wrap around
                break
        else:
            s.add(1)  # Add 1 if we carried all the way to the front
        
        x = L  # Reset x
        # Find the first available digit after carry propagation
        while x in s:
            x = (x - 1 + p) % p
            if x == L or x == 0:  # Prevent unnecessary loop
                break

    # Output the number of operations needed
    print((x + p - L) % p)


# https://github.com/VaHiX/CodeForces/