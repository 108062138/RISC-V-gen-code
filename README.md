# RISC-V-gen-code
===
## abstract
- This project is about the third project in LJK-NTHU-COMPILER class. Its main purpose targetes to generate RISC-V code based on the parser, which was implemented by the second project.
## how to run this project
- type `chmod 777 run.sh` to enable the the shell script in the current working directory
- type `./run.sh` to run the project. See the `./run.sh`'s content to realize work it executes. The first line `make` compiles the revised parser. Next, dump the testbench `./test.c` into the parser's binary executable file. It produces `./codegen.S`. `./codegen.S` is the assembly code generated by the parser. It interacts with `./main.c` to simulate the arduino board.
```javascript=
make
./parser < test.c
riscv64-unknown-elf-gcc -o sample_prog main.c codegen.S
spike pk sample_prog
```
## support function
- Up to level C. That is, basic, 
