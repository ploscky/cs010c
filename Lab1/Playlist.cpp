#include "Playlist.h"
#include <iostream>
using namespace std;

//PLAYLISTNODE CLASS
//default constructor
PlaylistNode::PlaylistNode()
    : uniqueID("none"),
      songName("none"),
      artistName("none"),
      songLength(0),
      nextNodePtr(nullptr) {}

//parameterized constructor
PlaylistNode::PlaylistNode(string id, string songName, string artistName, int length)
    : uniqueID(id),
      songName(songName),
      artistName(artistName),
      songLength(length),
      nextNodePtr(nullptr) {}

//mutator -- sets next node
void PlaylistNode::SetNext(PlaylistNode* nextNode) {
    nextNodePtr = nextNode;
}

//accessors
string PlaylistNode::GetID() const {
    return uniqueID;
}

string PlaylistNode::GetSongName() const {
    return songName;
}

string PlaylistNode::GetArtistName() const {
    return artistName;
}

int PlaylistNode::GetSongLength() const {
    return songLength;
}

PlaylistNode* PlaylistNode::GetNext() const {
    return nextNodePtr;
}

//inserts node after current node
void PlaylistNode::InsertAfter(PlaylistNode* node) {
    PlaylistNode* nextNode = nextNodePtr;
    nextNodePtr = node;
    node->SetNext(nextNode);
}

//prints the ID, song name, artist name, and song length in seconds
void PlaylistNode::PrintPlaylistNode() const {
    cout << "Unique ID: " << GetID() << endl;
    cout << "Song Name: " << GetSongName() << endl;
    cout << "Artist Name: " << GetArtistName() << endl;
    cout << "Song Length (in seconds): " << GetSongLength() << endl;
}


//PLAYLIST CLASS
//default constructor
Playlist::Playlist()
    : head(nullptr),
      tail(nullptr) {}

//destructor
Playlist::~Playlist() {
    PlaylistNode* pointerToBeDeleted = head; //declare victim node
    while (pointerToBeDeleted != nullptr) {
        PlaylistNode* nextLink = pointerToBeDeleted->GetNext(); //create temp node to iterate through list
        delete pointerToBeDeleted; //deletes nodes in playlist
        pointerToBeDeleted = nextLink;
    }
}

//copy constructor - included because destructor was included
Playlist::Playlist(const Playlist &cpy) {
    head = nullptr;
    tail = nullptr;
    for (PlaylistNode* curr = cpy.head; curr != nullptr; curr = curr->GetNext()) {
        addSong(curr); //copying in nodes into an empty list with a loop
    }
}

//copy assignment - included because destructor was included
Playlist & Playlist::operator=(const Playlist &rhs) {
    if (this == &rhs) { //prevent self-assignment
        return *this;
    }

    if (!empty()) { //if the list isn't empty, it needs to be cleared before copying in the nodes
        PlaylistNode* pointerToBeDeleted = head; //declare victim node
        while (pointerToBeDeleted != nullptr) {
            PlaylistNode* nextLink = pointerToBeDeleted->GetNext(); //create temp node to iterate through list
            delete pointerToBeDeleted; //deletes nodes in playlist
            pointerToBeDeleted = nextLink;
        }
    }

    for (PlaylistNode* curr = rhs.head; curr != nullptr; curr = curr->GetNext()) { //copying in nodes with loop
        addSong(curr);
    }
    return *this;
}

//checks if playlist is empty
//used to make printPlaylist and addSong easier
bool Playlist::empty() const {
    return (head == nullptr);
}

//prints out playlist title and playlist nodes
void Playlist::printPlaylist(string& playlistTitle) const {
    cout << playlistTitle << " - OUTPUT FULL PLAYLIST" << endl;
    if (empty()) {
        cout << "Playlist is empty" << endl << endl;
    }
    else {
        PlaylistNode* curr = head;
        int count = 1; //to print out position of each song (1., 2., etc.)

        //while loop to iterate through playlists and cout each node using the helper class function
        while (curr != nullptr) {
            cout << count << '.' << endl;
            curr->PrintPlaylistNode();
            cout << endl;
            ++count;
            curr = curr->GetNext();
        }
    }
}

//adds song to end of playlist
void Playlist::addSong(PlaylistNode* newSong) {
    //if playlist is empty, head and tail point to the new song node
    if (empty()) {
        head = newSong;
        tail = newSong;
    }
    //if playlist isn't empty, only tail changes since node is added to the end
    else {
        tail->SetNext(newSong);
        tail = newSong;
    }
}

//returns node given a unique song ID --
//trying to solve the issue of having to retrieve the song name given the id in main.cpp
PlaylistNode* Playlist::songNode(string& id) const {
    PlaylistNode* returnNode = nullptr;
    for (PlaylistNode* curr = head; curr != nullptr; curr = curr->GetNext()) {
        if (curr->GetID() == id) {
            returnNode = curr;
        }
    }
    return returnNode;
}

//removes song
void Playlist::remove(string& id) {
    PlaylistNode* prev = head;
    PlaylistNode* curr = prev->GetNext();

    //in case user wants to remove first song
    if (head->GetID() == id) {
        head = curr;
        delete prev;
        return;
    }

    while (curr != nullptr) {
        //move pointers along if curr hasn't reached id
        if (curr->GetID() != id) {
            prev = prev->GetNext();
            curr = curr->GetNext();
        }
        else {
            //delete curr
            prev->SetNext(curr->GetNext());

            //take care of tail if user wants to remove last song
            if (curr == tail) {
                tail = prev;
            }

            delete curr;
            curr = prev->GetNext();
        }
    }
}

//changes position of song from oldPos to newPos (positions 1-n)
//if new position is less than 1, move the node to the position 1 (the head)
//if new position greater than n, move the node to position n (the tail)
void Playlist::change_pos(int oldPos, int newPos) {
    int indexCounter = 1; //using indexCounter so curr pointer can move to the node to change
    PlaylistNode* prev = nullptr;
    PlaylistNode* curr = head;

    //while loop to move prev and curr together up to the oldPos
    //need curr to point to oldPos node so that it can be moved positions
    while (indexCounter < oldPos) {
        prev = curr;
        curr = curr->GetNext();
        ++indexCounter;
    }

    //remove node
    if (prev != nullptr) { //if user wants to move a node that's not head --> move prev's next
        prev->SetNext(curr->GetNext());
        if (curr == tail) { //take care of tail if user wants to move the node at tail
            tail = prev;
        }
        //not deleting or resetting curr to keep node info
    }
    else { //if user wants to move the head node --> have to reassign head
        head = curr->GetNext();
        //not deleting or resetting curr to keep node info
    }

    //insert node into newPos
    int newIndexCount = 1; //using a newIndexCount to move pointers up to newPos
    if (newPos <= 1) { //if the user entered a newPos that has index less than or equal to head
        if (empty()) { //if list is empty after "removing" curr earlier --> reassign tail
            tail = curr;
        }
        curr->SetNext(head); //curr becomes new head
        head = curr;
        cout << '\"' << curr->GetSongName() << '\"' << " moved to position 1" << endl;
    }
    else { //if the user entered a newPos that has index greater than head
        if (empty()) { //if list is empty after "removing" curr earlier
            addSong(curr); //use addSong function to assign head and tail to curr
        }
        else {
            PlaylistNode* newPrev = nullptr; //using new pointers to not mess with prev and curr pointers
            PlaylistNode* newCurr = head;

            //while loop that terminates when newCurr reaches newPos or when newCurr reaches nullptr
            //if newPos is greater than tail index, it gets moved to tail either way
            while (newIndexCount < newPos && newCurr != nullptr) {
                newPrev = newCurr;
                newCurr = newCurr->GetNext();
                ++newIndexCount;
            }
            newPrev->InsertAfter(curr); //use InsertAfter function to insert curr between newPrev and newCurr
            if (newCurr == tail) { //newPos is tail
                tail = curr;
            }
            cout << '\"' << curr->GetSongName() << '\"' << " moved to position " << newPos << endl;
        }
    }
}

//prints out nodes of a specific artist, starting with node's current pos
void Playlist::printArtistSongs(string& artist) const {
    int count = 1; //keep track of index of each song
    for (PlaylistNode* curr = head; curr != nullptr; curr = curr->GetNext()) {
        if (curr->GetArtistName() == artist) {
            cout << count << '.' << endl;
            curr->PrintPlaylistNode();
            cout << endl;
        }
        ++count;
    }
}

//prints playlist's total time
int Playlist::printTotalTime() const {
    int totalTime = 0;
    for (PlaylistNode* curr = head; curr != nullptr; curr = curr->GetNext()) {
        totalTime += curr->GetSongLength();
    }
    return totalTime;
}



