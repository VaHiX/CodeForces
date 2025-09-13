# Contest 2101, Problem F: Shoo Shatters the Sunshine
# URL: https://codeforces.com/contest/2101/problem/F

import sys

# Using sys.stdin.readline for speed
stdin_readline = sys.stdin.readline

# Precompute powers
mod, mx_val = (
    998244353,
    6001,
)  # mx_val is upper bound for values in p2/p3 indices (e.g. N_max + 1)

p2 = [1] * mx_val
p3 = [1] * mx_val
for i in range(1, mx_val):
    p2[i] = (p2[i - 1] * 2) % mod
    p3[i] = (p3[i - 1] * 3) % mod


def solve():
    n = int(stdin_readline())
    m = 2 * n - 1

    if (
        n == 1
    ):  # Base case: if n=1, m=1. The loops for graph and final sum behave correctly. ans = 0.
        return 0  # Or print(0) and return if this function must print. The structure suggests returning.

    g = [[] for _ in range(m)]
    # In Python 3, range is an iterator, _ is fine for loop var.
    # Max value for _ here is n-2. Max mid_node_idx = n + (n-2) = 2n-2.
    # This correctly populates nodes up to index m-1.
    for h_idx in range(n - 1):
        u, v = (int(x) - 1 for x in stdin_readline().split())
        mid_node_idx = n + h_idx
        g[u].append(mid_node_idx)
        g[mid_node_idx].append(u)
        g[v].append(mid_node_idx)
        g[mid_node_idx].append(v)

    ans = 0
    # Iterate through all possible M nodes as root
    for i_root in range(m):
        d_counts = [0] * m  # d_counts[k] = total original nodes at depth k from i_root
        a2_terms = [0] * m  # Accumulator for a2 related terms
        a3_terms = [0] * m  # Accumulator for a3 related terms

        max_overall_depth_with_orig_node = 0

        if i_root < n:  # If root is an "original" node (0 to n-1)
            d_counts[0] = 1
            a2_terms[0] = mod - 2  # Store as -2 effectively, (mod-2) % mod
            a3_terms[0] = mod - 3  # Store as -3 effectively, (mod-3) % mod
            # max_overall_depth_with_orig_node remains 0, as root is at depth 0

        # Explore subtrees attached to children of i_root
        for child_of_i_root in g[i_root]:
            # dr_branch_counts[k] = original nodes at depth k (from i_root) in THIS branch
            dr_branch_counts = [0] * m

            # DFS stack: (current_node, parent_in_dfs_path, depth_from_i_root)
            # Depth of child_of_i_root is 1 from i_root.
            st = [(child_of_i_root, i_root, 1)]
            max_dep_this_branch = 0

            while st:
                curr_u, parent_fa, depth_d = st.pop()

                # Nodes at depth m or more are too deep for arrays of size m (indices 0 to m-1)
                if depth_d >= m:
                    continue

                if curr_u < n:  # If curr_u is an "original" node
                    dr_branch_counts[depth_d] += 1
                    if depth_d > max_dep_this_branch:
                        max_dep_this_branch = depth_d

                for neighbor_v in g[curr_u]:
                    if neighbor_v != parent_fa:
                        st.append((neighbor_v, curr_u, depth_d + 1))

            if max_dep_this_branch > max_overall_depth_with_orig_node:
                max_overall_depth_with_orig_node = max_dep_this_branch

            # Update global d_counts, a2_terms, a3_terms using this branch's dr_branch_counts
            # Iterate only up to max depth found in this branch that has an original node
            for jj_depth in range(1, max_dep_this_branch + 1):
                if (
                    dr_branch_counts[jj_depth] == 0
                ):  # Skip if no original nodes at this depth in this branch
                    continue

                d_counts[jj_depth] += dr_branch_counts[jj_depth]
                # val is dr_branch_counts[jj_depth]
                a2_terms[jj_depth] = (
                    a2_terms[jj_depth] - p2[dr_branch_counts[jj_depth]] + 1 + mod
                ) % mod
                a3_terms[jj_depth] = (
                    a3_terms[jj_depth] - p3[dr_branch_counts[jj_depth]] + 1 + mod
                ) % mod

        # Finalize a2_terms[0], a3_terms[0] (depth 0 terms)
        # d_counts[0] is 1 if i_root < n, else 0.
        # a2_terms[0] was initialized to mod-2 or 0.
        a2_terms[0] = (a2_terms[0] + p2[d_counts[0]] - 1 + mod) % mod
        a3_terms[0] = (a3_terms[0] + p3[d_counts[0]] - 1 + mod) % mod

        # Finalize a2_terms, a3_terms for depths > 0
        # Iterate up to max_overall_depth_with_orig_node found across all branches
        for jj_depth in range(1, max_overall_depth_with_orig_node + 1):
            a2_terms[jj_depth] = (
                a2_terms[jj_depth] + p2[d_counts[jj_depth]] - 1 + mod
            ) % mod
            a3_terms[jj_depth] = (
                a3_terms[jj_depth] + p3[d_counts[jj_depth]] - 1 + mod
            ) % mod

        # Calculate sum for current root i_root (variable `curr` in original)
        # k_sum_prev_depths: sum of d_counts[s] for s from 0 to current_depth-1
        # x_carry: term carried from previous depth iteration
        k_sum_prev_depths = d_counts[0]
        x_carry = 0
        current_root_sum = 0

        # Loop over depth `j` (here j_calc_depth) from 1 up to max_overall_depth_with_orig_node
        # If j_calc_depth > max_overall_depth_with_orig_node, then d_counts[j_calc_depth] = 0.
        # Also, a2_terms[j_calc_depth] and a3_terms[j_calc_depth] would be 0.
        # So terms become 0; iterating further is not needed.
        for j_calc_depth in range(1, max_overall_depth_with_orig_node + 1):

            # x_for_sum_term corresponds to `x_old + p3[k]` in the original thinking process
            x_for_sum_term = (x_carry + p3[k_sum_prev_depths]) % mod

            # Term: (p3[k] * a3[j] - p2[k] * a2[j]) * j
            term1_val = (p3[k_sum_prev_depths] * a3_terms[j_calc_depth]) % mod
            term2_val = (p2[k_sum_prev_depths] * a2_terms[j_calc_depth]) % mod
            sum_part1 = (term1_val - term2_val + mod) % mod
            sum_part1_weighted = (sum_part1 * j_calc_depth) % mod
            current_root_sum = (current_root_sum + sum_part1_weighted) % mod

            # Term: - x_for_sum_term * a2[j]
            sum_part2 = (x_for_sum_term * a2_terms[j_calc_depth]) % mod
            current_root_sum = (current_root_sum - sum_part2 + mod) % mod

            # Update k and x for next iteration
            k_sum_prev_depths += d_counts[j_calc_depth]
            # This k_sum_prev_depths will not exceed N (total original nodes)
            # So p2/p3 access is safe.

            x_carry = (x_for_sum_term * p2[d_counts[j_calc_depth]]) % mod

        ans = (ans + current_root_sum) % mod
    return ans


num_tests = int(stdin_readline())
# If problem guarantees T >= 1, then N >= 1.
# If N=1, solve() returns 0.
# Building a list of results then printing is faster for many test cases.
output_results = []
for _ in range(num_tests):
    output_results.append(str(solve()))
sys.stdout.write("\n".join(output_results) + "\n")
