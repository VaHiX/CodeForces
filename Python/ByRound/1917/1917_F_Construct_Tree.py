# Problem: CF 1917 F - Construct Tree
# https://codeforces.com/contest/1917/problem/F

"""
Code Purpose:
This solution determines whether a tree can be constructed with specific edge lengths and a given diameter.
It uses dynamic programming approaches to check if the edge lengths can form a valid tree structure with the required diameter.
The approach involves:
1. Checking if the two longest edges can form a diameter (if their sum exceeds d, impossible).
2. Using DP to see if we can partition the edges into two subsets such that their sums are close to d/2.
3. Using a more complex rolling DP with bit manipulation for additional cases.

Time Complexity: O(n * d) where n is the number of edges and d is the diameter
Space Complexity: O(d) for the DP arrays used
"""

def combine(u, v):
    # Combine two values into a single index for 2D DP
    return u * m + v


t = int(input())
answers = []
power_of_2 = [1]
w = 63

# Precompute powers of 2 up to 63
for _ in range(w - 1):
    power_of_2.append(2 * power_of_2[-1])

sp = list(power_of_2)

# Build prefix XOR
for i in range(1, w):
    sp[i] ^= sp[i - 1]

for _ in range(t):
    n, d = map(int, input().split())
    lengths = list(map(int, input().split()))
    lengths.sort()
    result = "No"

    # Early check: if the two largest edges can't fit into diameter
    if lengths[-1] + lengths[-2] > d:
        answers.append(result)
        continue

    max_length = lengths[-1]
    m = d - max_length  # Remaining capacity for DP
    dp = [0] * (m + 1)  # DP array to track achievable sums
    dp[0] = 1  # Base case: sum 0 is achievable
    s = 0  # Current sum of added edges

    # Fill DP table with all but the last edge
    for rod_length in lengths[:-1]:
        s += rod_length
        # Traverse backwards to avoid using updated values in same iteration
        for j in range(min(s, m) - rod_length, -1, -1):
            dp[rod_length + j] |= dp[j]
        # Early exit if we can form diameter
        if dp[m]:
            result = "Yes"
            break

    # If the simple DP didn't work, try harder approach
    if result == "No" and 2 * max_length <= d:
        l0 = d // 2 + 3  # Size limit for first dimension of 2D DP
        m = d // w + 3  # Size limit for second dimension of 2D DP
        # Initialize 2D DP array
        dp = [0] * (m * (l0 + 1))
        dp[0] = 1  # Base case
        s = 0  # Current total length

        # Process each edge (except the last one)
        for rod_length in lengths[:-1]:
            u, x, y = rod_length * m, rod_length // w, rod_length % w
            for j in range(min(s, l0), -1, -1):
                v = combine(j + 1, 0)  # Compute boundary index
                # Traverse the possible combinations
                for k in range(
                    min(combine(j, (s - j + 1) // w + 1), v) - 1, combine(j, 0) - 1, -1
                ):
                    if not dp[k]:
                        continue
                    dpk = dp[k]
                    # Update DP with new combinations using bit manipulation
                    if rod_length + j <= l0:
                        dp[k + u] |= dpk
                    if k + x < v:
                        dp[k + x] |= (dpk & sp[w - y - 1]) << y
                        if k + x + 1 < v:
                            dp[k + x + 1] |= dpk >> (w - y)
            s = min(s + rod_length, d)  # Update total length

        # Check if a valid split can produce required diameter
        for i in range(max_length, min(d - max_length, l0) + 1):
            j = d - i
            if dp[combine(i, j // w)] & power_of_2[j % w]:
                result = "Yes"
                break

    answers.append(result)

print("\n".join(answers))


# https://github.com/VaHiX/CodeForces/