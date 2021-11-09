#include  "stdio.h"
#include  "stdlib.h"

int main(int argc, char **argv) {

    FILE *fp_in = NULL;
    FILE *fp_out = NULL;

    unsigned int x1;
    void *f1;
    void *f3;
    float result;

    fp_in = fopen("../fp_samples.hex", "r");
    if (fp_in == NULL) {
        printf("Error: cannot open file\n");
        exit(2);
    }

    fp_out = fopen("result.txt", "w");

    /// get factor
    do{
        fscanf(fp_in, "%x", &x1);
        f1 = &x1;
        result = *((float *) f1) * *((float *) f1);
        f3 = &result;
        //ieee 754 conversion
        fprintf(fp_out,"%8.8x\n",(unsigned int) *((int *) f3));
        fprintf(stdout,"[0x%8.8x (%19.16f)]^2  = 0x%8.8x (%19.16f)\n", x1, *((float *) f1), *((unsigned int *) f3), result);
    } while (!feof(fp_in));

    fclose(fp_in);
    fclose(fp_out);

    return 0;


}