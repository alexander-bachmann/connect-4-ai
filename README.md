# Connect 4 AI

## About
Command-line interface Connect 4 game with ability to change number of contiguous disks and board size. Using the Minimax and Alpha-beta pruning algorithms, the AI decides optimal moves after exploring hundreds of possible board positions several turns into the future.

For more detail, feel free to read the [report](https://github.com/alexander-bachmann/connect-4-ai/blob/master/Connect_M_Report.pdf)

## Compilation and Execution commands
```
make
./connectM n m
```
n = board dimension size
m = number of contiguous disks required for a win

---

e.g. this command will create a 7 x 7 game board and 4 disks will need to appear contiguously to win
```
./connectM 7 4
```
