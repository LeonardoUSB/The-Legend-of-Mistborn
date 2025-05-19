# include <stdio.h>
# include <string.h>
# include <stdlib.h>

int dinero = 0;
int aldeaActual = 1;
int mazmorraActual;
int aleatorio;
int corazones = 3;
int vida = 3;

void comprar(); void anteriorAldea(); void siguienteAldea(); void gameOver(); void mazmorra(); void generarAleatorio();

void aldea() {
    int i;
    char entrada[6];

    while (1) {
        printf("\nBienvenido a la aldea %d\n\n", aldeaActual);
        printf("Comandos disponibles:\n");
        /* Aqui en el if debe ir la condicion de que se imprime la lista de comandos incluyendo "trans" solo si
        El jugador ya derrotó la mazmorra que le permite transportarse al mundo paralelo. */
        if (15 > 70) printf("------------------------------------------\n| busq | maz | compr | trans | ant | sig |\n------------------------------------------\n\n");
        else {printf("----------------------------------\n| busq | maz | compr | ant | sig |\n----------------------------------\n"); printf("| Corazones:%d | Vida:%d | Dinero:%d |\n", corazones, vida, dinero); printf("----------------------------------\n\n");}
        printf("Ingrese un comando:\n");

        /* Almacena la entrada por teclado en el arreglo "entrada". */
        scanf("%6s", entrada);

        /* Convierte todos los caracteres de la entrada en minusculas. */
        for (i = 0; entrada[i] != '\0'; i++) entrada[i] = tolower(entrada[i]);

        if (strcmp(entrada, "busq") == 0) {
            printf("[Escogiste el comando de busqueda]\n");
            return;
        }
        else if (strcmp(entrada, "maz") == 0) {mazmorraActual = aldeaActual; mazmorra();}
        else if (strcmp(entrada, "compr") == 0) comprar();
        else if (strcmp(entrada, "trans") == 0 && 70>15) {
            printf("[Escogiste el comando de transportar]\n");
            return;
        }
        else if (strcmp(entrada, "ant") == 0) anteriorAldea();
        else if (strcmp(entrada, "sig") == 0) siguienteAldea();
        else if (strcmp(entrada, "+") == 0) dinero = dinero + 100;
        else if (strcmp(entrada, "-") == 0) dinero = 0;            
        else printf("\n[Comando no valido]\n\n");
    }
}

void anteriorAldea() {
    if (aldeaActual == 1) printf("\n[Estas en la primera aldea]\n\n");
    else {
        aldeaActual = aldeaActual - 1;
        dinero = dinero + 10;
        generarAleatorio();
    }

    return;
}

void siguienteAldea() {
    if (aldeaActual == 10) printf("\n[Estas en la ultima aldea]\n\n");
    else {
        aldeaActual = aldeaActual + 1;
        dinero = dinero + 10;
        generarAleatorio();
    }

    return;
}

void comprar() {
    char entrada[2];

    while (1) {
        printf("\n[TIENDA]\n");
        printf("1) Recuperar 1 punto de vida: $5\n");
        printf("2) Espada desafilada: $25\n");
        printf("3) Corazon adicional: $100\n");
        printf("4) Salir\n\n");
        printf("Dinero actual: $%d\n", dinero);
        printf("Ingrese el numero del item que desee comprar:\n");

        /* Limpia el bufer. */
        while (getchar() != '\n');

        /* Almacena la entrada por teclado en el arreglo "entrada". */
        scanf("%1s", entrada);

        if (strcmp(entrada, "1") == 0) {
            if(dinero >= 5) {if (vida < corazones) {dinero = dinero - 5; vida = vida + 1; printf("\nVida actual: %d\n\n", vida); printf("Presiona cualquier tecla para continuar...\n"); while (getchar() != '\n'); getchar();} else {printf("\n[Ya estas al maximo de vida]\n\n"); printf("Presiona cualquier tecla para continuar...\n"); while (getchar() != '\n'); getchar();}}
            else {printf("\n[No tienes suficiente dinero]\n\n"); printf("Presiona cualquier tecla para continuar...\n"); while (getchar() != '\n'); getchar();}
        }
        else if (strcmp(entrada, "2") == 0) {
            if(dinero >= 25) {dinero = dinero - 25; printf("\n[Compraste la espada desafilada]\n\n"); printf("Presiona cualquier tecla para continuar...\n"); while (getchar() != '\n'); getchar();}
            else {printf("\n[No tienes suficiente dinero]\n\n"); printf("Presiona cualquier tecla para continuar...\n"); while (getchar() != '\n'); getchar();}
        }
        else if (strcmp(entrada, "3") == 0) {
            if(dinero >= 100) {if (corazones < 127) {dinero = dinero - 100; corazones = corazones + 1; vida = corazones; printf("\nCorazones actuales: %d\n\n", corazones); printf("Presiona cualquier tecla para continuar...\n"); while (getchar() != '\n'); getchar();} else {printf("\n[Ya tienes la maxima cantidad de corazones]\n\n"); printf("Presiona cualquier tecla para continuar...\n"); while (getchar() != '\n'); getchar();}}
            else {printf("\n[No tienes suficiente dinero]\n\n"); printf("Presiona cualquier tecla para continuar...\n"); while (getchar() != '\n'); getchar();}
        }
        else if (strcmp(entrada, "4") == 0) return;
        else {printf("\n[Opcion no valida]\n\n"); printf("Presiona cualquier tecla para continuar...\n"); while (getchar() != '\n'); getchar();}
    }
}

void mazmorra() {
    int i;
    char entrada[5];

    while (1) {
        printf("\nBienvenido a la mazmorra %d\n\n", mazmorraActual);
        printf("Comandos disponibles:\n");        
        printf("----------------------------------\n| busq | atac | ant | sig |\n----------------------------------\n"); 
        printf("| Corazones:%d | Vida:%d | Dinero:%d |\n", corazones, vida, dinero); 
        printf("----------------------------------\n\n");
        printf("Ingrese un comando:\n");

        /* Almacena la entrada por teclado en el arreglo "entrada". */
        scanf("%5s", entrada);

        /* Convierte todos los caracteres de la entrada en minusculas. */
        for (i = 0; entrada[i] != '\0'; i++) entrada[i] = tolower(entrada[i]);

        /* Toda accion en la mazmorra genera un numero aleatorio para determinar si el jugador pierde vida. */
        generarAleatorio();

        if (strcmp(entrada, "busq") == 0) {
            printf("[Escogiste el comando de busqueda]\n");
            return;
        }
        else if (strcmp(entrada, "atac") == 0) {
            printf("[Escogiste el comando de atacar]\n");
            return;
        }
        else if (strcmp(entrada, "ant") == 0) return;
        else if (strcmp(entrada, "sig") == 0) {siguienteAldea(); return;}      
        else printf("\n[Comando no valido]\n\n");
    }
}

void generarAleatorio() {
    aleatorio = random();
    if (aleatorio % 2 != 0) {
        vida = vida - 1;
        printf("\n[Has perdido 1 punto de vida]\n\n");
        if (vida == 0) gameOver();
    }
    return;
}

void gameOver() {
    printf("\nTE HAS MORIDO\n");
    exit(0);
}

int main() {

    aldea();

    return 0;
}