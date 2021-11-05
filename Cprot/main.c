#include <stdio.h>
#include <stdlib.h>
#include "IEEE754.h"
enum testModes {TEST_INIT_MODE, TEST_VALIDATION_MODE, UNEXPECTED};
int main(int argc, char* argv[]){

    enum testModes mode;
    /*I have to include:
     argc check
     switch construct to enter in the 2 modes:
        1.generating input vectors file and expectedoutputfile
        2.call diff between modelsim-returned output file and the one previusly generated
    */

    /*variables declaration for TEST_INIT_MODE*/
    FILE *fpin, *fpout1, *fpout2;
    float readValue;
    char IEEE754EncodingSTR[SIZE+1];
    /*******************************************/

    if(argc == 1)   //program name only
        mode = TEST_INIT_MODE;
    else if(argc == 2){
        if(*argv[1] == 'i')
            mode = TEST_INIT_MODE;
        else if(*argv[1] == 'v')
            mode = TEST_VALIDATION_MODE;
        else 
            mode = UNEXPECTED;
    }
    else mode = UNEXPECTED;

    switch(mode){

        case TEST_INIT_MODE:
            fpin = fopen("handwrittensamples.txt", "r");
            //fpin = fopen("testSamples.txt", "r");
            fpout1 = fopen("./simulation_inputs.txt", "w");
            fpout2 = fopen("./expected_outputs.txt", "w");
            if(NULL == fpin){
            printf("samples file not found\n");
            }
            printf("generating std_logic_vector samples and expected output result\n");
            while(EOF != fscanf(fpin, "%f", &readValue)){
                printf("read value: %f\n", readValue);
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
            fclose(fpout1);
            fclose(fpout2);
            break;
        case TEST_VALIDATION_MODE:
            /* invoke system() to call a diff between the two output files, 
               the C-generated one and the VHDL-generated one. */
               
               //system("diff ./expected_outputs.txt ./../...addpath...");
        break;
        default:    //i.e. wrong parameters from command line
            printf("Error: wrong arguments\n");
        break;
   }
    
    
    return 0;
}
