# LongestCommonSubsequence (Dynamic Programming)
LongestCommonSubsequence 



In this solution, a program using the Longest Common Subsequence method based on dynamic programming logic should be written to perform the following steps:

1. Obtain two different strings of varying lengths from the user.
2. Calculate the size of the longest common subsequence(s) among the given strings.
3. Print all expressions of the same length to the screen.


The problem has been solved using the dynamic programming approach. Firstly, two words are obtained from the user. The sizes of the input words are calculated. Then, the LcsAlgo function, which operates based on dynamic programming logic, is called with the words and their calculated sizes as input.

In the LcsAlgo function, a dynamic matrix of size [size1+1][size2+1] is created to store the results, where size1 and size2 represent the sizes of the input words. The Longest Common Subsequence method is employed to determine the size of the longest common subsequence between the words. According to this method, the indices of the two words are checked, and whenever a match is found, the current position in the dynamic matrix is updated, considering one more than the diagonal element of the matrix. The size of the longest common subsequence between the words is represented by the element at the bottom-right corner of the dynamic matrix (LCS_table[size1][size2]).

The printing of the results is performed in the printUniqueLCS function. In cases where there are multiple results, multiple expressions of the same length are printed to the screen. It is ensured that each expression is printed only once, even if there are multiple expressions of the same length. This check is performed within the respective function, and only distinct expressions of the same length are printed to the screen.



