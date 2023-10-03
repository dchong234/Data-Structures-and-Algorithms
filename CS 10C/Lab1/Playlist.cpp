#include "Playlist.h"
#include <iostream>
using namespace std;

//Default constuctor
PlaylistNode::PlaylistNode(){
  uniqueID = "none";
  songName = "none";
  artistName = "none";
  songLength = 0;
  nextNodePtr = nullptr;
}
//Parameterized constructor
PlaylistNode::PlaylistNode(string ID, string sName, string aName, int sLength){
  uniqueID = ID;
  songName = sName;
  artistName = aName;
  songLength = sLength;
  nextNodePtr = nullptr;
}
//InsertAfter() function
void PlaylistNode::InsertAfter(PlaylistNode* difNode) {
  PlaylistNode* temp = nextNodePtr;
  nextNodePtr = difNode;
  difNode->SetNext(temp);
}
//SetNext() function
void PlaylistNode::SetNext(PlaylistNode* newNode) {
  nextNodePtr = newNode;
}
//GetID() function
string PlaylistNode::GetID() const{
  return uniqueID;
}
//GetSongName() function
string PlaylistNode::GetSongName() const{
  return songName;
}
//GetArtistName() function
string PlaylistNode::GetArtistName() const{
  return artistName;
} 
//GetSongLength() function
int PlaylistNode::GetSongLength() const{
  return songLength;
}
//GetNext() function
PlaylistNode* PlaylistNode::GetNext() const{
  return nextNodePtr;
}
//PrintPlaylistNode() function
void PlaylistNode::PrintPlaylistNode(PlaylistNode* listNode) const{
  cout << "Unique ID: " << listNode->GetID() << endl;
  cout << "Song Name: " << listNode->GetSongName() << endl;
  cout << "Artist Name: " << listNode->GetArtistName() << endl;
  cout << "Song Length (in seconds): " << listNode->GetSongLength() << endl;
}
