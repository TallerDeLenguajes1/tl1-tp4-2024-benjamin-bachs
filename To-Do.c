#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    int TareaID;//Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion; // entre 10 – 100
} Tarea;
typedef struct Nodo Nodo;
struct Nodo{
    Tarea T;
    Nodo * Siguiente;
};


typedef Nodo * Lista;

Nodo * CrearNodo(int id, char *descripcion, int duracion, Nodo * siguiente);
void cargarTareas(Lista * lista);
void mostrarLista(Lista lista);
void moverNodo(int id, Lista * lista, Lista * lista1);
void moverEntreListas(Lista * lista, Lista * lista1);
void buscarID();
void buscarDescripcion(Lista lista, char * descripcion);
void buscar(Lista TareasPendientes, Lista TareasRealizadas);

int main(int argc, char const *argv[])
{
    Lista TareasPendientes = NULL;
    Lista TareasRealizadas = NULL;
    cargarTareas(&TareasPendientes);
    printf("\n------------------------------\n");
    printf("TAREAS PENDIENTES\n");
    mostrarLista(TareasPendientes);
    printf("\nTAREAS REALIZADAS\n");
    mostrarLista(TareasRealizadas);
    printf("\n------------------------------\n");
    moverEntreListas(&TareasPendientes, &TareasRealizadas);
    buscar(TareasPendientes, TareasRealizadas);

}

Nodo * CrearNodo(int id, char *descripcion, int duracion, Nodo * siguiente){
    Nodo * nuevoNodo = (Nodo *)malloc(sizeof(Nodo));
    (nuevoNodo->T).Descripcion = (char *)malloc((strlen(descripcion)+1)*sizeof(char));
    strcpy((nuevoNodo->T).Descripcion, descripcion);
    (nuevoNodo->T).Duracion = duracion;
    (nuevoNodo->T).TareaID = id;
    nuevoNodo->Siguiente = siguiente;
}

void cargarTareas(Lista * lista){
    for (int i = 1000; i < 2000; i++)
    {
        printf("AGREGAR TAREA PENDIENTE\n");
        printf("Ingrese la descripcion:");
        char *Buff; //variable auxiliar
        Buff = (char *) malloc(100*sizeof(char));
        fflush(stdin);
        gets(Buff);
        printf("Ingrese la duracion: ");
        int d;
        scanf("%d", &d);
        *lista = CrearNodo(i, Buff, d, *lista);
        free(Buff);
        printf("Quiere seguir ingresando? S/N\n");
        fflush(stdin);
        char a = getchar();
        if (a == 'N')
        {
            break;
        }
    }
}

void mostrarLista(Lista lista){
    while (lista != NULL)
    {
        printf("ID: %d, Descripcion: %s, Duracion: %d\n", (lista->T).TareaID, (lista->T).Descripcion, (lista->T).Duracion);
        lista = lista->Siguiente;
    }
    
}

void moverNodo(int id, Lista * lista, Lista * lista1){
    Lista * iterador = lista;
    while (*iterador != NULL)
    {
        if (((*iterador)->T).TareaID == id)
        {
            Nodo * aux = *iterador;
            *iterador = (*iterador)->Siguiente;
            aux->Siguiente = *lista1;
            *lista1 = aux;
        } else {
            iterador = &((*iterador)->Siguiente);
        }
    }
}

void moverEntreListas(Lista * lista, Lista * lista1){
    for (int i = 1000; i < 2000; i++)
    {
        printf("PASAR A TAREA REALIZADA\n");
        printf("Ingrese el ID:");
        int id;
        scanf("%d", &id);
        moverNodo(id, lista, lista1);
        printf("\n------------------------------\n");
        printf("TAREAS PENDIENTES\n");
        mostrarLista(*lista);
        printf("\nTAREAS REALIZADAS\n");
        mostrarLista(*lista1);
        printf("\n------------------------------\n");
        printf("Quiere seguir pasando? S/N\n");
        fflush(stdin);
        char a = getchar();
        if (a == 'N')
        {
            break;
        }
    }
}

void buscarDescripcion(Lista lista, char * descripcion){
    while (lista != NULL)
    {
        if (strstr((lista->T).Descripcion, descripcion))
        {
            printf("ID: %d, Descripcion: %s, Duracion: %d\n", (lista->T).TareaID, (lista->T).Descripcion, (lista->T).Duracion);
        }
        lista = lista->Siguiente;
    }
}

void buscarID(Lista lista, int ID){
    while (lista != NULL)
    {
        if (((lista->T).TareaID) == ID)
        {
            printf("ID: %d, Descripcion: %s, Duracion: %d\n", (lista->T).TareaID, (lista->T).Descripcion, (lista->T).Duracion);
        }
        lista = lista->Siguiente;
    }
}

void buscar(Lista TareasPendientes, Lista TareasRealizadas){
    for (int i = 1000; i < 2000; i++)
    {
        char a;
        do
        {
            printf("Quiere buscar por ID o por descripcion? I/D\n");
            fflush(stdin);
            a = getchar();
        } while (a!='I' && a!='D');

        if (a == 'D')
        {
            printf("Ingrese la descripcion: ");
            char *descripcion = (char *) malloc(100*sizeof(char));
            fflush(stdin);
            gets(descripcion);
            printf("TAREAS PENDIENTES\n");
            buscarDescripcion(TareasPendientes, descripcion);
            printf("TAREAS REALIZADAS\n");
            buscarDescripcion(TareasRealizadas, descripcion);
            free(descripcion);

        } else {
            printf("Ingrese el ID: ");
            int id;
            scanf("%d", &id);
            printf("TAREAS PENDIENTES\n");
            buscarID(TareasPendientes, id);
            printf("TAREAS REALIZADAS\n");
            buscarID(TareasRealizadas, id);
        }
        
        printf("Quiere seguir buscando? S/N\n");
        fflush(stdin);
        a = getchar();
        if (a == 'N')
        {
            break;
        }
    }
}