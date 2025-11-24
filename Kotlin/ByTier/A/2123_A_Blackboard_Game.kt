// Problem: CF 2123 A - Blackboard Game
// https://codeforces.com/contest/2123/problem/A

/*
 * Problem: Blackboard Game
 * 
 * Algorithm/Technique: Game Theory, Modular Arithmetic, Greedy Matching
 * 
 * Description:
 * - Initially, integers from 0 to n-1 are written on a blackboard.
 * - Alice and Bob take turns choosing numbers such that the sum of chosen numbers is congruent to 3 modulo 4.
 * - The game ends when a player cannot make a valid move. That player loses.
 * - We determine who wins with optimal play.
 * 
 * Approach:
 * - For each number i on the blackboard, compute i % 4 and count how many numbers fall into each residue class (0,1,2,3).
 * - Valid pairs are those where a + b ≡ 3 (mod 4). This means pairs like:
 *   (0,3), (1,2) etc.
 * - Greedily match:
 *   - Match all (0,3) pairs: min(count[0], count[3])
 *   - Match all (1,2) pairs: min(count[1], count[2])
 * - If total number of such pairs is odd or there are unpaired elements left, Alice wins.
 * 
 * Complexity:
 * Time: O(n) per test case — we iterate through n numbers once.
 * Space: O(1) — fixed-size array for counting.
 */

fun main() {
    val t = readLine()!!.toInt()
    repeat(t) {
        val n = readLine()!!.toInt()
        val count = IntArray(4)
        for (i in 0 until n) {
            count[i % 4]++ // Count numbers by residue mod 4
        }
        val pairs03 = minOf(count[0], count[3]) // Match 0s and 3s
        val pairs12 = minOf(count[1], count[2]) // Match 1s and 2s
        val totalPairs = pairs03 + pairs12 // Total matched pairs
        val unpaired = (count[0] - pairs03) + (count[3] - pairs03) +
                (count[1] - pairs12) + (count[2] - pairs12) // Remaining unmatched numbers
        if (unpaired > 0 || totalPairs % 2 == 1) {
            println("Alice") // Alice wins if there are unpaired numbers or an odd number of valid moves
        } else {
            println("Bob") // Bob wins otherwise
        }
    }
}


// https://github.com/VaHiX/CodeForces/