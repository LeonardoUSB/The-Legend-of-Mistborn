#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

// Declaracion de variables globales.
int dinero = 0;
int comandoTrans = 0;
int aleatorio;
int transportaParalelo;
int aldeasTotales;
struct Jugador jugador;
struct Aldea* aldeaActual = NULL;
struct Aldea* aldeaOrigenDePana = NULL;
struct AldeaParalela* aldeaActualParalela = NULL;
struct AldeaParalela* aldeaParalelaOrigenDePana = NULL;
struct Item* itemOrigenDePana = NULL;
struct ItemParalelo* itemParaleloOrigenDePana = NULL;

// Firma de algunas funciones.
void comprar(); void anteriorAldea(); void siguienteAldea(); void gameOver(); void mazmorra(); void generarAleatorio(); void buscar(); void buscarMazmorra(); int indiceAldea(); void atacar(); void victoria(); int indiceAldeaParalela(); void transportar(); void imprimirUbicaciones(); void aldeasDerrotadas();


// Structs de Jugador, Aldea, AldeaParalela, Item e ItemParalelo.

struct Jugador
{
    int vidas;
    int corazones;
    struct Aldea* ubicacion;
    int mazmorrasVencidas;
    int paralelo;
};


struct Aldea
{
    char* nombre;
    struct Aldea* siguiente;
    struct Aldea* anterior;
    struct Item* derrotadoPor;
    struct Item* contiene;
    struct Item* mazContiene;
    int vencida;
    int yaBusco;
};


struct AldeaParalela
{
    char* nombre;
    struct AldeaParalela* siguiente;
    struct AldeaParalela* anterior;
    struct ItemParalelo* derrotadoPor;
    struct ItemParalelo* contiene;
    struct ItemParalelo* mazContiene;
    int vencida;
    int yaBusco;
};

struct Item
{
    char* nombre;
    struct Item* siguiente;
    struct Item* anterior;
    int encontrado;
    struct Aldea* ubicacion;
    struct Aldea* derrotaA;
};


struct ItemParalelo
{
    char* nombre;
    struct ItemParalelo* siguiente;
    struct ItemParalelo* anterior;
    int encontrado;
    struct AldeaParalela* ubicacion;
    struct AldeaParalela* derrotaA;
};


// Funcion potencia desarrollada por nosotros mismos.
int potencia(int base, int exponente){
    int resultado=1;
    for (int i = 0; i < exponente; i++) resultado*=base;
    return resultado;
}


// Funciones para crear los nombres de las aldeas e items.

void creaNombresAldea(struct Aldea* cabeza,char**nombres,char**nuevosNombres,int tamNuevos,int profundidad){
    struct Aldea* siguiente= cabeza;

    for (int i = 0; i < tamNuevos; i++)                         //Asigna los nombres de la recursion pasada
    {
        siguiente->nombre=malloc(profundidad*15*sizeof(char));
        strcpy(siguiente->nombre, "");
        siguiente->nombre=strcat(siguiente->nombre, nuevosNombres[i]);
        siguiente=siguiente->siguiente;
        if (siguiente==NULL)
        {
            return;
        }
    }
                                                                //Crea un arreglo que tendra las nuevas combinaciones de nombres
    profundidad++;
    int numCombinaciones= potencia(16, profundidad);
    char **combinaciones=malloc(numCombinaciones * sizeof(char*));
    for (int i = 0; i < numCombinaciones; i++)
    {
        combinaciones[i]=malloc(profundidad*15 * sizeof(char));
        strcpy(combinaciones[i],"");
    }
    
    int k=0;
                                                                //Genera las Combinaciones
    for (int i = 0; i < tamNuevos; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            strcat(combinaciones[k],nuevosNombres[i]);
            strcat(combinaciones[k],"-");
            strcat(combinaciones[k],nombres[j]);
            k++;
        }
    }
    
    creaNombresAldea(siguiente,nombres,combinaciones,numCombinaciones, profundidad );

    for (int i = 0; i < numCombinaciones; i++) {                //Libera la memoria creada
        free(combinaciones[i]);
    }
    free(combinaciones);
}


void creaNombresAldeaAlter(struct AldeaParalela* cabeza,char**nombres,char**nuevosNombres,int tamNuevos,int profundidad){
    struct AldeaParalela* siguiente= cabeza;
                                                                    //Explicacion se encuentra en creaNombresAldea
    for (int i = 0; i < tamNuevos; i++)
    {
        siguiente->nombre=malloc(profundidad*25*sizeof(char));
        strcpy(siguiente->nombre, "Shadesmar ");
        siguiente->nombre=strcat(siguiente->nombre, nuevosNombres[i]);
        siguiente=siguiente->siguiente;
        if (siguiente==NULL)
        {
            return;
        }
    }

    profundidad++;
    int numCombinaciones= potencia(16, profundidad);
    char **combinaciones=malloc(numCombinaciones * sizeof(char*));
    for (int i = 0; i < numCombinaciones; i++)
    {
        combinaciones[i]=malloc(profundidad*15 * sizeof(char));
        strcpy(combinaciones[i],"");
    }
    
    int k=0;

    for (int i = 0; i < tamNuevos; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            strcat(combinaciones[k],nuevosNombres[i]);
            strcat(combinaciones[k],"-");
            strcat(combinaciones[k],nombres[j]);
            k++;
        }
    }
    
    creaNombresAldeaAlter(siguiente,nombres,combinaciones,numCombinaciones, profundidad );

    for (int i = 0; i < numCombinaciones; i++) {
        free(combinaciones[i]);
    }
    free(combinaciones);
}


void creaItems(struct Item* cabeza,char**nombres,char**nuevosNombres,int tamNuevos,int profundidad){
    struct Item* siguiente= cabeza;
                                                                                    //Explicacion se encuentra en creaNombresAldea
    for (int i = 0; i < tamNuevos; i++)
    {
        siguiente->nombre=malloc(profundidad*15*sizeof(char));
        strcpy(siguiente->nombre, "");
        siguiente->nombre=strcat(siguiente->nombre, nuevosNombres[i]);
        siguiente=siguiente->siguiente;
        if (siguiente==NULL)
        {
            return;
        }
    }

    profundidad++;
    int numCombinaciones= potencia(16, profundidad);
    char **combinaciones=malloc(numCombinaciones * sizeof(char*));
    for (int i = 0; i < numCombinaciones; i++)
    {
        combinaciones[i]=malloc(profundidad*25 * sizeof(char));
        strcpy(combinaciones[i],"");
    }
    
    int k=0;

    for (int i = 0; i < tamNuevos; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            strcat(combinaciones[k],nuevosNombres[i]);
            strcat(combinaciones[k],"-");
            strcat(combinaciones[k],nombres[j]);
            k++;
        }
    }
    
    creaItems(siguiente,nombres,combinaciones,numCombinaciones, profundidad );

    for (int i = 0; i < numCombinaciones; i++) {
        free(combinaciones[i]);
    }
    free(combinaciones);
}


void creaItemsAlter(struct ItemParalelo* cabeza,char**nombres,char**nuevosNombres,int tamNuevos,int profundidad){
    struct ItemParalelo* siguiente= cabeza;
                                                                        // Explicacion se encuentra en creaNombresAldea.
    for (int i = 0; i < tamNuevos; i++)
    {
        siguiente->nombre=malloc(profundidad*25*sizeof(char));
        strcpy(siguiente->nombre, "Shadesmar ");
        siguiente->nombre=strcat(siguiente->nombre, nuevosNombres[i]);
        siguiente=siguiente->siguiente;
        if (siguiente==NULL)
        {
            return;
        }
    }

    profundidad++;
    int numCombinaciones= potencia(16, profundidad);
    char **combinaciones=malloc(numCombinaciones * sizeof(char*));
    for (int i = 0; i < numCombinaciones; i++)
    {
        combinaciones[i]=malloc(profundidad*25 * sizeof(char));
        strcpy(combinaciones[i],"");
    }
    
    int k=0;

    for (int i = 0; i < tamNuevos; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            strcat(combinaciones[k],nuevosNombres[i]);
            strcat(combinaciones[k],"-");
            strcat(combinaciones[k],nombres[j]);
            k++;
        }
    }
    
    creaItemsAlter(siguiente,nombres,combinaciones,numCombinaciones, profundidad );

    for (int i = 0; i < numCombinaciones; i++) {
        free(combinaciones[i]);
    }
    free(combinaciones);
}


// Funciones para crear las listas enlanzadas.

struct Aldea* crearListaAldeas(int numAldeas){
    struct Aldea* cabeza =malloc(sizeof(struct Aldea));
    cabeza->anterior=NULL;
    cabeza->siguiente=NULL;

    struct Aldea* nuevaAldea = cabeza;

    for (size_t i = 0; i < numAldeas-1; i++)
    {
        
        nuevaAldea->siguiente=malloc(sizeof(struct Aldea));
        nuevaAldea->siguiente->anterior=nuevaAldea;
        nuevaAldea=nuevaAldea->siguiente;
        nuevaAldea->siguiente=NULL;

    }
    
    return cabeza;
}


struct AldeaParalela* crearListaAldeasParalelas(int numAldeas){
    struct AldeaParalela* cabeza =malloc(sizeof(struct AldeaParalela));
    cabeza->anterior=NULL;
    cabeza->siguiente=NULL;

    struct AldeaParalela* nuevaAldea = cabeza;

    for (size_t i = 0; i < numAldeas-1; i++)
    {
        
        nuevaAldea->siguiente=malloc(sizeof(struct AldeaParalela));
        nuevaAldea->siguiente->anterior=nuevaAldea;
        nuevaAldea=nuevaAldea->siguiente;
        nuevaAldea->siguiente=NULL;

    }
    
    return cabeza;
}


struct Item* crearListaItem(int numAldeas){
    struct Item* cabeza =malloc(sizeof(struct Item));
    cabeza->anterior=NULL;
    cabeza->siguiente=NULL;

    struct Item* nuevoItem = cabeza;

    for (size_t i = 0; i < numAldeas-1; i++)
    {
        nuevoItem->siguiente=malloc(sizeof(struct Item));
        nuevoItem->siguiente->anterior=nuevoItem;
        nuevoItem=nuevoItem->siguiente;
        nuevoItem->siguiente=NULL;
    }
    
    return cabeza;
}


struct ItemParalelo* crearListaItemAlter(int numAldeas){
    struct ItemParalelo* cabeza =malloc(sizeof(struct ItemParalelo));
    cabeza->anterior=NULL;
    cabeza->siguiente=NULL;

    struct ItemParalelo* nuevoItem = cabeza;

    for (size_t i = 0; i < numAldeas-1; i++)
    {
        nuevoItem->siguiente=malloc(sizeof(struct ItemParalelo));
        nuevoItem->siguiente->anterior=nuevoItem;
        nuevoItem=nuevoItem->siguiente;
        nuevoItem->siguiente=NULL;
    }
    
    return cabeza;
}


// Funciones para ubicar los items y asignar a que mazmorra derrotan.

struct Aldea* encontrarAldea(struct  Aldea* AldeaIni, struct  Aldea* cabeza, struct  Item* ItemIni, int* cont){
    struct Aldea* AldeaSig=AldeaIni;
    if (AldeaSig==NULL)
    {                                                         // Trabaja con todos los casos donde una aldea inadmisible aparece.
        AldeaSig=cabeza;
        AldeaSig=encontrarAldea(AldeaSig, cabeza,ItemIni, cont);
        if(AldeaSig->contiene==NULL){
            AldeaSig->contiene=ItemIni;
            ItemIni->ubicacion=AldeaSig;
            ItemIni=ItemIni->siguiente;
            (*cont)++;
            AldeaSig=encontrarAldea(AldeaSig, cabeza, ItemIni, cont);
        }
        else{
            AldeaSig->mazContiene=ItemIni;
            ItemIni->ubicacion=AldeaSig;
            ItemIni=ItemIni->siguiente;
            (*cont)++;
            AldeaSig=encontrarAldea(AldeaSig, cabeza, ItemIni, cont);
        }
        
    }
    
    while((AldeaSig->contiene!=NULL && AldeaSig->mazContiene!=NULL) && AldeaSig->siguiente!=NULL){
        AldeaSig=AldeaSig->siguiente;
    }
    if (AldeaSig->siguiente==NULL && AldeaSig->contiene==NULL && AldeaSig->mazContiene==NULL){
        AldeaSig=cabeza;
        encontrarAldea(AldeaSig, cabeza,ItemIni,cont);
    }
    else{
        return AldeaSig;
    }
}


struct AldeaParalela* encontrarAldeaAlter(struct  AldeaParalela* AldeaIni, struct  AldeaParalela* cabeza, struct  ItemParalelo* ItemIni, int* cont){
    struct AldeaParalela* AldeaSig=AldeaIni;
    if (AldeaSig==NULL)
    {                                                                                // Explicacion se encuentra en encontrar Aldea.
        AldeaSig=cabeza;
        AldeaSig=encontrarAldeaAlter(AldeaSig, cabeza,ItemIni, cont);
        if(AldeaSig->contiene==NULL){
            AldeaSig->contiene=ItemIni;
            ItemIni->ubicacion=AldeaSig;
            ItemIni=ItemIni->siguiente;
            (*cont)++;
            AldeaSig=encontrarAldeaAlter(AldeaSig, cabeza, ItemIni, cont);
        }
        else{
            AldeaSig->mazContiene=ItemIni;
            ItemIni->ubicacion=AldeaSig;
            ItemIni=ItemIni->siguiente;
            (*cont)++;
            AldeaSig=encontrarAldeaAlter(AldeaSig, cabeza, ItemIni, cont);
        }
    }
    
    while((AldeaSig->contiene!=NULL && AldeaSig->mazContiene!=NULL) && AldeaSig->siguiente!=NULL){
        AldeaSig=AldeaSig->siguiente;
    }
    if (AldeaSig->siguiente==NULL && AldeaSig->contiene==NULL && AldeaSig->mazContiene==NULL){
        AldeaSig=cabeza;
        encontrarAldeaAlter(AldeaSig, cabeza,ItemIni,cont);
    }
    else{
        return AldeaSig;
    }
}


void ubicaTodo(struct Aldea* cabeza,struct Item* ItemIni, int numAldeas){
    struct Aldea* aldeaSig=cabeza;
    struct Item* itemSig=ItemIni;
    int random;
    int cont=0;
    while(cont<numAldeas){
        random=rand();                          // Trabaja con cada caso posible.
        aldeaSig=encontrarAldea(aldeaSig,cabeza, itemSig,&cont);  // Funcion que asegura que la aldea sea elegida.
        
        if(random%2==0 && aldeaSig->contiene ==NULL){
            aldeaSig->contiene=itemSig;
            itemSig->ubicacion=aldeaSig;

            aldeaSig=aldeaSig->siguiente;
            itemSig=itemSig->siguiente;
            cont++;
        }
        else{
            random=rand();
            if(random%2==0 && aldeaSig->mazContiene ==NULL){
                aldeaSig->mazContiene=itemSig;
                itemSig->ubicacion=aldeaSig;

                aldeaSig=aldeaSig->siguiente;
                itemSig=itemSig->siguiente;
                cont++;
            }
            else{
                aldeaSig=aldeaSig->siguiente;
            }
        }
    }
}


void ubicaTodoAlter(struct AldeaParalela* cabeza, struct ItemParalelo* ItemIni ,int numAldeas){
    struct AldeaParalela* aldeaSig=cabeza;
    struct ItemParalelo* itemSig=ItemIni;
    int random;                                                 // Explicacion se Encuentra en UbicaTodo.
    int cont=0;
    while(cont<numAldeas){
        random=rand();
        aldeaSig=encontrarAldeaAlter(aldeaSig,cabeza, itemSig,&cont);
        
        if(random%2==0 && aldeaSig->contiene == NULL){
            aldeaSig->contiene=itemSig;
            itemSig->ubicacion=aldeaSig;

            aldeaSig=aldeaSig->siguiente;
            itemSig=itemSig->siguiente;
            cont++;
        }
        else{
            random=rand();
            if(random%2==0 && aldeaSig->mazContiene == NULL){
                aldeaSig->mazContiene=itemSig;
                itemSig->ubicacion=aldeaSig;

                aldeaSig=aldeaSig->siguiente;
                itemSig=itemSig->siguiente;
                cont++;
            }
            else{
                aldeaSig=aldeaSig->siguiente;
            }
        }
    }
}


struct Item* encontrarItem(struct  Item* ItemIni,struct  Item* cabeza,struct  Aldea** AldeaIni, int* cont){
    struct Item* itemSig=ItemIni;
                                                                    // Explicacion se encuentra en encontrar Aldea.
    if(itemSig==NULL){
        itemSig=cabeza;
        itemSig=encontrarItem(itemSig, cabeza,AldeaIni,cont);
        (*AldeaIni)->derrotadoPor=itemSig;
        itemSig->derrotaA=(*AldeaIni);
        (*AldeaIni)=(*AldeaIni)->siguiente;
        (*cont)++;
        if ((*AldeaIni)==NULL){
            return NULL;
        }
        itemSig=encontrarItem(itemSig, cabeza,AldeaIni,cont);
    }

    while(itemSig->derrotaA!=NULL && itemSig->siguiente!=NULL){
        itemSig=itemSig->siguiente;
    }
    if (itemSig->siguiente ==NULL && itemSig->derrotaA!=NULL){
        itemSig=cabeza;
        encontrarItem(itemSig, cabeza,AldeaIni,cont);
    }
    else{
        

        return itemSig;
    }
}


struct ItemParalelo* encontrarItemAlter(struct  ItemParalelo* ItemIni,struct  ItemParalelo* cabeza,struct  AldeaParalela** AldeaIni, int* cont){
    struct ItemParalelo* itemSig=ItemIni;
                                                                            // Explicacion se encuentra en encontrar Aldea.
    if(itemSig==NULL){
        itemSig=cabeza;
        itemSig=encontrarItemAlter(itemSig, cabeza,AldeaIni,cont);
        (*AldeaIni)->derrotadoPor=itemSig;
        itemSig->derrotaA=(*AldeaIni);
        (*AldeaIni)=(*AldeaIni)->siguiente;
        (*cont)++;
        if ((*AldeaIni)==NULL){
            return NULL;
        }
        itemSig=encontrarItemAlter(itemSig, cabeza,AldeaIni,cont);
    }

    while(itemSig->derrotaA!=NULL && itemSig->siguiente!=NULL){
        itemSig=itemSig->siguiente;
    }
    if (itemSig->siguiente ==NULL && itemSig->derrotaA!=NULL){
        itemSig=cabeza;
        encontrarItemAlter(itemSig, cabeza,AldeaIni,cont);
    }
    else{
        

        return itemSig;
    }
}


void derrotaTodo(struct Aldea* cabeza,struct Item* ItemIni, int numAldeas){
    struct Aldea* aldeaSig=cabeza;
    struct Item* itemSig=ItemIni;
    struct Aldea** punAldea=&aldeaSig;
    int random;
    int cont=0;
    while(cont<numAldeas){
        random=rand(); 
        itemSig=encontrarItem(itemSig,ItemIni,punAldea,&cont);
        if (aldeaSig==NULL){
            break;
        }
        if(random%2==0){
            aldeaSig->derrotadoPor=itemSig;
            itemSig->derrotaA=aldeaSig;
            aldeaSig=aldeaSig->siguiente;
            itemSig=itemSig->siguiente;
            cont++;
        }
        else{
            itemSig=itemSig->siguiente;
        }
    }
}


void derrotaTodoAlter(struct AldeaParalela* cabeza,struct ItemParalelo* ItemIni, int numAldeas){
    struct AldeaParalela* aldeaSig=cabeza;
    struct ItemParalelo* itemSig=ItemIni;
    struct AldeaParalela** punAldea=&aldeaSig;
    int random;
    int cont=0;
    while(cont<numAldeas){
        random=rand(); 
        itemSig=encontrarItemAlter(itemSig,ItemIni,punAldea,&cont);
        if (aldeaSig == NULL){
            break;
        }
        if(random%2==0){
            aldeaSig->derrotadoPor=itemSig;
            itemSig->derrotaA=aldeaSig;
            aldeaSig=aldeaSig->siguiente;
            itemSig=itemSig->siguiente;
            cont++;
        }
        else{
            itemSig=itemSig->siguiente;
        }
    }
};


//Funciones Generales

void imprimirAldeas(struct Aldea* cabeza, struct AldeaParalela* cabeazaAlter) {
    
    printf("[ALDEAS]\n\n");

    struct Aldea* siguiente= cabeza;
    while(siguiente !=NULL){
        printf("%s\n", siguiente->nombre);
        siguiente=siguiente->siguiente;
    }

    printf("\n\n[ALDEAS PARALELAS]\n\n");
    
    struct AldeaParalela* siguienteAlter= cabeazaAlter;
    while(siguienteAlter !=NULL){
        printf("%s\n", siguienteAlter->nombre);
        siguienteAlter=siguienteAlter->siguiente;
    }

    printf("\n\n");

    return;
}


void imprimirItems(struct Item* ItemIni,  struct ItemParalelo* ItemIniAlter) {
    
    printf("[ITEMS]\n\n");

    struct Item* siguienteItem= ItemIni;
    while(siguienteItem !=NULL){
        printf("%s\n", siguienteItem->nombre);
        siguienteItem=siguienteItem->siguiente;
       
    }

    printf("\n\n[ITEMS PARALELOS]\n\n");

    struct ItemParalelo* siguienteItemAlter= ItemIniAlter;
    while(siguienteItemAlter !=NULL){
        printf("%s\n", siguienteItemAlter->nombre);
        siguienteItemAlter=siguienteItemAlter->siguiente;
    }

    printf("\n\n");

    return;
}

// Funcion que inicia toda la ejecucion.
void inicializar(){
    int numAldeas;
    jugador.corazones = 3;
    jugador.vidas = 3;

    // Pedimos las aldeas.
    printf("Bienvenido a The Legend of Mistborn\n");
    printf("Digo... Zelda Rogue\n");
    printf("Por favor indica el numero de aldeas:\n");
    scanf("%d",&numAldeas);
    
    // Inicializamos las estructuras.
    struct Aldea* aldeaOrigen=crearListaAldeas(numAldeas);
    struct AldeaParalela* aldeaParalelaOrigen=crearListaAldeasParalelas(numAldeas);
    struct Item* itemOrigen=crearListaItem(numAldeas);
    struct ItemParalelo* itemParaleloOrigen=crearListaItemAlter(numAldeas);

    char**nomAldeas=malloc(16 * sizeof(char*));
    for (int i = 0; i < 16; i++)
    {
        nomAldeas[i]=malloc(15 * sizeof(char));
    }
    strcpy(nomAldeas[0], "Luthadel");
    strcpy(nomAldeas[1], "Elendel");
    strcpy(nomAldeas[2], "Urteau");
    strcpy(nomAldeas[3], "Fadrex");
    strcpy(nomAldeas[4], "Tathingdwen");
    strcpy(nomAldeas[5], "Seran");
    strcpy(nomAldeas[6], "Fellise");
    strcpy(nomAldeas[7], "Weathering");
    strcpy(nomAldeas[8], "Dryport");
    strcpy(nomAldeas[9], "Tremredare");
    strcpy(nomAldeas[10], "Zincell");
    strcpy(nomAldeas[11], "Madil");
    strcpy(nomAldeas[12], "Roughs");
    strcpy(nomAldeas[13], "Faleen");
    strcpy(nomAldeas[14], "Dramali");
    strcpy(nomAldeas[15], "Telsin");
    
    creaNombresAldea(aldeaOrigen, nomAldeas,nomAldeas, 16,1);
    creaNombresAldeaAlter(aldeaParalelaOrigen, nomAldeas,nomAldeas, 16,1);

    strcpy(nomAldeas[0], "Hierro");
    strcpy(nomAldeas[1], "Acero");
    strcpy(nomAldeas[2], "Estaño");
    strcpy(nomAldeas[3], "Peltre");
    strcpy(nomAldeas[4], "Zinc");
    strcpy(nomAldeas[5], "Laton");
    strcpy(nomAldeas[6], "Cobre");
    strcpy(nomAldeas[7], "Bronce");
    strcpy(nomAldeas[8], "Aluminio");
    strcpy(nomAldeas[9], "Duraluminio");
    strcpy(nomAldeas[10], "Bendaleo");
    strcpy(nomAldeas[11], "Cadmio");
    strcpy(nomAldeas[12], "Oro");
    strcpy(nomAldeas[13], "Electrum");
    strcpy(nomAldeas[14], "Atium");
    strcpy(nomAldeas[15], "Malatium");

    creaItems(itemOrigen, nomAldeas,nomAldeas, 16,1);
    creaItemsAlter(itemParaleloOrigen, nomAldeas,nomAldeas, 16,1);

    for (int i = 0; i < 16; i++) {
        free(nomAldeas[i]);
    }
    free(nomAldeas);

    srand(time(NULL));
    ubicaTodo(aldeaOrigen,itemOrigen,numAldeas);  
    derrotaTodo(aldeaOrigen,itemOrigen,numAldeas); 

    ubicaTodoAlter(aldeaParalelaOrigen,itemParaleloOrigen,numAldeas);
    derrotaTodoAlter(aldeaParalelaOrigen,itemParaleloOrigen,numAldeas);

    // Inicializacion de variables globales que seran de utilidad mas adelante.
    aldeaActual = aldeaOrigen;
    aldeaOrigenDePana = aldeaOrigen;
    aldeaActualParalela = aldeaParalelaOrigen;
    aldeaParalelaOrigenDePana = aldeaParalelaOrigen;
    itemOrigenDePana = itemOrigen;
    itemParaleloOrigenDePana = itemParaleloOrigen;
    aldeasTotales = 2*numAldeas;

    transportaParalelo = (rand() % (numAldeas - 1 + 1)) + 1;

    printf("\n\n[Despiertas en tu habitacion]\n[Miras por la ventana y te das cuenta de que el apocalipsis ha llegado]\n[El sol es rojo]\n[Cae ceniza del cielo]\n[Las plantas son marrones]\n\n\n[Derrota a todas las mazmorras para salvar al mundo]\n");

    printf("\n\n");

    return;
}


/* [NOTA]: A partir de aqui habran muchas ocasiones donde haya codigo casi duplicado. Esto debido a la forma en que
           manejamos las funciones y el mundo paralelo. Como las aldeas y los items pertenecen a estructuras distintas
           si son paralelas, en el codigo se hace muchas veces una distincion por casos:
           
           Si esta en el mundo normal: ejecutar la funcion con las variables pertenecientes a las estructuras Aldea e Item.
           Si esta en el mundo paralelo: ejecutar la funcion con las variables pertenecientes a las estructuras AldeaParalela
                                         e ItemParalelo.
*/

// Funcion que imprime la aldea y el menu de comandos.
void aldea() {
    int i;
    char entrada[6];

    while (1) {
        if (jugador.paralelo == 0) printf("[ALDEA %d: %s]\n\n", indiceAldea(aldeaActual), aldeaActual->nombre);
        else printf("[ALDEA %d: %s]\n\n", indiceAldeaParalela(aldeaActualParalela), aldeaActualParalela->nombre);
        printf("Comandos disponibles:\n");
        // Si el jugador ya puede usar el comando "trans".
        if (comandoTrans == 1) {printf("------------------------------------------\n| busq | maz | compr | trans | ant | sig |\n------------------------------------------\n"); printf("| Corazones:%d | Vida:%d | Dinero:%d |\n", jugador.corazones, jugador.vidas, dinero); printf("------------------------------------------\n\n");}
        // Si el jugador aun no puede usar el comando "trans".
        else {printf("----------------------------------\n| busq | maz | compr | ant | sig |\n----------------------------------\n"); printf("| Corazones:%d | Vida:%d | Dinero:%d |\n", jugador.corazones, jugador.vidas, dinero); printf("----------------------------------\n\n");}
        printf("Ingresa un comando:\n");

        /* Almacena la entrada por teclado en el arreglo "entrada". */
        scanf("%6s", entrada);

        /* Convierte todos los caracteres de la entrada en minusculas. */
        for (i = 0; entrada[i] != '\0'; i++) entrada[i] = tolower(entrada[i]);

        printf("\n\n");

        /* Evalua las entradas y ejecuta los comandos correspondientes. */
        if (strcmp(entrada, "busq") == 0) buscar();
        else if (strcmp(entrada, "maz") == 0) mazmorra();
        else if (strcmp(entrada, "compr") == 0) comprar();
        // Para usar el comando "trans" es necesario haberlo desbloqueado. Se verifica con comandoTrans == 1.
        else if (strcmp(entrada, "trans") == 0 && comandoTrans == 1) transportar();
        else if (strcmp(entrada, "ant") == 0) anteriorAldea();
        else if (strcmp(entrada, "sig") == 0) siguienteAldea();
        
        // Comandos extra:
        else if (strcmp(entrada, "+") == 0) dinero = dinero + 100;
        else if (strcmp(entrada, "-") == 0) dinero = 0;
        else if (strcmp(entrada, "num") == 0) printf("Numero de mazmorra para transportar al mundo paralelo: %d\n\n\n", transportaParalelo);
        else if (strcmp(entrada, "ald") == 0) imprimirAldeas(aldeaOrigenDePana, aldeaParalelaOrigenDePana);
        else if (strcmp(entrada, "items") == 0) imprimirItems(itemOrigenDePana, itemParaleloOrigenDePana);
        else if (strcmp(entrada, "ubi") == 0) imprimirUbicaciones();
        else if (strcmp(entrada, "vida") == 0) jugador.vidas = jugador.corazones;
        else if (strcmp(entrada, "max") == 0) {jugador.corazones = 127; jugador.vidas = jugador.corazones;}
        else if (strcmp(entrada, "derr") == 0) aldeasDerrotadas();
        else printf("[Comando no valido]\n\n\n");
    }
}


// Funcion para buscar el item oculto de la aldea o aldea paralela.
void buscar() {
    // Mundo normal.
    if (jugador.paralelo == 0) {
        // Si no hay objeto en la aldea.
        if (aldeaActual->contiene == NULL) {
            printf("[No hay un objeto en esta aldea]\n");
            // Si es la primera aldea.
            if (aldeaActual->nombre == aldeaOrigenDePana-> nombre) printf("[El item que derrota a la mazmorra de Luthadel se encuentra en la tienda]\n\n\n");
            // Si la ubicacion del item que derrota a esta aldea se encuentra en una mazmorra.
            else if (aldeaActual->derrotadoPor->ubicacion->mazContiene != NULL) printf("[El item que derrota a la mazmorra de %s se encuentra en la mazmorra %d: %s]\n\n\n", aldeaActual->nombre, indiceAldea(aldeaActual->derrotadoPor->ubicacion), aldeaActual->derrotadoPor->ubicacion->nombre);
            // Si no, entonces, la ubicacion del item que derrota a esta aldea se encuentra en una aldea.
            else printf("[El item que derrota a la mazmorra de %s se encuentra en la aldea %d: %s]\n\n\n", aldeaActual->nombre, indiceAldea(aldeaActual->derrotadoPor->ubicacion), aldeaActual->derrotadoPor->ubicacion->nombre);
        }
        // Si en efecto hay objeto oculto.
        else {
            // Si ya lo encontro.
            if (aldeaActual->contiene->encontrado == 1) {
                printf("[Ya has encontrado %s]\n", aldeaActual->contiene->nombre);
                printf("[Este item derrota a la mazmorra de la aldea %d: %s]\n\n\n", indiceAldea(aldeaActual->contiene->derrotaA), aldeaActual->contiene->derrotaA->nombre);
            }
            // Si no lo ha encontrado.
            else {
                aldeaActual->contiene->encontrado = 1;
                printf("[Has encontrado %s]\n", aldeaActual->contiene->nombre);
                printf("[Este item derrota a la mazmorra de la aldea %d: %s]\n\n\n", indiceAldea(aldeaActual->contiene->derrotaA), aldeaActual->contiene->derrotaA->nombre);
            }        
        }
    }
    // Mundo paralelo.
    else {
        // Si no hay objeto en la aldea paralela.
        if (aldeaActualParalela->contiene == NULL) {
            printf("[No hay un objeto en esta aldea]\n");
            // Si es la primera aldea paralela.
            if (aldeaActualParalela->nombre == aldeaParalelaOrigenDePana-> nombre) printf("[El item que derrota a la mazmorra de Shadesmar Luthadel se encuentra en la tienda]\n\n\n");
            // Si la ubicacion del item que derrota a esta aldea paralela se encuentra en una mazmorra.
            else if (aldeaActualParalela->derrotadoPor->ubicacion->mazContiene != NULL) printf("[El item que derrota a la mazmorra de %s se encuentra en la mazmorra %d: %s]\n\n\n", aldeaActualParalela->nombre, indiceAldeaParalela(aldeaActualParalela->derrotadoPor->ubicacion), aldeaActualParalela->derrotadoPor->ubicacion->nombre);
            // Si no, entonces, la ubicacion del item que derrota a esta aldea paralela se encuentra en una aldea paralela.
            else printf("[El item que derrota a la mazmorra de %s se encuentra en la aldea %d: %s]\n\n\n", aldeaActualParalela->nombre, indiceAldeaParalela(aldeaActualParalela->derrotadoPor->ubicacion), aldeaActualParalela->derrotadoPor->ubicacion->nombre);
        }
        // Si en efecto hay objeto oculto.
        else {
            // Si ya lo encontro.
            if (aldeaActualParalela->contiene->encontrado == 1) {
                printf("[Ya has encontrado %s]\n", aldeaActualParalela->contiene->nombre);
                printf("[Este item derrota a la mazmorra de la aldea %d: %s]\n\n\n", indiceAldeaParalela(aldeaActualParalela->contiene->derrotaA), aldeaActualParalela->contiene->derrotaA->nombre);
            }
            // Si no lo ha encontrado.
            else {
                aldeaActualParalela->contiene->encontrado = 1;
                printf("[Has encontrado %s]\n", aldeaActualParalela->contiene->nombre);
                printf("[Este item derrota a la mazmorra de la aldea %d: %s]\n\n\n", indiceAldeaParalela(aldeaActualParalela->contiene->derrotaA), aldeaActualParalela->contiene->derrotaA->nombre);
            }        
        }        
    }
    return;
}


// Funcion para transportar al jugador del mundo normal al mundo paralelo.
void transportar() {
    struct Aldea* temporal;
    struct AldeaParalela* temporalParalela;

    // Si esta en el mundo normal, hay que transportarlo al paralelo.
    if (jugador.paralelo == 0) {
        jugador.paralelo = 1;
        temporalParalela = aldeaParalelaOrigenDePana;

        while (indiceAldeaParalela(temporalParalela) != indiceAldea(aldeaActual)) temporalParalela = temporalParalela->siguiente;

        aldeaActualParalela = temporalParalela;
    }
    // Si esta en el mundo paralelo, hay que transportarlo al normal.
    else {
        jugador.paralelo = 0;
        temporal = aldeaOrigenDePana;

        while (indiceAldea(temporal) != indiceAldeaParalela(aldeaActualParalela)) temporal = temporal-> siguiente;

        aldeaActual = temporal;
    }

    return;
}


// Funcion que retorna el indice de la aldea que se pase por parametro.
int indiceAldea(struct Aldea* aldeaBuscar) {
    int indice = 1;
    struct Aldea* temporal = aldeaOrigenDePana;

    while (temporal != aldeaBuscar) {temporal = temporal->siguiente; indice = indice + 1;}

    return indice;
}


// Funcion que retorna el indice de la aldea paralela que se pase por parametro.
int indiceAldeaParalela(struct AldeaParalela* aldeaBuscar) {
    int indice = 1;
    struct AldeaParalela* temporal = aldeaParalelaOrigenDePana;

    while (temporal != aldeaBuscar) {temporal = temporal->siguiente; indice = indice + 1;}

    return indice;
}


// Funcion para trasladar al jugador a la aldea anterior.
void anteriorAldea() {
    // Mundo normal.
    if (jugador.paralelo == 0) {
        // Si ya esta en la primera aldea, no puede retroceder mas.
        if (aldeaActual->anterior == NULL) printf("[Estas en la primera aldea]\n\n\n");
        else {
            aldeaActual = aldeaActual->anterior;
            dinero = dinero + 10;
            generarAleatorio();
        }
    }
    // Mundo paralelo.
    else {
        // Si ya esta en la primera aldea, no puede retroceder mas.
        if (aldeaActualParalela->anterior == NULL) printf("[Estas en la primera aldea]\n\n\n");
        else {
            aldeaActualParalela = aldeaActualParalela->anterior;
            dinero = dinero + 10;
            generarAleatorio();
        }        
    }

    return;
}


// Funcion para trasladar al jugador a la aldea siguiente.
void siguienteAldea() {
    // Mundo normal.
    if (jugador.paralelo == 0) {
        // Si ya esta en la ultima aldea, no puede seguir avanzando.
        if (aldeaActual->siguiente == NULL) printf("[Estas en la ultima aldea]\n\n\n");
        else {
            aldeaActual = aldeaActual->siguiente;
            dinero = dinero + 10;
            generarAleatorio();
        }
    }
    // Mundo paralelo.
    else {
        // Si ya esta en la ultima aldea paralela, no puede seguir avanzando.
        if (aldeaActualParalela->siguiente == NULL) printf("[Estas en la ultima aldea]\n\n\n");
        else {
            aldeaActualParalela = aldeaActualParalela->siguiente;
            dinero = dinero + 10;
            generarAleatorio();
        }        
    }

    return;
}


// Funcion de la tienda para comprar items
void comprar() {
    char entrada[2];

    while (1) {
        printf("[TIENDA]\n");
        printf("1) Recuperar 1 punto de vida: $5\n");
        // Mundo normal: ofrece el item de la primera aldea del mundo normal.
        if (jugador.paralelo == 0) printf("2) %s: $25\n", aldeaOrigenDePana->derrotadoPor->nombre);
        // Mundo paralelo: ofrece el item de la primera aldea del mundo paralelo.
        else printf("2) %s: $25\n", aldeaParalelaOrigenDePana->derrotadoPor->nombre);
        printf("3) Corazon adicional: $100\n");
        printf("4) Salir\n\n");
        printf("| Corazones:%d | Vida:%d | Dinero:%d |\n", jugador.corazones, jugador.vidas, dinero); 
        printf("Ingresa el numero del item que deseas comprar:\n");

        /* Limpia el bufer. */
        while (getchar() != '\n');

        /* Almacena la entrada por teclado en el arreglo "entrada". */
        scanf("%1s", entrada);

        if (strcmp(entrada, "1") == 0) {
            if(dinero >= 5) {
                if (jugador.vidas < jugador.corazones) {
                    dinero = dinero - 5;
                    jugador.vidas = jugador.vidas + 1;
                    printf("\n\n");
                }
                else printf("\n\n[Ya estas al maximo de vida]\n\n\n");
            }
            else printf("\n\n[No tienes suficiente dinero]\n\n\n");
        }
        else if (strcmp(entrada, "2") == 0) {
            if(dinero >= 25) {
                // Mundo normal.
                if (jugador.paralelo == 0) {
                    if (aldeaOrigenDePana->derrotadoPor->encontrado == 0) {
                        dinero = dinero - 25;
                        aldeaOrigenDePana->derrotadoPor->encontrado = 1;
                        printf("\n\n[Compraste %s]\n", aldeaOrigenDePana->derrotadoPor->nombre);
                        printf("[Este item derrota a la mazmorra de la aldea %d: %s]\n\n\n", indiceAldea(aldeaOrigenDePana->derrotadoPor->derrotaA), aldeaOrigenDePana->derrotadoPor->derrotaA->nombre);
                    } 
                    else printf("\n\n[Ya tienes el objeto]\n\n\n");
                }
                // Mundo paralelo.
                else {
                    if (aldeaParalelaOrigenDePana->derrotadoPor->encontrado == 0) {
                        dinero = dinero - 25;
                        aldeaParalelaOrigenDePana->derrotadoPor->encontrado = 1;
                        printf("\n\n[Compraste %s]\n", aldeaParalelaOrigenDePana->derrotadoPor->nombre);
                        printf("[Este item derrota a la mazmorra de la aldea %d: %s]\n\n\n", indiceAldeaParalela(aldeaParalelaOrigenDePana->derrotadoPor->derrotaA), aldeaParalelaOrigenDePana->derrotadoPor->derrotaA->nombre);
                    }
                    else printf("\n\n[Ya tienes el objeto]\n\n\n");
                }
            }
            else printf("\n\n[No tienes suficiente dinero]\n\n\n");
        }
        else if (strcmp(entrada, "3") == 0) {
            if(dinero >= 100) {
                if (jugador.corazones < 127) {
                    dinero = dinero - 100;
                    jugador.corazones = jugador.corazones + 1;
                    jugador.vidas = jugador.corazones;
                    printf("\n\n");
                }
                else printf("\n\n[Ya tienes la maxima cantidad de corazones]\n\n\n");
            }
            else printf("\n\n[No tienes suficiente dinero]\n\n\n");
        }
        else if (strcmp(entrada, "4") == 0) {printf("\n\n"); return;}
        else printf("\n\n[Opcion no valida]\n\n\n");
    }
}

// Implementacion de: Presiona cualquier tecla para continuar...
// (Ya no lo usamos).
/*printf("Presiona cualquier tecla para continuar...\n"); 
while (getchar() != '\n');
getchar();*/

// Funcion que imprime la mazmorra y el menu de comandos.
void mazmorra() {
    char entrada[5];

    while (1) {
        if (jugador.paralelo == 0) printf("[MAZMORRA %d: %s]\n\n", indiceAldea(aldeaActual), aldeaActual->nombre);
        else printf("[MAZMORRA %d: %s]\n\n", indiceAldeaParalela(aldeaActualParalela), aldeaActualParalela->nombre);
        printf("Comandos disponibles:\n");        
        printf("---------------------------\n| busq | atac | ant | sig |\n----------------------------------\n"); 
        printf("| Corazones:%d | Vida:%d | Dinero:%d |\n", jugador.corazones, jugador.vidas, dinero); 
        printf("----------------------------------\n\n");
        printf("Ingresa un comando:\n");

        /* Almacena la entrada por teclado en el arreglo "entrada". */
        scanf("%5s", entrada);

        /* Convierte todos los caracteres de la entrada en minusculas. */
        for (int i = 0; entrada[i] != '\0'; i++) entrada[i] = tolower(entrada[i]);

        printf("\n\n");

        /* Toda accion en la mazmorra genera un numero aleatorio para determinar si el jugador pierde vida. */
        generarAleatorio();

        if (strcmp(entrada, "busq") == 0) buscarMazmorra();
        else if (strcmp(entrada, "atac") == 0) {
            // Solo para el caso cuando se transporta al mundo paralelo por primera vez.
            if (indiceAldea(aldeaActual) == transportaParalelo && comandoTrans == 0) {atacar(); return;}
            // Todos los demas casos.
            else atacar();
        }
        else if (strcmp(entrada, "ant") == 0) return;
        else if (strcmp(entrada, "sig") == 0) {siguienteAldea(); return;}      
        else printf("[Comando no valido]\n\n\n");
    }
}


// Funcion para buscar el item oculto de la mazmorra o mazmorra paralela.
void buscarMazmorra() {
    // Mundo normal.
    if (jugador.paralelo == 0) {
        // Si ya busco en la mazmorra.
        if (aldeaActual->yaBusco == 1) {printf("[Ya has buscado en esta mazmorra, pierdes 1 punto de vida]\n\n"); jugador.vidas = jugador.vidas - 1; if (jugador.vidas == 0) gameOver();}
        // Si no hay item oculto en la mazmorra.
        if (aldeaActual->mazContiene == NULL) {
            printf("[No hay ningun objeto en esta mazmorra]\n");
            // Si el jugador esta en la primera mazmorra.
            if (aldeaActual->nombre == aldeaOrigenDePana-> nombre) printf("[El item que derrota a la mazmorra de Luthadel se encuentra en la tienda]\n\n\n");
            // Si el item que derrota a la mazmorra esta en una mazmorra.
            else if (aldeaActual->derrotadoPor->ubicacion->mazContiene != NULL) printf("[El item que derrota esta mazmorra se encuentra en la mazmorra %d: %s]\n\n\n", indiceAldea(aldeaActual->derrotadoPor->ubicacion), aldeaActual->derrotadoPor->ubicacion->nombre);
            // Si no, entonces, esta en una aldea.
            else printf("[El item que derrota a esta mazmorra se encuentra en la aldea %d: %s]\n\n\n", indiceAldea(aldeaActual->derrotadoPor->ubicacion), aldeaActual->derrotadoPor->ubicacion->nombre);
        }
        // Si efectivamente hay item oculto.
        else {
            // Si ya lo encontro.
            if (aldeaActual->mazContiene->encontrado == 1) {
                printf("[Ya has encontrado %s]\n", aldeaActual->mazContiene->nombre);
                printf("[Este item derrota a la mazmorra de la aldea %d: %s]\n\n\n", indiceAldea(aldeaActual->mazContiene->derrotaA), aldeaActual->mazContiene->derrotaA->nombre);
            }
            // Si no lo ha encontrado.
            else {
                aldeaActual->mazContiene->encontrado = 1;
                printf("[Has encontrado %s]\n", aldeaActual->mazContiene->nombre);
                printf("[Este item derrota a la mazmorra de la aldea %d: %s]\n\n\n", indiceAldea(aldeaActual->mazContiene->derrotaA), aldeaActual->mazContiene->derrotaA->nombre);
            }        
        }
        aldeaActual->yaBusco = 1;
    }
    // Mundo paralelo.
    else {
        // Si ya busco en la mazmorra paralela.
        if (aldeaActualParalela->yaBusco == 1) {printf("[Ya has buscado en esta mazmorra, pierdes 1 punto de vida]\n\n"); jugador.vidas = jugador.vidas - 1; if (jugador.vidas == 0) gameOver();}
        // Si no hay item oculto en la mazmorra paralela.
        if (aldeaActualParalela->mazContiene == NULL) {
            printf("[No hay ningun objeto en esta mazmorra]\n");
            // Si el jugador esta en la primera mazmorra.
            if (aldeaActualParalela->nombre == aldeaParalelaOrigenDePana-> nombre) printf("[El item que derrota a la mazmorra de Shadesmar Luthadel se encuentra en la tienda]\n\n\n");
            // Si el item que derrota a la mazmorra paralela esta en una mazmorra paralela.
            else if (aldeaActualParalela->derrotadoPor->ubicacion->mazContiene != NULL) printf("[El item que derrota esta mazmorra se encuentra en la mazmorra %d: %s]\n\n\n", indiceAldeaParalela(aldeaActualParalela->derrotadoPor->ubicacion), aldeaActualParalela->derrotadoPor->ubicacion->nombre);
            // Si no, entonces, esta en una aldea paralela.
            else printf("[El item que derrota a esta mazmorra se encuentra en la aldea %d: %s]\n\n\n", indiceAldeaParalela(aldeaActualParalela->derrotadoPor->ubicacion), aldeaActualParalela->derrotadoPor->ubicacion->nombre);
        }
        // Si efectivamente hay item oculto
        else {
            // Si ya lo encontro.
            if (aldeaActualParalela->mazContiene->encontrado == 1) {
                printf("[Ya has encontrado %s]\n", aldeaActualParalela->mazContiene->nombre);
                printf("[Este item derrota a la mazmorra de la aldea %d: %s]\n\n\n", indiceAldeaParalela(aldeaActualParalela->mazContiene->derrotaA), aldeaActualParalela->mazContiene->derrotaA->nombre);
            }
            // Si no lo ha encontrado.
            else {
                aldeaActualParalela->mazContiene->encontrado = 1;
                printf("[Has encontrado %s]\n", aldeaActualParalela->mazContiene->nombre);
                printf("[Este item derrota a la mazmorra de la aldea %d: %s]\n\n\n", indiceAldeaParalela(aldeaActualParalela->mazContiene->derrotaA), aldeaActualParalela->mazContiene->derrotaA->nombre);
            }        
        }
        aldeaActualParalela->yaBusco = 1;        
    }
    return;
}


// Funcion para atacar a una mazmorra.
void atacar() {
    // Mundo normal.
    if (jugador.paralelo == 0) {
        // Si el jugador ya tiene el item que derrota a la aldea.
        if (aldeaActual->derrotadoPor->encontrado == 1) {
            // Si la aldea no ha sido derrotada.
            if (aldeaActual->vencida == 0) {
                jugador.mazmorrasVencidas = jugador.mazmorrasVencidas + 1;
                aldeaActual->vencida = 1;
                printf("[¡Has derrotado a la mazmorra!]\n\n\n");
                // Si el jugador ha derrotado todas las mazmorras, gano el juego.
                if (jugador.mazmorrasVencidas == aldeasTotales) victoria();
                // Si el jugador derrota a la mazmorra que lo transporta al mundo paralelo.
                if (indiceAldea(aldeaActual) == transportaParalelo) {
                    printf("\n[Encuentras un pozo pequeño y de pocos metros de profundidad]\n[Empiezas a sentir unas ligeras pulsaciones]\n[El pozo te llama...]\n[Como hipnotizado, tus pies se mueven y te sumerges en las aguas]\n[Se te bruma la vista y pierdes la consciencia]\n\n\n[Despiertas en un lugar conocido]\n\n\n[Miras a tu alrededor y te das cuenta que estas en Luthadel]\n\n\n[... Pero no es Luthadel]\n\n\n[BIENVENIDO A SHADESMAR]\n\n\n");
                    jugador.paralelo = 1;
                    comandoTrans = 1;
                }
            }
            // Si la aldea ya fue derrotada.
            else printf("[Ya has derrotado a esta mazmorra]\n\n\n");
        }
        // Si el jugador no tiene el item que derrota a la aldea.
        else {
            printf("[No posees el item para derrotar a esta mazmorra]\n[Pierdes 1 punto de vida]\n\n\n");
            jugador.vidas = jugador.vidas - 1; 
            if (jugador.vidas == 0) gameOver();
        }
    }
    // Mundo paralelo.
    else {
        // Si el jugador ya tiene el item que derrota a la aldea paralela.
        if (aldeaActualParalela->derrotadoPor->encontrado == 1) {
            // Si la aldea paralela no ha sido derrotada.
            if (aldeaActualParalela->vencida == 0) {
                jugador.mazmorrasVencidas = jugador.mazmorrasVencidas + 1;
                aldeaActualParalela->vencida = 1;
                printf("[¡Has derrotado a la mazmorra!]\n\n\n");
                // Si el jugador ha derrotado todas las mazmorras, gano el juego.
                if (jugador.mazmorrasVencidas == aldeasTotales) victoria();
            }
            // Si la aldea paralela ya fue derrotada.
            else printf("[Ya has derrotado a esta mazmorra]\n\n\n");
        }
        // Si el jugador no tiene el item que derrota a la aldea paralela.
        else {
            printf("[No posees el item para derrotar a esta mazmorra]\n[Pierdes 1 punto de vida]\n\n\n");
            jugador.vidas = jugador.vidas - 1; 
            if (jugador.vidas == 0) gameOver();
        }        
    }

    return;
}


// Funcion que genera un numero aleatorio y determina si el jugador pierde vida.
// Si la vida llega a 0, pierde.
void generarAleatorio() {
    aleatorio = rand();
    if (aleatorio % 2 != 0) {
        jugador.vidas = jugador.vidas - 1;
        printf("[Has perdido 1 punto de vida]\n\n\n");
        if (jugador.vidas == 0) gameOver();
    }
    return;
}


// Funcion para cuando el jugador muere.
void gameOver() {
    printf("[Y en un abrir y cerrar de ojos el mundo cambio]\n[Tu mundo]\n\n\n[A tu lado se encuentra alguien de pie observandote]\n[No lo conoces, pero comprendes de quien se trata]\n\n\n'...Has muerto.'\n");
    exit(0);
}


// Funcion para cuando el jugador gana.
void victoria() {
    printf("\n[¡Has derrotado a todas las mazmorras!]\n\n[Gracias a ti el mundo ha sobrevivido a la ruina]\n[Ahora a descansar, por fin]\n\n\n\n[CREDITOS]\n\nIdea original: Prof. Fernando Torre Mora\nDireccion: Alejandro De Vincenzo y Leonardo Dolande\nProgramadores: Alejandro De Vincenzo y Leonardo Dolande\nDireccion de arte: Leonardo Dolande\nBanda sonora: Alejandro De Vincenzo\nDiseño de niveles: Leonardo Dolande\nNarrador: Leonardo Dolande\nTraduccion al español: Alejandro De Vincenzo\nTraduccion al japones: Alejandro De Vincenzo\n");
    exit(0);    
}


// Funcion que imprime la ubicacion de todos los items e items paralelos.
void imprimirUbicaciones() {
    struct Aldea* temporal = aldeaOrigenDePana;
    struct AldeaParalela* temporalParalela = aldeaParalelaOrigenDePana;

    while (temporal != NULL) {
        printf("[Aldea %s]: %s\n[Mazmorra %s]: %s\n\n", 
            temporal->nombre, 
            (temporal->contiene != NULL) ? temporal->contiene->nombre : "Sin item",
            temporal->nombre, 
            (temporal->mazContiene != NULL) ? temporal->mazContiene->nombre : "Sin item");

        temporal = temporal->siguiente;
    }

    printf("\n\n");

    while (temporalParalela != NULL) {
        printf("[Aldea %s]: %s\n[Mazmorra %s]: %s\n\n", 
            temporalParalela->nombre, 
            (temporalParalela->contiene != NULL) ? temporalParalela->contiene->nombre : "Sin item",
            temporalParalela->nombre, 
            (temporalParalela->mazContiene != NULL) ? temporalParalela->mazContiene->nombre : "Sin item");

        temporalParalela = temporalParalela->siguiente;
    }    

    printf("\n\n");
    return;
}


// Funcion que imrpime una lista con todas las aldeas seguidas de 0 (no derrotada) o 1 (derrotada).
// Sirve para saber que aldeas ya fueron derrotadas.
void aldeasDerrotadas() {
    struct Aldea* temporal = aldeaOrigenDePana;
    struct AldeaParalela* temporalParalela = aldeaParalelaOrigenDePana;

    while (temporal != NULL) {
        printf("[Aldea %s]: %d\n\n",temporal->nombre, temporal->vencida);
        temporal = temporal->siguiente;
    }

    printf("\n\n");

    while (temporalParalela != NULL) {
        printf("[Aldea %s]: %d\n\n",temporalParalela->nombre, temporalParalela->vencida);
        temporalParalela = temporalParalela->siguiente;
    }    

    printf("\n\n");
    return;
}


// Funcion main desde donde inicia el programa.
int main(){
    inicializar();
    aldea();
    return 0;
}