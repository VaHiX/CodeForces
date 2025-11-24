# Problem: CF 1912 K - Kim's Quest
# https://codeforces.com/contest/1912/problem/K

"""
K. Kim's Quest
Algorithms/Techniques: Dynamic Programming, Modular Arithmetic
Time Complexity: O(n)
Space Complexity: O(1)

The problem asks to count the number of "Harmonious Subsequences" in a sequence,
where a Harmonious Subsequence has the property that the sum of every three 
consecutive elements is even. This implies that the parity (odd/even) of the 
elements must follow a specific pattern over any 3-element subsequence.

This implementation uses dynamic programming to keep track of different parity 
patterns as we iterate through the array, updating counters based on current 
element's parity to determine valid subsequences ending at each position.
"""
n, a, p110, p101, p011, p000 = int(input()), list(map(int, input().split())), 1, 1, 1, 0
for i in range(n):
    if a[i] % 2 == 0:  # If current element is even
        p000, p110 = p000 + 1, (p011 + p110) % 998244353  # Update counters for even cases
    else:  # If current element is odd
        p011, p101 = (p011 + p101) % 998244353, (p110 + p101) % 998244353  # Update counters for odd cases
print(
    ((p101 + p011 + p110) - 4 - 2 * n - (n * (n - 1)) // 2 + (2**p000) % 998244353)
    % 998244353
)


# https://github.com/VaHiX/codeForces/