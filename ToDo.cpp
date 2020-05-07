#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Tarea{
    int TareaID;
    char * Descripcion;
    int Duracion;
}; 

void cargar_tareas(Tarea ** tareas_pendientes, int cantidad_tareas);
void separar_tareas(Tarea ** tareas_pendientes, Tarea ** tareas_realizadas, int cantidad_tareas);
void mostrar_tareas(Tarea ** tareas, int cantidad_tareas);
Tarea BusquedaPorID(Tarea ** tareas_pendientes, Tarea ** tareas_realizadas, int cantidad_tareas);
Tarea BusquedaPorPalabra(Tarea ** tareas_pendientes, Tarea ** tareas_realizadas, int cantidad_tareas);
void Busqueda(Tarea ** tareas_pendientes, Tarea ** tareas_realizadas, int cantidad_tareas);

int main(){
    srand(time(NULL));
    int cantidad_tareas;
        
    printf("Numero de tareas a cargar: ");
    scanf("%d", &cantidad_tareas);
    system("cls");

    Tarea **tareas_realizadas = (Tarea **) malloc(sizeof(Tarea *) * cantidad_tareas);
    Tarea **tareas_pendientes = (Tarea **) malloc(sizeof(Tarea *) * cantidad_tareas);
    
    cargar_tareas(tareas_pendientes, cantidad_tareas);
    separar_tareas(tareas_pendientes, tareas_realizadas, cantidad_tareas);
    
    printf("---------------TAREAS REALIZADAS---------------\n\n");
    mostrar_tareas(tareas_realizadas, cantidad_tareas);
    printf("---------------TAREAS PENDIENTES---------------\n\n");
    mostrar_tareas(tareas_pendientes, cantidad_tareas);
    
    Tarea Buscar1;
    printf("---------------BUSQUEDA POR ID---------------\n\n");
    BusquedaPorID(tareas_pendientes, tareas_realizadas, cantidad_tareas);
        
    Tarea Buscar2;
    printf("---------------BUSQUEDA POR PALABRA---------------\n\n");
    BusquedaPorPalabra(tareas_pendientes, tareas_realizadas, cantidad_tareas);
    
    getchar();
}

void cargar_tareas(Tarea ** tareas_pendientes, int cantidad_tareas){
    for (int i = 0; i < cantidad_tareas; i++)
    {
        char descripcion[60];
        tareas_pendientes[i] = (Tarea *) malloc(sizeof(Tarea));
        printf("Tarea #%d\n", i+1);
        tareas_pendientes[i]->TareaID = i+1;
        printf("Descripcion: ");
        fflush(stdin);
        gets(descripcion);
        tareas_pendientes[i]->Descripcion = (char *)malloc(sizeof(descripcion) * (strlen(descripcion)));
        strcpy(tareas_pendientes[i]->Descripcion, descripcion);
        tareas_pendientes[i]->Duracion = rand() % 91 + 10;;
        system("cls");
        tareas_pendientes++;
    }   
}

void separar_tareas(Tarea **tareas_pendientes, Tarea **tareas_realizadas, int cantidad_tareas){
    int aux;
    for (int i = 0; i < cantidad_tareas; i++){
        printf("Tarea ID: %d\n", tareas_pendientes[i]->TareaID);
        printf("Descripcion: \"%s\"\n", tareas_pendientes[i]->Descripcion);
        printf("Duracion: %d\n\n", tareas_pendientes[i]->Duracion);
        do{
            printf("Esta tarea esta realizada?\n");
            printf("Presone 1(SI) o 0(NO): ");
            scanf("%d",&aux);
        } while (aux != 0 && aux != 1);
        
        if (aux == 1){
            tareas_realizadas[i] = (Tarea *) malloc(sizeof(Tarea));
            tareas_realizadas[i] = tareas_pendientes[i];
            tareas_pendientes[i] = NULL;
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