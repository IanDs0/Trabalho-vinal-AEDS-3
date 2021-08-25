#include<stdio.h>
#include<stdlib.h>

typedef struct Dados{

    int num;
    int peso;

}dados;

typedef struct Bloco{

    dados A1;

    struct Bloco *Ligamento;

}bloco;

typedef bloco*caixa;

//Inicia as caixas como NULL
caixa incializa();

//ADD o ligação do vértice
caixa ADD(caixa lista,caixa dado);

//faz as perguntas para ADD ligação do vértice
void Lista(caixa lista[],int ligamento);

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


void Prim(caixa gr[],int tam, int orig, int *pai);

void Kruskal(caixa lista[],int tam, int inicio, int *visita);

/*
Tamanho: 3
Test: 0 3 0 1 1 1 1 0 0 0 1 1 1 1
Tamanho: 5
Teste: 0 5 0 1 1 0 0 1 0 1 1 1 1 0 0 1 0 1 0 1 0 1 1 1 1 0 1 0 1 0 1 1 0 1 1 0

tamanho = 5 | ligamentos = 20: 
1 2 6
2 1 6
1 3 1
3 1 1
1 4 5
4 1 5
2 3 2
3 2 2
2 5 5
5 2 5
3 5 6
5 3 6
3 4 2
4 3 2
3 6 4
6 3 4
4 6 4
6 4 4
5 6 3
6 5 3

6 20 1 2 6 2 1 6 1 3 1 3 1 1 1 4 5 4 1 5 2 3 2 3 2 2 2 5 5 5 2 5 3 5 6 5 3 6 3 4 2 4 3 2 3 6 4 6 3 4 4 6 4 6 4 4 5 6 3 6 5 3

*/

int main(){
    
    int tam,op,ligamentos;
    
    printf("Digite o tamanho da Lista de adjacência\n");
    scanf("%d",&tam);

    printf("Digite o numero de ligamentos\n");
    scanf("%d",&ligamentos);
    
    caixa*lista=(caixa*)malloc(tam*sizeof(caixa));
    for(int i=0;i<tam;i++)
        lista[i]=incializa();
    
    Lista(lista,ligamentos);
        
    CoordenaPrint(lista,tam);
    
    do{
        
        printf("\n1)Algoritmo de busca em largura\n2)Algoritmode busca emprofundidade\n3)Árvore geradora mínima com Prim\n4)Árvore geradora mínima com Kruskalf\n0)Para sair\n");
        scanf("%d",&op);
    
    }while(op!=1 && op!=2 && op!=0 && op!=3 && op!=4);
    
    int*visita=(int*)malloc(tam*sizeof(int));
    switch(op){
        
        case 1:
        printf("\nVisita por largura [ ");
        Largura(lista,tam,0,visita);
        break;
        
        case 2:
        printf("\nVisita por Profundidade [ ");
        CoordenaProfundidade(lista,tam,0,visita);
        break;

        case 3:
        printf("\nPrim [ ");
        Prim(lista,tam,0,visita);
        for (int i=0;i<tam;i++)
            printf("%d  ",visita[i]);
        break;

        case 4:
        printf("\nKruskal [ ");
        Kruskal(lista,tam,0,visita);
        for (int i=0;i<tam;i++)
            printf("%d  ",visita[i]);
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

//ADD o ligação do vértice
caixa ADD(caixa lista,caixa dado){
    
    //usa recurção para ADD na lista
    if(lista==NULL)
        return dado;
    
    lista->Ligamento=ADD(lista->Ligamento,dado);
    return lista;
}

//faz as perguntas para ADD ligação do vértice
void Lista(caixa lista[],int ligamentos){
    
    int j,i,p;
    
    //criar a LISTA
    for(int k=0; k<ligamentos; k++){

        printf("ligamentos -> ");
        scanf("%d",&i);i-=1;
        scanf("%d",&j);j-=1;
        scanf("%d",&p);p-=1;
            
        //coloca os valores iniciais ddo blococomo tendo coisa para a lista
        caixa l=(caixa)malloc(sizeof(caixa));
        l->A1.num=j;
        l->A1.peso=p;
        l->Ligamento=NULL;
        lista[i]=ADD(lista[i],l);

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


void Prim(caixa lista[],int tam, int inicio, int *visita){

    int i,dest,pri,menor;

    for(i=0; i<tam; i++)
        visita[i]=-1;

    visita[inicio] = inicio;

    caixa aux =(caixa)malloc(1*sizeof(caixa));
    caixa aux2 =(caixa)malloc(1*sizeof(caixa));

    while (1){
    
        pri = 1;
        for ( i = 0; i < tam; i++){

            aux=lista[i];
            if (visita[i]!= -1){

                aux2=aux;
                while(aux2!=NULL){
                    
                    if (visita[aux2->A1.num] == -1){
                        if (pri){
                            menor = aux2->A1.peso;
                            inicio = i;
                            dest = aux2->A1.num;
                            pri = 0;
                        }else
                            if (menor > aux2->A1.peso)
                            {
                                menor = aux2->A1.peso;
                                inicio = i;
                                dest = aux2->A1.num;
                            }
                    }
                    aux2=aux2->Ligamento;                   
                }   
            }
        }
        if(pri == 1)
            break;

        visita[dest] = inicio;
    }
}


void Kruskal(caixa lista[],int tam, int inicio, int *visita){

  int i,dest,pri,menor;

  int *arv=(int *)malloc(tam*sizeof(int));

    for(i=0; i<tam; i++){
        visita[i]=-1;
        arv[i]=i;

    }

    visita[inicio] = inicio;

    caixa aux =(caixa)malloc(1*sizeof(caixa));
    caixa aux2 =(caixa)malloc(1*sizeof(caixa));

    while (1){
        
        pri = 1;
        for ( i = 0; i < tam; i++){

            aux=lista[i];
            aux2=aux;
            while(aux2!=NULL){
                
                if (visita[aux2->A1.num] == -1 && arv[i] != arv[aux2->A1.num]){
                        if (pri){
                            menor = aux2->A1.peso;
                            inicio = i;
                            dest = aux2->A1.num;
                            pri = 0;
                        }else
                            if (menor > aux2->A1.peso)
                            {
                                menor = aux2->A1.peso;
                                inicio = i;
                                dest = aux2->A1.num;
                            }
                    }
                aux2=aux2->Ligamento;                   
            }   
            
        }

        if(pri == 1){
            break;printf("oi");}
        
        if (visita[inicio] == -1){
            visita[inicio] = dest;
        }else
            visita[dest] = inicio;

        for (i = 0; i < tam; i++)
            if (arv[i] == arv[dest])
                arv[i] = arv[inicio];  

    }
}
