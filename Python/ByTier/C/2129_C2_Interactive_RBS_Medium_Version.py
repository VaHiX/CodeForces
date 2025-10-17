# Problem: CF 2129 C2 - Interactive RBS (Medium Version)
# https://codeforces.com/contest/2129/problem/C2

# C2. Interactive RBS (Medium Version)
# Purpose: Given a hidden bracket sequence of length n, reconstruct it using at most 200 queries.
# Algorithm/Technique:
#   - First find the position of the first '(' and last ')' in the sequence using binary search.
#   - Then determine each character bit by bit using a multi-query strategy on groups of 8 positions.
# Time Complexity: O(n * log n + n) = O(n * log n) due to binary search and bitwise queries
# Space Complexity: O(n) for storing the result string

def ask(s):
    print("?", len(s), *s, flush=True)
    return int(input())


def answer(s):
    print("!", "".join(s), flush=True)


for _ in range(int(input())):
    n = int(input())
    s = [" " for i in range(n + 1)]
    if ask(list(range(1, n + 1))) == 0:
        # If entire sequence has 0 regular brackets, it's all ')' or all '('
        # But since constraints say at least one '(' and one ')', we can't have all same type.
        # Here we deduce that first '(' is at position 1, last ')' at n
        fq = 1
        fp = n
    else:
        # Binary search to locate the first '(' in the sequence
        l = 2
        r = n
        ans = -1
        while l <= r:
            mid = (l + r) >> 1  # Midpoint calculation using bit shift
            if ask(list(range(1, mid + 1))):  # Query from 1 to mid
                ans = mid
                r = mid - 1  # Move left to find earlier '('
            else:
                l = mid + 1  # Move right since we didn't find a '(' yet
        fq = ans   # First '(' position found at 'ans'
        fp = ans - 1  # Last ')' might be one before the first '(' if it starts with '))...'

    # Process in chunks of 8 positions to determine characters via bit manipulation
    for i in range(1, n + 1, 8):
        idx = [min(j, n) for j in range(i, i + 8)]  # Get indices safely within bounds
        q = []
        # Prepare queries for bits using a pattern of indices repeated with masks applied
        for j in range(7, -1, -1):  # Iterate from 7 down to 0 (bit positions)
            q += [idx[7 - j], fq, fq] * (1 << j)  # Repeat each index as per bit shift logic
        res = ask(q)  # Get the combined result of all queries
        for j in range(7, -1, -1):  # Process bits from MSB to LSB
            if res >> j & 1:  # Check the j-th bit (from right)
                s[idx[7 - j]] = "("  # If bit is set, assign '(', else ')'
            else:
                s[idx[7 - j]] = ")"

    answer(s[1:])  # Print the final reconstructed sequence starting from index 1


# https://github.com/VaHiX/codeForces/