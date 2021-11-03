#include <stdio.h>
#include <stdlib.h>
#include "IEEE754.h"

int main(int argc, char* argv[]){

    /*I have to include:
     argc check
     switch construct to enter in the 2 modes:
        1.generating input vectors file and expectedoutputfile
        2.call diff between modelsim-returned output file and the one previusly generated
    */
    FILE *fpin, *fpout1, *fpout2;
    float readValue;
    char IEEE754EncodingSTR[SIZE+1];
    fpin = fopen("handwrittensamples.txt", "r");
    fpout1 = fopen("./simulation_inputs.txt", "w");
    fpout2 = fopen("./expected_outputs.txt", "w");
    if(NULL == fpin){
        printf("samples file not found\n");
    }
    printf("generating std_logic_vector samples and expected output result\n");
    while(EOF != fscanf(fpin, "%f", &readValue)){
        printf("input vector generation\n");
        Float2IEEE754Conversion(readValue, IEEE754EncodingSTR);
        printf("converted\n");
        fprintf(fpout1, "%s\n", IEEE754EncodingSTR);
         printf("wrote into file.\n");
        readValue = readValue*readValue;
        printf("corresponding expected output generation\n");
        Float2IEEE754Conversion(readValue, IEEE754EncodingSTR);
        printf("converted\n");
        fprintf(fpout2, "%s\n", IEEE754EncodingSTR);
        printf("wrote into file.\n");
    }
    printf("done.\n");
    fclose(fpin);
    //fclose(fpout1);
    //fclose(fpout2);
    return 0;
}