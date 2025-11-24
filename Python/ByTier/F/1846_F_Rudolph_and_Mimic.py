# Problem: CF 1846 F - Rudolph and Mimic
# https://codeforces.com/contest/1846/problem/F

"""
Task: Find a mimic among n objects using at most 5 stages of interaction.
The mimic can transform into any object but cannot remain the same for more than 2 stages.
Strategy:
1. First, perform 2 stages without removing any objects to detect if mimic changed.
2. If change detected, identify the mimic by comparing object counts.
3. Remove all non-mimic objects to isolate the mimic.
4. If only one object remains, report it as mimic.
5. Otherwise, use additional stages to detect mimic based on object distribution.
Time Complexity: O(n) per test case (linear scan and counting)
Space Complexity: O(1) (fixed-size arrays of size 9 for counting)
"""

from sys import stdin

for _ in range(int(input())):
    n = int(input())
    types = list(map(int, input().split()))
    prev = [0] * 9
    for i in types:
        prev[i - 1] += 1
    mimic = -1

    # Stage 1 and 2: Check if mimic changes in first two stages
    for _ in range(2):
        print("-", 0, flush=True)
        types = list(map(int, input().split()))
        cur = [0] * 9
        for i in types:
            cur[i - 1] += 1
        if cur != prev:
            # MIMIC CHANGED: Find which type increased
            for i in range(9):
                if cur[i] > prev[i]:
                    mimic = i + 1
            break
        prev = cur

    # Build list of indices to remove (all non-mimic objects)
    rem = []
    for i in range(n):
        if types[i] != mimic:
            rem.append(i + 1)
    print("-", len(rem), *rem, flush=True)
    types = list(map(int, input().split()))
    
    # If only one object remains, it is the mimic
    if len(types) == 1:
        print("!", 1, flush=True)
        continue
    
    # If all objects are same type, need to do further checks
    if len(set(types)) == 1:
        prev = [0] * 9
        for i in types:
            prev[i - 1] += 1
        # Perform 2 more stages to detect change
        for _ in range(2):
            print("-", 0, flush=True)
            types = list(map(int, input().split()))
            cur = [0] * 9
            for i in types:
                cur[i - 1] += 1
            if cur != prev:
                # Detected change - mimic is the only object of that type
                for i in range(9):
                    if cur[i] > prev[i]:
                        mimic = i + 1
                        assert cur[i] == 1
                break
            prev = cur
        # Now we know the mimic's type; find its index
        for i in range(n):
            if types[i] == mimic:
                mimic = i + 1
                break
    else:
        # If there are multiple types, the mimic is the first object of a unique type
        # Find first object that isn't the mimic's type, or the first if all same
        for i in range(n):
            if types[i] != mimic:
                mimic = i + 1
                break

    print("!", mimic, flush=True)


# https://github.com/VaHiX/CodeForces/