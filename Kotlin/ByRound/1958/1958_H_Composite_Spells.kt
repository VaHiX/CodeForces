// Problem: CF 1958 H - Composite Spells
// https://codeforces.com/contest/1958/problem/H

/*
 * Problem: H. Composite Spells
 * 
 * Purpose:
 *   This solution determines whether a monster with initial health 'hp' will die when a composite spell
 *   (the last one in the spellbook) is cast on it. If it dies, the index of the basic spell that kills it is returned.
 *   Otherwise, -1 is returned.
 * 
 * Approach:
 *   1. Parse input to represent spells as a dependency tree.
 *   2. For each spell (basic or composite), track:
 *      - Dif[i]: total change in health from all sub-spells (used for propagation).
 *      - Min[i]: minimum cumulative change that can be reached by traversing this spell subtree.
 *   3. Using these values, simulate the process to find which basic spell causes the monster to die.
 * 
 * Time Complexity: O(n + m + total_length_of_all_composite_spells)
 * Space Complexity: O(n + m)
 */
import java.math.BigInteger
import kotlin.math.*
fun readLn() = readLine()!!
fun readInt() = readLn().toInt()
fun readStrings() = readLn().split(" ")
fun readInts() = readStrings().map { it.toInt() }
fun main() {
    var T = readInt()
    for (t in 1..T) {
        // Read number of basic spells and initial health
        var (N, H) = readInts()
        var A = readInts()
        var M = readInt()
        
        // Spell structure: Spell[i] contains the indices of spells that are part of spell i
        val Spell = MutableList(N + M) { mutableListOf<Int>() }
        for (i in 0..(M - 1)) {
            var S = readInts()
            for (j in 1..S[0]) Spell[N + i].add(S[j] - 1)
        }
        
        // Dif[i] keeps the total change of health due to spell i
        var Dif = Array(N + M) { BigInteger("0") }
        // Min[i] keeps the minimum cumulative effect of all sub-spells in spell i
        var Min = Array(N + M) { BigInteger("0") }
        
        // Initialize basic spells' differences and minima
        for (i in 0..(N - 1)) Dif[i] = A[i].toBigInteger()
        for (i in 0..(N - 1)) Min[i] = A[i].toBigInteger()
        
        // Process composite spells from bottom to top, computing their effect recursively
        for (i in N..(N + M - 1)) {
            for (idx in Spell[i]) {
                if (Min[i] > Dif[i] + Min[idx]) Min[i] = Dif[i] + Min[idx]
                Dif[i] = Dif[i] + Dif[idx]
            }
        }
        
        // If even the last composite spell couldn't kill the monster, return -1
        if (Min[N + M - 1] + H.toBigInteger() > BigInteger("0")) {
            println("-1")
        } else {
            // Traverse backwards to find which basic spell made the monster die
            var cx = N + M - 1
            var current = H.toBigInteger()
            while (cx >= N) {
                for (idx in Spell[cx]) {
                    if (Min[idx] + current <= BigInteger("0")) { // If this spell kills the monster now
                        cx = idx
                        break
                    }
                    current += Dif[idx]
                }
            }
            println(cx + 1)
        }
    }
}


// https://github.com/VaHiX/codeForces/