# Problem: CF 1863 C - MEX Repetition
# https://codeforces.com/contest/1863/problem/C

"""
Algorithm: MEX Repetition
Techniques: Mathematical Observation, Modular Arithmetic

Time Complexity: O(n) per test case
Space Complexity: O(n) per test case

The problem involves repeatedly replacing each element in an array with the MEX (Minimum Excluded) of the entire array.
Key Insight:
- After the first operation, the array will contain all integers from 0 to n (but not necessarily in order).
- For any array of size n filled with distinct values from 0 to n, the MEX after one operation is always n+1.
- After the second operation, we have all numbers from 0 to n+1, and so on.
- The pattern repeats every n+1 operations.

Steps:
1. Compute initial MEX value.
2. Create a list D0 = a + [mex]
3. Use modular arithmetic to determine the resulting array after k operations,
   based on the periodicity of the sequence.
"""

import sys


def main():
    data = sys.stdin.read().split()
    t = int(data[0])
    index = 1
    out_lines = []
    for _ in range(t):
        n = int(data[index])
        k = int(data[index + 1])
        index += 2
        a = list(map(int, data[index : index + n]))
        index += n
        size = n + 2
        present = [False] * size
        for x in a:
            if x < size:
                present[x] = True
        mex = 0
        while mex < size and present[mex]:
            mex += 1
        # D0: extended array with MEX appended
        D0 = a + [mex]
        # T: number of operations to simulate after periodicity
        T = k % (n + 1)
        # start_index: determines where in D0 to start reading for result
        start_index = (n + 1 - T) % (n + 1)
        res = []
        for i in range(n):
            # Use modular indexing and periodic nature to avoid full simulation
            idx = (start_index + i) % (n + 1)
            res.append(str(D0[idx]))
        out_lines.append(" ".join(res))
    print("\n".join(out_lines))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/