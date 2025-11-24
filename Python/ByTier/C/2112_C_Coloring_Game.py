# Problem: CF 2112 C - Coloring Game
# https://codeforces.com/contest/2112/problem/C

"""
C. Coloring Game
Algorithms/Techniques: Sorting, Two Pointers, Combinatorial Counting

Time Complexity: O(n^3) per test case, where n is the size of the array.
Space Complexity: O(n) for storing the input array.

The problem asks to count how many ways Alice can choose 3 red elements such that no matter which element Bob chooses to color blue (including recoloring a red one), the sum of red elements remains strictly greater than the blue element.

Approach:
1. For each possible choice of two largest elements in sorted array as part of the triplet,
   we determine how many third elements can form a valid triplet.
2. We use two pointers technique to count valid combinations efficiently.
3. The solution relies on sorting the array and iterating over all pairs of large values,
   then using binary search or two pointers to find valid third elements.
"""

t = int(input())
d = []
for _ in [0] * t:
    n = int(input())
    d += [(n, sorted(map(int, input().split())))]
for n, a in d:
    m, s = a[-1], a[-2]
    r = 0
    for k in range(2, n):  # Iterate through possible third element
        x = max(2 * a[k], s if k == n - 1 else m) - a[k]  # Compute threshold for valid sum
        i, j = 0, k - 1  # Two pointers to count valid pairs
        while i < j:
            if a[i] + a[j] > x:  # If current pair exceeds threshold
                r += j - i  # Add number of valid pairs
                j -= 1  # Move right pointer
            else:
                i += 1  # Move left pointer
    print(r)


# https://github.com/VaHiX/codeForces/