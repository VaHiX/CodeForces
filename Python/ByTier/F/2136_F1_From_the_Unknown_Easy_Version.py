# Problem: CF 2136 F1 - From the Unknown (Easy Version)
# https://codeforces.com/contest/2136/problem/F1

"""
Interactive problem to determine the width parameter W of a text editor.

Algorithms/Techniques:
- Binary search approach using two queries to narrow down W
- First query uses long words to check if W is small (L1 = 0)
- Second query uses varying word lengths to find exact W using binary search logic

Time Complexity: O(1) - only 2 queries are made per test case, regardless of input size
Space Complexity: O(1) - fixed amount of memory used

This solution works by:
1. First querying with a long article of same-length words to test if W is small
2. If L1 = 0 (editor can't display), it finds an upper bound for W using shortest words
3. Otherwise, it uses binary search logic with variable word lengths to determine W

"""

import sys

t = int(input())


def calcL(W, article):
    article = article.split()
    x = 1
    y = 0
    for i in range(2, len(article)):
        word_length = int(article[i])
        if y + word_length <= W:
            y += word_length
        elif word_length > W:
            return 0
        else:
            x += 1
            y = word_length
    return x


for _ in range(t):
    input_W = _
    article_1 = ["111"] * 12500  # First query with fixed length words (111)
    output_str = f"? {len(article_1)} {' '.join(article_1)}"
    print(output_str)
    sys.stdout.flush()
    L1 = int(input())  # Read the number of lines from first query
    if L1 == 0:  # If it's not displayable, then W is small
        max_W = 110  # Upper bound for width estimation based on minimum word length
        min_W = 1    # Lower bound (minimum possible width)
        article_2 = ["1"] * 12500  # Second query with minimal words to find max W
        output_str = f"? {len(article_2)} {' '.join(article_2)}"
        print(output_str)
        sys.stdout.flush()
        L2 = int(input())
        W = 12500 // L2  # Estimate W based on how many lines are needed
        if W * L2 < 12500:  # Correct to next integer if necessary
            W += 1
    else:
        # Calculate range of possible widths for current line count
        min_word = 12500 // L1  # Minimum word length based on number of lines
        if min_word * L1 < 12500:
            min_word += 1
        max_word = 12500 // (L1 - 1)  # Maximum word length for L1-1 lines
        if max_word * (L1 - 1) > 12500:
            max_word -= 1
        min_W = 111 * min_word   # Minimum W based on min word length
        max_W = 111 * max_word + (111 - 1)  # Maximum W including edge case
        # Query with increasing lengths between calculated bounds
        article_2 = [f"{min_W} {i}" for i in range(1, max_W - min_W + 1)]
        output_str = f"? {len(article_2) * 2} {' '.join(article_2)}"
        print(output_str)
        sys.stdout.flush()
        L2 = int(input())
        reduced_lines = 2 * (max_W - min_W) - L2  # Adjust based on actual lines
        W = min_W + reduced_lines  # Estimate the final width
    print(f"! {W}")  # Output the found value


# https://github.com/VaHiX/codeForces/