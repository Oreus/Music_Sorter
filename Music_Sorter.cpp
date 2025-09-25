#include "Song_N_List.h"

int main() {
    // Song creation
    Song Gravity("Gravity", 4.5, "Rock", "John Mayer");
    Song DOAE("Death Of An Executioner", 4.27, "Rock", "Pierce The Veil");
    Song King("King For A Day", 3.56, "Rock", "Pierce The Veil");
    Song Tiramisu("Tiramisu", 2.18, "Rap", "Don Toliver");
    Song BlueInGreen("Blue in Green", 5.1, "Jazz", "Miles Davis");

    //List creation
    List myList;
    
    //Adding songs to list 
    myList.addSong(&Gravity);
    myList.addSong(&BlueInGreen); 
    myList.addSong(&DOAE);
    myList.addSong(&King);
    myList.addSong(&Tiramisu);

    // Display unsorted song list
    myList.listSongs();

    // Sort List (By Artist)
    myList.sortSongs(compareByArtist);
    // Display sorted list
    myList.listSongs();

    // Sort List (By Title)
    myList.sortSongs(compareByTitle);
    // Display sorted list
    myList.listSongs();

    // Sort List (By Duration)
    myList.sortSongs(compareByDuration);
    // Display sorted list
    myList.listSongs();

    // Sort List (By Genre)
    myList.sortSongs(compareByGenre);
    // Display sorted list
    myList.listSongs();
    
}