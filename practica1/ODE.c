#include <stdio.h> 
#include <math.h>

#define a -1

// define parametros para usar en el sistem en todo el codigo
struct Par{
  double  mu, omega;
} aa;


// Ecuaciones del sistema
void ecuaciones(int n, double v[], double dv[], double t){
  double x,y;
  x=v[0];/*y=v[1];*/

  dv[0]= x+10/(1+(x-1)*(x-1))-0.1*exp(x);
/*  dv[1]= x + a*y*(x*x + y*y);*/
  
  return;
}


//Programa principal
int main(){

  int i,j;
  FILE *ptr;
  double v[2],t,dt,t_pre,t_max;

  //Archivo de salida
  ptr=fopen("ej1.dat","w");

  dt=0.01;
  t_max=2;

  //Condiciones Iniciales
  
  v[0]=i;
  /*v[1]=0;*/
				
  t=0.;
					
  while(t<t_max){
    //Integra las ecuaciones utilizando el metodo de Runge Kutta
    rk4(ecuaciones,v,1,t,dt);
    
    //Imprime la integracion
    fprintf(ptr,"%lg\t%lg\n",t,v[0]);

    t+=dt;
  }
        fprintf(ptr,"\n");
  
  fclose(ptr);
  return(0);
}
