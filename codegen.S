.global codegen
codegen:
  // BEGIN PROLOGUE
addi sp, sp, -104
sd sp, 96(sp)    
sd s0, 88(sp)    
sd s1, 80(sp)    
sd s2, 72(sp)    
sd s3, 64(sp)    
sd s4, 56(sp)    
sd s5, 48(sp)    
sd s6, 40(sp)    
sd s7, 32(sp)    
sd s8, 24(sp)    
sd s9, 16(sp)    
sd s10, 8(sp)    
sd s11, 0(sp)    
addi s0, sp, 104 
  // END PROLOGUE
  
//start push 58 on the stack       
li t0, 58       
addi sp, sp, -4 
sw t0, 0(sp)    
//end push 58 on the stack       

//start push 17 on the stack       
li t0, 17       
addi sp, sp, -4 
sw t0, 0(sp)    
//end push 17 on the stack       

lw t0, 0(sp)   
addi sp,sp, 4  
lw t1, 0(sp)   
addi sp,sp, 4  
div t0, t1, t0 
addi sp,sp, -4 
sw t0, 0(sp)   

//start type ident 
lw t0, 0(sp)  
addi sp,sp, 4 
sw t0, -20(fp) 
//finish place a into memory and it is stored at -20  

// ident: a and it is stored at -20(fp)  
lw t0, -20(fp)  
addi sp,sp, -4 
sw t0, 0(sp)   

//start push 2 on the stack       
li t0, 2       
addi sp, sp, -4 
sw t0, 0(sp)    
//end push 2 on the stack       

lw t0, 0(sp)   
addi sp,sp, 4  
lw t1, 0(sp)   
addi sp,sp, 4  
mul t0, t0, t1 
addi sp,sp, -4 
sw t0, 0(sp)   

//start push 10 on the stack       
li t0, 10       
addi sp, sp, -4 
sw t0, 0(sp)    
//end push 10 on the stack       

lw t0, 0(sp)   
addi sp,sp, 4  
lw t1, 0(sp)   
addi sp,sp, 4  
add t0, t0, t1 
addi sp,sp, -4 
sw t0, 0(sp)   

//start type ident 
lw t0, 0(sp)  
addi sp,sp, 4 
sw t0, -24(fp) 
//finish place b into memory and it is stored at -24  

// ident: a and it is stored at -20(fp)  
lw t0, -20(fp)  
addi sp,sp, -4 
sw t0, 0(sp)   

// enter & expr, retriving the address 
// ident: a and it is stored at -20(fp)  
lw t0, 0(sp)   
addi sp,sp, 4  
li t0, -20      
addi sp,sp, -4 
sw t0, 0(sp)   
//start type ident 
lw t0, 0(sp)  
addi sp,sp, 4 
sw t0, -28(fp) 
//finish place c into memory and it is stored at -28  

// ident: c and it is stored at -28(fp)  
lw t0, -28(fp)  
addi sp,sp, -4 
sw t0, 0(sp)   

lw t0, 0(sp)   
addi sp,sp, 4  
lw t1, -28(fp)  
add t2, t1, fp 
lw t3, 0(t2)   
addi sp,sp, -4 
sw t3, 0(sp)   
// ident: c and it is stored at -28(fp)  
lw t0, -28(fp)  
addi sp,sp, -4 
sw t0, 0(sp)   

lw t0, 0(sp)   
addi sp,sp, 4  
lw t1, -28(fp)  
add t2, t1, fp 
lw t3, 0(t2)   
addi sp,sp, -4 
sw t3, 0(sp)   
//start push 1 on the stack       
li t0, 1       
addi sp, sp, -4 
sw t0, 0(sp)    
//end push 1 on the stack       

lw t0, 0(sp)   
addi sp,sp, 4  
lw t1, 0(sp)   
addi sp,sp, 4  
add t0, t0, t1 
addi sp,sp, -4 
sw t0, 0(sp)   

//enter expr assign 
// ident: *c and it is stored at -28(fp)  
lw t0, 0(sp)   
addi sp,sp, 4  
lw t1, 0(sp)   
addi sp,sp, 4  
lw t2, -28(fp)  
add t3, t2, fp 
sw t0, 0(t3) 
//finish expr assign 

// ident: c and it is stored at -28(fp)  
lw t0, -28(fp)  
addi sp,sp, -4 
sw t0, 0(sp)   

// ident: b and it is stored at -24(fp)  
lw t0, -24(fp)  
addi sp,sp, -4 
sw t0, 0(sp)   

// enter & expr, retriving the address 
// ident: b and it is stored at -24(fp)  
lw t0, 0(sp)   
addi sp,sp, 4  
li t0, -24      
addi sp,sp, -4 
sw t0, 0(sp)   
//enter expr assign 
// ident: c and it is stored at -28(fp)  
lw t0, 0(sp)   
addi sp,sp, 4  
lw t1, 0(sp)   
addi sp,sp, 4  
sw t0, -28(fp)  
//finish expr assign 

// ident: c and it is stored at -28(fp)  
lw t0, -28(fp)  
addi sp,sp, -4 
sw t0, 0(sp)   

lw t0, 0(sp)   
addi sp,sp, 4  
lw t1, -28(fp)  
add t2, t1, fp 
lw t3, 0(t2)   
addi sp,sp, -4 
sw t3, 0(sp)   
// ident: b and it is stored at -24(fp)  
lw t0, -24(fp)  
addi sp,sp, -4 
sw t0, 0(sp)   

// ident: a and it is stored at -20(fp)  
lw t0, -20(fp)  
addi sp,sp, -4 
sw t0, 0(sp)   

lw t0, 0(sp)   
addi sp,sp, 4  
lw t1, 0(sp)   
addi sp,sp, 4  
div t0, t1, t0 
addi sp,sp, -4 
sw t0, 0(sp)   

//enter expr assign 
// ident: *c and it is stored at -28(fp)  
lw t0, 0(sp)   
addi sp,sp, 4  
lw t1, 0(sp)   
addi sp,sp, 4  
lw t2, -28(fp)  
add t3, t2, fp 
sw t0, 0(t3) 
//finish expr assign 

addi sp, sp, -8  
sd ra, 0(sp)  
//start push 29 on the stack       
li t0, 29       
addi sp, sp, -4 
sw t0, 0(sp)    
//end push 29 on the stack       

ld a0, 0(sp)  
addi sp, sp, 4  
//start push 1 on the stack       
li t0, 1       
addi sp, sp, -4 
sw t0, 0(sp)    
//end push 1 on the stack       

ld a1, 0(sp)  
addi sp, sp, 4  
jal ra,digitalWrite  
ld ra, 0(sp)  
addi sp, sp, 8

addi sp, sp, -8  
sd ra, 0(sp)  
// ident: a and it is stored at -20(fp)  
lw t0, -20(fp)  
addi sp,sp, -4 
sw t0, 0(sp)   

//start push 1000 on the stack       
li t0, 1000       
addi sp, sp, -4 
sw t0, 0(sp)    
//end push 1000 on the stack       

lw t0, 0(sp)   
addi sp,sp, 4  
lw t1, 0(sp)   
addi sp,sp, 4  
mul t0, t0, t1 
addi sp,sp, -4 
sw t0, 0(sp)   

//start push 1000 on the stack       
li t0, 1000       
addi sp, sp, -4 
sw t0, 0(sp)    
//end push 1000 on the stack       

lw t0, 0(sp)   
addi sp,sp, 4  
lw t1, 0(sp)   
addi sp,sp, 4  
add t0, t0, t1 
addi sp,sp, -4 
sw t0, 0(sp)   

ld a0, 0(sp)  
addi sp, sp, 4  
jal ra, delay  
ld ra, 0(sp)  
addi sp, sp, 8

addi sp, sp, -8  
sd ra, 0(sp)  
//start push 29 on the stack       
li t0, 29       
addi sp, sp, -4 
sw t0, 0(sp)    
//end push 29 on the stack       

ld a0, 0(sp)  
addi sp, sp, 4  
//start push 0 on the stack       
li t0, 0       
addi sp, sp, -4 
sw t0, 0(sp)    
//end push 0 on the stack       

ld a1, 0(sp)  
addi sp, sp, 4  
jal ra,digitalWrite  
ld ra, 0(sp)  
addi sp, sp, 8

addi sp, sp, -8  
sd ra, 0(sp)  
// ident: b and it is stored at -24(fp)  
lw t0, -24(fp)  
addi sp,sp, -4 
sw t0, 0(sp)   

//start push 1000 on the stack       
li t0, 1000       
addi sp, sp, -4 
sw t0, 0(sp)    
//end push 1000 on the stack       

lw t0, 0(sp)   
addi sp,sp, 4  
lw t1, 0(sp)   
addi sp,sp, 4  
mul t0, t0, t1 
addi sp,sp, -4 
sw t0, 0(sp)   

//start push 250 on the stack       
li t0, 250       
addi sp, sp, -4 
sw t0, 0(sp)    
//end push 250 on the stack       

//start push 8 on the stack       
li t0, 8       
addi sp, sp, -4 
sw t0, 0(sp)    
//end push 8 on the stack       

lw t0, 0(sp)   
addi sp,sp, 4  
lw t1, 0(sp)   
addi sp,sp, 4  
mul t0, t0, t1 
addi sp,sp, -4 
sw t0, 0(sp)   

lw t0, 0(sp)   
addi sp,sp, 4  
lw t1, 0(sp)   
addi sp,sp, 4  
sub t0, t1, t0 
addi sp,sp, -4 
sw t0, 0(sp)   

ld a0, 0(sp)  
addi sp, sp, 4  
jal ra, delay  
ld ra, 0(sp)  
addi sp, sp, 8

// BEGIN EPILOGUE: restore callee-saved registers                              
// note that here we assume that the stack is properly maintained, which means 
// $sp should point to the same address as when the function prologue exits    
ld sp, 96(sp)                                                                  
ld s0, 88(sp)                                                                  
ld s1, 80(sp)                                                                  
ld s2, 72(sp)                                                                  
ld s3, 64(sp)                                                                  
ld s4, 56(sp)                                                                  
ld s5, 48(sp)                                                                  
ld s6, 40(sp)                                                                  
ld s7, 32(sp)                                                                  
ld s8, 24(sp)                                                                  
ld s9, 16(sp)                                                                  
ld s10, 8(sp)                                                                  
ld s11, 0(sp)                                                                  
addi sp, sp, 104                                                               
// END EPILOGUE                                                                
jalr zero, 0(ra)

