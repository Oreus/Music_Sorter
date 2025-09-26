// Oscar Lopez Cardoso
// A01713355
// 09/26/2025

#ifndef SONG_N_LIST_H_
#define SONG_N_LIST_H_
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

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

class List {
    private:
    // Creation of a list to hold all of the created songs
        vector<Song*> songs;
    
    public:
    // List constructor
    List() : songs() {}

    // List getter
    vector<Song*> getSongs() { 
        return songs; 
        }

    // Function to add a song to the list
    void addSong(Song* s) { 
        songs.push_back(s); 
        }

    // Function to remove a song from the list
    void removeSong(Song* s) {
        // Searches song list for the song
        for (int i = 0; i < songs.size(); ++i) {
            if (songs[i] == s) {
                songs.erase(songs.begin() + i);
                break;
            }
        }
    }
    // Lists songs info in list
    void listSongs() {
            cout << "Songs: " << endl;
            for (int i = 0; i < songs.size(); ++i) {
                cout << i << ") " << 
                songs[i] -> getTitle() << " - " << 
                songs[i] -> getArtist() << " (" << 
                songs[i] -> getDuration() << ") (" << 
                songs[i] -> getGenre() << ")" << endl;
            }
        }

    void sortSongs(bool (*compare)(const Song*, const Song*)) {
        sort(songs.begin(), songs.end(), compare);
    }
};

// Custom comparisons
bool compareByTitle(const Song* a, const Song* b) {
    return a -> getTitle() < b -> getTitle();
}

bool compareByArtist(const Song* a, const Song* b) {
    return a -> getArtist() < b -> getArtist();
}

bool compareByDuration(const Song* a, const Song* b) {
    return a -> getDuration() < b -> getDuration();
}

bool compareByGenre(const Song* a, const Song* b) {
    return a -> getGenre() < b -> getGenre();
}

#endif
