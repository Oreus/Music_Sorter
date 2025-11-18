// Oscar Lopez Cardoso
// A01713355
// 11/18/2025

#include "Song_N_List.h"

int main() {
    List* list = new List();
    list->loadFromCSV("songs.csv");
    UI ui(list);
    ui.begin();
    return 0;
}
