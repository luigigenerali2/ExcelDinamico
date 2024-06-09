struct MatrizEsparsa{
	int linha;
	char coluna, valor[50];
	struct MatrizEsparsa *proxc;
	struct MatrizEsparsa *proxl;
}; typedef struct MatrizEsparsa MatEsp;

struct MatrizEsparsaColuna{
	char coluna;
	struct MatrizEsparsa *primC;
	struct MatrizEsparsaColuna *prox;
}; typedef struct MatrizEsparsaColuna MatEspC;

struct MatrizEsparsaLinha{
	int linha;
	struct MatrizEsparsa *primL;
	struct MatrizEsparsaLinha *prox;
}; typedef struct MatrizEsparsaLinha MatEspL;

struct MatrizDesc{
	struct MatrizEsparsaLinha *pLinha;
	struct MatrizEsparsaColuna *pColuna;
}; typedef struct MatrizDesc Desc;

struct Planilha{
	int linha;
	char coluna;
	char valor[50];
}; typedef struct Planilha Plan;

struct Lista {
    char info[50];
    struct Lista* prox;
}; typedef struct Lista Lista;

union valor{
	char operador;
	float valor;
};

struct ListaGeneralizada{
	char terminal;
	union valor no;
	struct ListaGeneralizada *cabeca;
	struct ListaGeneralizada *cauda;
}; 
typedef struct ListaGeneralizada ListaGen;

struct NoPilha{
	ListaGen *no;
	struct NoPilha *prox;
};
typedef struct NoPilha NoPilha;

struct Pilha{
	struct NoPilha *topo;
};
typedef struct Pilha Pilha;

struct NoPilhaValor{
	float valor;
	struct NoPilhaValor *prox;
};
typedef struct NoPilhaValor NoPilhaValor;

struct PilhaValor{
	struct NoPilhaValor *topo;	
};
typedef struct PilhaValor PilhaValor;

struct NoPilhaOperador{
	char operador;
	struct NoPilhaOperador *prox;
};
typedef struct NoPilhaOperador NoPilhaOperador;

struct PilhaOperador{
	struct NoPilhaOperador *topo;
};
typedef struct PilhaOperador PilhaOperador;

//--- conio 2 -------------------------------------------------------
void gotoxy(int x, int y)
{
  COORD c ;
  c.X = x - 1;
  c.Y = y - 1;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void textattr(int _attr)
{
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), _attr);
}

void textbackground(int _color)
{
  CONSOLE_SCREEN_BUFFER_INFO Info ;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
  textattr((Info.wAttributes & 0x0F) | (_color<<4));
}

void textcolor(int _color) {
  CONSOLE_SCREEN_BUFFER_INFO Info ;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
  textattr((Info.wAttributes & 0xF0) | _color);
}

int wherex()
{
  CONSOLE_SCREEN_BUFFER_INFO Info;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
  return Info.dwCursorPosition.X + 1;
}

int wherey()
{
  CONSOLE_SCREEN_BUFFER_INFO Info;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
  return Info.dwCursorPosition.Y + 1;
}

void clrscr(void)
{
  COORD coord = { 0, 0 };
  DWORD dwWritten, dwSize;
  HANDLE hScreen=GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO Info;

  if(GetConsoleScreenBufferInfo(hScreen, &Info))
  {
      dwSize = Info.dwSize.X * Info.dwSize.Y;
      FillConsoleOutputCharacter (hScreen, ' ', dwSize, coord, &dwWritten);
      FillConsoleOutputAttribute (hScreen, Info.wAttributes, dwSize, coord, &dwWritten);
      gotoxy (1, 1);
  }
}
//-------------------------------------------------------------------

void infoEsq(int n, int info, char s_info[])
{
    int i, tam;
    itoa(info,s_info,10);
    tam = strlen(s_info);
    for (i=0; i<n-tam; i++)
        strcat(s_info," ");
}

void infoCenter(int info, char s_info[])
{
    char s[9];
    strcpy(s,"    ");
    sprintf(s_info,"%c",info);
    strcat(s,s_info);
    strcat(s,"    ");
    strcpy(s_info,s);
}

void Init(Pilha **P){
	*P = (Pilha*)malloc(sizeof(Pilha));
	(*P) -> topo = NULL;
}

void initPOperador(PilhaOperador **P){
	(*P) = (PilhaOperador*)malloc(sizeof(PilhaOperador));
	(*P) -> topo = NULL;
}

void initPValor(PilhaValor **P){
	(*P) = (PilhaValor*)malloc(sizeof(PilhaValor));
	(*P) -> topo = NULL;
}

int IsEmpty(Pilha* P) {
    return P->topo == NULL;
}

char isEmptyPilhaOperador(PilhaOperador *P){
	return P -> topo == NULL;
}

char isEmptyPilhaValor(PilhaValor *P){
	return P -> topo == NULL;
}

void Push(Pilha ** P, ListaGen * noLista) {
    NoPilha *novoNo = (NoPilha *)malloc(sizeof(NoPilha));
    novoNo->no = noLista;
    novoNo->prox = (*P)->topo;
    (*P)->topo = novoNo;
}

void pushValor(PilhaValor ** P, float valor){
	NoPilhaValor *novoNo = (NoPilhaValor *)malloc(sizeof(NoPilhaValor));
	novoNo -> valor = valor;
	novoNo -> prox = (*P) -> topo;
	(*P) -> topo = novoNo; 
}

void pushOperador(PilhaOperador ** P, char operador){
	NoPilhaOperador *novoNo = (NoPilhaOperador *)malloc(sizeof(NoPilhaOperador));
	novoNo -> operador = operador;
	novoNo -> prox = (*P) -> topo;
	(*P) -> topo = novoNo;
}

void Pop(Pilha **P, ListaGen **noLista) {
    NoPilha *noRemovido = (*P)->topo;
    *noLista = noRemovido->no;
    (*P)->topo = noRemovido->prox;
    free(noRemovido);
}

void popValor(PilhaValor * * P, float * valor){
	*valor = (*P) -> topo -> valor;
	NoPilhaValor *noRemovido = (*P) -> topo;
	(*P) -> topo = (*P) -> topo -> prox;
	free(noRemovido);
}

void popOperador(PilhaOperador * * P, char * operador){
	*operador = (*P) -> topo -> operador;
	NoPilhaOperador *noRemovido = (*P) -> topo;
	(*P) -> topo = (*P) -> topo -> prox;
	free(noRemovido);
}

void Inicializar(Desc *desc){
	(*desc).pColuna=NULL;
	(*desc).pLinha=NULL;
}

MatEspC *NovaCaixaCol(char coluna)
{
	MatEspC *caixa=(MatEspC*)malloc(sizeof(MatEspC));
	caixa->coluna=coluna;
	caixa->primC=NULL;
	caixa->prox=NULL;
	return caixa;
}

MatEspL *NovaCaixaLin(int num)
{
	MatEspL *caixa=(MatEspL*)malloc(sizeof(MatEspL));
	caixa->linha=num;
	caixa->primL=NULL;
	caixa->prox=NULL;
	return caixa;
}

MatEsp *NovaCaixaMatEsp(char valor[],char coluna, int linha)
{
	MatEsp *caixa=(MatEsp*)malloc(sizeof(MatEsp));
	caixa->coluna=coluna;
	caixa->linha=linha;
	strcpy(caixa->valor,valor);
	caixa->proxc=NULL;
	caixa->proxl=NULL;	
	return caixa;
}

void CriaColuna(Desc *desc,char coluna){
	MatEspC *col,*aux,*ant;
	col=NovaCaixaCol(coluna);
	if((*desc).pColuna==NULL)
		(*desc).pColuna=col;
	else if(coluna<(*desc).pColuna->coluna)
	{
		col->prox=(*desc).pColuna;
		(*desc).pColuna=col;
	}
	else
	{
		aux=(*desc).pColuna;
		while(aux!=NULL && coluna>aux->coluna)
		{
			ant=aux;
			aux=aux->prox;	
		}
		ant->prox=col;
		col->prox=aux;
	}
}

void CriaLinha(Desc *desc,int linha){
	MatEspL *lin,*aux,*ant;
	lin=NovaCaixaLin(linha);
	if((*desc).pLinha==NULL)
		(*desc).pLinha=lin;
	else if(linha<(*desc).pLinha->linha)
	{
		lin->prox=(*desc).pLinha;
		(*desc).pLinha=lin;
	}
	else
	{
		aux=(*desc).pLinha;
		while(aux != NULL && linha > aux->linha)
		{
			ant=aux;
			aux=aux->prox;
		}
		ant->prox=lin;
		lin->prox=aux;
	}
}

ListaGen* ConsV(char *valor) {
    ListaGen *novo = (ListaGen*)malloc(sizeof(ListaGen));
    novo->terminal = 'V';
    novo->no.valor= atof(valor);
    novo->cabeca = NULL;
    novo->cauda = NULL;
    return novo;
}

ListaGen* ConsO(char operador) {
    ListaGen *novo = (ListaGen*)malloc(sizeof(ListaGen));
    novo->terminal = 'O'; 
    novo->no.operador = operador; 
    novo->cabeca = NULL;
    novo->cauda = NULL;
    return novo;
}

char verificaExisteLin(MatEspL *linhas, int lin, MatEspL *auxL)
{
    MatEspL *aux=linhas;
    while(aux != NULL && lin != aux->linha)
        aux=aux->prox;
    return aux !=NULL;
}

char verificaExisteCol(MatEspC *colunas,char col, MatEspC *auxC)
{
    MatEspC *aux=colunas;
    while(aux != NULL && col != aux->coluna)
        aux=aux->prox;
    return aux != NULL;
}

void selecionaLinha(MatEspL *linhas, int lin, MatEspL **auxL)
{
	MatEspL *aux=linhas;
    while(aux != NULL && lin != aux->linha)
        aux=aux->prox;
    *auxL=aux;
}
void selecionaColuna(MatEspC *colunas,char col, MatEspC **auxC)
{
	MatEspC *aux=colunas;
    while(aux != NULL && col != aux->coluna)
        aux=aux->prox;
    *auxC=aux;
}

void verificaOcupado(MatEspL *linhas, int lin, char col, MatEsp **aux)
{
    MatEspL *aux_lin = linhas;
    MatEsp *aux_col;
    while (aux_lin != NULL && aux_lin->linha != lin)
    {
        aux_lin = aux_lin->prox;
    }
    if (aux_lin == NULL)
    {
        *aux = NULL;
    }
    else{
	    aux_col = aux_lin->primL;
	    while (aux_col != NULL && aux_col->coluna != col)
	    {
	        aux_col = aux_col->proxl;
	    }
	    *aux = aux_col;
	}
}

void mostrarcelula(Desc desc, int linha, char coluna)
{
    MatEspL *linha_atual = desc.pLinha;
    MatEsp *celula_atual;
    while (linha_atual != NULL && linha_atual->linha != linha)
    {
        linha_atual = linha_atual->prox;
    }
    if (linha_atual != NULL)
    {
        celula_atual = linha_atual->primL;
        while (celula_atual != NULL && celula_atual->coluna != coluna)
        {
            celula_atual = celula_atual->proxl;
        }
        if (celula_atual != NULL)
        {
            printf("Valor da celula (%d, %c): %s", linha, coluna, celula_atual->valor);
        }
        else
        {
            printf("Celula (%d, %c) esta vazia.", linha, coluna);
        }
    }
    else
    {
        printf("A celula %d %c nao existe.", linha,coluna);
    }
}

Lista* novoElemento(char info[]) {
    Lista* elemento = (Lista*)malloc(sizeof(Lista));
    strcpy(elemento->info, info);
    elemento->prox = NULL;
    return elemento;
}

void adicionarElemento(Lista** lista, char info[]) {
    Lista* novo = novoElemento(info);
    Lista* atual;
    if (*lista == NULL) {
        novo->prox = *lista;
        *lista = novo;
    }
	else
	{
		atual = *lista;
	    while (atual->prox != NULL) {
	        atual = atual->prox;
	    }
	    novo->prox = atual->prox;
	    atual->prox = novo;
	}
}

float obterValor(MatEspL *matlinha, char info[]) {
    char coluna, numero[10], referencia[10];
    int linha, tam, i = 0,k=0; 
    MatEspL* linha_atual;
    MatEsp* celula_atual;
    Lista* lista;
    
    if (info[0] >= '0' && info[0] <= '9'){ 
        return atof(info);
    } else {
        coluna = info[0];
        tam = strlen(info);
        while (i < tam - 1) { 
            numero[i] = info[i + 1]; 
            i++;
        }
        numero[i] = '\0'; 
        linha = atoi(numero);
        linha_atual = matlinha;
        while (linha_atual != NULL && linha_atual->linha != linha) {
            linha_atual = linha_atual->prox;
        }
        if (linha_atual != NULL) {
            celula_atual = linha_atual->primL;
            
            while (celula_atual != NULL && celula_atual->coluna != coluna) {
                celula_atual = celula_atual->proxl;
            }
            if (celula_atual != NULL) {
                if (celula_atual->valor[0] == '=') {
                	if((toupper(celula_atual->valor[1]) >= 'A' && toupper(celula_atual->valor[1]) <= 'Z')){
	                	if(celula_atual->valor[2] >= '0' && celula_atual->valor[2] <= '9'){
						    referencia[0] = celula_atual->valor[1];
						    for(i=1; i<strlen(celula_atual->valor)-1;i++)
						    	referencia[i]=celula_atual->valor[i+1];
						    referencia[i]='\0';
		                    return obterValor(matlinha, referencia);
		                }
	            	}
				} else {
				    return atof(celula_atual->valor);
				}
			}
        }
    }
    return 0;
}


int teste(char string[], char substring[]) {
	int i = 0, y, j;
	char c, subaux[strlen(substring)],achou;
	while(string[i] != '\0') {
		for (y = 0, j = i; y < strlen(substring); y++, j++)
			subaux[y] = string[j];
		subaux[y] = '\0';
		if(strcmp(subaux, substring) == 0)
		{
			achou=1;
		}
		i++;
	}
	if(achou==1)
		return 1;
	return 0;
}

int ehOperador(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

float calcularMIN(MatEspL* linhapos, char expressao[]) {
    float minimo = 9999999999;
    char referenciaInicio[5];
    float valor;
    int linha;
    char coluna;
    char referenciaFim[5];
    char colInicial, colFinal;
    int linhaInicial, linhaFinal;
    sscanf(expressao, "MIN(%c%d:%c%d)", &colInicial, &linhaInicial, &colFinal, &linhaFinal);
    for (coluna = colInicial; coluna <= colFinal; coluna++) {
        for (linha = linhaInicial; linha <= linhaFinal; linha++) {
            sprintf(referenciaInicio, "%c%d", coluna, linha);
            valor = obterValor(linhapos, referenciaInicio);
            if (valor < minimo) {
                minimo = valor;
            }
        }
    }
    return minimo;
}

float calcularMAX(MatEspL* linhapos, char expressao[]) {
    float maximo = 0;
    float valor;
    int linha;
    char coluna;
    char referenciaInicio[5];
    char referenciaFim[5];
    char colInicial, colFinal;
    int linhaInicial, linhaFinal;
    sscanf(expressao, "MAX(%c%d:%c%d)", &colInicial, &linhaInicial, &colFinal, &linhaFinal);
    for (coluna = colInicial; coluna <= colFinal; coluna++) {
        for (linha = linhaInicial; linha <= linhaFinal; linha++) {
            sprintf(referenciaInicio, "%c%d", coluna, linha);
            valor = obterValor(linhapos, referenciaInicio);
            if (valor > maximo) {
                maximo = valor;
            }
        }
    }
    return maximo;
}

float calcularAVG(MatEspL* linhapos, char expressao[]) {
    float soma = 0;
    int contador = 0;
    float valor;
    int linha;
    char coluna;
    char referenciaInicio[5];
    char referenciaFim[5];
    char colInicial, colFinal;
    int linhaInicial, linhaFinal;
    sscanf(expressao, "AVG(%c%d:%c%d)", &colInicial, &linhaInicial, &colFinal, &linhaFinal);
    for (coluna = colInicial; coluna <= colFinal; coluna++) {
        for (linha = linhaInicial; linha <= linhaFinal; linha++) {
            sprintf(referenciaInicio, "%c%d", coluna, linha);
            valor = obterValor(linhapos, referenciaInicio);
            soma += valor;
            contador++;
        }
    }
    if (contador != 0) {
        return soma / contador;
    }
    printf("Erro: Nenhuma célula no intervalo especificado para função AVG\n");
    return 0;
}

float calcularSUM(MatEspL* linhapos, char expressao[]) {
    float soma = 0;
    char referenciaInicio[5];
    char referenciaFim[5];
    float valor;
    int linha;
    char coluna;
    char colInicial, colFinal;
    int linhaInicial, linhaFinal;
    sscanf(expressao, "SUM(%c%d:%c%d)", &colInicial, &linhaInicial, &colFinal, &linhaFinal);
    for (coluna = colInicial; coluna <= colFinal; coluna++) {
        for (linha = linhaInicial; linha <= linhaFinal; linha++) {
            sprintf(referenciaInicio, "%c%d", coluna, linha);
            valor = obterValor(linhapos, referenciaInicio);
            soma += valor; 
        }
    }
    return soma;
}

Lista* separaTermos(char str[], MatEspL *Lin){
	Lista *novaLista= NULL;
	float valor;
	char strAux[20], strLin[5], coluna;
	int i= 0, j, k;
	if(str[i] == '='){
		i++;
	}
	while(i < strlen(str)){
		if(str[i] != ' '){
			strAux[0]= '\0';
			j= 0;
			if(str[i] >= '0' && str[i] <= '9'){
				while((str[i] >= '0' && str[i] <= '9') || str[i] == '.'){
					strAux[j++]= str[i++];
				}
				strAux[j++]= '\0';
			}
			else if(str[i] == '('){
				strAux[0]= '(';
				strAux[1]= '\0';
				i++;
			}
			else if(str[i] == ')'){
				strAux[0]= ')';
				strAux[1]= '\0';
				i++;
			}
			else if(str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/'){
				strAux[0]= str[i++];
				strAux[1]= '\0';
			}
			else if((toupper(str[i]) >= 'A' && toupper(str[i]) <= 'Z')){
				//Celula ou funcao
				if(str[i+1] >= '0' && str[i+1] <= '9'){
					k=0; 
                    strLin[k] = toupper(str[i]); 
                    i++;
                    k++;
                    while(str[i] >= '0' && str[i] <= '9'){
                        strLin[k++] = str[i++];
                    }
                    strLin[k]= '\0';
                    valor = obterValor(Lin, strLin);
                    sprintf(strAux, "%.2f", valor);
				}
				else{
					while(str[i] != ')'){
						strAux[j++]= toupper(str[i++]);
					}
					strAux[j++]= str[i++];
					strAux[j++]= '\0';
					if (teste(strAux, "MAX") == 1) {
                        valor = calcularMAX(Lin, strAux); 
                        sprintf(strAux, "%.2f", valor);
                    } else if (teste(strAux, "MIN") == 1) {
                        valor = calcularMIN(Lin, strAux); 
                        sprintf(strAux, "%.2f", valor);
                    } else if (teste(strAux, "AVG") == 1) {
                        valor = calcularAVG(Lin, strAux);
                        sprintf(strAux, "%.2f", valor);
                    } else if (teste(strAux, "SUM") == 1) {
                        valor = calcularSUM(Lin, strAux); 
                        sprintf(strAux, "%.2f", valor);
                    }
				}
			}
			adicionarElemento(&novaLista, strAux);
		}
		else{
			i++;
		}
	}
	return novaLista;
}

int prioridade(char operador){
	switch(operador){
		case '+':
		case '-':
			return 1;
		
		case '*':
		case '/':
			return 2;
	}
}


float calculaEquacao(ListaGen *caixa) {
    PilhaOperador *POperador;
    PilhaValor *PValor;
    initPOperador(&POperador); 
    initPValor(&PValor);
    char op;
    float resultado, val1, val2;
    while(caixa!=NULL) {
        if(caixa->terminal == 'V') {
            pushValor(&PValor, caixa->no.valor);
        }
        if(caixa->terminal == 'O') {
            while(!isEmptyPilhaOperador(POperador) && prioridade(caixa->no.operador) <= prioridade(POperador->topo->operador)) {
                popOperador(&POperador, &op);
                popValor(&PValor, &val1);
                popValor(&PValor, &val2);
                switch(op) {
                    case '+':
                        pushValor(&PValor, val2 + val1);
                        break;
                        
                    case '-':
                        pushValor(&PValor, val2 - val1);
                        break;
                        
                    case '/':
                        pushValor(&PValor, val2 / val1);
                        break;
                        
                    case '*':
                        pushValor(&PValor, val2 * val1);
                        break;
                }
            }
            
            pushOperador(&POperador, caixa->no.operador);
        }
        caixa = caixa->cauda;
    }
    while(!isEmptyPilhaOperador(POperador)) {
        popOperador(&POperador, &op);
        popValor(&PValor, &val1);
        popValor(&PValor, &val2);
        switch(op) {
            case '+':
                pushValor(&PValor, val2 + val1);
                break;
                
            case '-':
                pushValor(&PValor, val2 - val1);
                break;
                
            case '/':
                pushValor(&PValor, val2 / val1);
                break;
                
            case '*':
                pushValor(&PValor, val2 * val1);
                break;
        }
    }
    popValor(&PValor, &resultado);
    return resultado;
}

float constroiResolveListaGen(char equacao[], ListaGen **L,Desc *desc){
	ListaGen *nova,*atual;
	Pilha *P1,*P2;
	char dir;
	float resultado;
	Lista *lista = separaTermos(equacao,(*desc).pLinha);
	Lista *aux;
	Init(&P1);
	Init(&P2);
	while(lista!=NULL)
	{
		if(lista->info[0]!='(' &&  lista->info[0]!=')') // numero,operador,celula
		{
			if(lista->info[0]>='0' &&  lista->info[0]<='9')
				nova=ConsV(lista->info);
			else if(lista->info[0]=='+' ||  lista->info[0]=='-' ||  lista->info[0]=='*' ||  lista->info[0]=='/')
				nova=ConsO(lista->info[0]);
			if(*L==NULL){
				*L=atual=nova;
				Push(&P2,atual);
			}
			else
			{
				if(dir=='H'){
					atual->cauda=nova;
					atual=atual->cauda;
				}
				else{
					atual->cabeca=nova;
					atual=atual->cabeca;
				}
			}
			dir='H';
		}
		else
			if(lista->info[0]=='(')
			{
				nova=ConsV("0");
				if(*L==NULL){
					*L=atual=nova;
				}
				else{
					if(dir=='H'){
						atual->cauda=nova;
						atual=atual->cauda;
					}
					else{
						atual->cabeca=nova;
						atual=atual->cabeca;
					}
					Push(&P1,atual);
				}
				Push(&P2,atual);
				dir='V';
			}
			else{ 
				Pop(&P1,&atual);
				dir='H';
			}
		aux=lista;
		lista=lista->prox;
		free(aux);
	}	
	while(!IsEmpty(P2))
	{
		Pop(&P2,&atual);
		if(atual!=*L)
			atual->no.valor=calculaEquacao(atual->cabeca);
		else
			resultado = calculaEquacao(atual);
	}
	*L=NULL;
	return resultado;
}

void desenhaTela(int lin, char col, Desc desc)
{
    int i, j;
    ListaGen *L=NULL;
    float resultado;
    char slin[4], scol[9], str_resultado[50];
    MatEspL *linha_atual;
    MatEsp *celula_atual;
    int x, y;
    char col_final = col + 7;
    char lin_final = lin + 19;
    
    // Verifica se a última linha exibida ultrapassa 100
    if (lin_final > 100) {
        lin_final = 100;
    }
    
    // Verifica se a última coluna exibida ultrapassa Z
    if (col_final > 'Z') {
        col_final = 'Z';
    }
    
    textbackground(0);
    clrscr();
    textbackground(7);
	textcolor(0);
    
    // Desenha as linhas esq 1..20
    for (i = lin; i <= lin_final; i++)
    {
        gotoxy(1, i - lin + 4);
        infoEsq(3, i, slin);
        printf("%s", slin);
    }
    
    // Desenha as colunas sup A..H
    j = 4;
    for (i = col; i <= col_final; i++)
    {
        gotoxy(j, 3);
        infoCenter(i, scol);
        printf("%s", scol);
        j = j + 9;
    }
    linha_atual = desc.pLinha;
    while (linha_atual != NULL)
    {
        if (linha_atual->linha >= lin && linha_atual->linha <= lin_final)
        {
            celula_atual = linha_atual->primL;
            while (celula_atual != NULL)
            {
                if (celula_atual->coluna >= col && celula_atual->coluna <= col_final)
                {
                    x = (celula_atual->coluna - col) * 9 + 4;
                    y = celula_atual->linha - lin + 4;
                    gotoxy(x, y);
                    if(celula_atual->valor[0]!='=')
                    	printf("%s", celula_atual->valor);
                    else
                    {
                    	resultado = constroiResolveListaGen(celula_atual->valor, &L, &desc); 
                    	L=NULL;
		                sprintf(str_resultado, "%.2f", resultado); 
		                textbackground(0);
		                for (i = 0; i < 8; i++) {
		                    gotoxy(x + i, y);
		                    printf(" ");
		                }
		                textbackground(0);
		                textcolor(7);
		                gotoxy(x,y);
		                printf("%s", str_resultado);
                    }
                    	
                }
                celula_atual = celula_atual->proxl;
            }
        }
        linha_atual = linha_atual->prox;
    }
}

void removerCelula(Desc *desc, int linha, char coluna)
{
    MatEspL *linhaAtual = (*desc).pLinha;
    MatEspL *antLinha = NULL;
    MatEsp *celulaAtualC = NULL, *celulaAtualL = NULL;
    MatEsp *celulaAnteriorL = NULL,*celulaAnteriorC = NULL;
    MatEspC *colunaAtual = (*desc).pColuna;
    MatEspC *antColunaAtual = NULL;
    while (linhaAtual != NULL && linhaAtual->linha != linha)
    {
        antLinha = linhaAtual;
        linhaAtual = linhaAtual->prox;
    }
    while (colunaAtual != NULL && colunaAtual->coluna != coluna)
    {
        antColunaAtual = colunaAtual;
        colunaAtual = colunaAtual->prox;
    }
    if (linhaAtual != NULL && colunaAtual != NULL)
    {
        celulaAtualL = linhaAtual->primL;
        celulaAtualC = colunaAtual->primC;
        while (celulaAtualL != NULL && celulaAtualL->coluna != coluna)
        {
            celulaAnteriorL = celulaAtualL;
            celulaAtualL = celulaAtualL->proxl;
        }
        while (celulaAtualC != NULL && celulaAtualC->coluna != coluna)
        {
            celulaAnteriorC = celulaAtualC;
            celulaAtualC = celulaAtualC->proxl;
        }
        
        
        if (celulaAtualL != NULL)
        {
            if (celulaAnteriorL != NULL)
            {
                celulaAnteriorL->proxl = celulaAtualL->proxl;
            }
            else
            {
                linhaAtual->primL = celulaAtualL->proxl;
            }
        }
        if(celulaAtualC != NULL)
        {
        	if(celulaAnteriorC != NULL)
        	{
        		celulaAnteriorC->proxc = celulaAtualC->proxc;
        	}
        	else
        	{
        		colunaAtual->primC = celulaAtualC->proxc;
        	}
        }
        free(celulaAtualL);
        if (linhaAtual->primL == NULL)
        {
            if (antLinha != NULL)
            {
                antLinha->prox = linhaAtual->prox;
            }
            else
            {
                (*desc).pLinha = linhaAtual->prox;
            }
            free(linhaAtual);
        }
        if(colunaAtual->primC == NULL)
        {
        	if(antColunaAtual != NULL)
        	{
        		antColunaAtual->prox = colunaAtual->prox;
        	}
        	else
        	{
        		(*desc).pColuna = colunaAtual->prox;
        	}
        	free(colunaAtual);
        }
    }
}

void InserirCelula(Desc *desc, int linha, char coluna, char valor[])
{
	char str_resultado[50];
	ListaGen *L=NULL;
	MatEspL *linhaAtual = (*desc).pLinha;
    MatEspL *auxL;
    MatEsp *celulaAtual;
    float resultado;
    MatEspC *auxC;
    MatEsp *ant,*atual,*aux, *nova;
    char existeLin = verificaExisteLin((*desc).pLinha, linha, auxL);
    char existeCol = verificaExisteCol((*desc).pColuna, coluna, auxC);
    int x,y,i;
    if (!existeLin)
    {
        CriaLinha(&(*desc), linha);
        selecionaLinha((*desc).pLinha, linha, &auxL);
    }
    else
    {
        selecionaLinha((*desc).pLinha, linha, &auxL);
    }
    if (!existeCol)
    {
        CriaColuna(&(*desc), coluna);
        selecionaColuna((*desc).pColuna, coluna, &auxC);
    }
    else
    {
        selecionaColuna((*desc).pColuna, coluna, &auxC);
    }
    verificaOcupado(auxL, linha, coluna, &aux);
    if (aux != NULL)
    {
    	if (strcmp(valor, "") == 0)
	    {
	        removerCelula(&(*desc), linha, coluna);
	    }
	    else
        	strcpy(aux->valor, valor);
    }
    else
    {
        nova = NovaCaixaMatEsp(valor, coluna, linha);
        if (auxL->primL == NULL)
        {
            auxL->primL = nova;
            nova->proxl = NULL;
        }
        else if (coluna < auxL->primL->coluna)
        {
            nova->proxl = auxL->primL;
            auxL->primL = nova;
        }
        else
        {
            ant = NULL;
            atual = auxL->primL;
            while (atual != NULL && coluna > atual->coluna)
            {
                ant = atual;
                atual = atual->proxl;
            }
            ant->proxl = nova;
            nova->proxl = atual;
        }
        if (auxC->primC == NULL)
        {
            auxC->primC = nova;
            nova->proxc = NULL;
        }
        else if (linha < auxC->primC->linha)
        {
            nova->proxc = auxC->primC;
            auxC->primC = nova;
        }
        else
        {
            atual = auxC->primC;
            while (atual != NULL && linha > atual->linha)
            {
                ant = atual;
                atual = atual->proxc;
            }
            ant->proxc = nova;
            nova->proxc = atual;
        }
    }
    while (linhaAtual != NULL) {
        celulaAtual = linhaAtual->primL;
        while (celulaAtual != NULL) {
            if (celulaAtual->valor[0] == '=') {
                resultado = constroiResolveListaGen(celulaAtual->valor, &L, &(*desc));
                sprintf(str_resultado, "%.2f", resultado);
                x = (celulaAtual->coluna - 'A') * 9 + 4;
                y = celulaAtual->linha - linha + 4;
                for (i = 0; i < 8; i++) {
                    gotoxy(x + i, y);
                    printf(" ");
                }
                textbackground(0);
                textcolor(7);
                printf("%s", str_resultado);
            }
            celulaAtual = celulaAtual->proxl;
        }
        linhaAtual = linhaAtual->prox;
    }
	desenhaTela(linha, coluna,*desc);
}

void limparMatrizEsparsa(Desc *desc) {
    MatEspL *linha_atual = (*desc).pLinha;
    MatEspC *coluna_atual = (*desc).pColuna,*coluna_temp;
    MatEspL *linha_temp;
    MatEsp *celula_atual;
    MatEsp *celula_temp;
    while (linha_atual != NULL) {
        linha_temp = linha_atual;
        coluna_temp = coluna_atual;
        coluna_atual=coluna_atual->prox;
        linha_atual = linha_atual->prox;
        celula_atual = linha_temp->primL;
        while (celula_atual != NULL) {
            celula_temp = celula_atual;
            celula_atual = celula_atual->proxl;
            free(celula_temp);
        }
        free(linha_temp);
        free(coluna_temp);
    }
    (*desc).pLinha = NULL;
    (*desc).pColuna=NULL;
}

void salvarPlanilha(Desc desc, char *nomeArquivo) {
	Plan planilha;
	MatEsp *celula_atual;
	MatEspL *linha_atual = desc.pLinha;
    FILE *arquivo = fopen(nomeArquivo, "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
    }
    else
	{
		while (linha_atual != NULL) {
        	celula_atual = linha_atual->primL;
	        while (celula_atual != NULL) {
	            Plan planilha;
	            planilha.linha = celula_atual->linha;
	            planilha.coluna = celula_atual->coluna;
	            strcpy(planilha.valor, celula_atual->valor);
	            fwrite(&planilha, sizeof(Plan), 1, arquivo);
	            celula_atual = celula_atual->proxl;
	        }
	        linha_atual = linha_atual->prox;
    	}
    }
    fclose(arquivo);
}

void abrirPlanilha(Desc *desc, char *nomeArquivo) {
	Plan planilha;
    FILE *arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
    }
    else
	{
		limparMatrizEsparsa(&(*desc));
		fread(&planilha, sizeof(Plan), 1, arquivo);
    	while (!feof(arquivo)) {
		    InserirCelula(&(*desc), planilha.linha, planilha.coluna, planilha.valor);
		    fread(&planilha, sizeof(Plan), 1, arquivo);
		}	
    }
    fclose(arquivo);
}

void gerarGrafico(char regiao[], Desc desc) {
    char colInicial, colFinal;
    int linhaInicial, linhaFinal;
    int i, j, k;
    char auxfunc[50];
    ListaGen *L=NULL;
    float n, maior = -9999.99, menor = 9999.99, qtdValores = (colFinal - colInicial + 1) * 1.00, valor;
    MatEsp *aux;
    sscanf(regiao, "%c%d:%c%d", &colInicial, &linhaInicial, &colFinal, &linhaFinal);
	clrscr();
    for(i = linhaFinal; i >= linhaInicial+1; i--){
        for(j = colInicial; j <= colFinal; j++){
            verificaOcupado(desc.pLinha, i, j, &aux);
            if(aux != NULL){
                if(aux->valor[0] == '='){
                	for(k=0;k<strlen(aux->valor);k++)
                	{
                		auxfunc[k]=aux->valor[k+1];
                	}
                	auxfunc[k]='\0';
                    n = constroiResolveListaGen(aux->valor, &L, &desc);
                    L=NULL;
                }
                else if(aux->valor[0]>='0' && aux->valor[0]<='9'){
                    n = atof(aux->valor);
                }
                if(n > maior){
                    maior = n;
                }
                if(n < menor){
                    menor = n;
                }
            }
        }
    }
    for(i = linhaFinal; i >= linhaInicial; i--){
        for(j = colInicial; j <= colFinal; j++){
            verificaOcupado(desc.pLinha, i, j, &aux);
            if(aux != NULL){
                if(aux->valor[0] == '='){
                	for(k=0;k<strlen(aux->valor);k++)
                	{
                		auxfunc[k]=aux->valor[k+1];
                	}
                	auxfunc[k]='\0';
                    n = constroiResolveListaGen(aux->valor, &L, &desc);
                    L=NULL;
                }
                else if(aux->valor[0]>='0' && aux->valor[0]<='9'){
                    n = atof(aux->valor);
                }
                if(j==colInicial)
                	printf("%s\n",aux->valor);
                else{
	                valor = round((0.5 * qtdValores * n) / maior);
	                for(k = 0; k < valor; k++){
	                    printf("%c",219);
	                }
	                printf("%.2f",n);
	            }
                printf("\n");
            }
        }
    }
    getch();
}

void iniciaExcel(Desc *desc)
{
    char key;
    int c, l, col, lin;
    int modo_edicao = 0; // 0: modo de seleção, 1: modo de edição
    char valor_editado[50] = "",nome[50],regiao[5],auxnome[50];
	Lista* lista = NULL;
    textbackground(3);
    clrscr();
    desenhaTela(1, 65, *desc);
    //coordenadas de t(*ela )
    c = l = 1;
    //coordenadas da matriz
    col = 65; 
    lin = 1;
    gotoxy(c * 9 - 9 + 4, l + 3);
    printf("         ");
    do
    {
    	gotoxy(1, 24);
        printf("F2 - Editar celula | F3 - Salvar Planilha | F4 - Abrir Planilha | F5 - Gerar Grafico | Esc - Encerrar");
        key = getch();
	    if (key == -32)
	    {
	        key = getch();
	        switch (key)
	        { //linhas   linhas-1
	        case 80:
	            if (l == 20 && lin < 100 - 19) //seta p/ baixo
	                lin++;
	            if (l < 20)
	                l++;
	            break;
	        case 72:
	            if (l == 1 && lin > 1) //seta p/ cima
	                lin--;
	            if (l > 1)
	                l--;
	            break;
	            //'A' alfabeto  colunas-1
	        case 77:
	            if (c == 8 && col < 65 + 26 - 8) //seta p/ direita
	                col++;
	            if (c < 8)
	                c++;
	            break;
	        case 75:
	            if (c == 1 && col > 65) //seta p/ esquerda
	                col--;
	            if (c > 1)
	                c--;
	            break;
	        }
	        desenhaTela(lin, col, *desc);
	        // Atualiza as coordenadas da célula selecionada
	        gotoxy(c * 9 - 9 + 4, l + 3);
	    }
	    else 
		if (key == 0)
	    {
	        key = getch();
	        switch(key)
	        {
	        	case 60: // F2 - entra no modo de edição
		            if (!modo_edicao) { 
	                    modo_edicao = 1;
	                    gotoxy(1,1);
	                    mostrarcelula(*desc, lin+l-1,col+c-1);
	                    gotoxy(1, 2);
	                    printf("Digite o valor da celula (Enter para confirmar) %d%c: ",lin+l-1,col+c-1);
	                    fflush(stdin);
	                    gets(valor_editado); 
	                    InserirCelula(&(*desc), lin+l-1,col+c-1, valor_editado); 
	                    modo_edicao = 0; 
	                    gotoxy(c * 9 - 9 + 4, l + 3);
	                }
		            break;
		        case 61: // F3 - salvar planilha
		        	gotoxy(1,1);
		        	printf("Salvar Planilha - Escreva o nome da Plailha:");
		        	fflush(stdin); 
	                gets(nome);
	                strcpy(auxnome,nome);
	                strcat(nome, ".dat");
	                if(strcmp(auxnome,"")!=0)
                    	salvarPlanilha(*desc, nome);
                    break;
                case 62: // F4 - abrir planilha
                	gotoxy(1,1);
                	printf("Abrir Planilha - Escreva o nome da Plailha:");
                	fflush(stdin); 
                	gets(nome);
	                strcpy(auxnome,nome);
	                strcat(nome, ".dat");
	                if(strcmp(auxnome,"")!=0)
                    	abrirPlanilha(desc, nome);
                    break;
                case 63: // F5 - gerar gráfico
                	gotoxy(1,1);
                	printf("Gerar Gráfico - Escreva a região da Planilha(Ex:B4:C10):");
                	fflush(stdin);
                	gets(regiao);
                	if(strcmp(regiao,"")!=0)
                	{
                		gerarGrafico(regiao,*desc);
                	}
            }
	        desenhaTela(lin, col, *desc);
	        gotoxy(c * 9 - 9 + 4, l + 3);
        }
	    	textcolor(0);
	        textbackground(7); 
	        gotoxy(c * 9 - 9 + 4, l + 3); 
	        printf("         "); 
	        textbackground(7); 
    } while (key != 27);
}
						
