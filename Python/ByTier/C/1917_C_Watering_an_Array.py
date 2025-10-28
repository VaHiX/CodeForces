# Problem: CF 1917 C - Watering an Array
# https://codeforces.com/contest/1917/problem/C

"""
Algorithm: Watering an Array
Approach:
- We maintain an array `arrn` which is derived from the original array `arr` by subtracting index + 1 from each element.
- This transformation helps in identifying elements that are equal to their position (a[j] == j) more easily.
- The idea is to simulate operations optimally, considering that we can either increment the first b[i] elements or count and reset the array.
- The key optimization is based on the periodic nature of `b` array (repeating sequence v).
- We try to simulate some increments and then compute the potential score at each step.

Time Complexity: O(d * k) in worst case, but since d can be up to 1e9 and k up to 1e5, it is optimized due to early stopping condition.
Space Complexity: O(n + k) for storing the arrays `arr`, `v`, and `arrn`.

"""

for _ in range(int(input())):
    n, k, d = map(int, input().split())
    arr = [int(i) for i in input().split()]
    v = [int(i) for i in input().split()]
    # Transform array to check for positions where element equals index
    arrn = [arr[i] - i - 1 for i in range(n)]
    # Initial potential score based on current count and remaining operations
    x = arrn.count(0) + (d - 1) // 2
    i = 1
    # While conditions allow for better score:
    while (
        min(arrn) < 0  # if there are negative values in arrn
        and i <= d - 1  # while there are remaining days
        and len([j for j in arrn if j <= 0]) + (d - i - 1) // 2 > x  # if we can do better
    ):
        # Increment first b[i] elements of arrn
        for j in range(v[(i - 1) % k]):
            arrn[j] += 1
        i += 1
        # Recalculate potential score
        y = arrn.count(0) + (d - i) // 2
        x = max(x, y)
    print(x)


# https://github.com/VaHiX/CodeForces/