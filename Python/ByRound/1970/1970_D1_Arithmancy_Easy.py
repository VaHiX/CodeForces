# Problem: CF 1970 D1 - Arithmancy (Easy)
# https://codeforces.com/contest/1970/problem/D1

# =============================
# Problem: Arithmancy (Easy)
# Algorithm: Precomputed Mapping
# Time Complexity: O(1) per query
# Space Complexity: O(1) (fixed-size dictionary and magic words)
# =============================
i, s, d = (
    lambda: int(input()),  # Read integer input
    ["XXO", "XOXO", "X"],  # Predefined magic words
    {  # Precomputed mapping of spell power to word indices
        14: [1, 1],
        17: [1, 2],
        8: [1, 3],
        19: [2, 1],
        15: [2, 2],
        9: [2, 3],
        7: [3, 1],
        11: [3, 2],
        2: [3, 3],
    },
)
print(*s[: i()], sep="\n", flush=1)  # Print n magic words
for _ in "." * i():  # For each query
    print(*d[i()], flush=1)  # Print the corresponding word indices


# https://github.com/VaHiX/CodeForces/