# Problem: CF 1952 E - Sweep Line
# https://codeforces.com/contest/1952/problem/E

"""
Algorithm: Sweep Line
Time Complexity: O(n)
Space Complexity: O(1)

This solution uses a sweep line approach to count the number of valid
solutions for a given array of values in {0, 1, 2}. The key idea is to
iterate over possible initial values (h) and simulate the process,
checking whether a valid sequence can be formed such that each element
in the final array can be reconstructed using the recurrence relation
v_{i+1} = arr[i] - u_i, where u_i and v_i are elements in a solution.

The recurrence relation is used to validate the current choice of initial
values by simulating forward through the array and checking that all
intermediate values are in {0, 1}. A valid solution is one where the
final computed value matches the last element of the input array.
"""

n = int(input())
arr = list(map(int, input().split()))
if n == 1:
    print(2 if arr[0] == 0 else 0)
elif n == 2:
    print(1 if max(arr) <= 1 else 0)
else:
    num_solutions = 0

    def check_solution(u, v):
        # Simulate the recurrence: v_{i+1} = arr[i] - u_i
        for i in range(n - 1):
            u, v = v, arr[i] - u  # Update u and v for next iteration
            if v not in (0, 1):   # Invalid value in solution
                return 0
        return u == arr[-1]       # Must match the last element

    for h in range(2):            # Try all possible starting values for v
        num_solutions += check_solution(0, h)
    print(num_solutions % 20240401)  # Output modulo 20240401


# https://github.com/VaHiX/CodeForces/