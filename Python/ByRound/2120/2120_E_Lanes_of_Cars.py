# Problem: CF 2120 E - Lanes of Cars
# https://codeforces.com/contest/2120/problem/E

"""
E. Lanes of Cars

Purpose:
This code solves the problem of minimizing the total angriness of cars in toll plaza lanes. 
The approach uses binary search on the answer to find the minimum possible value of x such that 
the total angriness can be minimized.

Algorithms/Techniques:
- Binary search over the answer to determine optimal x.
- Greedy strategy for computing minimal cost using precomputed sums.

Time Complexity: O(n * log(max_a) + n^2) where n is number of lanes, max_a is maximum cars in lane
Space Complexity: O(1) excluding input storage

The code simulates optimal car distribution across lanes to minimize total angriness.
Each test case computes the minimal possible total angriness with lane changes allowed,
where switching lanes increases angriness by k units.

Example:
Input:
6
3 4
13 7 4
...
Output:
123
219
156
21
5315
82302351405
"""

import sys


def main():
    data = sys.stdin.read().split()
    t = int(data[0])
    index = 1
    out_lines = []
    for _ in range(t):
        n = int(data[index])
        index += 1
        k = int(data[index])
        index += 1
        a = list(map(int, data[index : index + n]))
        index += n
        T = sum(a)
        low = -(10**7)
        high = 10**10
        while low < high:
            mid = (low + high) // 2
            total_count = 0
            for a_i in a:
                if mid > a_i:  # if x > current lane size, we add x to total
                    total_count += mid
                else:
                    if mid + k < 0:  # if x + k is negative, no cars contribute to angriness due to shifting constraints
                        total_count += 0
                    else:
                        total_count += min(mid + k, a_i)  # compute effective contribution after adjustments
            if total_count >= T:
                high = mid  # we try to reduce x further
            else:
                low = mid + 1  # x is too small, need to increase it
        x_min = low
        x0 = x_min - 1  # set reference point x0 one less than x_min
        F0 = 0  # sum of computed effective car counts
        S0 = 0  # cumulative angriness without cost of lane changes
        for a_i in a:
            if x0 > a_i:  # if x0 > current lane size, all cars have same effective angriness x0
                F0_i = x0
                S0_i = (x0 * (x0 + 1)) // 2 - k * a_i  # compute partial sum from 1 to x0 minus cost of changes
            else:
                if x0 + k < 0:  # if x0 + k is negative, no contribution to cost
                    F0_i = 0
                    S0_i = 0
                else:
                    if x0 <= a_i - k:  # case when lane is large enough for shift effect
                        num = x0 + k  # effective number of cars considered after changing lane
                        S0_i = num * (num + 1) // 2 - k * num  # compute angriness with adjusted numbers
                        F0_i = num
                    elif x0 <= a_i:  # medium cases where car count fits within range
                        S0_i = (a_i * (a_i + 1)) // 2 - k * a_i  # standard formula with cost of lane changes
                        F0_i = a_i
                    else:
                        F0_i = 0
                        S0_i = 0  # no contribution when x0 > a_i (as per earlier conditions)
            F0 += F0_i
            S0 += S0_i
        sum_marginal = S0 + (T - F0) * x_min  # compute marginal cost using derived formula
        total_angriness = sum_marginal + k * T  # add fixed cost terms
        out_lines.append(str(total_angriness))
    sys.stdout.write("\n".join(out_lines))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/codeForces/