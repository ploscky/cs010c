#include "Playlist.h"
#include <iostream>
using namespace std;

//PrintMenu function
void PrintMenu(string playlistTitle);

//construct new Playlist object as a global variable so that info can be saved in PrintMenu
Playlist* myPlaylist = new Playlist(); 

int main() {
    //declare variable (playlist title)
    string playlistTitle;

    //prompt user to enter playlist title
    cout << "Enter playlist's title:" << endl;
    getline(cin, playlistTitle);
    cout << endl;

    //implement PrintMenu
    PrintMenu(playlistTitle);
    return 0;
}

void PrintMenu(string playlistTitle) {
    //output menu
    cout << playlistTitle << " PLAYLIST MENU" << endl;
    cout << "a - Add song" << endl;
    cout << "d - Remove song" << endl;
    cout << "c - Change position of song" << endl;
    cout << "s - Output songs by specific artist" << endl;
    cout << "t - Output total time of playlist (in seconds)" << endl;
    cout << "o - Output full playlist" << endl;
    cout << "q - Quit" << endl << endl;
    cout << "Choose an option:" << endl;

    char userChoice;
    cin >> userChoice;

    //add song-- uses addSong function and constructs a new node, adding to end of myPlaylist
    if (userChoice == 'a') {
        string id;
        string songName;
        string artistName;
        int songLength;
        cout << "ADD SONG" << endl;
        cout << "Enter song's unique ID:" << endl;
        cin.ignore(); //otherwise the two statements run together
        getline(cin, id);
        cout << "Enter song's name:" << endl;
        getline(cin, songName);
        cout << "Enter artist's name:" << endl;
        getline(cin, artistName);
        cout << "Enter song's length (in seconds):" << endl;
        cin >> songLength;
        cin.ignore();

        //create new song node based on user inputs
        PlaylistNode* newSong = new PlaylistNode(id, songName, artistName, songLength);
        myPlaylist->addSong(newSong);
        cout << endl;
        PrintMenu(playlistTitle);
    }

    //removes song-- used function songNode to get name of the song user wants to remove
    //removed song with remove function
    else if (userChoice == 'd') {
        string id;
        cout << "REMOVE SONG" << endl;
        cout << "Enter song's unique ID:" << endl;
        cin.ignore();
        getline(cin, id);
        PlaylistNode* removeNode = myPlaylist->songNode(id);
        cout << '\"' << removeNode->GetSongName() << '\"' << " removed." << endl;
        myPlaylist->remove(id); //had to move this after the print statement b/c segmentation fault otherwise
        cout << endl;
        PrintMenu(playlistTitle);
    }

    //changes position of song using change_pos function
    else if (userChoice == 'c') {
        int currPos;
        int newPos;
        cout << "CHANGE POSITION OF SONG" << endl;
        cout << "Enter song's current position:" << endl;
        cin >> currPos;
        cout << "Enter new position for song:" << endl;
        cin >> newPos;
        myPlaylist->change_pos(currPos, newPos);
        cout << endl;
        PrintMenu(playlistTitle);
    }

    //outputs songs by a specific artist using function printArtistSongs
    else if (userChoice == 's') {
        string artist;
        cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
        cout << "Enter artist's name:" << endl;
        cin.ignore();
        getline(cin, artist);
        cout << endl;
        myPlaylist->printArtistSongs(artist);
        PrintMenu(playlistTitle);
    }

    //outputs total time of playlist using printTotalTime function
    else if (userChoice == 't') {
        cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;
        cout << "Total time: " << myPlaylist->printTotalTime() << " seconds" << endl;
        cout << endl;
        PrintMenu(playlistTitle);
    }

    //outputs playlist
    else if (userChoice == 'o') {
        myPlaylist->printPlaylist(playlistTitle);
        PrintMenu(playlistTitle);
    }
    else if (userChoice == 'q') {
        //quit program;
    }
}