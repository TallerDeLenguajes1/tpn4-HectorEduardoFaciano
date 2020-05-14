#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Tarea{
    int TareaID;
    char * Descripcion;
    int Duracion;
}Tarea;

typedef struct Nodo{
    Tarea T​;
    Nodo * Siguiente; // Siguiente Nodo.
}Nodo;

void cargar_tareas(Tarea ** tareas_pendientes, int cantidad_tareas);
void separar_tareas(Tarea ** tareas_pendientes, Tarea ** tareas_realizadas, int cantidad_tareas);
void mostrar_tareas(Tarea ** tareas, int cantidad_tareas);
Tarea BusquedaPorID(Tarea ** tareas_pendientes, Tarea ** tareas_realizadas, int cantidad_tareas);
Tarea BusquedaPorPalabra(Tarea ** tareas_pendientes, Tarea ** tareas_realizadas, int cantidad_tareas);
void Busqueda(Tarea ** tareas_pendientes, Tarea ** tareas_realizadas, int cantidad_tareas);

Nodo *CrearNodo(Tarea *tareas_pendientes){
    Nodo *nodo = (Nodo *) malloc(sizeof(Nodo));
    nodo->T​.TareaID = tareas_pendientes->TareaID; 
    nodo->T​.Descripcion = tareas_pendientes->Descripcion;
    nodo->T​.Duracion = tareas_pendientes->Duracion;
    nodo->Siguiente = NULL;
    return nodo;
}

int main(){
    srand(time(NULL));
    int cantidad_tareas;
        
    printf("Numero de tareas a cargar: ");
    scanf("%d", &cantidad_tareas);
    system("cls");

    Tarea **tareas_realizadas = (Tarea **) malloc(sizeof(Tarea *) * cantidad_tareas);
    Tarea **tareas_pendientes = (Tarea **) malloc(sizeof(Tarea *) * cantidad_tareas);
    
    CrearNodo(*tareas_pendientes);
    cargar_tareas(tareas_pendientes, cantidad_tareas);
    separar_tareas(tareas_pendientes, tareas_realizadas, cantidad_tareas);
    
    printf("---------------TAREAS REALIZADAS---------------\n\n");
    Nodo *nodo_realizadas = (Nodo *)malloc(sizeof(Nodo) * cantidad_tareas);
    while (nodo_realizadas != NULL){
        printf("Tarea ID: %d\n", nodo_realizadas->T​.TareaID);
        printf("Descripcion: \"%s\"\n", nodo_realizadas->T​.Descripcion);
        printf("Duracion: %d\n\n", nodo_realizadas->T​.Duracion);
    }
    //mostrar_tareas(tareas_realizadas, cantidad_tareas);
    printf("---------------TAREAS PENDIENTES---------------\n\n");
    Nodo *nodo_pendientes = (Nodo *)malloc(sizeof(Nodo) * cantidad_tareas);
    while (nodo_pendientes != NULL){
        printf("Tarea ID: %d\n", nodo_pendientes->T​.TareaID);
        printf("Descripcion: \"%s\"\n", nodo_pendientes->T​.Descripcion);
        printf("Duracion: %d\n\n", nodo_pendientes->T​.Duracion);
    }
    //mostrar_tareas(tareas_pendientes, cantidad_tareas);
    
    Tarea Buscar1;
    printf("---------------BUSQUEDA POR ID---------------\n\n");
    BusquedaPorID(tareas_pendientes, tareas_realizadas, cantidad_tareas);
        
    Tarea Buscar2;
    printf("---------------BUSQUEDA POR PALABRA---------------\n\n");
    BusquedaPorPalabra(tareas_pendientes, tareas_realizadas, cantidad_tareas);
    
    getchar();
}

void cargar_tareas(Tarea ** tareas_pendientes, int cantidad_tareas){
    Nodo *nodo_pendientes = CrearNodo(*tareas_pendientes);
    for (int i = 0; i < cantidad_tareas; i++)
    {
        char descripcion[60];
        tareas_pendientes[i] = (Tarea *) malloc(sizeof(Tarea));
        printf("Tarea #%d\n", i+1);
        nodo_pendientes->T​.TareaID = i+1;
        printf("Descripcion: ");
        fflush(stdin);
        gets(descripcion);
        nodo_pendientes->T​.Descripcion = (char *)malloc(sizeof(descripcion) * (strlen(descripcion)));
        strcpy(nodo_pendientes->T​.Descripcion, descripcion);
        nodo_pendientes->T​.Duracion = rand() % 91 + 10;;
        system("cls");
        tareas_pendientes++;
    }   
}

void separar_tareas(Tarea **tareas_pendientes, Tarea **tareas_realizadas, int cantidad_tareas){
    int aux;
    Nodo *nodo_pendientes = CrearNodo(*tareas_pendientes);
    for (int i = 0; i < cantidad_tareas; i++){
        printf("Tarea ID: %d\n", nodo_pendientes->T​.TareaID);
        printf("Descripcion: \"%s\"\n", nodo_pendientes->T​.Descripcion);
        printf("Duracion: %d\n\n", nodo_pendientes->T​.Duracion);
        do{
            printf("Esta tarea esta realizada?\n");
            printf("Presone 1(SI) o 0(NO): ");
            scanf("%d",&aux);
        } while (aux != 0 && aux != 1);

        Nodo *nodo_pendientes = CrearNodo(*tareas_pendientes);
        Nodo *nodo_realizadas = CrearNodo(*tareas_realizadas);
        if (aux == 1){
            tareas_realizadas[i] = (Tarea *) malloc(sizeof(Tarea));
        //
            if (tareas_realizadas[i] == NULL){
                nodo_realizadas->T​.TareaID = nodo_pendientes->T​.TareaID;
                nodo_realizadas->T​.Descripcion = nodo_pendientes->T​.Descripcion;
                nodo_realizadas->T​.Duracion = nodo_pendientes->T​.Duracion;
            }else{
                while (nodo_pendientes->Siguiente){
                    nodo_pendientes = nodo_pendientes->Siguiente;
                } 
                nodo_pendientes->Siguiente = nodo_pendientes;
            }
            tareas_pendientes[i] = NULL;
        //
        }else{
            tareas_realizadas[i] = NULL;
        }
        printf("Clasificacion de Tareas Finalizado\n");
        system("cls");
        tareas_pendientes++;
        tareas_realizadas++;
    }
}

void mostrar_tareas(Tarea **tarea, int cantidad_tareas){

	for(int i = 0; i < cantidad_tareas; i++){
		if(tarea[i]){
			printf("Tarea ID: %d \n", tarea[i]->TareaID);
			printf("Descripcion: %s\n", tarea[i]->Descripcion);
			printf("Duracion: %d\n\n", tarea[i]->Duracion);
		}
        tarea++;
	}
}

Tarea BusquedaPorID(Tarea **tareas_pendientes, Tarea **tareas_realizadas, int cantidad_tareas){
    int id;
    printf("\nIngresar ID: ");
    scanf("%d", &id);
    for (int i = 0; i < cantidad_tareas; i++){
        if (tareas_pendientes[i] && tareas_pendientes[i]->TareaID == id){
            printf("La tarea esta pendiende\n", id);
            printf("Tarea ID: %d \n", tareas_pendientes[i]->TareaID);
			printf("Descripcion: %s\n", tareas_pendientes[i]->Descripcion);
			printf("Duracion: %d\n\n", tareas_pendientes[i]->Duracion);
            Tarea vacio;
            vacio.TareaID = 0;
            return vacio;
        }else if (tareas_realizadas[i] && tareas_realizadas[i]->TareaID == id){
            printf("La tarea esta realizada\n", id);
            printf("Tarea ID: %d \n", tareas_realizadas[i]->TareaID);
			printf("Descripcion: %s\n", tareas_realizadas[i]->Descripcion);
			printf("Duracion: %d\n\n", tareas_realizadas[i]->Duracion);
            Tarea vacio;
            vacio.TareaID = 0;
            return vacio;
        }
        tareas_realizadas++;
        tareas_pendientes++;
    }
    printf("No se encontraron coincidencias");
    return BusquedaPorID(tareas_pendientes, tareas_realizadas, cantidad_tareas);
}

Tarea BusquedaPorPalabra(Tarea **tareas_pendientes, Tarea **tareas_realizadas, int cantidad_tareas) {
    char palabra[60];
    printf("\nIngresar palabra clave: ");
    fflush(stdin);
    gets(palabra);
    
    for (int i = 0; i < cantidad_tareas; i++) {
        if (tareas_pendientes[i] && strcmp(tareas_pendientes[i]->Descripcion, palabra) == 0){
            printf("La tarea esta pendiende\n");
            printf("Tarea ID: %d \n", tareas_pendientes[i]->TareaID);
			printf("Descripcion: %s\n", tareas_pendientes[i]->Descripcion);
			printf("Duracion: %d\n\n", tareas_pendientes[i]->Duracion);
            Tarea vacio;
            vacio.TareaID = 0;
            return vacio;
        }else if (tareas_realizadas[i] && strcmp(tareas_realizadas[i]->Descripcion, palabra) == 0){
            printf("La tarea esta realizada\n");
            printf("Tarea ID: %d \n", tareas_realizadas[i]->TareaID);
			printf("Descripcion: %s\n", tareas_realizadas[i]->Descripcion);
			printf("Duracion: %d\n\n", tareas_realizadas[i]->Duracion);
            Tarea vacio;
            vacio.TareaID = 0;
            return vacio;
        }
        tareas_realizadas++;
        tareas_pendientes++;
    }
    printf("No se encontraron coincidencias");
    return BusquedaPorPalabra(tareas_pendientes, tareas_realizadas, cantidad_tareas);
}
