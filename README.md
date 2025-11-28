# LeetCode Problems
[Link to google Drive folder with all videos](https://drive.google.com/drive/folders/14VeDTzVBNgfMHUHsBpX4DSMftFE7tgso?usp=drive_link)

# Music List and Sorter
This C++ project is an interactive music manager. Songs are represented by a Song class and stored as pointers in a doubly-linked list (std::list<Song*>). The program supports adding, removing, listing, sorting, searching, filtering, and loading songs from a CSV file. The loader trims whitespace, strips common BOM/CR characters, and reports malformed lines. The UI auto-loads a default songs.csv on startup and provides an interactive console menu.

## Project features
- **Song model:** title, artist, duration (seconds), genre.

- **Storage:** std::list<Song*> (doubly-linked list of pointers).

- **Menu operations:**
  - Add
  - Remove (by index)
  - Sort (Title / Artist / Duration / Genre)
  - List
  - Load from CSV
  - Search (Title / Artist exact)
  - Filter (Genre case-insensitive or Duration range)
  - Quit.

- **CSV loader:** trims fields, removes UTF‑8 BOM and trailing \r, validates field count, converts duration, reports loaded/skipped counts.

- **Sorting:** uses std::list::sort (merge-like stable algorithm).

- **Ownership:** List owns and deletes Song* objects in its destructor.

## Build and run
Required files (same folder or adjust paths):

- **Song_N_List.h**

- **main.cpp**

- **songs.csv**

Compile (example single-file):

```bash
g++ -o music main.cpp -std=c++17
```
If the project is split across multiple .cpp files, include them in the compile command.

## Run:

### Windows (PowerShell):

```bash
.\music.exe
```
Linux / macOS:

```bash
./music
```
The program attempts to auto-load songs.csv from the working directory on startup. You may also load another CSV via the menu.

Input CSV format
Required header and columns (simple CSV, no quoted fields with embedded commas):

```csv
title,artist,duration,genre
Bohemian Rhapsody,Queen,354,Rock
Imagine,John Lennon,183,Pop
Hallelujah,Jeff Buckley,360,Folk
duration: numeric value in seconds (integer or floating point).
```
Loader expects exactly 4 fields per line; lines with wrong field counts are reported and skipped.

## Interactive menu (main options)
1. **Add Song** — enter Title, Artist, Duration (seconds), Genre

2. **Remove Song** — remove by index shown in List Songs

3. **Sort Songs** — choose comparator: Title / Artist / Duration / Genre

4. **List Songs** — display index and song details

5. **Load from CSV** — provide filename or full path

6. **Search** — search by Title or Artist (exact match)

7. **Filter** — filter by Genre (case-insensitive) or by Duration range

8. **Quit** — exit program

### Short usage examples
Example songs.csv:

```csv
title,artist,duration,genre
Bohemian Rhapsody,Queen,354,Rock
Imagine,John Lennon,183,Pop
Hallelujah,Jeff Buckley,360,Folk
```
1. Start program:

```bash
./music
```
Startup prints auto-load summary, e.g.:

```Code
Auto-loaded from 'songs.csv': Loaded: 3, Skipped: 0
```
2. List songs (menu: 4):

```Code
Songs:
0) Bohemian Rhapsody - Queen (354) (Rock)
1) Imagine - John Lennon (183) (Pop)
2) Hallelujah - Jeff Buckley (360) (Folk)
```
3. Add a song (menu: 1) — follow prompts:

```Code
Title: King For A Day
Artist: Pierce The Veil
Duration (seconds): 216
Genre: Rock
```
4. Sort by duration (menu: 3 → 3), then list (4) to verify order.

5. Filter by genre (menu: 7 → 1) — enter rock → matching Rock songs shown (case-insensitive).

6. Search by artist (menu: 6 → 2) — enter Queen → prints matches.

7. Remove a song (menu: 2) — program prompts for index shown in list.

8. Load a different CSV (menu: 5) — enter filename or full path.

Example condensed session:

```Code
$ ./music
Auto-loaded from 'songs.csv': Loaded: 3, Skipped: 0

--- Menu ---
1) Add Song
2) Remove Song
3) Sort Songs
4) List Songs
5) Load from CSV
6) Search
7) Filter
8) Quit
Choose an action: 4
Songs:
0) Bohemian Rhapsody - Queen (354) (Rock)
1) Imagine - John Lennon (183) (Pop)
2) Hallelujah - Jeff Buckley (360) (Folk)
```
## Complexity analyses (best / average / worst)
Assumptions:

- n = number of songs stored

- Song objects are pointers (Song*) inside std::list nodes

- Traversals use node-to-node iteration (no random access)

Data structure: std::list<Song*>

- Access by index (songAtIndex)

  - Best: O(1) (index 0)

  - Average: O(n)

  - Worst: O(n)

- Insertion at end (addSong / push_back)

  - Best/Average/Worst: O(1)

- Deletion given iterator/pointer (erase when iterator known)

  - Best/Average/Worst: O(1)

  - If locate first: O(n) + O(1) erase

- Traversal / listing / filter / search

  - Best: O(1) (if target at head and early exit)

  - Average/Worst: O(n)

- loadFromCSV

  - Time: O(L · m) ≈ O(L) where L = number of lines, m = average line length

  - Space: O(n)

- sortSongs using std::list::sort

  - Best/Average/Worst: O(n log n)

  - Auxiliary: O(1) node splices (merge-style)

  - Stable: yes

- printMatchesByIndex (current UI)

  - Worst-case: O(m · n) if printing m indices by repeated songAtIndex

  - Improvement: single-pass traversal prints matches in O(n)

- Memory complexity:

  - Storage: O(n) Song objects + per-node overhead (prev/next pointers, allocator)

  - Auxiliary: O(1) typical; result vectors O(k) where k = number of matches

Practical note: std::list has poor cache locality. If frequent random access or large n, prefer std::vector<Song*> (O(1) index) and std::sort for better locality and speed; trade-off: deletions from middle become O(n).

## Design decisions and justification
- Data structure chosen: std::list<Song*>

  - Rationale: O(1) insertion/erase at known positions, bidirectional traversal, stable iterators. Suited to interactive add/remove and potential splicing features.

- Sorting chosen: std::list::sort (merge-style, stable)

  - Rationale: merge-like sort fits linked lists (O(n log n), stable, O(1) splicing).

- Alternatives and trade-offs:

  - If workload moves to heavy indexed access: use std::vector<Song*> + std::sort or std::stable_sort.

  - For fast genre/artist queries: build auxiliary indices (unordered_map<string, vector<Song*>>) at load time for O(1) average lookup.

## SICT0301: Evalúa los componentes
Complete analyses and evidence of component evaluation.

### Sorting algorithms (used)
- Implementation: std::list::sort (merge-like for linked lists)

  - Worst-case: O(n log n)

  - Best-case: O(n log n)

  - Average-case: O(n log n)

  - Space: O(1) auxiliary (node splices), O(n) storage overall

  - Stability: stable

Comparison:

- std::list::sort is superior for linked lists vs. std::sort (introsort) which requires random access and benefits vectors due to cache locality. O(n²) sorts (Bubble/Selection) are asymptotically worse.

### Data-structure operations (per operation)
- addSong: O(1)

- removeSong (search+erase): O(n) to find + O(1) erase

- removeSongByIndex: O(n) to advance + O(1) erase

- songAtIndex: O(n)

- listSongs: O(n)

- search/filter: O(n)

- loadFromCSV: O(L · m) ≈ O(L)

- sortSongs: O(n log n)

All operations state best/average/worst as in the Complexity section.

## SICT0302: Toma decisiones
Documented choices and complexity-based justification.

### Data structure choice
- std::list<Song*> chosen for O(1) insert/erase at known positions and bidirectional traversal. Complexity comparisons and trade-offs provided above.

### Sorting choice
- std::list::sort chosen because it matches linked-list structure: stable, O(n log n), and uses O(1) splices. If container changes to vector, prefer std::sort for speed and locality.

### Recommendations
- Build auxiliary indices (genreIndex, artistIndex) at load time for O(1) average lookups.

- Consider smart pointers (unique_ptr) for safer memory management.

## SICT0303: Implementa acciones científicas
Detailed mapping of implemented mechanisms and evidence-ready behavior.

### File I/O and CSV loader (loadFromCSV)
- Behavior: safe open, read line-by-line, skip empty lines, split on commas into 4 fields, trim fields, remove BOM and \r, validate field count, stod conversion for duration, create Song via addSong, return (loaded, skipped).

- Complexity: O(L · m) per file; O(n) to store n songs.

- Edge cases handled: BOM, CRLF, extra/missing fields, invalid duration; logs include line numbers.

### Query mechanisms
- searchByTitle(title) → vector<int> indices (exact match). Complexity: O(n).

- searchByArtist(artist) → vector<int> indices (exact match). Complexity: O(n).

- filterByGenre(genre) → vector<Song*> (case-insensitive when normalized). Complexity: O(n).

- filterByDurationRange(min,max) → vector<Song*>. Complexity: O(n).

### Conversion / utilities
- songAtIndex(int) → Song* (or nullptr) — O(n).

- listSongs() — prints list — O(n).

### UI instrumentation
- Auto-load summary printed at startup for evidence (Loaded: X, Skipped: Y).

- Per-line error reporting in loader for traceability.

- Interactive menu demonstrates user-driven use for video evidence.
