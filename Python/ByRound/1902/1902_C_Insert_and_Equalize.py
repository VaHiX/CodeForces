# Problem: CF 1902 C - Insert and Equalize
# https://codeforces.com/contest/1902/problem/C

"""
Algorithm: Insert and Equalize

This problem involves inserting one element into an array and then making all elements equal using a fixed increment x.
The approach is based on finding a target value to which all elements should be made equal, and then computing the minimum number of operations needed.

Key Observations:
- After inserting an element, we aim to bring all elements to a common value.
- We can choose a value x (the increment) and determine how many operations each element requires to reach that value.
- The minimal number of operations depends on choosing optimal a_{n+1} and x.

Approach:
1. Compute the minimum and maximum of the original array.
2. Calculate differences of all elements from the minimum (a_min).
3. Find GCD of these differences, call it g0.
4. Determine candidate values for a_{n+1} by considering multiples of g0 around a_min.
5. Try both a suitable value before and after a_max to be able to insert successfully without conflicts.
6. For each valid candidate, calculate required operations and return the minimum.

Time Complexity: O(n log(max(a)) + n) where n is the size of input array.
Space Complexity: O(n) due to storing the input array and set of elements.
"""

import math
import sys


def main():
    data = sys.stdin.read().split()
    t = int(data[0])
    index = 1
    results = []
    for _ in range(t):
        n = int(data[index])
        index += 1
        arr = list(map(int, data[index : index + n]))
        index += n
        if n == 1:
            results.append("1")
            continue
        a_min = min(arr)
        a_max = max(arr)
        total_sum = sum(arr)
        g0 = 0
        for num in arr:
            diff = num - a_min
            if g0 == 0:
                g0 = diff
            else:
                g0 = math.gcd(g0, diff)
        s = set(arr)
        k_max = (a_max - a_min) // g0
        c1 = None
        k = k_max
        while True:
            candidate = a_min + k * g0
            if candidate not in s:
                c1 = candidate
                break
            k -= 1
        k_min = k_max + 1
        c2 = None
        k = k_min
        while True:
            candidate = a_min + k * g0
            if candidate not in s and candidate > a_max:
                c2 = candidate
                break
            k += 1
        S1 = ((n + 1) * a_max - (total_sum + c1)) // g0
        S2 = (n * c2 - total_sum) // g0
        ans = min(S1, S2)
        results.append(str(ans))
    print("\n".join(results))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/