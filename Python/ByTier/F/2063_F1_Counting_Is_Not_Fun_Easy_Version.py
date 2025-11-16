# Problem: CF 2063 F1 - Counting Is Not Fun (Easy Version)
# https://codeforces.com/contest/2063/problem/F1

"""
Algorithm: Dynamic Programming with Catalan Numbers
Time Complexity: O(N^2) where N is the maximum number of pairs (5000)
Space Complexity: O(N^2) for precomputing factorials, Catalan numbers, and face tracking arrays

This solution uses the concept of "faces" in a bracket sequence to track how constraints 
reduce the number of valid sequences. For each good pair (l,r), we update the face counts 
and compute the remaining valid sequences using Catalan numbers.
"""

def main():
    import sys

    data = sys.stdin.read().split()
    it = iter(data)
    mod = 998244353
    N = 5000
    maxf = 2 * N
    fact = [1] * (maxf + 1)
    # Precompute factorials
    for i in range(1, maxf + 1):
        fact[i] = fact[i - 1] * i % mod
    invfact = [1] * (maxf + 1)
    # Precompute inverse factorials using Fermat's little theorem
    invfact[maxf] = pow(fact[maxf], mod - 2, mod)
    for i in range(maxf, 0, -1):
        invfact[i - 1] = invfact[i] * i % mod
    inv = [1] * (N + 2)
    # Precompute modular inverses
    for i in range(2, N + 2):
        inv[i] = (mod - mod // i) * inv[mod % i] % mod
    catalan = [0] * (N + 1)
    inv_catalan = [0] * (N + 1)
    # Precompute Catalan numbers and their inverses
    for n in range(N + 1):
        c = fact[2 * n] * invfact[n] % mod * invfact[n] % mod
        c = c * inv[n + 1] % mod
        catalan[n] = c
    for n in range(N + 1):
        if catalan[n] == 0:
            inv_catalan[n] = 0
        else:
            inv_catalan[n] = pow(catalan[n], mod - 2, mod)
    t = int(next(it))
    out_lines = []
    for _ in range(t):
        n = int(next(it))
        pairs = [(0, 0)] * n
        for i in range(n):
            l = int(next(it))
            r = int(next(it))
            if l > r:
                l, r = r, l
            pairs[i] = (l, r)
        m = 2 * n
        # face_id tracks which face each position belongs to
        face_id = [0] * (m + 1)
        # face_count tracks the number of positions in each face
        face_count = [0] * (n + 1)
        face_count[0] = m  # Initially, all positions are in face 0
        next_face = 1
        ans = catalan[n]  # Start with total number of balanced sequences
        res = [str(ans)]
        for l, r in pairs:
            f = face_id[l]  # Get the face containing position l
            cnt_f = face_count[f]  # Number of positions in face f
            cnt_between = 0
            fid = face_id
            # Count how many positions between l and r belong to face f
            for p in range(l + 1, r):
                if fid[p] == f:
                    cnt_between += 1
            # Count positions outside the current pair (outside l and r)
            cnt_out = cnt_f - cnt_between - 2
            # Compute the counts for internal Catalan numbers
            i = cnt_f // 2  # Internal positions for face f
            j = cnt_between // 2  # Internal positions in the new face
            k = cnt_out // 2  # Internal positions outside the pair
            # Update answer by adjusting with inverse Catalan numbers for face f
            ans = ans * inv_catalan[i] % mod
            # Multiply by Catalan numbers for internal parts
            ans = ans * catalan[j] % mod
            ans = ans * catalan[k] % mod
            face_count[f] = cnt_out  # Update face size
            newf = next_face  # Create new face for contents between l and r
            next_face += 1
            face_count[newf] = cnt_between  # Set size of new face
            fid[l] = -1  # Mark positions l and r as removed from face assignment
            fid[r] = -1
            # Assign new faces to positions between l and r
            for p in range(l + 1, r):
                if fid[p] == f:
                    fid[p] = newf
            res.append(str(ans))
        out_lines.append(" ".join(res))
    sys.stdout.write("\n".join(out_lines))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/