Author: Bilal Nurhusien
Created on: 2013-08-05 

Description:
Implemented a variant of the median maintenance algorithm using max and min heaps.

Input File:
The text file (Median.txt) contains a list of integers from 1 to 10000 in unsorted
order. The numbers are treated as a stream of integers arriving one by one. Let xi
denote the ith number of the file. The kth median mk is defined as the median of the
numbers x1,...,xk. If k is odd, then mk is the((k+1)/2)th smallest number among 
x1,...,xk; if k is even, then mk is the (k/2)th smallest number among x1,...,xk.

The input file was taken from an Algorithms and Analysis course from Stanford,
taught by Tim Roughgarden.

Output:
The median sum of numbers modulo 10000 is displayed using standard output.
i.e. (m1+m2+m3+...+m10000)mod10000 where m1 is the first median, m2 is
the second median, etc.
