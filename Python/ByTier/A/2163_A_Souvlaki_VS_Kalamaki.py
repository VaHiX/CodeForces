# Problem: CF 2163 A - Souvlaki VS. Kalamaki
# https://codeforces.com/contest/2163/problem/A

"""
Code Purpose:
This code determines whether Souvlaki can guarantee a win in a sorting game against Kalamaki by reordering the sequence before the game starts. 
The game involves n-1 rounds where Souvlaki (odd rounds) and Kalamaki (even rounds) can either skip or swap adjacent elements.
Souvlaki wins if the sequence becomes sorted in non-decreasing order by the end of the game.

Algorithm:
1. If all elements are the same, Souvlaki wins immediately (return "YES").
2. Otherwise, sort the sequence.
3. For each even round (Kalamaki's turn), check if the current and previous elements are equal. 
   If they are not equal, then Kalamaki can make a move that prevents sorting, so return "NO".
4. If all checks pass, return "YES".

Time Complexity: O(n log n) due to sorting.
Space Complexity: O(n) for storing the input and output.
"""

answers = []


def solve():
    n = int(input())  # Read the number of elements
    seq = list(map(int, input().split()))  # Read the sequence of integers
    
    # If all elements are the same, the sequence is already sorted
    if len(set(seq)) == 1:
        answers.append("YES")
        return
    
    # Sort the sequence to analyze it
    seq.sort()
    
    # Check for even rounds (Kalamaki's turn)
    # For each even index i, check if the element at i-1 and i are the same
    for i in range(1, n):
        if i % 2 == 0:
            if seq[i - 1] != seq[i]:
                answers.append("NO")
                return
    
    # If all checks pass, Souvlaki can win
    answers.append("YES")


def main():
    testc = int(input())  # Read the number of test cases
    for _ in range(testc):
        solve()
    print(*answers, sep="\n")  # Print all answers


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/