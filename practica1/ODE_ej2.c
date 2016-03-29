#include <stdio.h> 
#include <math.h>

#define a -1

// Define parametros para usar en el sistema en todo el codigo
struct Par{
    double  gamma, omega;
} aa;


// Ecuaciones del sistema
void ecuaciones(int n, double v[], double dv[], double t){
    double x,y;
    x=v[0];
    y=v[1];

    // En este caso son 2 ecuaciones acopladas
    dv[0]= y;
    dv[1]= -2*aa.gamma*y-aa.omega*aa.omega*x;
  
  return;
}


// Programa principal
int main(){

    int i,j;
    FILE *ptr;
    double v[2],t,dt,t_pre,t_max;

    // Archivo de salida
    ptr=fopen("ej2.dat","w");

    dt=0.01;
    t_max=2;

    // Condiciones iniciales. Se analizaron 3 casos: sub, sobre y amortiguamiento critico variando gamma y omega con valores opuestos en el rango de 1 a 10, con pasos de 5  
    for (j=1;j<=10;j=j+4) {
        v[0] = 0.5*j;
        v[1] = 0.5*(10-j);
        aa.gamma=(10-j);
        aa.omega=j;
 
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

