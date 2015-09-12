#include <stdint.h>
#include "alu.h"
#include <stdint.h>
#include <stdbool.h>
#include "flags.h"

void flag(uint32_t *Rd,uint32_t *Rm,uint32_t *Rn,bool *banderas) /* Define las direcciones de las variables que deteremina el valor de la banderas (C,Z y N) */
{
	if(*Rd>((1<<31)-1)) 
	{
		banderas[N]=1;
	}
	else
	{
		banderas[N]=0;
	}
	if(!*Rd)
	{
		banderas[Z]=1;
	}
	else
	{
		banderas[Z]=0;
	}
	if(((*Rm>=(1<<31)-1)^(*Rn<0))&&((*Rn>=(1<<31)-1)^(*Rm<0)))
	{
		banderas[C]=1;
	}
	else
	{
		banderas[C]=0;
	}
	if((((*Rm&(1<<31))==(1<<31)&&(*Rn&(1<<31))==(1<<31))&&((*Rd&(1<<31))==0))&&(((*Rm&(1<<31))==0&&(*Rn&(1<<31))==0&&((*Rd&(1<<31))==(1<<31)))))
	{
		banderas[V]=1;
	}
	else
	{
		banderas[V]=0;
	}
	printf("N:%d Z:%d C:%d V:%d\n",banderas[N],banderas[Z],banderas[C],banderas[V]); /* Imprime en pantalla los valores de las banderas */
}
