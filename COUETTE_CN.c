#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int main()
{
    int i, j, n=101, iteration=0;
    double dy, Re=100.0, dt=5.0e-3,t=0.0,error=0.0;
    double gamma = 1.0;
    
    

    double phi_old[n+10], phi_new[n+10];

    dy = 1.0/(n-1);

    double a, b, c, d[n+10], p[n+10], q[n+10];
    a = 2.0;
    b = -0.5;
    c = -0.5;
        
    
    FILE *f1;
    f1 = fopen("COUETTE_CN.txt","w");
    if(f1== NULL){
            printf("\n cannot open file\n");
            exit(1);
    }

    
    for (int i = 1; i <= n; i++)
    {
        if(i==1){
            phi_new[i] = 0.0;
        }
        else if( i == n){
            phi_new[i]= 1.0;
        }
        else{
            phi_new[i]=0.0;
        }       
             
    }
    

    FILE *f4;
    f4 = fopen("COUETTE_CN_error.txt","w");
    if(f4== NULL){
            printf("\n cannot open file\n");
            exit(1);
    }
    
    char name[50];

    do{
        if ((iteration+100)%100 == 0){
            sprintf(name, "velocity_CN_%.2f.dat",t);
                FILE *f2;
                f2 = fopen(name,"w");
                for(i=1;i<n;i++){
                    fprintf(f2,"%lf\t%lf\n", phi_new[i+1], i*dy);
                }fclose(f2);
        }
        

       
       
            error=0.0;
            d[1] = (((1-gamma)*phi_new[1])+((gamma/2.0)*phi_new[2]));
            p[1] = -b/a;
            q[1] = d[1]/a;
           
            for(int j=2; j <=n; j++){
                
                d[j] = (((1-gamma)*phi_new[j])+((gamma/2.0)*phi_new[j+1])+((gamma/2)*phi_new[j-1]));
                p[j] = ((-1.0*b)/(a + c*p[j-1]));
                q[j] = ((d[j] - c*q[j-1])/(a + c*p[j-1]));
            }

          
            

            for(i=n-1; i>1; i--){
                phi_old[i] = phi_new[i];
                phi_new[i] = p[i]*phi_new[i+1]+q[i];
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
    
    }while(error>1e-6);

    fclose(f1);
    fclose(f4);
    return 0;

}