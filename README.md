-**CATALOGO DE CANCIONES🎵**

Este programa permite gestionar un catálogo de canciones y listas de reproducción utilizando estructuras de datos en C. Puedes buscar canciones por género, artista o tempo, y crear tus propias listas.

-**¿QUE HACE EL PROGRAMA ?** 

- Carga canciones desde un archivo CSV (`song_dataset_.csv`).
- Permite buscar canciones por: 
        - Género
        - Artista
        - Tempo (lentas, moderadas, rápidas)
- Crea listas de reproducción personalizadas.
- Permite agregar canciones a listas existentes.
- Muestra las canciones dentro de una lista de reproducción.

----**¿COMO SE INSTALA?**----

- Compilador de C
- Implementar tdas listas y mapas en una carpeta
- Tener el archivo con datos de las canciones ""data/song_dataset_.csv""

----**¿COMO SE COMPILA Y EJECUTA ?**----


- Introduzca el comando ""gcc -o catalogo catalogo.c tdas/*.c"" para compilar
y para ejecutarlo ingrese "" ./catalogo ""

----**FUNCIONES**----

- void cargar_canciones() : Esta funcion se encarga de leer el archivo song_dataset_.csv
y cargar las canciones en mapas para buscarlas por id, genero y artista.


- void buscar_por_genero() : Esta funcion permite al usuario buscar canciones por un genero.
especifico 


- void buscar_por_artista() : Muestras las canciones asociadas a un artista ingresado.


- void buscar_por_tempo() : Clasifica las canciones segun (lenta, moderada, rapida).


- void crear_lista_reproduccion() : Crea una nueva lista vacia con nombre personaizable y 
le da la oportunidad al usuario de organizar sus canciones favoritas.


- void agregar_cancion_a_lista() : Agrega una cancion existente por id a una lista especifica,
lo que permite personalizar las listas.


- void void mostrar_canciones_lista() : Muestra las canciones de una lista seleccionada


----**MENU DE CANCIONES**----

- ESTA ES LA INTERFAZ DEL PROGRAMA : 

=========== Catalogo de Canciones ===========
1) Cargar Canciones
2) Buscar por Genero
3) Buscar por Artista
4) Buscar por Tempo
5) Crear Lista de Reproduccion
6) Agregar Cancion a Lista
7) Mostrar Canciones de una Lista
8) Salir

---- **BUSQUEDA POR GENERO** ----

Ingrese el genero a buscar: Pop
ID: 001
Título: Let It Be
Artista: The Beatles
Tempo: 72.0 BPM
Generos: Pop Rock 
-----------------------------

- Se ingresa el genero, id, titulo, artista, tempo y genero.


---- **FUNCIONALIDADES QUE NO FUNCIONAN DEL TODO BIEN** ----


- **Tiempo de carga** : El programa Se demora en cargar debido a la gran cantidad de canciones.

---- **FUNCIONALIDAD PARA OPTIMIZAR CARGA DE CANCIONES**----

- Puedes modificar el numero de canciones que se cargan desde csv.

EJEMPLO : if (k > 800000) break; ## CARGA LAS PRIMERAS 800000 CANCIONES.

----**APORTES**----

Rafael Cortes : Lista de reproduccion, Agregar canciones a la lista , Implementacion de tdas, Readme, mostrar canciones.

Jose Jorquera : Diseño del codigo, menu principal, funciones "buscar", Readme, cargar canciones.
