# Problem: CF 1089 A - Alice the Fan
# https://codeforces.com/contest/1089/problem/A

"""
Problem: Alice the Fan
This problem involves determining valid volleyball match outcomes given total points scored by each team.
Volleyball match rules:
- Up to 5 sets
- First 4 sets: win by scoring at least 25 points, with minimum 2-point lead
- 5th set: win by scoring at least 15 points, with minimum 2-point lead
- Match ends when one team wins 3 sets
- Given total points for each team, determine possible match score and set-by-set breakdown

Approach:
- Use BFS/DP to precompute all valid score combinations
- For each input, look up if combination is possible
- Reconstruct path to get set scores
- Time complexity: O(200^2 * 4^2) for precomputation, O(1) per query
- Space complexity: O(200^2 * 4^2) for DP table
"""
def II():
    return int(input())

def MII():
    return map(int, input().split())

dic_1 = [(0, 1), (0, -1), (-1, 0), (1, 0)]
dic_2 = [(0, 1), (0, -1), (-1, 0), (1, 0), (-1, -1), (-1, 1), (1, 1), (1, -1)]
tt = 1


def yyn():
    def f(score1, score2, set1, set2):
        # Hash function to map state to index
        return (((score1 * 201) + score2) * 4 + set1) * 4 + set2

    # DP table to store if state is reachable (-2: not visited, -1: start, otherwise parent index)
    dp = [-2] * (201 * 201 * 4 * 4)
    dp[f(0, 0, 0, 0)] = -1  # Start state
    que = [f(0, 0, 0, 0)]   # BFS queue
    
    # BFS to find all valid state transitions
    for u in que:
        cur = u
        u, set2 = divmod(u, 4)      # Extract set2
        u, set1 = divmod(u, 4)      # Extract set1
        score1, score2 = divmod(u, 201)  # Extract scores
        
        # Team A wins a set
        if set1 + 1 <= 3 and set2 < 3:
            set_score = 25 if set1 + set2 < 4 else 15  # Determine set target score
            # Normal win: team A scores set_score and team B scores less than set_score
            if score1 + set_score <= 200:
                for i in range(set_score - 1):  # Valid scores for team B
                    if score2 + i <= 200:
                        ncur = f(score1 + set_score, score2 + i, set1 + 1, set2)
                        if dp[ncur] == -2:  # Unvisited state
                            dp[ncur] = cur
                            que.append(ncur)
            # Win by 2-point lead: team A scores more than set_score and team B scores 2 less
            for i in range(set_score + 1, 201):
                if score1 + i > 200 or score2 + i - 2 > 200:
                    break
                ncur = f(score1 + i, score2 + i - 2, set1 + 1, set2)
                if dp[ncur] == -2:
                    dp[ncur] = cur
                    que.append(ncur)
        
        # Team B wins a set
        if set1 < 3 and set2 + 1 <= 3:
            set_score = 25 if set1 + set2 < 4 else 15
            if score2 + set_score <= 200:
                for i in range(set_score - 1):
                    if score1 + i <= 200:
                        ncur = f(score1 + i, score2 + set_score, set1, set2 + 1)
                        if dp[ncur] == -2:
                            dp[ncur] = cur
                            que.append(ncur)
            for i in range(set_score + 1, 201):
                if score1 + i - 2 > 200 or score2 + i > 200:
                    break
                ncur = f(score1 + i - 2, score2 + i, set1, set2 + 1)
                if dp[ncur] == -2:
                    dp[ncur] = cur
                    que.append(ncur)
    
    # Process queries
    t = II()
    outs = []
    for _ in range(t):
        x, y = MII()   # Total points for Team A and Team B
        cx, cy = -1, -1  # Final scores for Team A and Team B in match
        
        # Check for win by Team A (3 sets)
        for i in range(3):
            if dp[f(x, y, 3, i)] != -2:
                cx, cy = 3, i
                break
        
        # Check for win by Team B (3 sets)
        if cx == -1:
            for i in range(2, -1, -1):
                if dp[f(x, y, i, 3)] != -2:
                    cx, cy = i, 3
                    break
        
        if cx != -1:
            # Reconstruct path from target to start
            outs.append(f"{cx}:{cy}")
            cur = f(x, y, cx, cy)
            sets = []
            for _ in range(cx + cy):
                prev = dp[cur]
                scores = (cur - prev) // 16  # Get score difference info
                sets.append(divmod(scores, 201))  # Extract individual scores
                cur = prev
            sets.reverse()
            outs.append(" ".join(f"{a}:{b}" for a, b in sets))
        else:
            outs.append("Impossible")
    
    print("\n".join(outs))


if __name__ == "__main__":
    for ii in range(tt):
        yyn()


# https://github.com/VaHiX/CodeForces/