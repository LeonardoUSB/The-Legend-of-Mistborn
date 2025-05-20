#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int potencia(int base, int exponente){
    int resultado=1;
    for (int i = 0; i < exponente; i++)
    {
        resultado*=base;
    }
    return resultado;
}

struct Aldea
{
    char* nombre;
    struct Aldea* siguiente;
    struct Aldea* anterior;
    struct Item* derrotadoPor;
    struct Item* contiene;
    struct Item* mazContiene;
    int yaBusco;

};

void creaNombresAldea(struct Aldea* cabeza,char**nombres,char**nuevosNombres,int tamNuevos,int profundidad){
    struct Aldea* siguiente= cabeza;

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
    
    creaNombresAldea(siguiente,nombres,combinaciones,numCombinaciones, profundidad );

    for (int i = 0; i < numCombinaciones; i++) {
        free(combinaciones[i]);
    }
    free(combinaciones);
}

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

struct AldeaParalela
{
    char* nombre;
    struct Aldea* siguiente;
    struct Aldea* anterior;
    struct Item* derrotadoPor;
    struct Item* contiene;
    struct Item* mazContiene;
    int yaBusco;
};

void creaNombresAldeaAlter(struct AldeaParalela* cabeza,char**nombres,char**nuevosNombres,int tamNuevos,int profundidad){
    struct AldeaParalela* siguiente= cabeza;

    for (int i = 0; i < tamNuevos; i++)
    {
        siguiente->nombre=malloc(profundidad*25*sizeof(char));
        strcpy(siguiente->nombre, "Dark ");
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

struct Item
{
    char* nombre;
    struct Item* siguiente;
    struct Item* anterior;
    int encontrado;
    struct Aldea* ubicacion;
    struct Aldea* derrotaA;
};


void creaItems(struct Item* cabeza,char**nombres,char**nuevosNombres,int tamNuevos,int profundidad){
    struct Item* siguiente= cabeza;

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

struct ItemParalelo
{
    char* nombre;
    struct Item* siguiente;
    struct Item* anterior;
    int encontrado;
    struct Aldea* ubicacion;
    struct Aldea* derrotaA;
};

void creaItemsAlter(struct ItemParalelo* cabeza,char**nombres,char**nuevosNombres,int tamNuevos,int profundidad){
    struct ItemParalelo* siguiente= cabeza;

    for (int i = 0; i < tamNuevos; i++)
    {
        siguiente->nombre=malloc(profundidad*25*sizeof(char));
        strcpy(siguiente->nombre, "Dark ");
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

struct Jugador
{
    int vidas;
    struct Aldea*ubicacion;
    int estado;
};


struct Aldea* encontrarAldea(struct  Aldea* AldeaIni, struct  Aldea* cabeza, struct  Item* ItemIni, int* cont){
    struct Aldea* AldeaSig=AldeaIni;
    if (AldeaSig==NULL)
    {
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

void ubicaTodo(struct Aldea* cabeza,struct Item* ItemIni, int numAldeas){
    struct Aldea* aldeaSig=cabeza;
    struct Item* itemSig=ItemIni;
    int random;
    int cont=0;
    while(cont<numAldeas){
        random=rand();
        aldeaSig=encontrarAldea(aldeaSig,cabeza, itemSig,&cont);
        
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
                aldeaSig->contiene=itemSig;
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

void derrotaTodo(struct Aldea* cabeza,struct Item* ItemIni, int numAldeas){
    struct Aldea* aldeaSig=cabeza;
    struct Item* itemSig=ItemIni;
    struct Aldea** punAldea=&aldeaSig;
    int random;
    int cont=0;
    //int i=0;
    while(cont<numAldeas){
        random=rand();
        //int num[]={1724200880,819850994,1019632478,34542735,360296537,568650271,1228424318,};
        //random=num[i];
        //i++;
        //printf("%d\n", random);
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

/*
void ubicaTodoAlter(struct AldeaParalela* cabeza, struct ItemParalelo* ItemIni ,int numAldeas){
    struct AldeaParalela* aldeaSig=cabeza;
    struct ItemParalelo* itemSig=ItemIni;
    int random;
    int cont=0;
    while(cont<numAldeas){
        random=rand();
        aldeaSig=encontrarAldea(aldeaSig,cabeza, itemSig,&cont);
        
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
                aldeaSig->contiene=itemSig;
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
};
*/

void imprimeTodo(struct Aldea* cabeza, struct AldeaParalela* cabeazaAlter, struct Item* ItemIni,  struct ItemParalelo* ItemIniAlter){
    struct Aldea* siguiente= cabeza;
    while(siguiente !=NULL){
        //printf("%s\n", siguiente->nombre);
        siguiente=siguiente->siguiente;
    }
    
    struct AldeaParalela* siguienteAlter= cabeazaAlter;
    while(siguienteAlter !=NULL){
        //printf("%s\n", siguienteAlter->nombre);
        siguienteAlter=siguienteAlter->siguiente;
    }

    struct Item* siguienteItem= ItemIni;
    int i=0;
    printf("%s\n", "Modo Impresion");   
    while(siguienteItem !=NULL){
        
        printf("%d\n",i );
        printf("%s\n", siguienteItem->nombre);
        printf("%s\n", siguienteItem->derrotaA->nombre);
        siguienteItem=siguienteItem->siguiente;
        i++;
    }

    struct ItemParalelo* siguienteItemAlter= ItemIniAlter;
    while(siguienteItemAlter !=NULL){
        //printf("%s\n", siguienteItemAlter->nombre);
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
    

    char**nomAldeas=malloc(16 * sizeof(char*));
    for (int i = 0; i < 16; i++)
    {
        nomAldeas[i]=malloc(15 * sizeof(char));
    }
    strcpy(nomAldeas[0], "Luthadel");
    strcpy(nomAldeas[1], "Elendel");
    strcpy(nomAldeas[2], "Rochelle");
    strcpy(nomAldeas[3], "Fadrex");
    strcpy(nomAldeas[4], "Urbain");
    strcpy(nomAldeas[5], "Doxonar");
    strcpy(nomAldeas[6], "Tathingdwen");
    strcpy(nomAldeas[7], "Rendoux");
    strcpy(nomAldeas[8], "Dryport");
    strcpy(nomAldeas[9], "Seran");
    strcpy(nomAldeas[10], "Zincell");
    strcpy(nomAldeas[11], "Murthel");
    strcpy(nomAldeas[12], "Southern");
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
    strcpy(nomAldeas[10], "Cromo");
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

    //ubicaTodoAlter(aldeaParalelaOrigen,itemParaleloOrigen,numAldeas);
    //derrotaTodoAlter(aldeaParalelaOrigen,itemParaleloOrigen,numAldeas);
    imprimeTodo(aldeaOrigen, aldeaParalelaOrigen, itemOrigen, itemParaleloOrigen);

    


    
}


int main(){
    inicializar();
}

