#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdlib>

struct Tarea {
    int TareaID; //Numerado en ciclo iterativo
    char *Descripcion; //
    int Duracion; // entre 10 – 100
}; 

void cargar_tareas(Tarea * TareasPendientes,int cantTareas);
void realizar_tareas(Tarea * TareasPendientes,Tarea * TareasRealizadas,int cantTareas);
void mostrar_tareas(Tarea * TareasPendientes,Tarea * TareasRealizadas,int cantTareas);
Tarea BuscarTarea(Tarea * TareasPendientes,Tarea * TareasRealizadas,int cantTareas);
Tarea BuscarTareaID(Tarea * TareasPendientes,Tarea * TareasRealizadas,int cantTareas);

int main() {
    int cantTareas;
    Tarea Resultado;
    Tarea ResultadoID;
    
    printf("Cuantas tareas desea cargar?: ");
    scanf("%d",&cantTareas);
    system("cls");

    Tarea * TareasPendientes = (Tarea *) malloc(sizeof(Tarea)*cantTareas);
    Tarea * TareasRealizadas = (Tarea *) malloc(sizeof(Tarea)*cantTareas);

    cargar_tareas(TareasPendientes,cantTareas);
    realizar_tareas(TareasPendientes,TareasRealizadas,cantTareas);
    mostrar_tareas(TareasPendientes,TareasRealizadas,cantTareas);

    printf("---------------BUSCAR TAREAS---------------\n\n");

    ResultadoID = BuscarTareaID(TareasPendientes,TareasRealizadas,cantTareas);
    if (ResultadoID.TareaID == 0){
        printf("No se encontró el ID");
    }else{
        printf("\nTarea ID: %d \n", ResultadoID.TareaID);
		printf("Descripción: \"%s\"\n", ResultadoID.Descripcion);
		printf("Duración: %d\n\n", ResultadoID.Duracion);
    }
    getchar();
}

void cargar_tareas(Tarea * TareasPendientes,int cantTareas){
    for (int i = 0; i < cantTareas; i++)
    {
        char descripcion[60];
        int duracion = 0;

        printf("Tarea #%d\n", i+1);
        TareasPendientes->TareaID = i + 1;

        printf("Descripcion: ");
        fflush(stdin);
        gets(descripcion);
        TareasPendientes->Descripcion = (char*)malloc(sizeof(descripcion)*(strlen(descripcion)));
        strcpy(TareasPendientes->Descripcion,descripcion);

        do
        {
            printf("Duración: ");
            scanf("%d",&duracion);
        } while (duracion < 10 || duracion > 100);
        TareasPendientes->Duracion = duracion;
        system("cls");
        TareasPendientes++;
    }   
}

void realizar_tareas(Tarea * TareasPendientes,Tarea * TareasRealizadas,int cantTareas){
    int aux;
    for (int i = 0; i < cantTareas; i++)
    {
        printf("Esta tarea esta realizada?\n\n");
        printf("Tarea ID: %d\n", TareasPendientes->TareaID);
        printf("Descripcion: \"%s\"\n", TareasPendientes->Descripcion);
        printf("Duracion: %d\n\n", TareasPendientes->Duracion);
        do
        {
            printf("1 / 0 (Si / No): ");
            scanf("%d",&aux);
        } while (aux != 0 && aux != 1);
        if (aux == 1)
        {
            *TareasRealizadas = *TareasPendientes;
            TareasPendientes->TareaID = 0;
        }else
        {
            TareasRealizadas->TareaID = 0;
        }
        system("cls");
        TareasPendientes++;
        TareasRealizadas++;
    }
}

void mostrar_tareas(Tarea * TareasPendientes,Tarea * TareasRealizadas, int cantTareas){
    printf("---------------TAREAS REALIZADAS---------------\n\n");
	for(int i = 0; i < cantTareas; i++){
		if(TareasRealizadas->TareaID != 0){
			printf("Tarea ID: %d \n", TareasRealizadas->TareaID);
			printf("Descripcion: \"%s\"\n", TareasRealizadas->Descripcion);
			printf("Duracion: %d\n\n", TareasRealizadas->Duracion);
		}
		TareasRealizadas++;
	}
    printf("---------------TAREAS PENDIENTES---------------\n\n");
    for (int i = 0; i < cantTareas; i++)
    {
        if (TareasPendientes->TareaID != 0){
            printf("Tarea ID: %d \n", TareasPendientes->TareaID);
		    printf("Descripcion: \"%s\"\n", TareasPendientes->Descripcion);
		    printf("Duracion: %d\n\n", TareasPendientes->Duracion);
        }
        TareasPendientes++;
    }  
}



//nuevo branch
Tarea BuscarTareaID(Tarea * TareasPendientes,Tarea * TareasRealizadas,int cantTareas){
    int id;
    printf("\nIngresar ID: ");
    scanf("%d", &id);
    for (int i = 0; i < cantTareas; i++)
    {
        if (TareasPendientes->TareaID == id)
        {
            return *TareasPendientes;
        }
        else if (TareasRealizadas->TareaID == id)
        {
            return *TareasRealizadas;
        }
        TareasRealizadas++;
        TareasPendientes++;
    }
    Tarea Sin;
    Sin.TareaID = 0;
    return Sin;
}