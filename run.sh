clear
gcc ./src/master.c -lm -lrt  -o ./bin/master
gcc ./src/processA.c -lbmp -lncurses -lm -lrt -o ./bin/processA
gcc ./src/processB.c -lbmp -lncurses -lm -lrt -o ./bin/processB
./bin/master

