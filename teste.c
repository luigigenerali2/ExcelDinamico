#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdarg.h>
#include <windef.h>
#include <winbase.h>
#include <wincon.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "TadTrabalho.h"


void ExibirColuna(MatEspC *Coluna)
{
	MatEsp *celula;
    while (Coluna != NULL)
    {
        printf("%c\t", Coluna->coluna);
        celula = Coluna->primC;
        while (celula != NULL)
        {
            printf("%s\t", celula->valor);
            celula = celula->proxc;
        }
        printf("\n");
        Coluna = Coluna->prox;
    }
}

void ExibirLinha(MatEspL *Linha)
{
	MatEsp *celula;
    while (Linha != NULL)
    {
        printf("%d\t", Linha->linha);
        celula = Linha->primL;
        while (celula != NULL)
        {
            printf("%s\t", celula->valor);
            celula = celula->proxl;
        }
        printf("\n");
        Linha = Linha->prox;
    }
}


int main()
{
	Desc desc;
	Inicializar(&desc);
	iniciaExcel(&desc);
}
