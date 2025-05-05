# Catálogo de Canciones 🎵

Este programa permite gestionar un catálogo de canciones y listas de reproducción utilizando estructuras de datos en C. Puedes buscar canciones por género, artista o tempo, y crear tus propias listas.

## ✅ ¿Qué hace el programa?

- Carga canciones desde un archivo CSV (`song_dataset_.csv`).
- Permite buscar canciones por:
  - Género
  - Artista
  - Tempo (lentas, moderadas, rápidas)
- Crea listas de reproducción personalizadas.
- Permite agregar canciones a listas existentes.
- Muestra las canciones dentro de una lista de reproducción.

## ⚠️ Funcionalidades que **NO** funcionan del todo bien

- **Cargar canciones**: actualmente solo se cargan las primeras 10 canciones del archivo para pruebas. Falta implementar la carga completa (hasta 1000).
- **Búsqueda por artista y género**: no muestra resultados porque aún no se insertan correctamente en los mapas correspondientes (`canciones_byartist`, `canciones_bygenre`).
- **Validaciones de entrada**: no hay manejo de errores si el usuario ingresa datos inválidos (por ejemplo, espacios extra o artistas que no existen).

## ▶️ Cómo compilar y ejecutar

Desde una terminal con `gcc` instalado:

```bash
gcc -Wall -g tdas/*.c main.c -o main
./main