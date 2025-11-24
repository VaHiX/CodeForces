// Problem: CF 2087 C - Coin Game
// https://codeforces.com/contest/2087/problem/C

/*
C. Coin Game
Algorithms/Techniques: Prefix sums, Greedy, Game Theory
Time Complexity: O(n + q)
Space Complexity: O(n)

The problem involves a game where two players take turns collecting coins of specific types (G, S, B) from a range [l, r]. 
Each player plays optimally to maximize their own collection. For any given segment [l, r], the optimal strategy involves:
1. Counting how many coins of each type are present in that segment.
2. Greedily choosing to take the type with maximum count first (first player benefits more by taking it).
3. Then, the second player will take the remainder of the remaining two types optimally.
4. The first player's final count is: max(count of G,S,B) + min(count of G,S,B).

We use prefix sums to quickly compute counts for any range [l,r].

Input:
- A string s consisting of 'G', 'S', 'B'
- An integer q representing number of queries
- For each query: two integers l and r indicating the range [l, r]

Output:
- For each query, print the number of coins the first player can collect.
*/

import java.util.StringTokenizer

fun main() {
    val br = System.`in`.bufferedReader()
    val out = StringBuilder()
    var tc = 1
    repeat(tc) { solve(br, out) }
    print(out.toString())
}

fun solve(br: java.io.BufferedReader, out: StringBuilder) {
    val s = br.readLine()
    val n = s.length
    val Gold = IntArray(n + 1)
    val Silver = IntArray(n + 1)
    val Bronze = IntArray(n + 1)
    
    // Build prefix sums for each coin type
    for (i in 0 until n) {
        Gold[i + 1] = Gold[i] + if (s[i] == 'G') 1 else 0
        Silver[i + 1] = Silver[i] + if (s[i] == 'S') 1 else 0
        Bronze[i + 1] = Bronze[i] + if (s[i] == 'B') 1 else 0
    }
    
    val q = br.readLine().toInt()
    repeat(q) {
        val st = StringTokenizer(br.readLine())
        val l = st.nextToken().toInt()
        val r = st.nextToken().toInt()
        
        // Get counts in range [l, r] using prefix sums (convert to 0-based indexing)
        val gold = Gold[r] - Gold[l - 1]
        val silver = Silver[r] - Silver[l - 1]
        val bronze = Bronze[r] - Bronze[l - 1]
        
        // First player collects max + min of the three counts
        out.append(maxOf(gold, maxOf(silver, bronze)) + minOf(gold, minOf(silver, bronze))).append('\n')
    }
}


// https://github.com/VaHiX/codeForces/