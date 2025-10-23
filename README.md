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

song list (structure: vector<Song*>)

access by index: O(1) because songs[i] is direct vector access.

search by value (e.g., find by title): O(n) because you must scan and compare each element.

insertion (addSong — push_back): amortized O(1).

deletion (removeSong — find + erase): O(n) because find is O(n) and erase may shift elements O(n); overall O(n).

list all (listSongs): O(n).

## SICT0302B: Toma decisiones

### Selecciona un algoritmo de ordenamiento adecuado al problema y lo usa correctamente.

For this project I used sort() which invokes std::sort — commonly implemented as introsort. I chose std::sort because it combines quicksort’s practical speed with a heapsort fallback that guarantees O(n log n) worst-case and uses insertion sort on small partitions to reduce constant factors, making it appropriate when element moves are cheap (pointer assignments in vector<Song*>) and string comparisons dominate the cost. The call is used in List::sortSongs in Song_N_List.h and the comparators are the free functions compareByTitle, compareByArtist, compareByDuration, and compareByGenre. If stability is required, switch to stable_sort (mergesort) accepting O(n) additional memory.

## SICT0303B: Implementa acciones científicas

