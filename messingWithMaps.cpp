//Connor Riley 1/30/23 
//learning what maps do and how they work
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>
using namespace std;
struct Song {
	string songTitle;
	int secTime;  // could also be a string
	
};

struct Album {
	map <int, Song > songMap;
	string name;
	int time;
	int nsongs;  // optional variable but makes it easier
};

struct Artist {
	map <string, Album > albumMap;
	string name;
	int time;
	int nSongs;
	Artist(string s) {
		name = s;
	}
};


int main() {
	ifstream fin;
	ofstream fout;
	string pain;
	string title, sLength, name, album, genre;
	int min, sec, totalSongTime, count = 0, trackNum;
	char colon;
	stringstream ss;
	fin.open("input.txt");
	fout.open("output.txt");
	map<string, Artist> ArtistMap;
	map<string, Artist>::iterator it;
	
	while (getline(fin, pain)) {

		istringstream iss(pain);
		if (iss >> title >> sLength >> name >> album >> genre >> trackNum) {
			for (int i = 0; i < title.length(); i++) {
				if (title[i] == '_') {
					title[i] = ' ';
				}
			}
			for (int i = 0; i < name.length(); i++) {
				if (name[i] == '_') {
					name[i] = ' ';
				}
			}
			for (int i = 0; i < album.length(); i++) {
				if (album[i] == '_') {
					album[i] = ' ';
				}
			}
			for (int i = 0; i < genre.length(); i++) {
				if (genre[i] == '_') {
					genre[i] = ' ';
				}
			}
			fout << title << " " << sLength << " " << name << " " << album << " " << genre << " " << trackNum << "\n";
			ss << sLength;
			ss >> min >> colon >> sec;
			cout << "MINUTE = " << min << " COLON LMAO -> " << colon << "  SECONDS = " << sec << "\n";
			totalSongTime = (min * 60) + sec;
			
			it = ArtistMap.find(name);


			ss.clear();
			iss.clear();
			count++;
		}


	}
	

	fin.close();
	return 0;
}

