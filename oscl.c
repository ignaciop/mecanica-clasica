 
#include <stdio.h> 
#include <math.h>



//define una estructura de parametros para usar durante todo el programa
struct Par{
  double k,e;
} aa;


// Ecuaciones del sistema a resolver
void ecuaciones(int n, double v[], double dv[], double t){
  double x1,x2,v1,v2;
  x1=v[0];
  x2=v[1];
  v1=v[2];
  v2=v[3];
  
  dv[0]= v1;
  dv[1]= v2;
  dv[2]= -aa.k*x1 + aa.e*(x2-x1); 
  dv[3]= -aa.k*x2 + aa.e*(x1-x2);

  return;
}


//Programa principal
int main(){

  int i,j;
  FILE *ptr;
  double v[4],t,dt,t_pre,t_max,x,y;

  //Archivo de salida
  ptr=fopen("oscl.dat","w");

  //tiempo de integración y paso de integración
  dt=0.01;
  t_max=100;

  //Condiciones Iniciales
  v[0]=0;
  v[1]=1;
  v[2]=0.5;
  v[3]=-0.2;

  /*Condiciones Iniciales para modos normales con velocidades iniciales 0
  v[0]=1;
  v[1]=1;
  v[2]=0;
  v[3]=0;

  o bien...
  v[0]=1;
  v[1]=-1;
  v[2]=0;
  v[3]=0;
  */

  //valores de los parámetros
  aa.k = 0.005;

  aa.e = 0.5;


  //empieza a integrar
  t=0.;
  while(t<t_max){
    //Integra las ecuaciones utilizando el metodo de Runge Kutta
    rk4(ecuaciones,v,4,t,dt);

   //Imprime la integracion en un vector

   fprintf(ptr,"%lg\t%lg\t%lg\t%lg\t%lg\n",t,v[0],v[1],v[2],v[3]);

    t+=dt;
  }

    fprintf(ptr,"\n");

  fclose(ptr);
  return(0);
}

