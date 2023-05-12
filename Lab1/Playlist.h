#pragma once
#include <string>
using namespace std;

//helper class dealing with individual nodes
class PlaylistNode {
    public:
        //default constructor
        PlaylistNode();

        //parameterized constructor
        PlaylistNode(string id, string songName, string artistName, int length);

        //mutator-- sets node after current
        void SetNext(PlaylistNode* nextNode);

        //accessors
        string GetID() const;
        string GetSongName() const;
        string GetArtistName() const;
        int GetSongLength() const;
        PlaylistNode* GetNext() const;

        //inserts node after current node
        void InsertAfter(PlaylistNode* node);

        //prints current node
        void PrintPlaylistNode() const;
    
    private:
        string uniqueID;
        string songName;
        string artistName;
        int songLength;
        PlaylistNode* nextNodePtr;

};

//playlist class (using helper class) dealing with the entire playlist
class Playlist {
    public:
        //default constructor
        Playlist();

        //destructor
        ~Playlist();

        //copy constructor
        Playlist(const Playlist &cpy);

        //copy assignment
        Playlist& operator=(const Playlist &rhs);

        //checks if playlist is empty
        bool empty() const;

        //prints out playlist title and playlist nodes
        void printPlaylist(string& playlistTitle) const;

        //adds song to end of playlist
        void addSong(PlaylistNode* newSong);

        //removes song
        void remove(string& id);

        //changes position of song from oldPos to newPos (positions 1-n)
        //if new position is less than 1, move the node to the position 1 (the head)
        //if new position greater than n, move the node to position n (the tail)
        void change_pos(int oldPos, int newPos);

        //prints out nodes of a specific artist, starting with node's current pos
        void printArtistSongs(string& artist) const;

        //prints playlist's total time
        int printTotalTime() const;

        //returns node given a unique song ID
        PlaylistNode* songNode(string& id) const;

    private:
        PlaylistNode* head;
        PlaylistNode* tail;
};