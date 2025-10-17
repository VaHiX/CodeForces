# Problem: CF 2145 F - Long Journey
# https://codeforces.com/contest/2145/problem/F

"""
F. Long Journey

Purpose:
This code solves a problem where a chip moves along a numbered strip from cell 0 to cell m,
avoiding traps that activate at specific intervals and positions. The chips move one step or stay
in place each turn, and the game ends if the chip enters a cell with an active trap. The goal is
to determine the minimum number of turns to reach cell m, or return -1 if impossible.

Algorithms/Techniques:
- Simulation with cycle detection using Floyd's Cycle Detection (tortoise and hare).
- LCM (Least Common Multiple) for determining the period of trap activation patterns.
- Prefix sums to efficiently compute total moves during simulation.
- Modular arithmetic to map states and detect repeated configurations.

Time Complexity: O(n * L + m / L), where L is the LCM of all a_i values.
Space Complexity: O(n * L), for storing state information and prefix sums.

Input Format:
First line contains number of test cases t.
For each test case:
- Line 1: n (number of trap types) and m (target cell)
- Line 2: n integers a_1, ..., a_n (modulo values for trap activation)
- Line 3: n integers b_1, ..., b_n (remainder values for trap activation)

Output Format:
For each test case, output the minimum number of turns to reach cell m or -1 if impossible.
"""
import sys


def gcd(a, b):
    while b:
        a, b = b, a % b
    return a


def lcm(a, b):
    return a // gcd(a, b) * b


def solve_case(n, m, a, b):
    L = 1
    for v in a:
        L = lcm(L, v)
    size = n * L  # Size of the state space
    first_seen = [-1] * size  # Track when each state was first encountered
    deltas = []
    pref_moves = [0]
    r = 0  # Current trap type (0 to n-1)
    x = 0  # Current cell position
    t = 0  # Turn counter
    while True:
        state_id = r * L + x
        if first_seen[state_id] != -1:
            cycle_start = first_seen[state_id]
            break
        first_seen[state_id] = t
        ai = a[r]
        bi = b[r]
        q_mod = x % ai
        move_forbidden = (q_mod + 1) % ai == bi
        delta = 0 if move_forbidden else 1
        deltas.append(delta)
        x = (x + delta) % L
        t += 1
        pref_moves.append(pref_moves[-1] + delta)
        if pref_moves[-1] == m:
            return t
        r = (r + 1) % n
    total_steps = t
    cycle_len = total_steps - cycle_start
    moves_before_cycle = pref_moves[cycle_start]
    moves_total_at_cycle_end = pref_moves[total_steps]
    moves_in_cycle = moves_total_at_cycle_end - moves_before_cycle
    if moves_total_at_cycle_end >= m:
        for i in range(1, total_steps + 1):
            if pref_moves[i] >= m:
                return i
    if moves_in_cycle == 0:
        return -1
    remaining = m - moves_before_cycle
    full_cycles = (remaining - 1) // moves_in_cycle
    turns_so_far = cycle_start + full_cycles * cycle_len
    moves_so_far = moves_before_cycle + full_cycles * moves_in_cycle
    need = m - moves_so_far
    for s in range(1, cycle_len + 1):
        gained = pref_moves[cycle_start + s] - pref_moves[cycle_start]
        if gained >= need:
            return turns_so_far + s


def main():
    data = list(map(int, sys.stdin.read().strip().split()))
    t = data[0]
    idx = 1
    out = []
    for _ in range(t):
        n = data[idx]
        m = data[idx + 1]
        idx += 2
        a = data[idx : idx + n]
        idx += n
        b = data[idx : idx + n]
        idx += n
        ans = solve_case(n, m, a, b)
        out.append(str(ans))
    print("\n".join(out))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/