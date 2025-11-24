# Problem: CF 1949 E - Damage per Second
# https://codeforces.com/contest/1949/problem/E

"""
Algorithm: Optimal Skill Distribution for Minimizing Kill Time
Purpose: To distribute k skill points between damage per hit and hits per second 
         such that the total time to kill all monsters is minimized.

Approach:
- Use a combination of mathematical analysis and binary search techniques.
- First, determine the number of smallest health monsters that can be handled 
  efficiently by increasing damage.
- Then, use a heap-based search to evaluate different damage values to find 
  optimal damage and hits per second combination.
- Time complexity: O(n log n + k log k), where n is number of monsters and k is skill points.
- Space complexity: O(n + k), for storing healths and health distribution.

Techniques Used:
- Mathematical optimization using logarithms for approximating optimal hit counts.
- Binary search for efficient calculation of hit counts.
- Heap-based optimization for evaluating candidate damage values.
"""

from fractions import Fraction
from heapq import heapify, heappop
from math import log
from sys import stdin


def select_n_small(healths, k):
    """
    Determine how many of the smallest health monsters should be handled 
    with increased damage to minimize total time.
    """
    n_small = 0
    best_diff = 0
    log_k = log(k)

    for i, h in enumerate(healths, 1):
        # Compute a relevance score for considering this monster
        diff = h * (log_k - 2 * log(h / i) + 2)
        if diff > best_diff:
            best_diff = diff
            n_small = i
    return n_small


def find_optimal_stats(healths, k):
    """
    Compute the optimal distribution of skill points between damage and hits per second.
    Returns (damage_per_hit, hits_per_second)
    """
    H = sum(healths)
    n = len(healths)
    n_small = select_n_small(healths, k)
    n_large = n - n_small
    # Width of the health distribution array
    distr_width = 0 if n_small == 0 else healths[n_small - 1] + 1

    # Precompute a prefix sum of health distribution
    health_distr = [0] * distr_width
    for h in healths[:n_small]:
        health_distr[h] += 1
    for i in range(1, distr_width):
        health_distr[i] += health_distr[i - 1]

    def eval_damage(d):
        """
        Evaluate total time (in seconds) needed with given damage d and fixed hit rate (k-d).
        """
        hit_count = 0
        if n_small > 0:
            # For small monsters, compute using prefix sums and efficient range counting
            hit_count += n_small * ((distr_width + d - 2) // d) - sum(
                health_distr[: distr_width - 1 : d]
            )
        pos = n_small
        if pos < n:
            # Process remaining large monsters
            curr = (healths[pos] + d - 1) // d
            stop_val = curr + n_large
            while pos < n and curr < stop_val:
                curr = (healths[pos] + d - 1) // d
                curr_lim = curr * d
                step = 1
                while pos + step < n and healths[pos + step] <= curr_lim:
                    step <<= 1
                l, r = pos + (step >> 1), pos + step
                while l + 1 < r:
                    mid = (l + r) >> 1
                    if mid < n and healths[mid] <= curr_lim:
                        l = mid
                    else:
                        r = mid
                hit_count += curr * (r - pos)
                pos = r
        # Add hits for remaining monsters
        hit_count += sum((h + d - 1) // d for h in healths[pos:])
        # Return time as fraction for precision
        return Fraction(hit_count, k - d)

    # Start with middle damage as a guess
    best_damage = k // 2
    best_time = eval_damage(best_damage)
    
    # Generate candidates for evaluation using linear scan
    candidates = [(Fraction((H + d - 1) // d, k - d), d) for d in range(1, k)]
    candidates = [(t, d) for t, d in candidates if t < best_time]
    heapify(candidates)
    
    # Process candidates to refine optimal damage
    while candidates:
        lower_t, d = heappop(candidates)
        if lower_t >= best_time:
            break
        t = eval_damage(d)
        if t < best_time:
            best_damage = d
            best_time = t
    return best_damage, k - best_damage


n, k = map(int, stdin.readline().split())
healths = sorted(map(int, stdin.readline().split()))
print(*find_optimal_stats(healths, k))


# https://github.com/VaHiX/CodeForces/