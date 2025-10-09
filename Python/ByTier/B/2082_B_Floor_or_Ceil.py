# Problem: CF 2082 B - Floor or Ceil
# https://codeforces.com/contest/2082/problem/B

# B. Floor or Ceil
# Algorithms/Techniques: Greedy simulation with bit manipulation
# Time Complexity: O(log x) per test case
# Space Complexity: O(1)

for s in [*open(0)][1:]:
    x, *a = map(int, s.split())
    # Lambda function to compute the result of applying operations
    # i is index of operation (0 for floor, 1 for ceil)
    # p is the current value of x
    f = lambda i, p=x: p + (i << (k := min(30, a[i]))) - i >> k
    # Apply two operations in different orders to get min and max results
    print(f(0, f(1)), f(1, f(0)))


# https://github.com/VaHiX/codeForces/