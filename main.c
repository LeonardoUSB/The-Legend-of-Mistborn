#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Aldea
{
    char nombre[20];
    struct Aldea* siguiente;
    struct Aldea* anterior;
};

struct Aldea* crearListaAldeas(int numAldeas){
    struct Aldea* cabeza =malloc(sizeof(struct Aldea));
    strcpy(cabeza->nombre, "Luthadel");
    cabeza->anterior=NULL;
    cabeza->siguiente=NULL;

    struct Aldea* nuevaAldea = cabeza;

    for (size_t i = 0; i < numAldeas-1; i++)
    {
        
        nuevaAldea->siguiente=malloc(sizeof(struct Aldea));
        strcpy(nuevaAldea->siguiente->nombre, "Luthadel");
        nuevaAldea->siguiente->anterior=nuevaAldea;
        nuevaAldea=nuevaAldea->siguiente;
        nuevaAldea->siguiente=NULL;

    }
    
    return cabeza;
}

struct AldeaParalela
{
    char nombre[20];
    struct AldeaParalela* siguiente;
    struct AldeaParalela* anterior;
};

struct AldeaParalela* crearListaAldeasParalelas(int numAldeas){
    struct AldeaParalela* cabeza =malloc(sizeof(struct AldeaParalela));
    strcpy(cabeza->nombre, "LuthadelAlter");
    cabeza->anterior=NULL;
    cabeza->siguiente=NULL;

    struct AldeaParalela* nuevaAldea = cabeza;

    for (size_t i = 0; i < numAldeas-1; i++)
    {
        
        nuevaAldea->siguiente=malloc(sizeof(struct AldeaParalela));
        strcpy(nuevaAldea->siguiente->nombre, "LuthadelAlter");
        nuevaAldea->siguiente->anterior=nuevaAldea;
        nuevaAldea=nuevaAldea->siguiente;
        nuevaAldea->siguiente=NULL;

    }
    
    return cabeza;
}

struct Item
{
    char nombre[20];
    struct Item* siguiente;
    struct Item* anterior;
};

struct Item* crearListaItem(int numAldeas){
    struct Item* cabeza =malloc(sizeof(struct Item));
    strcpy(cabeza->nombre, "Peltre");
    cabeza->anterior=NULL;
    cabeza->siguiente=NULL;

    struct Item* nuevoItem = cabeza;

    for (size_t i = 0; i < numAldeas-1; i++)
    {
        
        nuevoItem->siguiente=malloc(sizeof(struct Item));
        strcpy(nuevoItem->siguiente->nombre, "Peltre");
        nuevoItem->siguiente->anterior=nuevoItem;
        nuevoItem=nuevoItem->siguiente;
        nuevoItem->siguiente=NULL;

    }
    
    return cabeza;
}

struct ItemParalelo
{
    char nombre[20];
    struct ItemParalelo* siguiente;
    struct ItemParalelo* anterior;
};

struct ItemParalelo* crearListaItemAlter(int numAldeas){
    struct ItemParalelo* cabeza =malloc(sizeof(struct ItemParalelo));
    strcpy(cabeza->nombre, "Duraluminio");
    cabeza->anterior=NULL;
    cabeza->siguiente=NULL;

    struct ItemParalelo* nuevoItem = cabeza;

    for (size_t i = 0; i < numAldeas-1; i++)
    {
        
        nuevoItem->siguiente=malloc(sizeof(struct ItemParalelo));
        strcpy(nuevoItem->siguiente->nombre, "Duraluminio");
        nuevoItem->siguiente->anterior=nuevoItem;
        nuevoItem=nuevoItem->siguiente;
        nuevoItem->siguiente=NULL;

    }
    
    return cabeza;
}

struct Jugador
{
    int vidas;
};

void imprimeTodo(struct Aldea* cabeza, struct AldeaParalela* cabeazaAlter, struct Item* ItemIni,  struct ItemParalelo* ItemIniAlter){
    struct Aldea* siguiente= cabeza;
    while(siguiente !=NULL){
        printf("%s\n", siguiente->nombre);
        siguiente=siguiente->siguiente;
    }
    
    struct AldeaParalela* siguienteAlter= cabeazaAlter;
    while(siguienteAlter !=NULL){
        printf("%s\n", siguienteAlter->nombre);
        siguienteAlter=siguienteAlter->siguiente;
    }

    struct Item* siguienteItem= ItemIni;
    while(siguienteItem !=NULL){
        printf("%s\n", siguienteItem->nombre);
        siguienteItem=siguienteItem->siguiente;
    }

    struct ItemParalelo* siguienteItemAlter= ItemIniAlter;
    while(siguienteItemAlter !=NULL){
        printf("%s\n", siguienteItemAlter->nombre);
        siguienteItemAlter=siguienteItemAlter->siguiente;
    }
}


void inicializar(){
                                                        //Pedimos las aldeas
    printf("Bienvenido a Zelda\n");
    printf("Por favor indica el nùmero de aldeas\n");
    int numAldeas;
    scanf("%d",&numAldeas);
                                                        //Inicializamos las estructuas
    struct Jugador jugador;
    jugador.vidas=3;

    struct Aldea* aldeaOrigen=crearListaAldeas(numAldeas);
    struct AldeaParalela* aldeaParalelaOrigen=crearListaAldeasParalelas(numAldeas);
    struct Item* itemOrigen=crearListaItem(numAldeas);
    struct ItemParalelo* itemParaleloOrigen=crearListaItemAlter(numAldeas);

    imprimeTodo(aldeaOrigen, aldeaParalelaOrigen, itemOrigen, itemParaleloOrigen);
    
}

int main(){
    inicializar();
}

