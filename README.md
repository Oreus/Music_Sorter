# Music List and Sorter
This C++ project implements an interactive music manager that stores Song objects in a doubly linked list, lets the user add/remove/list/sort/search/filter songs, and load songs from a CSV file.

How to build and run
1. Files to place in the same folder:

- Song_N_List.h
- main.cpp
- songs.csv

2. Compile the code

3. Run the code

4. Interactive menu (main options):

- Add Song — provide title, artist, duration (seconds), genre.

- Remove Song — remove by index shown in List Songs.

- Sort Songs — choose comparator: Title / Artist / Duration / Genre.

- List Songs — show index and song details.

- Load from CSV — enter filename or full path (e.g., songs.csv).

- Search — search by Title or Artist (exact match).

- Filter — filter by Genre or by Duration range.

- Quit — exit program.

Notes:

CSV format required: title,artist,duration,genre (duration in seconds as a number).

The built-in CSV splitter is simple (splits on commas) and does not handle quoted fields with embedded commas; use Excel to export correct CSV or avoid commas inside fields.

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

### Hace un análisis de complejidad correcto y completo de todas las estructuras de datos y cada uno de sus usos en el programa.

Song list (std::list<Song*>)

access by value (searchByTitle / searchByArtist / filterByGenre / filterByDurationRange): O(n) because the list is scanned and each element compared until matches are found.

access by index (songAtIndex / used by removeSongByIndex): O(n) because advancing to index i requires iterating i steps.

insertion (addSong / push_back): O(1) time; O(1) additional space per element.

deletion by pointer (removeSong): O(n) time to locate the pointer (linear scan) + O(1) erase; O(1) space.

deletion by index (removeSongByIndex): O(n) time to advance to the index + O(1) erase; O(1) space.

list all songs (listSongs): O(n) time to traverse the list; O(1) space.

load from CSV (loadFromCSV): O(L) time where L = number of lines read; each line is validated and addSong is O(1) so total O(L); O(n) space to store n songs (n ≤ L).

sorting (sortSongs using std::list::sort): O(n log n) time (std::list::sort uses a merge-like algorithm suitable for linked lists) and O(1) auxiliary memory for the operation on lists.

printing matches (printMatchesByIndex): O(m · n) in the worst case if there are m indices and each printed index calls songAtIndex (O(n) per call); a more efficient approach (not implemented) is a single-pass traversal to print matches in O(n).

Memory complexity (implemented)

total memory: O(n) for n Song objects stored as pointers plus per-node overhead (prev/next pointers and heap allocation overhead).

auxiliary memory: O(1) for most operations; search/filter result vectors use O(k) space where k = number of matches.

Practical observations (implemented)

CSV parser is simple: splits on commas and does not handle quoted fields; this affects correctness on complex CSVs but not asymptotic costs.

Ownership: List destructor deletes Song* (manual memory management); deallocation cost at destruction is O(n).

## SICT0302B: Toma decisiones

### Selecciona una estructura de datos adecuada al problema y la usa correctamente.

I use a doubly linked list (std::list<Song*>) to store songs because the UI needs fast insertions and safe removals while preserving insertion order. Each Song is an object containing title, artist, duration and genre. Elements are inserted and removed via the List methods addSong, removeSong and removeSongByIndex; these methods are implemented in Song_N_List.h and show how the list is manipulated and the Song objects are owned and freed by the List destructor.

### Selecciona un algoritmo de ordenamiento adecuado al problema y lo usa correctamente.

For this project I used sort() which invokes std::sort — commonly implemented as introsort. I chose std::sort because it combines quicksort’s practical speed with a heapsort fallback that guarantees O(n log n) worst-case and uses insertion sort on small partitions to reduce constant factors, making it appropriate when element moves are cheap (pointer assignments in vector<Song*>) and string comparisons dominate the cost. The call is used in List::sortSongs in Song_N_List.h and the comparators are the free functions compareByTitle, compareByArtist, compareByDuration, and compareByGenre. If stability is required, switch to stable_sort (mergesort) accepting O(n) additional memory.

## SICT0303B: Implementa acciones científicas

### Implementa mecanismos para consultar información de las estructras correctos.

The program provides these query mechanisms over the linked list:

- searchByTitle(title) — returns indices of exact-title matches (vector<int>) so the UI can display matched songs.

- searchByArtist(artist) — returns indices of exact-artist matches (vector<int>).

- filterByGenre(genre) — returns a vector<Song*> of matching Song pointers.

- filterByDurationRange(min,max) — returns a vector<Song*> of songs whose duration lies between min and max.

These functions are implemented in Song_N_List.h and are callable from the UI menu options (Search and Filter).

### Implementa mecanismos de lectura de archivos para cargar datos a las estructuras de manera correcta.

- The program implements loadFromCSV(filename) that:

- reads the CSV line by line, skipping empty lines;

- splits each line into four fields (title, artist, duration, genre) using a simple comma split;

- validates the field count and attempts to convert the duration field to a number;

- reports malformed lines with line numbers and counts loaded vs skipped;

- appends valid Song objects to the list (addSong).

This loader is robust for the expected simple CSV format and returns pair(loaded, skipped) so the UI can present results to the user.
