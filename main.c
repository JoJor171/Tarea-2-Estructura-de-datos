#include "tdas/extra.h"
#include "tdas/list.h"
#include "tdas/map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LIMITE_CANCIONES 113998

typedef struct {
    char id[100];
    char title[100];
    char artist[200];
    List *genres;
    float tempo;
  } Song;

// Menú principal
void mostrarMenuPrincipal() {
    limpiarPantalla();
    puts("=========== Catalogo de Canciones ===========");
    puts("1) Cargar Canciones");
    puts("2) Buscar por Genero");
    puts("3) Buscar por Artista");
    puts("4) Buscar por Tempo");
    puts("5) Crear Lista de Reproduccion");
    puts("6) Agregar Cancion a Lista");
    puts("7) Mostrar Canciones de una Lista");
    puts("8) Salir");
  }

/**
 * Compara dos claves de tipo string para determinar si son iguales.
 * Esta función se utiliza para inicializar mapas con claves de tipo string.
 *
 * @param key1 Primer puntero a la clave string.
 * @param key2 Segundo puntero a la clave string.
 * @return Retorna 1 si las claves son iguales, 0 de lo contrario.
 */
int is_equal_str(void *key1, void *key2) {
    return strcmp((char *)key1, (char *)key2) == 0;
  }

  void mostrarCancion(Song *song) {
    printf("ID: %s\n", song->id);
    printf("Titulo: %s\n", song->title);
    printf("Artista: %s\n", song->artist);
    printf("Tempo: %.1f BPM\n", song->tempo);
    printf("Generos: ");
    for (char *g = list_first(song->genres); g != NULL; g = list_next(song->genres)) {
      printf("%s ", g);
    }
    printf("\n-----------------------------\n");
  }


  void mostrar_canciones_lista(Map *listas_reproduccion) {
    char nombre_lista[100];
    printf("Ingrese el nombre de la lista de reproduccion: ");
    scanf(" %[^\n]", nombre_lista);

    MapPair *pair = map_search(listas_reproduccion, nombre_lista);
    if (!pair) {
        printf("No se encontro esa lista.\n");
        return;
    }

    List *lista = pair->value;
    printf("Canciones en la lista '%s':\n", nombre_lista);
    for (Song *s = list_first(lista); s != NULL; s = list_next(lista)) {
        mostrarCancion(s);
    }
}

Song* crear_cancion(char **campos) {
  Song *cancion = (Song *)malloc(sizeof(Song));
  if (cancion == NULL) {
      perror("Error al asignar memoria para la canción");
      exit(1);
  }

  strcpy(cancion->id, campos[0]);
  strcpy(cancion->title, campos[4]);
  strcpy(cancion->artist, campos[2]);
  cancion->genres = split_string(campos[20], ";");
  cancion->tempo = atof(campos[18]);

  return cancion;
}

void cargar_canciones(Map *canciones_byid, Map *canciones_bygenre, Map *canciones_byartist) {
  long cuantas_cargar = 0;

  printf("Canciones que desea cargar (MAX. 113998): ");
  scanf("%ld", &cuantas_cargar);

  FILE *archivo = fopen("data/song_dataset_.csv", "r");
  if (archivo == NULL) {
      perror("ERROR: No se pudo abrir el archivo");
      return;
  }

  char **campos;
  campos = leer_linea_csv(archivo, ','); // Saltar encabezado

  long k = 0;
  while ((campos = leer_linea_csv(archivo, ',')) != NULL) {
      if (k >= cuantas_cargar) break;

      Song *nueva_cancion = (Song *)malloc(sizeof(Song));
      if (nueva_cancion == NULL) {
          perror("ERROR: No se pudo asignar memoria para la canción");
          fclose(archivo);
          return;
      }

      strncpy(nueva_cancion->id, campos[0], sizeof(nueva_cancion->id));
      strncpy(nueva_cancion->artist, campos[2], sizeof(nueva_cancion->artist));
      strncpy(nueva_cancion->title, campos[4], sizeof(nueva_cancion->title));
      nueva_cancion->tempo = atof(campos[18]);
      nueva_cancion->genres = split_string(campos[20], ";");

      map_insert(canciones_byid, nueva_cancion->id, nueva_cancion);

      for (char *genero = list_first(nueva_cancion->genres); genero != NULL; genero = list_next(nueva_cancion->genres)) {
          MapPair *par_genero = map_search(canciones_bygenre, genero);
          if (par_genero == NULL) {
              List *lista_genero = list_create();
              list_pushBack(lista_genero, nueva_cancion);
              map_insert(canciones_bygenre, genero, lista_genero);
          } else {
              List *lista_genero = (List *)par_genero->value;
              list_pushBack(lista_genero, nueva_cancion);
          }
      }

      List *artistas = split_string(nueva_cancion->artist, ";");
      for (char *artista = list_first(artistas); artista != NULL; artista = list_next(artistas)) {
          MapPair *par_artista = map_search(canciones_byartist, artista);
          if (par_artista == NULL) {
              List *lista_artista = list_create();
              list_pushBack(lista_artista, nueva_cancion);
              map_insert(canciones_byartist, artista, lista_artista);
          } else {
              List *lista_artista = (List *)par_artista->value;
              list_pushBack(lista_artista, nueva_cancion);
          }
      }
      list_clean(artistas); 

      if (k == 1) printf("Cargando canciones...\n");

      k++;
  }

  fclose(archivo);
  printf("Canciones cargadas exitosamente.\n");
  printf("Se han cargado %ld canciones.\n", k);
}


void crear_lista_reproduccion(Map *listas_reproduccion) {
    char nombre[100];
    printf("Nombre de la nueva lista de reproduccion: ");
    scanf(" %[^\n]", nombre);

    if (map_search(listas_reproduccion, nombre)) {
        printf("Ya existe una lista con ese nombre.\n");
        return;
    }
    List *nueva_lista = list_create();
    map_insert(listas_reproduccion, strdup(nombre), nueva_lista);
    printf("Lista de reproduccion '%s' creada exitosamente.\n", nombre);
}

void agregar_cancion_a_lista(Map *canciones_byid, Map *listas_reproduccion) {
  char id[100], nombre_lista[100];

  printf("Ingrese el ID de la cancion: ");
  scanf(" %s", id);
  printf("Ingrese el nombre de la lista de reproduccion: ");
  scanf(" %[^\n]", nombre_lista);

  MapPair *cancion_pair = map_search(canciones_byid, id);
  if (!cancion_pair) {
      printf("No se encontro una cancion con ese ID.\n");
      return;
  }

  MapPair *lista_pair = map_search(listas_reproduccion, nombre_lista);
  if (!lista_pair) {
      printf("No se encontro una lista con ese nombre.\n");
      return;
  }

  Song *cancion = cancion_pair->value;
  List *lista = lista_pair->value;
  list_pushBack(lista, cancion);
  printf("Cancion '%s' agregada a la lista '%s'.\n", cancion->title, nombre_lista);
}


void buscar_por_artista(Map *canciones_byartist) {
    char artista[200];
    printf("Ingrese el nombre del artista: ");
    getchar();
    scanf("%[^\n]", artista);
  
    MapPair *pair = map_search(canciones_byartist, artista);
    if (!pair) {
      printf("No se encontraron canciones del artista.\n");
      return;
    }
  
    List *lista = pair->value;
    for (Song *s = list_first(lista); s != NULL; s = list_next(lista)) {
      mostrarCancion(s);
    }
  }

void buscar_por_genero(Map *canciones_bygenre) {
    char genero[100];
    printf("Ingrese el genero a buscar: ");
    scanf(" %[^\n]", genero);
  
    MapPair *pair = map_search(canciones_bygenre, genero);
    if (!pair) {
      printf("No se encontraron canciones de ese genero.\n");
      return;
    }
  
    List *lista = pair->value;
    for (Song *s = list_first(lista); s != NULL; s = list_next(lista)) {
      mostrarCancion(s);
    }
  }

void buscar_por_tempo(Map *canciones_byid) {
    char tipo[20];
    printf("Tipo de tempos: (lentas, moderadas, rapidas): ");
    scanf(" %s", tipo);
  
    float min = 0, max = 1000;
  
    if (strcmp(tipo, "lentas") == 0) {
      max = 80;
    } else if (strcmp(tipo, "moderadas") == 0) {
      min = 80;
      max = 120;
    } else if (strcmp(tipo, "rapidas") == 0) {
      min = 120;
    } else {
      printf("Tipo de tempo no reconocido.\n");
      return;
    }
  
    MapPair *pair = map_first(canciones_byid);
    while (pair != NULL) {
      Song *s = pair->value;
      if (s->tempo >= min && s->tempo < max) {
        mostrarCancion(s);
      }
      pair = map_next(canciones_byid);
    }
  }

  int main() {
    char opcion;
  
    Map *canciones_byid = map_create(is_equal_str);
    Map *canciones_bygenre = map_create(is_equal_str);
    Map *canciones_byartist = map_create(is_equal_str);
    Map *listas_reproduccion = map_create(is_equal_str);
  
    do {
        mostrarMenuPrincipal();
        printf("Ingrese una opcion: ");
        scanf(" %c", &opcion);
  
        switch (opcion) {
        case '1':
            cargar_canciones(canciones_byid, canciones_bygenre, canciones_byartist);
            break;
        case '2':
            buscar_por_genero(canciones_bygenre);
            break;
        case '3':
            buscar_por_artista(canciones_byartist);
            break;
        case '4':
            buscar_por_tempo(canciones_byid);
            break;
        case '5':
            crear_lista_reproduccion(listas_reproduccion);
            break;
        case '6':
            agregar_cancion_a_lista(canciones_byid, listas_reproduccion);
            break;
        case '7':
            mostrar_canciones_lista(listas_reproduccion);
            break;
        case '8':
            printf("Saliendo del programa...\n");
            break;
        default:
            printf("Opción no válida. Intente nuevamente.\n");
            break;
        }

        if (opcion != '8') {
            presioneTeclaParaContinuar();
        }

    } while (opcion != '8');
  
    return 0;
}
