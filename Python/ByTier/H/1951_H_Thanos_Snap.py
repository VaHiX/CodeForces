# Problem: CF 1951 H - Thanos Snap
# https://codeforces.com/contest/1951/problem/H

"""
Purpose: Solve the "H. Thanos Snap" problem where Alice and Bob play a game on an array.
         Alice can swap two elements, Bob can erase either the left or right half.
         Both play optimally to maximize/minimize the final maximum element.
         
Algorithms/Techniques: 
- Simulation with merging steps to efficiently compute possible outcomes
- Dynamic programming approach with precomputed merged arrays
- Careful handling of Alice's swaps and Bob's erasing operations

Time Complexity: O(k * 2^k), where k is the input parameter determining array size (2^k)
Space Complexity: O(k * 2^k) for storing the merged arrays and intermediate results
"""

from sys import stdin


def calc_outcomes(arr, k):
    outcomes = [0] * k
    outcomes[k - 1] = 1  # Base case for t = k (no moves left)
    n = len(arr)

    # Precompute merged arrays for all stages
    merged = [arr]
    for stage in range(1, k + 1):
        block_size = 1 << stage
        new_arr = []
        curr_arr = merged[-1]
        for start in range(0, n, block_size):
            end = start + block_size
            mid = start + (block_size >> 1)
            l, r = start, mid
            for _ in range(block_size):
                if l == mid or r < end and curr_arr[r] > curr_arr[l]:
                    new_arr.append(curr_arr[r])
                    r += 1
                else:
                    new_arr.append(curr_arr[l])
                    l += 1
        merged.append(new_arr)

    # For each number of rounds from 1 to k-1
    for n_rounds in range(1, k):
        start_stage = k - n_rounds
        arr_block_size = 1 << start_stage
        # Get the initial elements that will be considered
        elems = merged[start_stage][::arr_block_size]

        elem_block_size = 1
        # Process merging stages for this number of rounds
        for stage in range(start_stage + 1, k + 1):
            curr_arr = merged[stage]
            new_elems = []
            elem_block_size <<= 1  # Double the block size
            for start in range(0, 1 << n_rounds, elem_block_size):
                end = start + elem_block_size
                mid = start + (elem_block_size >> 1)
                arr_block_start = start << (start_stage)
                l, r = start, mid
                has_swap = True
                for i in range(elem_block_size):
                    if l == mid or r < end and elems[r] > elems[l]:
                        if has_swap and curr_arr[arr_block_start + i] != elems[r]:
                            has_swap = False
                            new_elems.append(curr_arr[arr_block_start + i])
                        else:
                            new_elems.append(elems[r])
                            r += 1
                    else:
                        if has_swap and curr_arr[arr_block_start + i] != elems[l]:
                            has_swap = False
                            new_elems.append(curr_arr[arr_block_start + i])
                        else:
                            new_elems.append(elems[l])
                            l += 1
            elems = new_elems

        outcomes[n_rounds - 1] = elems[-1]
    return outcomes


n_tests = int(stdin.readline())
for test_id in range(n_tests):
    k = int(stdin.readline())
    arr = list(map(int, stdin.readline().split()))
    print(*calc_outcomes(arr, k))


# https://github.com/VaHiX/CodeForces/