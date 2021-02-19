#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h> //TODO: Use less libraries

//Complex number in trigonometric form: nth root calculator
//Version: 1.0b

typedef struct trigonometric_complex {
    float modulus;
    float argument;
} trigonometric_cmp;

float pi = 3.14159265;

void n_root_trig_number(float modulus, float argument, float n_root, unsigned int mode, FILE* out_file) {
    trigonometric_cmp trig_num;
    trig_num.modulus = modulus;
    trig_num.argument = argument;
    trigonometric_cmp n_root_trig;
    n_root_trig.modulus = pow(trig_num.modulus, (1/n_root));
    for(int i=0; i<n_root; i++) {
        n_root_trig.argument = (trig_num.argument+2*pi*i)/n_root;
        if(mode==0) {
            printf("%f %f ", n_root_trig.modulus, n_root_trig.argument);
        }
        else if(mode==1) {
            fprintf(out_file, "%f %f ", n_root_trig.modulus, n_root_trig.argument);
        }
    }
}

int main(int argc, char** argv) {
    float modulus, argument, n_root;
    if(!strcmp("-d", argv[1])) {
        modulus = atof(argv[2]);
        argument = atof(argv[3]);
        n_root = atof(argv[4]);
        n_root_trig_number(modulus, argument, n_root, 0, 0);
    }
    else if(!strcmp(("-f"), argv[1])) {
        FILE *in_file, *out_file;
        in_file = fopen(argv[2], "rb");
        out_file = fopen(argv[3], "wb");
        do{
            fscanf(in_file, "%f %f %f", &modulus, &argument, &n_root);
            n_root_trig_number(modulus, argument, n_root, 1, out_file);
            fprintf(out_file, "\n");
        } while(!feof(in_file));
        fclose(in_file);
        fclose(out_file);
    }
    else if(!strcmp(("-b"), argv[1])) {
        clock_t tick = clock();
        for(int i=0; i<atoi(argv[2]); i++) {
            modulus = rand()%1000000;
            argument = rand()%1000000;
            n_root = rand()%200;
            n_root_trig_number(modulus, argument, n_root, 2, 0);

        }
        clock_t tock = clock();
        double time_benchmark = (double)(tock-tick)/CLOCKS_PER_SEC;
        printf("Benchmark time: %fms", time_benchmark);
    }
return 0;
}
