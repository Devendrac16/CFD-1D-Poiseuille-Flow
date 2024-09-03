#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
int main()
{
    int i, j, n=101, iteration=0;
    double dx, Re=100.0, dt=5.0e-3,t=0.0;
    double gamma = 0.5, error;

    double phi_old[n], phi_new[n];

    dx = 1.0/(n-1);

    FILE *f1;
    f1 = fopen("COUETTE_FTCS.txt","w");
    if(f1== NULL){
            printf("\n cannot open file\n");
            exit(1);
    }

    FILE *f4;
    f4 = fopen("COUETTE_FTCS_error.txt","w");
    if(f4== NULL){
            printf("\n cannot open file\n");
            exit(1);
    }
    
    for (int i = 0; i < n; i++)
    {
        if(i==0){
            phi_new[i] = 0.0;
        }
        else if( i == n-1){
            phi_new[i]= 1.0;
        }
        else{
            phi_new[i]=0.0;
        }       
    }

    char name[50];

    do{
        if ((iteration+100)%100 == 0){
            sprintf(name, "velocity_%.2f.dat",t);
                FILE *f2;
                f2 = fopen(name,"w");
                for(i=1;i<n;i++){
                    fprintf(f2,"%lf\t%lf\n", phi_new[i], i*dx);
                }fclose(f2);
        }

        for(i=0;i<n;i++){
            phi_old[i]=phi_new[i];
        }

        for(i=1;i<(n-1);i++){
            phi_new[i]=phi_old[i] + gamma*(phi_old[i+1] - 2.0*phi_old[i] + phi_old[i-1]);
        }

        error = 0.0;
        for (int i = 1; i < n-1; i++)
        {
            error = error + pow((phi_new[i] - phi_old[i]), 2.0);
        }
        error = sqrt ( error / ( double )( (n-1) ) );
        printf( "\niteration = %d \t" "Error =  %.10lf", iteration, error);
        fprintf(f4, "%d \t %.10lf\n", iteration, error);
        fprintf(f1,"\n %.10lf", error);

        t+=dt;
        printf("\tTime = %lf\n",t);
        fprintf(f1,"\t%lf\n",t);
        iteration++;
    }while(error > 1e-6);

    fclose(f1);
    fclose(f4);
    
    return 0;
}