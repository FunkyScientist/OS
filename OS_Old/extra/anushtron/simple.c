#include <stdio.h>
#include <stdlib.h>
#include "simple.h"

//void smlTxt_Into_RAM(int array[],const *char fileName);

void smlTxt_Into_RAM(int array[],const char *fileName);
void display(int accum, int instCounter, int instructionRegister, int opCode, int operand, int array[]) {
    
    printf("Accumulator : %d \n", accum);
    printf("Instruction Counter : %d \n", instCounter);
    printf("Instruction Register : %04d \n", instructionRegister);
    printf("OpCode : %02d \n", opCode);
    printf("Operand : %02d\n\n", operand);
    
    for(int i=0; i<100; i++)
     {
        printf("%04d \t", array[i]);
        if ((i + 1) % 10 == 0) {
            printf("\n");
        }
}}


int main(int argc,char *agrv[]){
    const char *filename=agrv[1];
    int instructionRegister;
    int Ram[SIZE];
    int opCode;
    int operand;
    int accumulator=0;
     int instructionCounter = 0;
 
 smlTxt_Into_RAM(Ram,filename);
  
     for (int i=0; i<SIZE && Ram[i]!= 0; i++)
  {
   instructionRegister=Ram[i];
   instructionCounter=i+1;    
   opCode=Ram[i]/100;
   operand=Ram[i]%100; 
 
   
   //display(accumulator,instructionCounter,instructionRegister,opCode,operand,Ram);
   if(opCode==READ){
   printf("\nExecuting Instruction : %04d \n",instructionRegister);
   printf("------------------------------------------------------------------\n");
   int num;
   printf("\nEnter a number ");
   scanf("%d" , &num);
   Ram[operand-1]=num;
   display(accumulator,instructionCounter,instructionRegister,opCode,operand,Ram);
   }
   
   else if(opCode==WRITE){
   printf("Number %d is at Memory location %d \n " , Ram[operand], operand );
   }
   
   else if (opCode==LOAD ){ 
   printf("\nExecuting Instruction : %04d \n",instructionRegister);
   printf("------------------------------------------------------------------\n");
   
   accumulator=Ram[operand-1];
    display(accumulator,instructionCounter,instructionRegister,opCode,operand,Ram);
   }
   
   else if( opCode==STORE ){
   printf("\nExecuting Instruction : %04d \n",instructionRegister);
   printf("------------------------------------------------------------------\n");
   Ram[operand-1]=accumulator;
   display(accumulator,instructionCounter,instructionRegister,opCode,operand,Ram);

   }
   else if(opCode== ADD){
   printf("\nExecuting Instruction : %04d \n",instructionRegister);
   printf("------------------------------------------------------------------\n");
  
   accumulator= accumulator + Ram[operand-1];
   display(accumulator,instructionCounter,instructionRegister,opCode,operand,Ram);

   }
   else if(opCode==SUBTRACT){
   printf("\nExecuting Instruction : %04d \n",instructionRegister);
   printf("------------------------------------------------------------------\n");
   accumulator= accumulator - Ram[operand-1];
   display(accumulator,instructionCounter,instructionRegister,opCode,operand,Ram);

   }
   else if(opCode==DIVIDE){
   printf("\nExecuting Instruction : %04d \n",instructionRegister);
   printf("------------------------------------------------------------------\n");
   accumulator= accumulator / Ram[operand-1];
   display(accumulator,instructionCounter,instructionRegister,opCode,operand,Ram);
   }
   else if(opCode==MULTIPLY){
   printf("\nExecuting Instruction : %04d \n",instructionRegister);
   printf("------------------------------------------------------------------\n");
   accumulator= accumulator * Ram[operand-1];
   display(accumulator,instructionCounter,instructionRegister,opCode,operand,Ram);
   }
   else if(opCode==BRANCH){
   printf("\nExecuting Instruction : %04d \n",instructionRegister);
   printf("------------------------------------------------------------------\n");
   instructionCounter= operand-1;
   display(accumulator,instructionCounter,instructionRegister,opCode,operand,Ram);
   }
    else if(opCode==BRANCHNEG){
   printf("\nExecuting Instruction : %04d \n",instructionRegister);
   printf("------------------------------------------------------------------\n");
   if(accumulator<0){
   instructionCounter= operand-1;
   }
   display(accumulator,instructionCounter,instructionRegister,opCode,operand,Ram);
   }
    else if(opCode==BRANCHZERO){
   printf("\nExecuting Instruction : %04d \n",instructionRegister);
   printf("------------------------------------------------------------------\n");
   if(accumulator==0){
   instructionCounter= operand-1;
   }
   display(accumulator,instructionCounter,instructionRegister,opCode,operand,Ram);
   }
  else if(opCode==HALT){
   display(accumulator,instructionCounter,instructionRegister,opCode,operand,Ram);
  exit(0);
  printf("\nSimpletron Execution completed/terminated");
  }   
 
  }
     printf("\n\n");
     return 0;
}
