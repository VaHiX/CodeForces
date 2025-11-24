# Problem: CF 1894 E - Freedom of Choice
# https://codeforces.com/contest/1894/problem/E

"""
Algorithm: Greedy with Binary Search andHashMap
Time Complexity: O(sum of n_i * log(sum of n_i)) for each test case, where n_i is the number of distinct elements in the i-th multiset
Space Complexity: O(sum of n_i) for storing the multisets and auxiliary data structures

This solution uses a greedy approach to minimize the anti-beauty of the resulting multiset X.
The main idea is to determine, for each possible size T of the multiset X (between sum(l_i) and sum(r_i)), 
how many elements of value T must be forced into X to keep the anti-beauty minimal.

We iterate over all possible sizes T of X and compute the minimum number of elements of value T that must be added.
The key insight is to analyze for each multiset how many elements of a given value can be safely taken,
and how much capacity is left for choosing other elements.
"""

import sys
from collections import defaultdict


def main():
    data = sys.stdin.read().split()
    t = int(data[0])
    index = 1
    results = []
    for _ in range(t):
        m = int(data[index])
        index += 1
        multisets = []
        l_list = []
        r_list = []
        for i in range(m):
            n_i = int(data[index])
            l_i = int(data[index + 1])
            r_i = int(data[index + 2])
            index += 3
            a_list = list(map(int, data[index : index + n_i]))
            index += n_i
            c_list = list(map(int, data[index : index + n_i]))
            index += n_i
            total_i = sum(c_list)
            multisets.append((l_i, r_i, a_list, c_list, total_i))
            l_list.append(l_i)
            r_list.append(r_i)
        L0 = sum(l_list)
        R0 = sum(r_list)
        total_free_capacity = R0 - L0
        dict_T = defaultdict(list)
        for l_i, r_i, a_list, c_list, total_i in multisets:
            for j in range(len(a_list)):
                a_val = a_list[j]
                if a_val < L0 or a_val > R0:
                    continue
                count_val = c_list[j]
                dict_T[a_val].append((count_val, total_i, l_i, r_i))
        S = set(dict_T.keys())
        size_interval = R0 - L0 + 1
        if size_interval > len(S):
            results.append("0")
        else:
            ans = 10**18
            for T in range(L0, R0 + 1):
                if T not in dict_T:
                    forced_T = 0
                else:
                    lst = dict_T[T]
                    base_forced = 0
                    sum_capacity_B = 0
                    safe_capacity_B0 = 0
                    for count_val, total_i, l_i, r_i in lst:
                        d_i = total_i - count_val
                        base_forced_i = max(0, l_i - d_i)
                        base_forced += base_forced_i
                        if base_forced_i == 0:
                            safe_i = min(r_i - l_i, d_i - l_i)
                            safe_capacity_B0 += safe_i
                        sum_capacity_B += r_i - l_i
                    free_capacity_A = total_free_capacity - sum_capacity_B
                    D = T - L0
                    remaining_extra = max(0, D - (free_capacity_A + safe_capacity_B0))
                    forced_T = base_forced + remaining_extra
                if forced_T < ans:
                    ans = forced_T
            results.append(str(ans))
    print("\n".join(results))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/