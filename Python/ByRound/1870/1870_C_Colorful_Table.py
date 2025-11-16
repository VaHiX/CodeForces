# Problem: CF 1870 C - Colorful Table
# https://codeforces.com/contest/1870/problem/C

"""
Algorithm/Techniques: 
- Preprocessing to find the first and last occurrence of each color in the array 'a'
- Using suffix arrays to efficiently compute the minimum and maximum indices for each color from k down to 1
- For each color, determine the smallest rectangle that includes all cells with that color in the b matrix
- Time Complexity: O(n + k) per test case
- Space Complexity: O(k) per test case

The key insight is that b[i][j] = min(a[i], a[j]), so for a color c, all cells b[i][j] = c 
are formed when both a[i] and a[j] are >= c. The smallest rectangle is thus defined by 
the rows and columns where color c first appears and last appears.
"""

import sys


def main():
    data = sys.stdin.read().split()
    t = int(data[0])
    index = 1
    results = []
    for _ in range(t):
        n = int(data[index])
        k = int(data[index + 1])
        index += 2
        a = list(map(int, data[index : index + n]))
        index += n
        # Initialize arrays to store the min and max indices for each color
        min_val = [n] * (k + 1)
        max_val = [-1] * (k + 1)
        for i in range(n):
            v = a[i]
            if v <= k:
                if i < min_val[v]:
                    min_val[v] = i
                if i > max_val[v]:
                    max_val[v] = i
        # Suffix arrays to track minimum and maximum index for colors from k to 1
        min_index_ge = [n] * (k + 2)
        max_index_ge = [-1] * (k + 2)
        min_index_ge[k + 1] = n
        max_index_ge[k + 1] = -1
        # Iterate backwards from k to 1 to build suffix arrays
        for c in range(k, 0, -1):
            min_index_ge[c] = min(min_index_ge[c + 1], min_val[c])
            max_index_ge[c] = max(max_index_ge[c + 1], max_val[c])
        res = []
        for c in range(1, k + 1):
            if min_val[c] == n:
                res.append("0")
            else:
                # Calculate the span of indices for the color
                span = max_index_ge[c] - min_index_ge[c] + 1
                # For each color, rectangle height = width = span, so sum = 2 * span
                res.append(str(2 * span))
        results.append(" ".join(res))
    print("\n".join(results))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/