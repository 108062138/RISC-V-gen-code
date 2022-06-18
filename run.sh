make
#rm ./GOLDENOUTPUT.xml
#rm ./MYOUTPUT.xml
##./parser < ./testcases/test1.c > MYOUTPUT.xml
##golden_parser < ./testcases/test1.c > GOLDENOUTPUT.xml
#./parser < ./test.c > MYOUTPUT.xml
#golden_parser < ./test.c > GOLDENOUTPUT.xml
#diff MYOUTPUT.xml GOLDENOUTPUT.xml

./parser < test.c
riscv64-unknown-elf-gcc -o sample_prog main.c codegen.S
spike pk sample_prog