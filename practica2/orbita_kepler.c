 
#include <stdio.h> 
#include <math.h>



//define una estructura de parametros para usar durante todo el programa
struct Par{
  double gamma, mu,l;
} aa;


// Ecuaciones del sistema a resolver
void ecuaciones(int n, double v[], double dv[], double t){
  double r,sigma,tita;
  r=v[0];sigma=v[1], tita = v[2];

  dv[0]= sigma; //de la parte radial
  dv[1]= -aa.gamma/(aa.mu*r*r)+aa.l*aa.l/(aa.mu*aa.mu*r*r*r); //de la parte radial
  dv[2] = aa.l/(aa.mu*r*r); //de la parte angular

  return;
}


//Programa principal
int main(){

  int i,j;
  FILE *ptr;
  double v[4],t,dt,t_pre,t_max,x,y;

  //Archivo de salida
  ptr=fopen("orb_k.dat","w");

//tiempo de integración y paso de integración
  dt=0.01;
  t_max=1000;

  //Condiciones Iniciales
  v[0]=100.;
  v[1]=1.;


//valor de los parámetros - usando Mt= 5.97x1024kg; Ml = 1/18*Mt y G=6.6738x10-11 Nm^2/kg^2
 /*aa.mu = (5.97e+24)*(5.97e+24)/18./(5.97e+24+5.97e+24/18.);
  aa.l = 7.20005e+34;
  aa.gamma= ((5.97e+24)*(5.97e+24)/18.)*6.67e-11;	  //100000			
*/

//valores de los parámetros

  aa.mu = 0.8;
  aa.l = 1600;   //variar de 500 a 3000 para ver (en 500 se escapa, por 1500 elipse, ya por 3800 parabola)
  aa.gamma= 100000;

//empieza a integrar
  t=0.;
  while(t<t_max){
    //Integra las ecuaciones utilizando el metodo de Runge Kutta
    rk4(ecuaciones,v,4,t,dt);

  //define las variables en cartesianas
  x = v[0]*cos(v[2]); 
  y = v[0]*sin(v[2]); 

   //Imprime la integracion en un vector

   fprintf(ptr,"%lg\t%lg\t%lg\t%lg\n",t,x,y,v[0]);

    t+=dt;
  }
  fclose(ptr);
  return(0);
}

