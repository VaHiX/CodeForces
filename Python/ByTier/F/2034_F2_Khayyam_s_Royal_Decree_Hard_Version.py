# Problem: CF 2034 F2 - Khayyam's Royal Decree (Hard Version)
# https://codeforces.com/contest/2034/problem/F2

"""
Algorithm: Dynamic Programming with Combinatorics
Purpose: Calculate the expected value of gems in Khayyam's satchel at the end of the game, considering special conditions that double the value of gems.

Time Complexity: O(k^2 + n + m)
Space Complexity: O(k^2 + n + m)

The solution uses dynamic programming with precomputed factorials and their modular inverses to calculate combinations.
It builds a DP table where each state represents the number of ways to reach a certain configuration,
and then computes the expected value based on these states.
"""

import sys

mod = 998244353
maxn = 400010
facts = [1] * maxn
ifacts = [1] * maxn
for i in range(1, 400010):
    facts[i] = (i * facts[i - 1]) % mod
ifacts[maxn - 1] = pow(facts[maxn - 1], mod - 2, mod)
for i in range(maxn - 2, -1, -1):
    ifacts[i] = (ifacts[i + 1] * (i + 1)) % mod


def count(rb, r):
    # Calculate combination C(rb, r) = rb! / (r! * (rb - r)!)
    if r < 0 or r > rb:
        return 0
    return (facts[rb] * ifacts[r] % mod) * ifacts[rb - r] % mod


def solve(tok, idx):
    # Parse input values
    n = int(tok[idx])
    m = int(tok[idx + 1])
    k = int(tok[idx + 2])
    idx += 3
    scrolls = [(0, 0)] * (k + 2)
    
    # If no scrolls, return simple calculation result
    if k == 0:
        return ((2 * n + m) % mod, idx)
    
    # Process and store scrolls in reverse order
    for i in range(1, k + 1):
        r = int(tok[idx])
        b = int(tok[idx + 1])
        scrolls[i] = (n - r, m - b)  # Store remaining gems needed to trigger decree
        idx += 2
    scrolls[k + 1] = (n, m)  # Add final state (no gems remaining)
    scrolls.sort()  # Sort based on gem counts for DP processing
    k = len(scrolls) - 1  # Update k to new size including final state

    def paths(i, j):
        # Calculate number of paths between two scroll positions
        r = scrolls[j][0] - scrolls[i][0]
        b = scrolls[j][1] - scrolls[i][1]
        return count(r + b, b)  # Using combinatorics to count valid sequences

    cnt = [0] * (k + 1)
    cnt[k] = 1  # Base case: there's one way to reach the final configuration
    
    # Dynamic Programming from bottom up to compute transition counts
    for i in range(k - 1, 0, -1):
        s = 0
        for j in range(i + 1, k + 1):
            s = (s + paths(i, j) * cnt[j]) % mod
        cnt[i] = s

    ans = 0
    # Compute weighted sum of all possible ending configurations
    for i in range(1, k + 1):
        delta = (2 * scrolls[i][0] + scrolls[i][1]) % mod  # Value of final satchel configuration
        ans = (ans + delta * paths(0, i) % mod * cnt[i]) % mod
    
    # Normalize the result by total combinations (total ways to draw all gems)
    ans = ans * pow(count(n + m, m), mod - 2, mod) % mod
    return ans, idx


def main():
    tok = sys.stdin.buffer.read().split()
    idx = 0
    t = int(tok[idx])
    idx += 1
    out = []
    for _ in range(t):
        res, idx = solve(tok, idx)
        out.append(str(res))
    sys.stdout.write("\n".join(out))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/