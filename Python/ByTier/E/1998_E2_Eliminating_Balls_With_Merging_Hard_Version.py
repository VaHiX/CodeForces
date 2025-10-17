# Problem: CF 1998 E2 - Eliminating Balls With Merging (Hard Version)
# https://codeforces.com/contest/1998/problem/E2

"""
Algorithm: Efficient processing of ball merging operations to compute f(i) values.
Techniques: 
- Preprocessing with prefix sums and range updates
- Binary search-like logic with tracking of valid intervals
- Sliding window and cumulative counting

Time Complexity: O(n^2) in worst case, but optimized with early breaks and preprocessing
Space Complexity: O(n) for storing arrays and intermediate data structures

The problem involves simulating merging operations on balls and counting
how many starting positions can lead to a single ball remaining after i operations.
"""

def solve():
    import sys

    input = sys.stdin.read
    data = input().split()
    idx = 0
    T = int(data[idx])
    idx += 1
    results = []
    for _ in range(T):
        n, x = int(data[idx]), int(data[idx + 1])
        idx += 2
        n += 2
        a = [0] * n
        a[0], a[-1] = 1e18, 1e18 - 1  # Sentinel values to simplify comparisons
        for i in range(1, n - 1):
            a[i] = int(data[idx])
            idx += 1
        v = [1e9 + 10] * n  # Tracks minimum left index for valid merges
        u = [1e9 + 10] * n  # Tracks minimum left index for valid merges with specific conditions
        w = [0]  # Tracks boundary indices for efficient interval queries
        for i in range(n - 1):
            s = 0
            for j in range(i + 1, n - 1):
                s += a[j]
                if s >= a[i]:
                    break  # Stop if sum exceeds current element
                if i > 0:
                    v[j] = min(v[j], i + 1)  # Update the minimum left index
                if i > 0 and s < a[j + 1]:
                    u[j] = min(u[j], i + 1)  # Update condition-based index
                if i == 0 and s < a[j + 1]:
                    w.append(j)  # Add boundary for efficient lookup
        cnt = [0] * n
        pref = [0] * (n + 1)
        for i in range(n - 1):
            if u[i] != 1e9 + 10:
                cnt[u[i]] += 1
                cnt[i + 1] -= 1  # Range update for efficient counting
        bal = 0
        for i in range(n):
            bal += cnt[i]
            pref[i + 1] = pref[i] + (1 if bal == 0 and 1 <= i < n - 1 else 0)  # Pref sum for interval counts
        result = []
        j = 0
        for i in range(1, n - 1):
            while j < len(w) - 1 and w[j + 1] < i:
                j += 1  # Adjust j to match current i
            r = min(i, v[i] - 1)  # Right boundary of valid interval
            l = w[j]  # Left boundary of valid interval
            result.append(str(pref[r + 1] - pref[l + 1]))  # Count in range
        results.append(" ".join(result))
    print("\n".join(results))


if __name__ == "__main__":
    solve()


# https://github.com/VaHiX/CodeForces/