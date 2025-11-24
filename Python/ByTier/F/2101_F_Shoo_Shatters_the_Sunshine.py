# Problem: CF 2101 F - Shoo Shatters the Sunshine
# https://codeforces.com/contest/2101/problem/F

"""
F. Shoo Shatters the Sunshine

Problem Description:
We are given a tree with n vertices, each vertex can be colored red, blue, or white.
The coolness of a coloring is defined as the maximum distance between a red and a blue vertex.
We need to compute the sum of coolness over all 3^n possible colorings of the tree, modulo 998244353.

Algorithm:
- For each possible root of the tree, we compute contribution of all pairs of (red, blue) distances.
- Use DFS traversal and dynamic programming to calculate counts and terms efficiently.
- Precompute powers of 2 and 3 for fast modular arithmetic.
- Time complexity: O(n^2)
- Space complexity: O(n^2)

"""
import sys

stdin_readline = sys.stdin.readline
mod, mx_val = (
    998244353,
    6001,
)
p2 = [1] * mx_val
p3 = [1] * mx_val
for i in range(1, mx_val):
    p2[i] = (p2[i - 1] * 2) % mod
    p3[i] = (p3[i - 1] * 3) % mod


def solve():
    n = int(stdin_readline())
    m = 2 * n - 1
    if n == 1:
        return 0
    g = [[] for _ in range(m)]
    for h_idx in range(n - 1):
        u, v = (int(x) - 1 for x in stdin_readline().split())
        mid_node_idx = n + h_idx
        g[u].append(mid_node_idx)
        g[mid_node_idx].append(u)
        g[v].append(mid_node_idx)
        g[mid_node_idx].append(v)
    ans = 0
    for i_root in range(m):
        d_counts = [0] * m
        a2_terms = [0] * m
        a3_terms = [0] * m
        max_overall_depth_with_orig_node = 0
        if i_root < n:
            d_counts[0] = 1
            a2_terms[0] = mod - 2
            a3_terms[0] = mod - 3
        for child_of_i_root in g[i_root]:
            dr_branch_counts = [0] * m
            st = [(child_of_i_root, i_root, 1)]
            max_dep_this_branch = 0
            while st:
                curr_u, parent_fa, depth_d = st.pop()
                if depth_d >= m:
                    continue
                if curr_u < n:
                    dr_branch_counts[depth_d] += 1
                    if depth_d > max_dep_this_branch:
                        max_dep_this_branch = depth_d
                for neighbor_v in g[curr_u]:
                    if neighbor_v != parent_fa:
                        st.append((neighbor_v, curr_u, depth_d + 1))
            if max_dep_this_branch > max_overall_depth_with_orig_node:
                max_overall_depth_with_orig_node = max_dep_this_branch
            for jj_depth in range(1, max_dep_this_branch + 1):
                if dr_branch_counts[jj_depth] == 0:
                    continue
                d_counts[jj_depth] += dr_branch_counts[jj_depth]
                a2_terms[jj_depth] = (
                    a2_terms[jj_depth] - p2[dr_branch_counts[jj_depth]] + 1 + mod
                ) % mod
                a3_terms[jj_depth] = (
                    a3_terms[jj_depth] - p3[dr_branch_counts[jj_depth]] + 1 + mod
                ) % mod
        a2_terms[0] = (a2_terms[0] + p2[d_counts[0]] - 1 + mod) % mod
        a3_terms[0] = (a3_terms[0] + p3[d_counts[0]] - 1 + mod) % mod
        for jj_depth in range(1, max_overall_depth_with_orig_node + 1):
            a2_terms[jj_depth] = (
                a2_terms[jj_depth] + p2[d_counts[jj_depth]] - 1 + mod
            ) % mod
            a3_terms[jj_depth] = (
                a3_terms[jj_depth] + p3[d_counts[jj_depth]] - 1 + mod
            ) % mod
        k_sum_prev_depths = d_counts[0]
        x_carry = 0
        current_root_sum = 0
        for j_calc_depth in range(1, max_overall_depth_with_orig_node + 1):
            x_for_sum_term = (x_carry + p3[k_sum_prev_depths]) % mod
            term1_val = (p3[k_sum_prev_depths] * a3_terms[j_calc_depth]) % mod
            term2_val = (p2[k_sum_prev_depths] * a2_terms[j_calc_depth]) % mod
            sum_part1 = (term1_val - term2_val + mod) % mod
            sum_part1_weighted = (sum_part1 * j_calc_depth) % mod
            current_root_sum = (current_root_sum + sum_part1_weighted) % mod
            sum_part2 = (x_for_sum_term * a2_terms[j_calc_depth]) % mod
            current_root_sum = (current_root_sum - sum_part2 + mod) % mod
            k_sum_prev_depths += d_counts[j_calc_depth]
            x_carry = (x_for_sum_term * p2[d_counts[j_calc_depth]]) % mod
        ans = (ans + current_root_sum) % mod
    return ans


num_tests = int(stdin_readline())
output_results = []
for _ in range(num_tests):
    output_results.append(str(solve()))
sys.stdout.write("\n".join(output_results) + "\n")


# https://github.com/VaHiX/codeForces/