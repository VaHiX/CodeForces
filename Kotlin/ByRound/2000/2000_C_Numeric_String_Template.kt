// Problem: CF 2000 C - Numeric String Template
// https://codeforces.com/contest/2000/problem/C

/*
 * Problem: Numeric String Template
 * 
 * Algorithm/Technique:
 * - For each string, check if it can be mapped one-to-one with the given array.
 * - Use two hash maps:
 *   - mapAToS: maps array elements to characters
 *   - mapSToA: maps characters to array elements
 * - Traverse the array and string simultaneously:
 *   - If an array element is already mapped, verify the character matches.
 *   - If a character is already mapped, verify the array element matches.
 *   - If not mapped, set up the mapping.
 * - Time Complexity: O(n + m), where n is the length of the array and m is the total length of all strings.
 * - Space Complexity: O(n + k), where n is the number of unique elements in the array, and k is the number of unique characters in the strings.
 */

fun checkMatch(n: Int, a: List<Int>, s: String): String {
    if (s.length != n) { // Check if string length matches array length
        return "NO"
    }
    val mapAToS = mutableMapOf<Int, Char>() // Maps array elements to characters
    val mapSToA = mutableMapOf<Char, Int>() // Maps characters to array elements
    for (i in a.indices) { // Traverse each element
        if (mapAToS.contains(a[i])) { // If array element was already mapped
            if (mapAToS[a[i]] != s[i]) { // Verify character matches
                return "NO"
            }
        } else {
            mapAToS[a[i]] = s[i] // Set mapping from array element to character
        }
        if (mapSToA.contains(s[i])) { // If character was already mapped
            if (mapSToA[s[i]] != a[i]) { // Verify array element matches
                return "NO"
            }
        } else {
            mapSToA[s[i]] = a[i] // Set mapping from character to array element
        }
    }
    return "YES" // All checks passed
}

fun main() {
    val t = readLine()!!.toInt()
    val results = mutableListOf<String>()
    repeat(t) {
        val n = readLine()!!.toInt()
        val a = readLine()!!.split(" ").map { it.toInt() }
        val m = readLine()!!.toInt()
        repeat(m) {
            val s = readLine()!!.trim()
            results.add(checkMatch(n, a, s))
        }
    }
    println(results.joinToString("\n"))
}


// https://github.com/VaHiX/CodeForces/