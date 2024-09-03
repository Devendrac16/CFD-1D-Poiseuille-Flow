#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int main()
{
    int i, j, n=101, iteration=0;
    double dy, Re=100.0, dt=5.0e-3,t=0.0,error=0.0;
    double gamma = 1.0;
 
    

    double u_old[n+2], u_new[n+2];

    dy = 1.0/(n-1);

    double a= -(1+(2.0*gamma));
    double LHS, RHS, r;
    FILE *f1;
    f1 = fopen("COUETTE_GS_LINEAR.txt","w");
    if(f1== NULL){
            printf("\n cannot open file\n");
            exit(1);
    }
    FILE *f4;
    f4 = fopen("COUETTE_GS_LINEAR_error.txt","w");
    if(f4== NULL){
            printf("\n cannot open file\n");
            exit(1);
    }
    
    char name[50];


    
    for (int i = 1; i <= n; i++)
    {
        if(i==1){
            u_new[i] = 0.0;
            u_old[i] = 0.0;
        }
        else if( i == n){
            u_new[i]= 1.0;
            u_old[i] = 1.0;
        }
        else{
            u_new[i]=0.0;
            u_old[i] = 0.0;
        }     
    }

    do{
        if ((iteration+100)%100 == 0){
            sprintf(name, "velocity_GS_LINEAR_%.2f.dat",t);
                FILE *f2;
                f2 = fopen(name,"w");
                for(i=1;i<n;i++){
                    fprintf(f2,"%lf\t%lf\n", u_new[i+1], i*dy);
                }fclose(f2);
        }

        error = 0.0;
        for(i=2; i<n; i++){
            LHS = gamma*u_new[i-1] + a*u_new[i] + gamma*u_new[i+1];
            RHS = -u_old[i];
            r = RHS - LHS;
            u_new[i] = u_old[i] + (r/a);
            error = error + pow((u_new[i] - u_old[i]),2.0);
        }
        
        error = sqrt ( error / ( double )( (n-1) ) );
        printf( "\niteration = %d \t" "Error =  %.10lf", iteration, error);
        fprintf(f4, "\n %d \t %.10lf", iteration, error);
        fprintf(f1,"\n %.10lf", error);

        for(i=1; i<=n; i++){
            u_old[i] = u_new[i];
        }

        t+=dt;
        printf("\tTime = %lf\n",t);
        fprintf(f1,"\t%lf\n",t);
        iteration++;
    }while(error>1e-6);

    fclose(f1);
    fclose(f4);

    return 0;
}