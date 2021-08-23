#include<stdio.h>
#include<stdlib.h>

typedef struct Dados{

    int num;

}dados;

typedef struct Bloco{

    dados A1;

    struct Bloco *Ligamento;

}bloco;

typedef bloco*caixa;

//Inicia as caixas como NULL
caixa incializa();

//Cria a Matriz de adjacência e Adciona os valores
dados **Matriz(int tam);

//Printa a Matriz de adjacência
int *PrintMatriz(dados**matriz,int tam);

//Libera a Matriz de adjacência
void LiberaMatriz(int**matriz,int tam);

//ADD o ligação do vértice
caixa ADD(caixa lista,caixa dado);

//faz as perguntas para ADD ligação do vértice
void Lista(caixa lista[],int tam);

//Coordena e deixa organizado os print
void CoordenaPrint(caixa lista[],int tam);

//Printa a lista de maneira correta
void PrintaLista(caixa lista);

//Faz a Busca por Largura
void Largura(caixa lista[],int tam,int inicio,int*visita);

//Inicializa o vetor da busca e puxa a busca por Profundidade
void CoordenaProfundidade(caixa lista[],int tam,int inicio,int*visita);

//Faz a Busca por Profundidade
void Profundidade(caixa lista[],int tam,int inicio,int*visita,int cont);

/*
Tamanho: 3
Test: 0 3 0 1 1 1 1 0 0 0 1 1 1 1
Tamanho: 5
Teste: 0 5 0 1 1 0 0 1 0 1 1 1 1 0 0 1 0 1 0 1 0 1 1 1 1 0 1 0 1 0 1 1 0 1 1 0
*/

int main(){
    
    int tam,op;
    dados**matriz;

    printf("Digite o tamanho da Matriz de adjacência\n");
    scanf("%d",&tam);
    
    matriz=Matriz(tam);
    PrintMatriz(matriz,tam);
    
    printf("Digite o tamanho da Lista de adjacência\n");
    scanf("%d",&tam);
    
    caixa*lista=(caixa*)malloc(tam*sizeof(caixa));
    for(int i=0;i<tam;i++)
        lista[i]=incializa();
    
    Lista(lista,tam);
        
    CoordenaPrint(lista,tam);
    
    do{
        
        printf("\n1)Algoritmo de busca em largura\n2)Algoritmode busca emprofundidade\n0)Para sair\n");
        scanf("%d",&op);
    
    }while(op!=1&&op!=2&&op!=0);
    
    int*visita=(int*)malloc(tam*sizeof(int));
    switch(op){
        
        case 1:
        printf("\nVisita por largura [");
        Largura(lista,tam,0,visita);
        break;
        
        case 2:
        printf("\nVisita por Profundidade [");
        CoordenaProfundidade(lista,tam,0,visita);
        break;
        
        default:
        break;
    }
    printf("]\n");
    return 0;
}
//Inicia as caixas como NULL
caixa incializa(){
    return NULL;
}

//Cria a Matriz de adjacência e Adciona os valores
dados **Matriz(int tam){
    int op;
    
    //criar a MATRIZ
    dados**matriz=(dados**)malloc(tam*sizeof(dados*));
    
    for(int i=0;i<tam;i++)
        matriz[i]=(dados*)malloc(tam*sizeof(dados));
    
    //Inicializar a MATRIZ
    for(int i=0;i<tam;i++)
        for(int j=0;j<tam;j++)
            matriz[i][j].num=0;
    
    //Colocar os valores na MATRIZ
    for(int i=0;i<tam;i++){
        for(int j=0; j<tam; j++){
            do{
                printf("O vértice [%d] possui ligaçãocom o vértice [%d]\n", i+1,j+1);
                printf("1)Sim\n0)Não\n");
                scanf("%d",&op);
            }while(op!=1&&op!=0);
            if(op==1)matriz[i][j].num=1;
        }
    }
    return matriz;
}

//Printa a Matriz de adjacência
int *PrintMatriz(dados**matriz,int tam){
    
    //pritar os numeros das coluna
    for(int i=0; i<tam;i++)
        printf("\t%d",i+1);
    
    printf("\n");
    
    for(int i=0;i<tam;i++){
        //printar os numeros das linhas
        printf("\n%d",i+1);
        
        for(int j=0;j<tam;j++){
            printf("\t%d",matriz[i][j].num);
        }

        printf("\n");
    }
    return 0;
}

//Libera a Matriz de adjacência
void LiberaMatriz(int**matriz,int tam){
    
    for(int i=0; i<tam;i++)
        free(matriz[i]);
    
    free(matriz);
}

//ADD o ligação do vértice
caixa ADD(caixa lista,caixa dado){
    
    //usa recurção para ADD na lista
    if(lista==NULL)
        return dado;
    
    lista->Ligamento=ADD(lista->Ligamento,dado);
    return lista;
}

//faz as perguntas para ADD ligação do vértice
void Lista(caixa lista[],int tam){
    
    int op,j;
    
    //criar a LISTA
    for(int i=0; i<tam; i++){
        j=0;
        do{
            do{
            
                printf("\nO vértice [%d] possui ligaçãocom o vértice [%d]\n", i+1,j+1);
                printf("1)Sim\n0)Não\n");scanf("%d",&op);
            
            }while(op!=1&&op!=0);
            if(op==1){
                
                //coloca os valores iniciais ddo blococomo tendo coisa para a lista
                caixa l=(caixa)malloc(sizeof(caixa));
                l->A1.num=j;
                l->Ligamento=NULL;lista[i]=ADD(lista[i],l);
            }
            if(j<tam-1){
                
                do{
                
                    printf("\nPossui mais algum valorque se liga ao vértice[%d]\n",i+1);
                    printf("1)Sim\n0)Não\n");
                    scanf("%d",&op);
                
                }while(op!=1&&op!=0);
            }else
                op=0;
            j++;
        
        }while(op!=0);
    }
}

//Coordena e deixa organizado os print
void CoordenaPrint(caixa lista[],int tam){
    
    //Só chama a função de print e coloca bonitinhoem fila
    for(int i=0;i<tam;i++){
        
        printf("\nLigações deitas por [%d]",i+1);
        PrintaLista(lista[i]);
    }
    printf("\n");
}

//Printa a lista de maneira correta
void PrintaLista(caixa lista){
    
    //passa o print por recursividade
    if(!lista){
        printf("-> /");
        return;
    }
    
    printf("->%d",lista->A1.num+1);
    PrintaLista(lista->Ligamento);
    
}

//Faz a Busca por Largura
void Largura(caixa lista[],int tam,int inicio,int*visita){
    
    int vet, cont=1,*fil, inifila=0, fimfila=0;
    caixa aux=(caixa)malloc(sizeof(caixa));
    
    for(int i=0;i<tam;i++)
        visita[i]=0;
    
    fil=(int*)malloc(tam*sizeof(int));
    fimfila++;
    fil[fimfila]=inicio;visita[inifila]=cont;
    
    while(inifila!=fimfila){
        
        inifila=(inifila+1)%tam;vet=fil[inifila];
        cont++;printf("%d",vet+1);
        aux=lista[vet];
        
        while(aux!=NULL){
            if(!visita[aux->A1.num]){
            
                fimfila=(fimfila+1)%tam;fil[fimfila]=aux->A1.num;
                visita[aux->A1.num]=cont;
            
            }
            aux=aux->Ligamento;
        }
    }
    //for (int i = 0; i < tam; i++)
        //printf("%d ",visita[i]);
}

//Inicializa o vetor da busca e puxa a busca por Profundidade
void CoordenaProfundidade(caixa lista[],int tam,int inicio,int*visita){
    
    int cont=1;
    
    for(int i=0; i<tam; i++)
        visita[i]=0;
    
    Profundidade(lista,tam,inicio,visita,cont);
    //for (int i = 0; i < tam; i++)
    //    printf("%d ",visita[i]);
}

//Faz a Busca por Profundidade
void Profundidade(caixa lista[],int tam,int inicio,int*visita,int cont){
    
    visita[inicio]=cont;
    printf("%d",inicio+1);
    
    caixa aux=(caixa)malloc(sizeof(caixa));
    aux=lista[inicio];

    while(aux!=NULL){
        if(!visita[aux->A1.num])
            Profundidade(lista,tam,aux->A1.num,visita,cont+1);
        aux=aux->Ligamento;
    }
}