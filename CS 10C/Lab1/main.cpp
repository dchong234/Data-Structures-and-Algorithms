#include "Playlist.h"
#include <iostream>
#include <string>
using namespace std;

void PrintMenu(string);

int main(){
  string title;
  cout << "Enter playlist's title:" << endl;
  getline(cin, title);
  cout << endl;
  PrintMenu(title);
  return 0;
}
//function for the menu
void PrintMenu(string title){
  char ch = ' ';
  string ID, songName, artistName;
  int songLength;
  PlaylistNode playlist;
  PlaylistNode* head = nullptr;
  PlaylistNode* tail = nullptr;
  PlaylistNode* curr = nullptr;
  PlaylistNode* temp = nullptr;
  while(ch != 'q')
  {
    ch = ' ';
    while(!(ch == 'a' || ch == 'd' || ch == 'c' || ch == 's' || ch == 't' || ch == 'o' || ch == 'q')){
      cout << title << " PLAYLIST MENU" << endl;
      cout << "a - Add song" << endl;
      cout << "d - Remove song" << endl;
      cout << "c - Change position of song" << endl;
      cout << "s - Output songs by specific artist" << endl;
      cout << "t - Output total time of playlist (in seconds)" << endl;
      cout << "o - Output full playlist" << endl;
      cout << "q - Quit" << endl;
      cout << endl;
      cout << "Choose an option:";
      cin >> ch;
      cout << endl;
      cin.ignore(1);
    }
  

  //"Output full playlist" menu option
  if(ch == 'o'){
    cout << title << " - OUTPUT FULL PLAYLIST" << endl;
    //if playlist is empty
    if(head == nullptr){
      cout << "Playlist is empty" << endl;
      cout << endl;
    }
    else{
      curr = head;
      int i = 1;
      while(curr != nullptr){
        cout << i << "." << endl;
        playlist.PrintPlaylistNode(curr);
        curr = curr->GetNext();
        i++;
        cout << endl;
      }
    }
  }
  //"Add song" menu item
  else if(ch == 'a'){
    cout << "ADD SONG" << endl;
    cout << "Enter song's unique ID:" << endl;
    getline(cin, ID);
    cout << "Enter song's name:" << endl;
    getline(cin, songName);
    cout << "Enter artist's name:" << endl;
    getline(cin, artistName);
    cout << "Enter song's length (in seconds):" << endl;
    cin >> songLength;
    cout << endl;
    //creates a new PlaylistNode node with inputed values
    curr = new PlaylistNode(ID, songName, artistName, songLength);
  
    //checks if playlist is empty
    if(head == nullptr){
      head = curr;
      tail = curr;
    }
    //otherwise adds the song
    else{
      temp = tail;
      tail = curr;
      temp->SetNext(curr);
    }
  }

  else if(ch == 'd'){
    cout << "REMOVE SONG" << endl;
    cout << "Enter song's unique ID:" << endl;
    getline(cin, ID);
    curr = head;

    curr = head;
    temp = curr;

    while(curr != nullptr){
      if(curr->GetID() == ID){
        songName = curr->GetSongName();
        //checks if removed song is first
        if(head == curr){
          if(head == tail)
          {
            tail = nullptr;
          }
           
          temp = head;
          head = curr->GetNext();
          delete temp;
          curr = head;
          temp = curr;
        }
      else{
        //checks if removed song is last
        if(curr == tail){
          tail = temp;
        }
        //operation for removing
        temp->SetNext(curr->GetNext());
        delete curr;
        curr = temp;
        curr = curr->GetNext();
      }
        cout << "\"" << songName << "\"" << " removed." << endl;
        cout << endl; 
      }
      else{
        temp = curr;
        curr = curr->GetNext();
      }
    }
  }

  //"Change position of song" menu option
  else if(ch == 'c'){
  int position, desired_position;
  cout << "CHANGE POSITION OF SONG" << endl;
  cout << "Enter song's current position:" << endl;
  cin >> position;
  cout << "Enter new position for song:" << endl;
  cin >> desired_position;
  
  curr = head;
  temp = head;
  int i = 1;
  //searches for the inputted songs 
  while(i < position){
      temp = curr;
      curr = curr->GetNext();
      i++;
  }
    songName = curr->GetSongName();
    
    //checks if node at position is first
    if(curr == head){
      head = curr->GetNext();
    }
    //checks if node at position is last
    else if(curr == tail){
      temp->SetNext(tail->GetNext());
      tail = temp;
    }
    else{
      temp->SetNext(curr->GetNext());
    }

    temp = head;
    i = 2;
    //finds desired position
    while(i < desired_position){
      temp = temp->GetNext();
      i++;
    }
    //if the user enters a new position that is less than 1
    if(desired_position <= 1){
      curr->SetNext(head);
      head = curr;
    }
    else{
      //if desired position is last
      if(desired_position > (position-1)){
        tail = curr;
      }
      temp->InsertAfter(curr);
    }
    cout << "\"" << songName << "\"" << " moved to position " << desired_position << endl;
    cout << endl;
    }

    //"Output songs by specific artist" menu option
    else if(ch == 's'){
      string artist;
      cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl;
      cout << "Enter artist's name:" << endl;
      getline(cin, artist);
      cout << endl;
      curr = head;
      int i = 1;

      while(curr != nullptr){
        if(curr->GetArtistName() == artist){
          cout << i << "." << endl;
          playlist.PrintPlaylistNode(curr);
          cout << endl;
        }
        i++;
        curr = curr->GetNext();
      }
    }

    //"Output total time of playlist" menu option
    else if(ch == 't'){
      int time = 0;
      curr = head;
      cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;
      while(curr != nullptr){
        time += curr->GetSongLength();
        curr = curr->GetNext();
      }
      cout << "Total time: " << time << " seconds" << endl;
      cout << endl;
    }
  }
  return;
}
