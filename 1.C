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



void insereA( caixa lista[], int v, int num, int topo[]);

/*
Tamanho: 3
Test: 0 3 0 1 1 1 1 0 0 0 1 1 1 1
Tamanho: 5
Teste: 0 5 0 1 1 0 0 1 0 1 1 1 1 0 0 1 0 1 0 1 0 1 1 1 1 0 1 0 1 0 1 1 0 1 1 0

tamanho = 6 | ligamentos = 20: 
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

    int i,j,v,w;
    

    
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
    
    }while(op!=1 && op!=2 && op!=0 && op!=3 && op!=4 && op!=5);
    
    caixa*G=(caixa*)malloc(tam*sizeof(caixa));
    for(int i=0;i<tam;i++)
        G[i]=incializa();
    Lista(lista,ligamentos);

    int*aux =(int*)malloc(tam*sizeof(int));

    int*visita=(int*)malloc(tam*sizeof(int));
    int*visita2=(int*)malloc(tam*sizeof(int));
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

        case 5:

        //CoordenaProfundidade(lista,tam,0,visita);

        printf("\n");
        for (i = 0; i < tam+1; i++) {
            
            printf("%d  ",visita[i]);

        }
        printf("\n");

        for (i = 0; i < tam; i++) {
            for (j = 0; j < ligamentos; j++) {
                visita[j] = 0;
            }
            printf("\n\noioi");
            CoordenaProfundidade(G, tam, visita[i],visita2);
            
        }

        for (i = 0; i < tam+1; i++) {
            
            printf("%d  ",visita2[i]);

        }
       
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
    /*
    printf("\n\n Visitas\n");
    for(int i=0; i<tam; i++)
        printf("%d  ",visita[i]);
    printf("\n\n");
    */
    
}

//Faz a Busca por Profundidade
void Profundidade(caixa lista[],int tam,int inicio,int*visita,int cont){
    
    visita[inicio]=cont;
    printf("%d ",inicio+1);
    
    caixa aux=(caixa)malloc(sizeof(caixa));
    aux=lista[inicio];

    while(aux!=NULL){
        cont++;
        if(!visita[aux->A1.num])
            Profundidade(lista,tam,aux->A1.num,visita,cont);
        aux=aux->Ligamento;
    }
}


void Prim(caixa lista[],int tam, int inicio, int *visita){

    int i,dest,pri,menor;

    for(i=0; i<tam; i++)
        visita[i]=-1;

    visita[inicio] = inicio;

    caixa aux =(caixa)malloc(1*sizeof(caixa));

    do{
    
        pri = 1;
        for ( i = 0; i < tam; i++){

            aux=lista[i];
            if (visita[i]!= -1){

                while(aux!=NULL){
                    
                    if (visita[aux->A1.num] == -1){
                        if (pri){
                            menor = aux->A1.peso;
                            inicio = i;
                            dest = aux->A1.num;
                            pri = 0;
                        }else
                            if (menor > aux->A1.peso)
                            {
                                menor = aux->A1.peso;
                                inicio = i;
                                dest = aux->A1.num;
                            }
                    }
                    aux=aux->Ligamento;                   
                }   
            }
        }
        if(pri != 1)
            visita[dest] = inicio;
    }while(pri != 1);
}


void Kruskal(caixa lista[],int tam, int inicio, int *visita){

  int i,dest,pri,menor;

  int *O=(int *)malloc(tam*sizeof(int));

    for(i=0; i<tam; i++){
        visita[i]=-1;
        O[i]=i;

    }

    visita[inicio] = inicio;

    caixa aux =(caixa)malloc(1*sizeof(caixa));

    do{
        
        pri = 1;
        for ( i = 0; i < tam; i++){

            aux=lista[i];
            while(aux!=NULL){
                
                if (visita[aux->A1.num] == -1 && O[i] != O[aux->A1.num]){
                    if (pri){
                        menor = aux->A1.peso;
                        inicio = i;
                        dest = aux->A1.num;
                        pri = 0;
                    }else
                        if (menor > aux->A1.peso)
                        {
                            menor = aux->A1.peso;
                            inicio = i;
                            dest = aux->A1.num;
                        }
                }
                aux=aux->Ligamento;                   
            }   
            
        }

        if(pri != 1){

            if (visita[inicio] == -1){
                visita[inicio] = dest;
            }else
                visita[dest] = inicio;

            for (i = 0; i < tam; i++)
                if (O[i] == O[dest])
                    O[i] = O[inicio];     
        } 

    }while (pri != 1);
}

void insereA( caixa lista[], int v, int num, int topo[]){

    caixa aux, ant;
    aux = lista[v];
    ant = NULL;
    while( aux && aux->A1.num <= num ){
        if( aux->A1.num == num) {
            printf("Tarefas (%d, %d) ja inseridas !\n", v, num);
            return;
        }
        ant = aux;
        aux = aux->Ligamento;
    }
    caixa novo = (caixa)calloc(1, sizeof(caixa));
    novo->A1.num = num;
    novo->Ligamento = aux;
    if( ant == NULL)
        lista[v] = novo;
    else
        ant->Ligamento = novo;

    topo[num]++;
}

/*
1 2 1
1 3 1
1 4 1
1 6 1
2 3 1
3 4 1
3 5 1
6 5 1
6 7 1
5 7 1
7 8 1
7 9 1
8 9 1
10 7 1

10 14 1 2 1 1 3 1 1 4 1 1 6 1 2 3 1 3 4 1 3 5 1 6 5 1 6 7 1 5 7 1 7 8 1 7 9 1 8 9 1 10 7 1

2 1 3 1 4 1 6 1 3 2 4 3 5 3 5 6 7 6 7 5 8 7 9 7 9 8 7 10

*/