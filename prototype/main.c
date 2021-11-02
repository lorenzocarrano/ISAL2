#include  "stdio.h"
#include  "stdlib.h"

int main(int argc, char **argv) {

    FILE *fp_in = NULL;
    FILE *fp_out = NULL;

    unsigned int x1, x2;
    void *f1;
    void *f2;
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
        fscanf(fp_in, "%x", &x2);
        f1 = &x1;
        f2 = &x2;
        result = *((float *) f1) * *((float *) f2);
        f3 = &result;
        //ieee 754 conversion
        fprintf(fp_out,"%x\n",(unsigned int) *((int *) f1));
        fprintf(stdout,"0x%x (%.16f) * 0x%x (%.16f) = %.16f\n", x1, *((float *) f1), x2, *((float *) f2), result);
    } while (!feof(fp_in));

    fclose(fp_in);
    fclose(fp_out);

    return 0;


}