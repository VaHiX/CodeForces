// Problem: CF 2109 A - It's Time To Duel
// https://codeforces.com/contest/2109/problem/A

/*
 * Problem: A. It's Time To Duel
 * 
 * Purpose: Determine if at least one player must be lying based on their reported duel outcomes.
 * 
 * Algorithm:
 * - Model the tournament as a directed graph.
 * - Each player reports whether they won (1) or did not win (0) any duel.
 * - For each player, check constraints:
 *   - If a player reports 0: they must not have beaten anyone (no out edges), and cannot be beaten by anyone (no in edges).
 *   - If a player reports 1: they must have beaten at least one person or been beaten by someone.
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 */

import java.util.*

fun main() {
    val x = readLine()!!.toInt()
    repeat(x) {
        val y = readLine()!!.toInt() // number of players
        val z = IntArray(y + 1) // player reports, index 1 to y
        val input = readLine()!!.split(" ").map { it.toInt() }
        for (i in 1..y) {
            z[i] = input[i - 1] // load reports into array starting at index 1
        }
        val w = y - 1 // number of duels (consecutive pairs)
        val q = Array(w + 1) { mutableListOf<Int>() } // adjacency list for players who could beat others
        val u = mutableListOf<Pair<Int, Boolean>>() // queue of candidates to process with direction info

        // Build graph and initial queue based on reports
        for (i in 1..y) {
            if (z[i] == 0) { // player did not win any duel
                if (i > 1) u.add(Pair(i - 1, true)) // can be beaten by left neighbor
                if (i < y) u.add(Pair(i, false)) // could beat right neighbor
            } else { // player won at least one duel
                when (i) {
                    1 -> u.add(Pair(1, true)) // first player can't be beaten but might have beaten next
                    y -> u.add(Pair(y - 1, false)) // last player can't beat anyone but might have been beaten
                    else -> q[i - 1].add(i) // add edge from i-1 to i (i might win against i-1)
                }
            }
        }

        val p = IntArray(w + 1) { -1 } // -1 means unvisited, 0 means not selected, 1 means selected
        val v: Deque<Pair<Int, Boolean>> = ArrayDeque() // BFS queue with direction

        for (e in u) v.add(e)

        var o = false // flag to store contradiction found
        while (v.isNotEmpty() && !o) {
            val (a, b) = v.removeFirst() // get next candidate node with direction

            if (p[a] != -1) { // if already processed
                if (p[a] != if (b) 1 else 0) { // check if conflict exists
                    o = true
                }
                continue
            }

            p[a] = if (b) 1 else 0 // mark as selected in direction b

            if (b) { // traverse forward
                for (t in q[a]) {
                    v.add(Pair(t, true))
                }
            }
        }

        println(if (o) "YES" else "NO") // print result: YES if contradiction found, NO otherwise
    }
}


// https://github.com/VaHiX/CodeForces/