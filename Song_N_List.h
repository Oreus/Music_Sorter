// Oscar Lopez Cardoso
// A01713355
// 10/24/2025

#ifndef SONG_N_LIST_H_
#define SONG_N_LIST_H_
#include <iostream>
#include <list>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class Song {
    private:
        // Song attributes
        string title;
        double duration;
        string genre;
        string artist;

    public:
        // Song constructor
        Song(string title, double duration, string genre, string artist) 
        : title(title), duration(duration), genre(genre), artist(artist) {}

        // Song getters
        string getTitle() const { 
            return title; 
            }
        double getDuration() const { 
            return duration; 
            }
        string getGenre() const { 
            return genre; 
            }
        string getArtist() const { 
            return artist; 
            }

        // Song Setters
        void setTitle(string songTitle) { 
            title = songTitle; 
            }
        void setDuration(double songDuration) { 
            duration = songDuration; 
            }
        void setGenre(string songGenre) { 
            genre = songGenre; 
            }
        void setArtist(string songArtist) { 
            artist = songArtist; 
            }
};

// Custom comparisons 
bool compareByTitle(const Song* a, const Song* b) {
    return a->getTitle() < b->getTitle();
}

bool compareByArtist(const Song* a, const Song* b) {
    return a->getArtist() < b->getArtist();
}

bool compareByDuration(const Song* a, const Song* b) {
    return a->getDuration() < b->getDuration();
}

bool compareByGenre(const Song* a, const Song* b) {
    return a->getGenre() < b->getGenre();
}

class List {
    private:
        std::list<Song*> songs;   
        // Split a CSV line into fields
        static inline vector<string> splitCSVLineSimple(const string& line) {
            vector<string> fields;
            string field;
            istringstream ss(line);
            while (getline(ss, field, ',')) {
                fields.push_back(field); 
            }
            return fields;
        }

    public:
    List() : songs() {}

    // List getter
    size_t size() const { 
        return songs.size(); 
        }

    void addSong(Song* s) { 
        songs.push_back(s); 
        }

    void addSong(const string& title, double duration, const string& genre, const string& artist) {
        songs.push_back(new Song(title, duration, genre, artist));
    }

    void removeSong(Song* s) {
        for (auto it = songs.begin(); it != songs.end(); ++it) {
            if (*it == s) {
                delete *it;            
                songs.erase(it);       
                break;
            }
        }
    }

    // Convenience: remove by index with bounds checking and deletion
    void removeSongByIndex(int index) {
        if (index < 0 || static_cast<size_t>(index) >= songs.size()) return;
        auto it = songs.begin();
        std::advance(it, index);     
        delete *it;                  
        songs.erase(it);            
    }

    // Lists songs info in list
    void listSongs() {
            cout << "Songs: " << endl;
            int i = 0;
            for (auto it = songs.begin(); it != songs.end(); ++it, ++i) {
                Song* s = *it;
                cout << i << ") " << 
                s->getTitle() << " - " << 
                s->getArtist() << " (" << 
                s->getDuration() << ") (" << 
                s->getGenre() << ")" << endl;
            }
        }

    // Sort songs using a comparator. std::list has its own sort optimized for linked lists.
    void sortSongs(bool (*compare)(const Song*, const Song*)) {
        songs.sort([compare](Song* a, Song* b) { return compare(a, b); });
    }

    // Helper to access a song pointer by index (returns nullptr if out of range)
    Song* songAtIndex(int index) const {
        if (index < 0 || static_cast<size_t>(index) >= songs.size()) return nullptr;
        auto it = songs.begin();
        std::advance(it, index);
        return *it;
    }

    // Load songs from a CSV file.
    pair<int,int> loadFromCSV(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Failed to open file: " << filename << endl;
            return {0, 0};
        }

        int loaded = 0;
        int skipped = 0;
        string line;
        int lineNo = 0;

        // Skip empty lines
        while (getline(file, line)) {
            ++lineNo;
            if (line.find_first_not_of(" \t\r\n") == string::npos) continue;

            // Sets the standard of there being 4 fields
            auto fields = splitCSVLineSimple(line);
            if (fields.size() != 4) {
                cerr << "Line " << lineNo << ": wrong number of fields (" << fields.size() << "), skipping\n";
                ++skipped;
                continue;
            }

            const string& title = fields[0];
            const string& artist = fields[1];
            const string& durationStr = fields[2];
            const string& genre = fields[3];

            try {
                double duration = stod(durationStr);
                // create and insert Song; addSong overload handles allocation
                addSong(title, duration, genre, artist);
                ++loaded;
            } catch (const exception& e) {
                cerr << "Line " << lineNo << ": invalid duration '" << durationStr << "', skipping\n";
                ++skipped;
                continue;
            }
        }

        file.close();
        return {loaded, skipped};
    }

    // searchByTitle: returns indices of exact-title matches
    vector<int> searchByTitle(const string& title) const {
        vector<int> result;
        int i = 0;
        for (auto it = songs.begin(); it != songs.end(); ++it, ++i) {
            if ((*it)->getTitle() == title) result.push_back(i);
        }
        return result;
    }

    // searchByArtist: returns indices of exact-artist matches
    vector<int> searchByArtist(const string& artist) const {
        vector<int> result;
        int i = 0;
        for (auto it = songs.begin(); it != songs.end(); ++it, ++i) {
            if ((*it)->getArtist() == artist) result.push_back(i);
        }
        return result;
    }

    // filterByGenre: returns pointers to matching Song objects
    vector<Song*> filterByGenre(const string& genre) const {
        vector<Song*> result;
        for (auto it = songs.begin(); it != songs.end(); ++it) {
            if ((*it)->getGenre() == genre) result.push_back(*it);
        }
        return result;
    }

    // filterByDurationRange: returns pointers to matching Song objects
    vector<Song*> filterByDurationRange(double minSec, double maxSec) const {
        vector<Song*> result;
        for (auto it = songs.begin(); it != songs.end(); ++it) {
            double d = (*it)->getDuration();
            if (d >= minSec && d <= maxSec) result.push_back(*it);
        }
        return result;
    }


    ~List() {
        for (Song* s : songs) delete s;
    }
};

class UI {
    private:
    List* list;
            // Prompt the user for an integer until valid input or quit command is entered
            int promptForInt(const string& prompt) {
            while (true) {
                cout << prompt;
                string input;
                getline(cin, input);
                if (input == "q" or input == "Q") {
                    exitList();
                }
                try {
                    int value = stoi(input);
                    return value;
                }
                catch (const exception& e) {
                    cout << "Invalid input, please enter a valid number or enter 'q' to exit." << endl;
                }
            }
        }
            // Prompt the user for a double until valid input or quit command is entered
            double promptForDouble(const string& prompt) {
            while (true) {
                cout << prompt;
                string input;
                getline(cin, input);
                if (input == "q" || input == "Q") exitList();
                try {
                    return stod(input);
                } catch (const exception&) {
                    cout << "Invalid input, please enter a valid number or enter 'q' to exit." << endl;
                }
            }
        }
        // Prompt the user for a string and allow quit command
        string promptForString(const string& prompt) {
            cout << prompt;
            string input;
            getline(cin, input);
            if (input == "q" || input == "Q") exitList();
                return input;
        }

        // Helper to print search results
        void printMatchesByIndex(const vector<int>& indices) {
            if (indices.empty()) {
                cout << "No matches found." << endl;
                return;
            }
            for (int idx : indices) {
                Song* s = list->songAtIndex(idx); 
                if (s) {
                    cout << idx << ") " 
                    << s->getTitle() << " - " 
                    << s->getArtist() << " (" 
                    << s->getDuration() << ") (" 
                    << s->getGenre() << ")" << endl;
                }
            }
        }

        // Method for exiting the list
        void exitList() {
            cout << "\nExiting list" << endl;
            exit(0);
        }

    public:
    UI() : list(nullptr) {}

    // Constructor that accepts a pre-loaded list 
    UI(List* existingList) : list(existingList) {}

    void Inicializer() {
        // create list if not present
        if (list == nullptr) {
            list = new List();
            cout << "New list created!" << endl;
        }
    }

    void ListLoop() {
        Inicializer();
        cout << "\n--- Menu ---\n";
        cout << "1) Add Song\n2) Remove Song\n3) Sort Songs\n4) List Songs\n5) Load from CSV\n6) Search\n7) Filter\n8) Quit\n";        int action = promptForInt("Choose an action: ");
        switch (action) {
            case 1: {
                // gather song fields from user and add to list
                string title = promptForString("Title: ");
                string artist = promptForString("Artist: ");
                double duration = promptForDouble("Duration (seconds): ");
                string genre = promptForString("Genre: ");
                list->addSong(title, duration, genre, artist);
                cout << "Song added." << endl;
                break;
            }
            case 2: {
                // show list so user can choose index
                list->listSongs();
                int itemIndex = promptForInt("Enter song index to remove: ");
                list->removeSongByIndex(itemIndex);
                cout << "If index was valid, song removed." << endl;
                break;
            }
            case 3: {
                // choose comparator then call List::sortSongs
                cout << "Sort by: 1) Title 2) Artist 3) Duration 4) Genre" << endl;
                int choice = promptForInt("Choose comparator: ");
                switch (choice) {
                    case 1: list->sortSongs(compareByTitle); break;
                    case 2: list->sortSongs(compareByArtist); break;
                    case 3: list->sortSongs(compareByDuration); break;
                    case 4: list->sortSongs(compareByGenre); break;
                    default: cout << "Unknown comparator, no sort performed." << endl; break;
                }
                cout << "Sort completed if valid comparator chosen." << endl;
                break;
            }
            case 4:
                // list contents
                list->listSongs();
                break;
            case 5: {
                // load CSV
                string filename = promptForString("Enter CSV filename: ");
                auto result = list->loadFromCSV(filename);
                cout << "Loaded: " << result.first << ", Skipped: " << result.second << endl;
                break;
            }
            case 6: {
                // Search songs by either the exact title or artist
                cout << "Search by: 1) Title 2) Artist" << endl;
                int sc = promptForInt("Choose: ");
                if (sc == 1) {
                string q = promptForString("Title to search (exact match): ");
                auto idxs = list->searchByTitle(q);
                printMatchesByIndex(idxs);
                    } else if (sc == 2) {
                string q = promptForString("Artist to search (exact match): ");
                auto idxs = list->searchByArtist(q);
                printMatchesByIndex(idxs);
                    } else 
                cout << "Unknown search option." << endl;
                break;
            }
            case 7: {
                // Filter songs by either the genre or a duration range
                cout << "Filter by: 1) Genre 2) Duration range" << endl;
                int fc = promptForInt("Choose: ");
                if (fc == 1) {
                string g = promptForString("Genre: ");
                auto matches = list->filterByGenre(g);
                if (matches.empty()) cout << "No matches." << endl;
                    else {
                int i = 0;
                for (Song* s : matches) {
                cout << i++ << ") " << s->getTitle() << " - " << s->getArtist()
                     << " (" << s->getDuration() << ") (" << s->getGenre() << ")" << endl;
                        }
                    }
                } else if (fc == 2) {
                double mn = promptForDouble("Min duration (seconds): ");
                double mx = promptForDouble("Max duration (seconds): ");
                auto matches = list->filterByDurationRange(mn, mx);
                    if (matches.empty()) 
                    cout << "No matches." << endl;
                else {
                int i = 0;
                for (Song* s : matches) {
                    cout << i++ << ") " << s->getTitle() << " - " << s->getArtist()
                        << " (" << s->getDuration() << ") (" << s->getGenre() << ")" << endl;
                        }
                    }
                } else cout << "Unknown filter option." << endl;
                break;
                }
            case 8:
            // Exit the list
                exitList();
                break;
            default:
                cout << "Unknown action." << endl;
                break;
        }
    }
    
    // Allow injecting a pre-loaded List 
    void setList(List* existingList) {
        if (list != nullptr) delete list;
        list = existingList;
    }

    void begin() {
        while (true) ListLoop();
    }

    ~UI() { 
        delete list; 
        }
};

#endif
