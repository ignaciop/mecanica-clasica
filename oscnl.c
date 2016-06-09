 
#include <stdio.h> 
#include <math.h>

#define PI (3.141592653589793)



//define una estructura de parametros para usar durante todo el programa
struct Par{
  double mu1,mu2,e,omega1,omega2;
} aa;


// Ecuaciones del sistema a resolver
void ecuaciones(int n, double v[], double dv[], double t){
  double ro1,ro2,ji;
  ro1=v[0];
  ro2=v[1];
  ji=v[2];
  
  dv[0]= (aa.mu1-aa.e)*ro1-ro1*ro1*ro1+aa.e*ro2*cos(ji);
  dv[1]= (aa.mu2-aa.e)*ro2-ro2*ro2*ro2+aa.e*ro1*cos(ji);
  dv[2]= (aa.omega1 - aa.omega2) - ((ro1/ro2)+(ro2/ro1))*sin(ji);

  return;
}


//Programa principal
int main(){

  int i,j;
  FILE *ptr;
  double v[3],t,dt,t_pre,t_max,x,y;

  //Archivo de salida
  ptr=fopen("oscnl.dat","w");

  //tiempo de integración y paso de integración
  dt=0.01;
  t_max=100;

  //Condiciones Iniciales
  v[0]=1;
  v[1]=0.3;
  v[2]=PI/6;

  //valores de los parámetros
  aa.mu1 = 0.1;
  aa.mu2 = 0.1;
  aa.e = 0.5;
  aa.omega1 = 1;
  aa.omega2 = 1;



  //empieza a integrar
  t=0.;
  while(t<t_max){
    //Integra las ecuaciones utilizando el metodo de Runge Kutta
    rk4(ecuaciones,v,3,t,dt);

   //Imprime la integracion en un vector

   fprintf(ptr,"%lg\t%lg\t%lg\t%lg\n",t,v[0],v[1],v[2]);

    t+=dt;
  }

    fprintf(ptr,"\n");

  fclose(ptr);
  return(0);
}

