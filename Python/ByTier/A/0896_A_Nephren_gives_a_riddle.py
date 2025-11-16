# Problem: CF 896 A - Nephren gives a riddle
# https://codeforces.com/contest/896/problem/A

"""
Algorithm/Techniques: 
- Preprocessing the lengths of the strings f_i to avoid computing the full string.
- Using a recursive-like approach with iteration to find the k-th character in f_n without constructing it.
- Binary search or direct index mapping based on precomputed lengths.
- Time Complexity: O(log(max_length)) per query, where max_length is around 10^18.
- Space Complexity: O(log(max_length)) for storing precomputed lengths.

The solution calculates the length of each f_i iteratively and stores it in a list.
For each query, we determine which part of the string f_n the k-th character belongs to,
and recursively reduce the problem to a smaller index in a previous f_i or return a character from a base string.

This method avoids memory overflow by not building actual strings but using length logic to determine the required character.
"""

def func(n, i):
    while True:
        # Base case: if n == 0, we are looking at f0
        if n == 0:
            if i < N1:
                return f0[i]
            else:
                return "."
        # Get the length of f_{n-1}, using precomputed list or last known value
        l = lenf[n - 1] if n <= len(lenf) else lenf[-1]
        # Check if we are in the first prefix part of f_n
        if i < N2:
            return f10[i]
        # Check if we are in the first part followed by f_{n-1}
        elif i < N2 + l:
            # Reduce to f_{n-1}
            n -= 1
            i -= N2
        # Check if we are in second part of f_n
        elif i < N2 + l + N3:
            return f11[i - (N2 + l)]
        # Check if we are in third part of f_n
        elif i < N2 + l + N3 + l:
            # Reduce to f_{n-1}
            n -= 1
            i -= N2 + l + N3
        # Check if we are in fourth part of f_n
        elif i < N2 + l + N3 + l + N4:
            return f12[i - (N2 + l + N3 + l)]
        else:
            return "."

if __name__ == "__main__":
    q = int(input())
    ans = ""
    f0 = "What are you doing at the end of the world? Are you busy? Will you save us?"
    f10 = 'What are you doing while sending "'
    f11 = '"? Are you busy? Will you send "'
    f12 = '"?'
    N1, N2, N3, N4 = len(f0), len(f10), len(f11), len(f12)

    lenf = [N1]
    # Precompute lengths of f_i up to a sufficiently large limit
    while lenf[-1] < 1e18:
        lenf.append(N2 + N3 + N4 + 2 * lenf[-1])

    for i in range(q):
        n, k = [int(i) for i in input().split(" ")]

        res = func(n, k - 1)
        ans += res
    print(ans)


# https://github.com/VaHiX/CodeForces/