# Music List and Sorter
This project is a simple and dynamic song list in which the user can add, remove, and sort songs (based on title, artist, song duration, and genre)

>Example: Sort my songs by artist
>
>Step 1: Create song list, ie. :
><p>("King For A Day", 3.56, "Rock", "Pierce The Veil") <b>
><p>("Tiramisu", 2.18, "Rap", "Don Toliver") <b> 
><p>("Blue in Green", 5.1, "Jazz", "Miles Davis") <b>
>
>Step 2: Sort by song duration
><p>("Tiramisu", 2.18, "Rap", "Don Toliver") <b> 
><p>("King For A Day", 3.56, "Rock", "Pierce The Veil") <b>
><p>("Blue in Green", 5.1, "Jazz", "Miles Davis") <b>

## SICT0301B: Evalúa los componentes

### Hace un análisis de complejidad correcto y completo para los algoritmos de ordenamiento usados en el programa.

The code uses sort (introsort) on a vector of pointers, giving O(n log n) average and worst-case time; each custom comparison is constant-time aside from string comparisons, so practical cost is O(k · n log n) where k is the average string comparison length.

## SICT0302B: Toma decisiones

### Selecciona un algoritmo de ordenamiento adecuado al problema y lo usa correctamente.

Sort is an appropriate choice because it is efficient, in-place, and avoids pathological worst cases by switching to heapsort and it is used correctly with custom comparator functions (compareByTitle, compareByArtist, compareByDuration, compareByGenre) in List sortSongs.

## SICT0303B: Implementa acciones científicas

