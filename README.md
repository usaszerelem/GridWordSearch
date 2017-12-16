## Problem Details

A word can be found in a grid by starting on any letter, then moving to an
adjacent letter and so on.

Example 1.
```
a b a n
z q z d
r r o r
r n r r
```
The word "abandon" fits in the grid first horizontally, then diagonally down
and to the left. The word "ran" does NOT fit in the grid because 'r' and 'a'
are not adjacent.
```
Example 2.
z z z z
z z b z
h z e z
a z z z
```
Contains the words "be", "ha", and "ah". It should not contain "bee" or "ebb"
or "he" or "hah".

## Implementation Details
Your program should not print any word more than once. Your program can assume
that the word list file contains no duplicated words and that the input
arguments are valid.

Your program should be tolerant of word files that contain a mixture of upper
and lower case words and of words that contain punctuation. Your program can
deal with such words in some reasonable way. Note that different word list
files can be alphabetized differently.

## The original request was as follows

If you use C++, we ask that you do not use the Standard Template Library
containers and iterators; we would like to see your own data structures and
algorithms. (Exception: you can use std::string.)

Please do not copy or examine any of your or other peoples existing code while
writing this program. Please write it from scratch. (Exception: you may use the
file I/O code you wrote as part of the prerequisites mentioned previously.)
We realize your program will just be a prototype. We do not expect this to be
production quality software, nor is it embedded code (you need not restrict
yourself to embedded programming practices.)

Work quickly, but accurately because we take into consideration how fast you're
able to write the program. However, the most important thing is to make 
your program works correctly.

Strive for simplicity in your code and data structures. A simple, concise
program is more impressive than a long, complicated one and also easier to
write quickly.

## What I will demonstrate

I will write this test exercise twice. The first iteration will be entirely
in plain 'C' to demonstrate how this can be done with ye good ol' stone axe
approach. The second iteration of this program is going to be in more modern
C++, but still not relying on the STL libraries solely for the purpose of
showing how simple C++ can also be, and how this improved 'high level' by
today's standard, programming language simplifies the task of creating
software without memory leaks.

## Test Patterns to validate your code with

Grid xabaxnxbxxdaxxon : should find abandon
```
x a b a
x n x b
x x d a
x x o n
```
Grid xxonxxdaxnxbxaba : should find abandon
```
x x o n
x x d a
x n x b
x a b a
```
Grid noxxadxxbxnxabax : should find abandon
```
n o x x
a d x x
b x n x
a b a x
```
Grid abaxbxnxadxxnoxx : should find abandon
```
a b a x
b x n x
a d x x
n o x x
```
Grid acknelwodgemstne : should find acknowledgements
```
a c k n
e l w o
d g e m
s t n e
```
Grid niitrozaeacatcrh : should find characterization
```
n i i t
r o z a
e a c a
t c r h
```
Grid inzznnzzgznzzzzi : should find inning
```
i n z z
n n z z
g z n z
z z z i
```
Grid inzznnzzgznzzzzi : should find inning
```
i n z z
n n z z
g z n z
z z z i
```
Grid zzzigznznnzzinzz : should find inning
```
z z z i
g z n z
n n z z
i n z z
```
Grid ingznnzzzznzzzzi : should find inning
```
i n g z
n n z z
z z n z
z z z i
```
Grid zzzizznznnzzingz : should find inning
```
z z z i
z z n z
n n z z
i n g z
```
Grid izzzznzgzznnzzni : should find inning
```
i z z z
z n z g
z z n n
z z n i
```
Grid zznizznnznzgizzz : should find inning
```
z z n i
z z n n
z n z g
i z z z
```
Grid izzzznzzzznnzgni : should find inning
```
i z z z
z n z z
z z n n
z g n i
```
Grid zgnizznnznzzizzz : should find inning
```
z g n i
z z n n
z n z z
i z z z
```