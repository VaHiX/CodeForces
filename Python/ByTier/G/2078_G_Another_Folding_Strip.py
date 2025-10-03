# Problem: CF 2078 G - Another Folding Strip
# https://codeforces.com/contest/2078/problem/G

"""
G. Another Folding Strip

This problem involves computing the sum of f(a_l a_{l+1} ... a_r) over all subarrays,
where f(b) is the minimum number of operations to achieve darkness configuration b
on a 1xN strip using folding and dyeing operations.

Algorithm:
- For each subarray, compute prefix sums of the array with alternating signs (to simulate
  a modified cumulative array c), then use monotonic stack techniques to find for each
  element the nearest greater/less elements on both sides.
- Use these indices to compute contribution of each element in max and min calculations.
- The key insight is that f(b) = max contribution - min contribution of elements in b.

Time Complexity: O(n) per test case (amortized due to stack operations).
Space Complexity: O(n) for storing arrays and stacks.
"""

import sys


def solve():
    data = sys.stdin.buffer.read().split()
    if not data:
        return
    MOD = 998244353
    t = int(data[0])
    idx = 1
    out_lines = []
    for _ in range(t):
        n = int(data[idx])
        idx += 1
        a = list(map(int, data[idx : idx + n]))
        idx += n
        m = n + 1
        c = [0] * m
        # Compute cumulative values with alternating signs (signs are flipped for odd indices)
        for i in range(1, m):
            if i & 1:
                c[i] = c[i - 1] - a[i - 1]
            else:
                c[i] = c[i - 1] + a[i - 1]
        
        # Next Greater or Equal elements on the right using monotonic stack
        prev_g = [-1] * m
        stack = []
        for i in range(m):
            ci = c[i]
            while stack and c[stack[-1]] <= ci:
                stack.pop()
            prev_g[i] = stack[-1] if stack else -1
            stack.append(i)
        
        next_ge = [m] * m
        stack.clear()
        for i in range(m - 1, -1, -1):
            ci = c[i]
            while stack and c[stack[-1]] < ci:
                stack.pop()
            next_ge[i] = stack[-1] if stack else m
            stack.append(i)
        
        # Calculate maximum contribution using contributions of elements
        Smax = 0
        for i in range(m):
            left = i - prev_g[i]
            right = next_ge[i] - i
            val = c[i] % MOD
            Smax = (Smax + val * left % MOD * right) % MOD
        
        # Next Smaller or Equal elements on the right using monotonic stack
        prev_s = [-1] * m
        stack.clear()
        for i in range(m):
            ci = c[i]
            while stack and c[stack[-1]] >= ci:
                stack.pop()
            prev_s[i] = stack[-1] if stack else -1
            stack.append(i)
        
        next_se = [m] * m
        stack.clear()
        for i in range(m - 1, -1, -1):
            ci = c[i]
            while stack and c[stack[-1]] > ci:
                stack.pop()
            next_se[i] = stack[-1] if stack else m
            stack.append(i)
        
        # Calculate minimum contribution using contributions of elements
        Smin = 0
        for i in range(m):
            left = i - prev_s[i]
            right = next_se[i] - i
            val = c[i] % MOD
            Smin = (Smin + val * left % MOD * right) % MOD
        
        ans = (Smax - Smin) % MOD
        out_lines.append(str(ans))
    sys.stdout.write("\n".join(out_lines))


def main():
    solve()


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/codeForces/