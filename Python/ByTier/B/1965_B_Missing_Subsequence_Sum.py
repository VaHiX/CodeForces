# Problem: CF 1965 B - Missing Subsequence Sum
# https://codeforces.com/contest/1965/problem/B

"""
Missing Subsequence Sum Problem

Algorithm/Technique:
- The approach uses binary representation to construct a sequence that avoids a specific sum k
- It identifies a bit position where 2^i < k <= 2^(i+1) and uses this to construct values
- The idea is to use powers of 2 for most elements and tweak one element to avoid forming sum k
- This ensures all values from 1 to n except k can be formed as subsequence sums

Time Complexity: O(1) per test case - only a fixed number of operations
Space Complexity: O(1) - only storing a fixed-size array of at most 25 elements

The constructed sequence ensures:
1. No subsequence sums to k
2. All other values from 1 to n (excluding k) can be formed as subsequence sums
"""

t = int(input())

for tc in range(t):
    n, k = map(int, input().split())

    # Find the largest power of 2 such that 2^i < k
    i = 0
    while (1 << (i + 1)) <= k:
        i = i + 1

    # Construct the answer array
    # First element ensures we can form values around k
    # Then add k+1 and k+1 + 2^i to cover range
    # Then add powers of 2 (except the one at index i)
    ans = [k - (1 << i), k + 1, k + 1 + (1 << i)]

    # Add all powers of 2 from 0 to 19 except the one at position i
    for j in range(20):
        if j != i:
            ans.append(1 << j)

    print(len(ans))
    print(*ans)


# https://github.com/VaHiX/CodeForces/