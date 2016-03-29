#include <stdio.h> 
#include <math.h>

#define a -1

// define parametros para usar en el sistem en todo el codigo
struct Par{
  double  gamma, omega;
} aa;


// Ecuaciones del sistema
void ecuaciones(int n, double v[], double dv[], double t){
  double x,y;
  x=v[0];
  y=v[1];

  dv[0]= y;
  dv[1]= -2*aa.gamma*y-aa.omega*aa.omega*x;
  
  return;
}


//Programa principal
int main(){

  int i,j;
  FILE *ptr;
  double v[2],t,dt,t_pre,t_max;

  //Archivo de salida
  ptr=fopen("ej2d.dat","w");

  dt=0.01;
  t_max=5;

  //Condiciones Iniciales
  v[0] = 0.5;
  v[1] = 0.1;
  
  for (j=1;j<=5;j++) {
	  v[0] = 0.5*j;
	  aa.gamma=j;
	  aa.omega=j;
   for (i=1;j<=10;j++) {
	v[0] = 0.5*i;
 
    t=0.;
					
    while(t<t_max){
      //Integra las ecuaciones utilizando el metodo de Runge Kutta
      rk4(ecuaciones,v,2,t,dt);
    
      //Imprime la integracion
      fprintf(ptr,"%lg\t%lg\t%lg\n",t,v[0],v[1]);

      t+=dt;
    }
          fprintf(ptr,"\n");
  }
}
  
fclose(ptr);
  return(0);
}

