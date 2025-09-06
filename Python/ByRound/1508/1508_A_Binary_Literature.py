# Contest 1508, Problem A: Binary Literature
# URL: https://codeforces.com/contest/1508/problem/A

def solve():
    import sys
    data = sys.stdin.read().strip().split()
    if not data:
        return
    t = int(data[0])
    index = 1
    out_lines = []
    
    # Merge function: Given two strings s and t (each of length 2n)
    # that have at least n occurrences of the bit ch,
    # this function merges them to produce a string of length at most 3n
    # that has both s and t as subsequences.
    def merge(s, t, n, ch):
        L = 2 * n  # length of s and t
        i = 0
        j = 0
        need = n  # we need to pick n copies of ch
        res = []
        while need:
            # In s, append characters (which are not ch) until we must leave enough room for the remaining copies of ch.
            while i < L and s[i] != ch and (L - i) > need:
                res.append(s[i])
                i += 1
            # Do the same for t.
            while j < L and t[j] != ch and (L - j) > need:
                res.append(t[j])
                j += 1
            # Append the common character ch and move both pointers past a ch.
            res.append(ch)
            if i < L:
                i += 1
            if j < L:
                j += 1
            need -= 1
        
        # Append the remainders (order is preserved) from both strings.
        res.extend(s[i:])
        res.extend(t[j:])
        return "".join(res)
    
    # Process each test case.
    for _ in range(t):
        n = int(data[index])
        index += 1
        s1 = data[index]; index += 1
        s2 = data[index]; index += 1
        s3 = data[index]; index += 1
        strings = [s1, s2, s3]
        chosen = None
        chosen_char = None
        # Try all pairs and for each, try to find a bit (0 or 1) that appears at least n times in both.
        pairs = [(0, 1), (0, 2), (1, 2)]
        for (i, j) in pairs:
            for ch in ['0', '1']:
                if strings[i].count(ch) >= n and strings[j].count(ch) >= n:
                    chosen = (i, j)
                    chosen_char = ch
                    break
            if chosen is not None:
                break
        # It is guaranteed that a valid pair exists.
        sA = strings[chosen[0]]
        sB = strings[chosen[1]]
        res = merge(sA, sB, n, chosen_char)
        # (By design, the result is of length at most 3n.)
        out_lines.append(res)
    
    sys.stdout.write("\n".join(out_lines))

if __name__ == '__main__':
    solve()
