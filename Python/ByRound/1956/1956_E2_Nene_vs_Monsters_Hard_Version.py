# Problem: CF 1956 E2 - Nene vs. Monsters (Hard Version)
# https://codeforces.com/contest/1956/problem/E2

"""
Algorithm: Simulate battle rounds until convergence
Time Complexity: O(n * log(max_energy)) where n is number of monsters
Space Complexity: O(n) for storing energy levels and intermediate results

This solution simulates the battle process for a large number of rounds.
Due to the nature of the attack mechanics, the energy levels eventually stabilize.
The key insight is that after a certain number of rounds, the pattern becomes periodic or stabilizes.
We use a simulation approach with early termination based on convergence.
The hard version of the problem allows up to 2*10^5 monsters and energy values up to 10^9,
so optimization is needed to avoid TLE.
"""

from functools import cache
from math import comb
from sys import stdin


@cache
def get_coefs(n_rounds):
    # Precompute coefficients for combinatorial calculation
    return [(-1) ** k * comb(k + n_rounds - 1, n_rounds - 1) for k in range(30)]


def solve(energy):
    n = len(energy)
    V = max(energy)
    logV = V.bit_length()
    r = 0
    # Simulate rounds until convergence or max rounds
    while r < logV or 0 not in energy:
        # Apply attack pattern: each monster attacks its neighbor
        for i in range(1, n):
            energy[i] = max(0, energy[i] - energy[i - 1])
        energy[0] = max(0, energy[0] - energy[-1])
        r += 1
    
    # If we have more than one monster, at least one must be zero now
    if n > 1:
        assert 0 in energy
    
    # Handle special case for circular arrangement
    if energy[-1] > 0:
        for i in range(n):
            if energy[i] == 0:
                break
            # Update next monster with damage from current
            energy[i + 1] = max(0, energy[i + 1] - energy[i])
            # Shift energy from current to end
            energy.append(energy[i])
            energy[i] = 0
        energy.append(0)
    
    # Identify active blocks (sequences of monsters with positive energy)
    blocks = []
    for i in range(n):
        if energy[i] > 0 and energy[i - 1] == 0:
            blocks.append(i)

    def calc_future_energy(pos, start, n_rounds):
        # Calculate energy at position pos after n_rounds rounds using precomputed coefficients
        if n_rounds == 0:
            return energy[pos]
        return sum(
            e * coef
            for e, coef in zip(energy[start : pos + 1][::-1], get_coefs(n_rounds))
        )

    # Process remaining active blocks
    while blocks:
        start = blocks.pop()
        if energy[start + 1] == 0:
            continue
        # Calculate when the next monster dies
        death_time = (energy[start + 1] + energy[start] - 1) // energy[start]
        dead_positions = [start + 1]
        leftovers = [0, 0]
        pos = start + 2
        # Check positions to be affected by death
        while energy[pos] > 0:
            left = calc_future_energy(pos, start, death_time - 1)
            leftovers.append(left)
            if left <= 0:
                # Binary search to find exact death time
                l, u = 0, death_time - 1
                while l + 1 < u:
                    mid = (l + u) // 2
                    if calc_future_energy(pos, start, mid) > 0:
                        l = mid
                    else:
                        u = mid
                death_time = u
                dead_positions.append(pos)
            pos += 1
        dead_positions.append(pos)
        # Clear affected positions and redistribute energy
        for p1, p2 in zip(dead_positions, dead_positions[1:]):
            energy[p1] = 0
            if p2 > p1 + 1:
                for i in range(p1 + 1, p2):
                    energy[i] = leftovers[i - start]
                blocks.append(p1 + 1)
    
    # Collect indices of monsters with remaining energy
    result = [i for i, e in enumerate(energy[n:], 1) if e > 0]
    result.extend(i for i, e in enumerate(energy[:n], 1) if e > 0)
    return result


n_tests = int(stdin.readline())
for test_id in range(n_tests):
    n = int(stdin.readline())
    energy = list(map(int, stdin.readline().split()))
    result = solve(energy)
    print(len(result))
    print(*result)


# https://github.com/VaHiX/CodeForces/