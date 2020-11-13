# cliArgTest

Test project after the installation of Eclipse C/C++ on Manjaro.

---

Interesting: See how `setw()` handles unicode chars in the encoding module:
```
$ ./cliArgTest -a b ä en äöü test ÿ
arguments:

   1: -a              2D 61 nBytes: 2
   2: b               62 nBytes: 1
   3: ä              C3 A4 nBytes: 2
   4: en              65 6E nBytes: 2
   5: äöü          C3 A4 C3 B6 C3 BC nBytes: 6
   6: test            74 65 73 74 nBytes: 4
   7: ÿ              C3 BF nBytes: 2
```
