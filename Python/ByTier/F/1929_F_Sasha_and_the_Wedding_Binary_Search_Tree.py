# Problem: CF 1929 F - Sasha and the Wedding Binary Search Tree
# https://codeforces.com/contest/1929/problem/F

"""
Algorithm: Count Valid BSTs with Missing Values
Techniques:
- In-order traversal to verify BST property
- Segment-based counting using combinatorics
- Modular arithmetic for large results

Time Complexity: O(n log n) per test case due to sorting and modular operations
Space Complexity: O(n) for storing tree structure and in-order traversal

This solution works by:
1. Performing in-order traversal of the tree to check if the known values form a valid sequence
2. Identifying segments of unknown values between known values
3. Calculating valid combinations for each segment using combinatorics (multiset permutations)
4. Multiplying all valid combinations together modulo 998244353
"""

mod = 998244353
max_k = 500000
fact = [1] * (max_k + 1)
for i in range(1, max_k + 1):
    fact[i] = fact[i - 1] * i % mod
import sys


def main():
    data = sys.stdin.read().split()
    t = int(data[0])
    index = 1
    results = []
    for _ in range(t):
        n = int(data[index])
        C = int(data[index + 1])
        index += 2
        left_child = [-1] * (n + 1)
        right_child = [-1] * (n + 1)
        vals = [0] * (n + 1)
        for i in range(n):
            a = int(data[index])
            b = int(data[index + 1])
            c = int(data[index + 2])
            index += 3
            node = i + 1
            left_child[node] = a
            right_child[node] = b
            vals[node] = c
        in_order = []
        stack = []
        cur = 1
        while cur != -1 or stack:
            if cur != -1:
                stack.append(cur)
                cur = left_child[cur]
            else:
                cur = stack.pop()
                in_order.append(vals[cur])
                cur = right_child[cur]
        known_indices = []
        for i, value in enumerate(in_order):
            if value != -1:
                known_indices.append(i)
        valid = True
        for j in range(1, len(known_indices)):
            if in_order[known_indices[j - 1]] > in_order[known_indices[j]]:
                valid = False
                break
        if not valid:
            results.append("0")
            continue
        segments = []
        if known_indices:
            first_index = known_indices[0]
            if first_index > 0:
                L = 1
                R = in_order[first_index]
                k = first_index
                segments.append((L, R, k))
            for j in range(1, len(known_indices)):
                prev_index = known_indices[j - 1]
                curr_index = known_indices[j]
                if curr_index - prev_index > 1:
                    L = in_order[prev_index]
                    R = in_order[curr_index]
                    k = curr_index - prev_index - 1
                    segments.append((L, R, k))
            last_index = known_indices[-1]
            if last_index < n - 1:
                L = in_order[last_index]
                R = C
                k = n - 1 - last_index
                segments.append((L, R, k))
        else:
            segments.append((1, C, n))
        total_ways = 1
        for L, R, k in segments:
            if k == 0:
                ways = 1
            else:
                N = R - L + k
                numerator = 1
                for i in range(k):
                    numerator = numerator * (N - i) % mod
                denominator = fact[k]
                ways = numerator * pow(denominator, mod - 2, mod) % mod
            total_ways = total_ways * ways % mod
        results.append(str(total_ways))
    print("\n".join(results))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/