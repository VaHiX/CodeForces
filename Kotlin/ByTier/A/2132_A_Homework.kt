// Problem: CF 2132 A - Homework
// https://codeforces.com/contest/2132/problem/A

/*
 * Problem: Vlad and Dima append characters from string b to string a.
 *          Vlad appends to the beginning ('V'), Dima appends to the end ('D').
 *          
 * Algorithms/Techniques: String manipulation, simulation
 * 
 * Time Complexity: O(n * m) where n is the length of string a and m is the length of string b
 * Space Complexity: O(n + m) for storing the input strings and result
 */

fun main() {
    val T = readln().toInt(); // Read number of test cases
    repeat(T) {
        readln() // Read length of string a (not used further)
        var ans = readln(); // Read initial string a
        val n = readln().toInt(); // Read length of string b
        val toAdd = readln() // Read string b
        val whichSide = readln(); // Read distribution string c
        
        for (i in 0 until n) { // For each character in string b
            if (whichSide[i] == 'V') { // If Vlad adds it (to the beginning)
                ans = toAdd[i] + ans; // Prepend character to ans
            } else { // If Dima adds it (to the end)
                ans += toAdd[i]; // Append character to ans
            }
        }
        println(ans); // Print final result
    }
}


// https://github.com/VaHiX/codeForces/