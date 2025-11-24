# Problem: CF 1698 E - PermutationForces II
# https://codeforces.com/contest/1698/problem/E

"""
Code Purpose:
This solution determines the number of ways to fill missing elements in permutation b
such that permutation a can be transformed into b using a given strength s.
The approach uses a greedy method to check valid placements of elements and
counts valid assignments using combinatorial logic.

Algorithms/Techniques:
- Greedy assignment with sorting
- Modular arithmetic for large results
- Two-pointer technique for efficient interval matching

Time Complexity: O(n log n) due to sorting
Space Complexity: O(n) for storing auxiliary arrays

"""

def dc(x):
    return int(x) - 1 if x > -1 else -1


M = 998244353


def test():

    n, s = map(int, input().split())
    a = list(map(dc, map(int, input().split())))
    b = list(map(dc, map(int, input().split())))

    isfree = [True] * n
    sw = []
    k = 0
    fix = [0] * n

    # Identify which elements are fixed in b and which are free (-1)
    for i in range(n):
        if b[i] == -1:
            sw.append(a[i])  # Store values that need to be assigned
            k += 1
        else:
            isfree[b[i]] = False  # Mark the fixed value as used
            fix[b[i]] = a[i]      # Store the original value at that position

    # Sort the values to be assigned
    sw.sort()

    r = 1  # Result: number of ways
    p = 0  # Pointer for assigned values
    c = 0  # Count of fixed positions we have handled

    # Process each position from 0 to n-1
    for i in range(n):
        if isfree[i]:  # If position i in b is unfixed

            # Move pointer p to find all values that can be placed at position i (within strength s)
            while (p < k) and (sw[p] <= i + s):
                p += 1

            # If no valid swaps available, this is impossible
            if c >= p:
                return 0

            # Multiply result by number of choices available at this step
            r = (r * (p - c)) % M
            c += 1  # Increment count of fixed positions

        else:
            # If fixed, verify that the original value at b[i] is within reach
            if fix[i] > i + s:
                return 0

    return r


_tc_ = int(input())
for _t_ in range(_tc_):

    print(test())


# https://github.com/VaHiX/CodeForces/