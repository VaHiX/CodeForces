/*
 * Problem URL : https://codeforces.com/problemset/problem/12/A
 * Submit Date : 2025-08-08
 */

#include <fstream>
#include <iostream>
#include <sstream>

int main() {

  std::ifstream inputFile;
  inputFile.open("input.txt");
  int T;
  inputFile >> T;
  FILE *outputFile = fopen("output.txt", "w");
  while (T--) {
    long n;
    inputFile >> n;
    fputs((n % 2) ? "0\n" : "1\n", outputFile);
  }

  inputFile.close();
  fclose(outputFile);

  return 0;
}
