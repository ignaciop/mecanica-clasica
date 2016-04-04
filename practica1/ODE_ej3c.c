#include <stdio.h> 
#include <math.h>

#define a -1

// Define parametros para usar en el sistema en todo el codigo
struct Par{
    double  mu;
} aa;


// Ecuaciones del sistema
void ecuaciones(int n, double v[], double dv[], double t){
    double x,y;
    x=v[0];
    y=v[1];

    // En este caso son 2 ecuaciones acopladas
    dv[0]= y;
    dv[1]= -aa.mu*(x*x-1)*y-x;
  
  return;
}


// Programa principal
int main(){

    int i,j;
    FILE *ptr;
    double v[2],t,dt,t_pre,t_max;

    // Archivo de salida
    ptr=fopen("ej3c.dat","w");

    dt=0.01;
    t_max=20;

    // Condiciones iniciales fijas
    v[0] = -0.01;
    v[1] = 0.05;

    for (j=1;j<=10;j=j+4) {
        aa.mu= j;
 
        t=0.;
					
        while(t<t_max) {
            // Integra las ecuaciones utilizando el metodo de Runge Kutta
            rk4(ecuaciones,v,2,t,dt);
    
            // Imprime la integracion
            fprintf(ptr,"%lg\t%lg\t%lg\n",t,v[0],v[1]);

            t+=dt;
        }

        fprintf(ptr,"\n");
    }

    fclose(ptr);
    return(0);
}

