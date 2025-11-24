# Problem: CF 1883 E - Look Back
# https://codeforces.com/contest/1883/problem/E

"""
Algorithm: Greedy with Logarithmic Transformation
Technique: 
- Use logarithms to simulate multiplication by powers of 2.
- For each element, determine how many times it needs to be multiplied by 2 to become >= previous element.
- Greedily process the array from left to right, keeping track of the log of the current effective value.

Time Complexity: O(n) per test case, where n is the size of the array.
Space Complexity: O(1) excluding input storage.

This solution avoids directly working with large numbers and instead uses logarithms to compare growth factors.
"""

import math


def main():
    import sys

    data = sys.stdin.read().split()
    t = int(data[0])
    index = 1
    results = []
    for _ in range(t):
        n = int(data[index])
        index += 1
        a = list(map(int, data[index : index + n]))
        index += n
        if n == 0:
            results.append("0")
            continue
        # Initialize with log2 of first element
        v_prev = math.log2(a[0])
        total_ops = 0
        for i in range(1, n):
            current_log = math.log2(a[i])
            # If current element is already >= previous effective value
            if current_log >= v_prev - 1e-12:
                v_prev = current_log
            else:
                # Calculate how many operations needed to make current >= previous
                diff = v_prev - current_log
                f_i = math.ceil(diff - 1e-12)  # Number of times to multiply by 2
                total_ops += f_i
                # Update v_prev to reflect the new value after applying operations
                v_prev = current_log + f_i
        results.append(str(total_ops))
    sys.stdout.write("\n".join(results))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/