# Problem: CF 2146 D2 - Max Sum OR (Hard Version)
# https://codeforces.com/contest/2146/problem/D2

# D2. Max Sum OR (Hard Version)
# Algorithm: Greedy bit manipulation approach to maximize bitwise OR sum
# Time Complexity: O(30 * n) = O(n), where n = r - l + 1
# Space Complexity: O(n)

import sys


def solve():
    input_data = sys.stdin.read().strip().split()
    t = int(input_data[0])
    pos = 1
    out_lines = []
    for _ in range(t):
        l = int(input_data[pos])
        r = int(input_data[pos + 1])
        pos += 2
        n = r - l + 1
        a = [-1] * n  # Result array to be filled
        used = [False] * n  # Track which indices are already paired
        for k in range(31, -1, -1):  # Process from most significant bit to least
            mask = (1 << k) - 1  # Create a mask to check bits up to k-th bit
            for i in range(n):
                if used[i]:
                    continue
                x = l + i  # Value at index i in original array b
                y = mask ^ x  # Try pairing x with y (flip all bits from 0 to k-1)
                if not (l <= y <= r):
                    continue  # y is outside range [l, r]
                j = y - l  # Find position of y in the array
                if used[j]:
                    continue  # y is already paired
                used[i] = used[j] = True  # Mark both as used
                a[i] = y  # Assign y to a[i] (i's pair)
                a[j] = x  # Assign x to a[j]
        for i in range(n):
            if a[i] == -1:  # If a[i] wasn't assigned, assign it itself
                a[i] = l + i
        total = 0
        for i in range(n):
            b = l + i  # Original value in array b
            total += a[i] | b  # Add bitwise OR to total sum
        out_lines.append(str(total))
        out_lines.append(" ".join(map(str, a)))
    sys.stdout.write("\n".join(out_lines))


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/CodeForces/