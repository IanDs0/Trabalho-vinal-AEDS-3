#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Amostras{

    int A;
    int B;
    int Peso;

}ligandolista;

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
void Lista(caixa lista[],int ligamentos,ligandolista *LL);

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



void Topologica (caixa a[], int tam, int* visita);

void Cor (caixa lista[],int tam,int inicio,int*visita);


void GLista(caixa lista[],int ligamentos,ligandolista *LL);

void FortLigado(caixa lista[],int tam,int*visita,int*visita2);

void For(caixa lista[],int tam,int inicio,int*visita,int cont);


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
    
    int tam,ligamentos,i,j=0;

    char iii[100];

    FILE *oi;

    //Coleta Tamanho e NLigamentos do Grafo
    {
        oi = fopen("./Instâncias/DMXA/DEUS.txt","r");

        //TAMANHO
        while(fscanf(oi,"%s",iii)!=-1){

            if (strcmp(iii,"Nodes")==0)          
                fscanf(oi,"%d",&tam);
            
            if (strcmp(iii,"Edges")==0)
                fscanf(oi,"%d",&ligamentos);
        
        }

        fclose(oi);
        
    }  

        caixa*lista=(caixa*)malloc(tam*sizeof(caixa));
        caixa*Gt=(caixa*)malloc(tam*sizeof(caixa));
        for(int i=0;i<tam;i++){
            lista[i]=incializa();
            Gt[i]=incializa();
        }

        ligandolista*LL=(ligandolista*)malloc(ligamentos*sizeof(ligandolista));

        for ( i = 0; i < ligamentos; i++)
            LL->Peso=1;  

    //Lista
    {
        oi = fopen("./Instâncias/DMXA/DEUS.txt","r");
        int auxA, auxP;
        i=0;
        while(fscanf(oi,"%s",iii)!=-1){

            if (strcmp(iii,"E")==0)
            {
                
                fscanf(oi,"%d %d",&LL[i].A,&LL[i].B);

                i++;
            }

            if (strcmp(iii,"DD")==0)
            {
                
                fscanf(oi,"%d %d",&auxA,&auxP);

                for(j = 0; j < ligamentos; j++)
                    if (LL[j].A==auxA)
                    {
                        LL[j].Peso=auxP;
                    }

            }

        }
    
        fclose(oi);
    
        Lista(lista,ligamentos,LL);
        
        CoordenaPrint(lista,tam);

    }

    //Antlista
    {

        GLista(Gt,ligamentos,LL);
    }

    int*visita=(int*)malloc(tam*sizeof(int));
    int*visita2=(int*)malloc(tam*sizeof(int));

    //Funções
    {
        printf("\n\nTopologica");
        Topologica(lista,tam,visita); 

        /////////////////////////////////////////

        printf("\n\nKruskal");
        Kruskal(lista,tam,0,visita);
        for (int i=0;i<tam;i++)
            printf("%d  ",visita[i]);

        /////////////////////////////////////////

        printf("\n\nPrim");
        Prim(lista,tam,0,visita);
        for (int i=0;i<tam;i++)
            printf("%d  ",visita[i]);

        /////////////////////////////////////////

        printf("\n\nVisita por largura");
        Largura(lista,tam,0,visita);

        /////////////////////////////////////////

        printf("\n\nVisita por Profundidade");
        CoordenaProfundidade(lista,tam,0,visita);
        printf("\n");  

        /////////////////////////////////////////  

        printf("\n\nFortemente Conectado\n");
        FortLigado(Gt,tam,visita,visita2);
    
    }


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
void Lista(caixa lista[],int ligamentos,ligandolista *LL){
    
    int j,i,p;
    
    //criar a LISTA
    for(int k=0; k<ligamentos; k++){

        
        i=LL[k].A;i-=1;
        j=LL[k].B;j-=1;
        p=LL[k].Peso;p-=1;
            
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
        cont++;printf("%d ",vet+1);
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
        //cont++;
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

void Cor (caixa lista[],int tam,int inicio,int*visita){
    
    visita[inicio]=1;
    
    
    caixa aux=(caixa)malloc(sizeof(caixa));
    aux=lista[inicio];

    for(int i=0; i<tam; i++){
        while(aux!=NULL){
            if(!visita)
                Cor(lista,tam,aux->A1.num,visita);
            aux=aux->Ligamento;
        }
    }
    visita[inicio]=inicio+1;
    printf("%d ",inicio+1);
}

void Topologica (caixa lista[], int tam, int *visita){
    for (int i = 0; i < tam; i++){
        visita[i] = 0;
    }
    for (int i = 0; i < tam; i++){
        Cor (lista,tam,i,visita);
    }


}


void GLista(caixa lista[],int ligamentos,ligandolista *LL){
    
    int j,i,p;
    
    //criar a LISTA
    for(int k=0; k<ligamentos; k++){

        
        i=LL[k].B;i-=1;
        j=LL[k].A;j-=1;
        p=LL[k].Peso;p-=1;
            
        //coloca os valores iniciais ddo blococomo tendo coisa para a lista
        caixa l=(caixa)malloc(sizeof(caixa));
        l->A1.num=j;
        l->A1.peso=p;
        l->Ligamento=NULL;
        lista[i]=ADD(lista[i],l);

    }
}


void FortLigado(caixa Gt[],int tam,int*visita,int*visita2){
    
    int cont=1;
    //int *ban=(int*)calloc(tam,sizeof(int));
    
    for(int i=0; i<tam; i++)
    {
        cont=1;

        for(int i=0; i<tam; i++)
            visita2[i]=0;

        For(Gt,tam,visita[i],visita2,cont);
        
        printf("\n\n");

    }
}

void For(caixa lista[],int tam,int inicio,int*visita,int cont){
    
    visita[inicio]=cont;
    printf("%d ",inicio+1);
    
    caixa aux=(caixa)malloc(sizeof(caixa));
    aux=lista[inicio];

    while(aux!=NULL){
        //cont++;
        if(!visita[aux->A1.num])
            For(lista,tam,aux->A1.num,visita,cont);
        aux=aux->Ligamento;
    }
}
/*
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main(void)
{

    DIR *dir;
    struct dirent *lsdir;

    dir = opendir("./Instâncias/DMXA");

    // print all the files and directories within directory
    while ( ( lsdir = readdir(dir) ) != NULL )
    {
        printf ("----%s---\n", lsdir->d_name);
    }

    closedir(dir);

    return 0;

}
*/