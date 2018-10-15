#include <stdio.h>
#include <math.h>
int FileOpen ()
{
  int q=0;
  FILE*f1=fopen("lab.txt","r");
  if (!f1) q=1;
  return q;
}
  int Numbers()                                                                                                       //Подсчет строк (вычисление колличества данных)
{
  FILE*f1=fopen("lab.txt","r");
  char symbol=' ';
  int N1=0;
  while ((fscanf(f1,"%c", &symbol))!=EOF)
  {
    if (symbol=='\n') {(N1)++;}
  }
  fclose(f1);
  return N1;
}
void Array (int *N,float V1[],float A1[], float L1[],float D1[])                                                     //Зададь массив
{
	FILE*f1=fopen("lab.txt","r");
	for (int i=0;i<=(*N-1);i++)
	{
		fscanf(f1,"%f %f %f %f",&V1[i],&A1[i],&L1[i],&D1[i]);
	}
	fclose(f1);
}
void Calculation (int *N,float V1[],float A1[], float L1[],float D1[], float p1[])                                    //Вычисление массива удельного сопротивления
{
	FILE*f2=fopen("labrez.txt","w");
    fprintf(f2,"                   V       A     L    D          p\n");
	for (int i=0;i<=((*N)-1);i++)
	{
		p1[i]=(V1[i])/(A1[i])/(L1[i])*((3.14)/4)*(D1[i])*(D1[i])*1000000;
		fprintf(f2,"Эксперимент №%2i | %5.4f  %3.2f  %2.1f  %6.5f | %f\n",i+1,V1[i],A1[i],L1[i],D1[i],p1[i]);
	}
	fclose(f2);
}
int Verification (int *N,float p1[],float *av1)                                                                       // Проверка на адекватность данных
{
  int q=0;
  for (int i=0;i<=((*N)-1);i++)
  {
    if ((p1[i]/(*av1))>=1.25) q=1;
  }
  return q;
}
void Middle(int *N,float p[],float * average1)                                                                        //Вычисление среднего значения в массиве
{
	float summ=0;
	for (int i=0;i<=((*N)-1);i++)
	{
		summ=summ+p[i];
	}
	*average1=summ/(*N);
}
void Write_down_f2 (float*average1,float Sigma_final)                                                                  //Вывод результатов
{
  FILE*f2=fopen("labrez.txt","a");
  fprintf(f2,"\nРезультат р=%f±%f",*average1,Sigma_final);
  fclose(f2);
}
void Quadratic_mean (int *N1,float a[],float * Sigma1)                                                                //Средняя квадратичная погрешность для конкретного массива
{
  *Sigma1=0;
  float average2=0;
  Middle (&(*N1),a,&average2);
  for (int i=0;i<=((*N1)-1);i++)
  {
    *Sigma1=*Sigma1+(a[i]-average2)*(a[i]-average2);
  }
  *Sigma1=sqrt(*Sigma1/(*N1)/((*N1)-1));
}
float Sigma_error(float avV,float avA,float avL,float avD,float sigV,float sigA,float sigL,float sigD)                //Вычисление погрешности для сложной функции
{
	return sqrt((sigV/avV)*(sigV/avV)+(sigA/avA)*(sigA/avA)+(sigL/avL)*(sigL/avL)+4*(sigD/avD)*(sigD/avD));
}
int main()
{
  if (FileOpen()==1)
  {
    printf("Файл lab.txt не найден!\n");
    return 1;
  }
  int N=0;
  N=Numbers();
  float V[N],A[N],L[N],D[N],p[N];
	float average,average_V,average_A,average_L,average_D,Sigma_V,Sigma_A,Sigma_L,Sigma_D,Sigma_p;
  Array(&N,V,A,L,D);
  Calculation(&N,V,A,L,D,p);
	Middle (&N,p,&average);
  if (Verification (&N,p,&average)==1)
  {
    printf("Проверьте значения данных!\n");
    return 2;
  }
  Middle (&N,V,&average_V);
	Middle (&N,A,&average_A);
	Middle (&N,L,&average_L);
	Middle (&N,D,&average_D);
	Quadratic_mean(&N,V,&Sigma_V);
	Quadratic_mean(&N,A,&Sigma_A);
	Quadratic_mean(&N,L,&Sigma_L);
	Quadratic_mean(&N,D,&Sigma_D);
	Sigma_p=Sigma_error(average_V,average_A,average_L,average_D,Sigma_V,Sigma_A,Sigma_L,Sigma_D);
  Write_down_f2 (&average,Sigma_p);
}
