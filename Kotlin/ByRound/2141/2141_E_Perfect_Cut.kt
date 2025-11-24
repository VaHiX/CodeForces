// Problem: CF 2141 E - Perfect Cut
// https://codeforces.com/contest/2141/problem/E

/*
E. Perfect Cut

Problem Description:
Given a string s of '0', '1', and '?', we need to count how many ways we can replace '?' with '0' or '1'
such that the resulting binary string is "perfect". A string is perfect if it can be split into two non-empty parts
(a prefix and a suffix) such that for each position i, the character in the prefix is greater than or equal to
the character in the suffix (i.e., a[i] >= b[i]).

Algorithm:
1. For each test case:
   - Count the number of '?' characters (q).
   - Calculate 2^q possibilities for replacing '?'.
   - Check if there are any invalid patterns:
     * If first char is '1' → impossible to form perfect string.
     * If any character is '0', it can't be in a valid prefix because even the smallest suffix would
       require characters >= current prefix chars.
   - Subtract 1 from total possibilities if such constraints are met.

Time Complexity: O(n) per test case where n is length of string (due to counting '?' and checking conditions)
Space Complexity: O(1) additional space excluding input/output

Techniques:
- Modular exponentiation for fast computation of 2^q (mod 998244353)
- Bit manipulation for modular exponentiation
*/
import java.io.BufferedReader
import java.io.InputStreamReader

const val MOD: Long = 998244353L

fun modPow2(exp: Int): Long {
    var e = exp
    var base = 2L
    var res = 1L
    while (e > 0) {
        if ((e and 1) == 1) res = (res * base) % MOD // If exponent is odd, multiply result by current base
        base = (base * base) % MOD                  // Square the base
        e = e ushr 1                                // Right shift to halve exponent
    }
    return res
}

fun main() {
    val br = BufferedReader(InputStreamReader(System.`in`))
    val t = br.readLine().trim().toInt()
    val out = StringBuilder()
    
    repeat(t) {
        val s = br.readLine().trim()
        val n = s.length
        val q = s.count { it == '?' } // Count number of question marks
        val pow = modPow2(q)          // Total possible combinations for replacing '?'
        
        var patternPossible = true    // Flag to check if pattern is valid
        
        if (s[0] == '1') patternPossible = false  // First char cannot be '1' for a perfect string
        
        for (i in 1 until n) if (s[i] == '0') patternPossible = false // If any char after first is '0', not valid
        
        var ans = (pow - if (patternPossible) 1L else 0L) % MOD  // Subtract 1 if impossible patterns exist
        if (ans < 0) ans += MOD                                  // Ensure result is positive modulo
        out.append(ans).append('\n')
    }
    print(out.toString())
}


// https://github.com/VaHiX/codeForces/