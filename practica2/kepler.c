 
#include <stdio.h> 
#include <math.h>



//define una estructura de parametros para usar durante todo el programa
struct Par{
  double gamma, mu, l, m1, m2;
} aa;


// Ecuaciones del sistema a resolver
void ecuaciones(int n, double v[], double dv[], double t){
  double r,u,phi;
  r=v[0];
  u=v[1];
  phi = v[2];

  dv[0]= u; //de la parte radial
  dv[1]= -aa.gamma/(r*r)+aa.l*aa.l/(aa.mu*aa.mu*r*r*r); //de la parte radial
  dv[2] = aa.l/(aa.mu*r*r); //de la parte angular

  return;
}


//Programa principal
int main(){

  int i,j;
  FILE *ptr;
  double v[4],t,dt,t_pre,t_max,x,y;

  //Archivo de salida
  ptr=fopen("kepler.dat","w");

//tiempo de integración y paso de integración
  dt=0.01;
  t_max=1000;

  //Condiciones Iniciales
  v[0]=100.; //r
  v[1]=1.;  //u
  //v[2]=60; //phi


//valor de los parámetros - usando Mt= 5.97x1024kg; Ml = 1/18*Mt y G=6.6738x10-11 Nm^2/kg^2
 /*aa.mu = (5.97e+24)*(5.97e+24)/18./(5.97e+24+5.97e+24/18.);
  aa.l = 7.20005e+34;
  aa.gamma= ((5.97e+24)*(5.97e+24)/18.)*6.67e-11;	  //100000			
*/

//valores de los parámetros
    aa.m1 = 5970000;
    aa.m2 = 5970000./18;

    aa.mu = (aa.m1*aa.m2)/(aa.m1+aa.m2);
    aa.gamma= aa.m1*aa.m2*0.000000000066742; 

 //VER QUE l depende las CI!!!
    aa.l = 1500;   //variar de 500 a 3000 para ver (en 500 se escapa, por 1500 elipse, ya por 3800 parabola)
    

//empieza a integrar
  t=0.;
  while(t<t_max){
    //Integra las ecuaciones utilizando el metodo de Runge Kutta
    rk4(ecuaciones,v,4,t,dt);

  //define las variables en cartesianas
  x = v[0]*cos(v[2]); 
  y = v[0]*sin(v[2]);

    //definir r1 y r2 
    double r1x = x*(aa.m2/(aa.m1+aa.m2));
    double r1y = y*(aa.m2/(aa.m1+aa.m2));
    double r2x = x*(-aa.m1/(aa.m1+aa.m2));
    double r2y = y*(-aa.m1/(aa.m1+aa.m2)); 

   //Imprime la integracion en un vector

   fprintf(ptr,"%lg\t%lg\t%lg\t%lg\t%lg\t%lg\t%lg\t%lg\n",t,x,y,v[0],r1x,r1y,r2x,r2y);

    t+=dt;
  }

  fclose(ptr);
  return(0);
}

