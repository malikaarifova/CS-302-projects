#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>
using namespace std;
struct Song {
	string songTitle, songTime;
	Song() {};
	Song(string n, string t) {
		songTitle = n;
		songTime = t;
	}

};

struct Album {
	map <int, Song > songMap;
	string albumName;
	int albumTime;
	int albumNsongs;  // optional variable but makes it easier
	Album() {};
	Album(string s) {
		albumName = s;
		albumNsongs = 1;
		albumTime = 0;
	}
};

struct Artist {
	map <string, Album > albumMap;
	string artistName;
	int artistTime;
	int artistNsongs;
	Artist() {};
	Artist(string s) {
		artistName = s;
		artistNsongs = 1;
		artistTime = 0;
	}
};
int main(int argc, char* argv[])
{
	ifstream fin;
	string lineData, title, sLength, name, album, genre;
	int min, sec, totalSongTime, trackNum;
	char colon;
	stringstream ss;
	map<string, Artist> artistMap;
	map<string, Artist>::iterator artistItr;
	map<string, Album>::iterator albumItr;
	map<int, Song>::iterator songItr;
	fin.open(argv[1]);

	while (getline(fin, lineData)) {
		istringstream iss(lineData);
		iss >> title >> sLength >> name >> album >> genre >> trackNum;
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
		ss << sLength;
		ss >> min >> colon >> sec;
		totalSongTime = ((min * 60) + sec);

		artistItr = artistMap.find(name);
		//if artist doesnt exist yet
		if (artistItr == artistMap.end()) {
			//add artist to map
			artistMap.insert(make_pair(name, Artist(name)));
			artistMap[name].artistTime += totalSongTime;

			//make an album map and insert pair, set time of album += totalSongtime
			artistMap[name].albumMap.insert(make_pair(album, Album(album)));
			artistMap[name].albumMap[album].albumTime += totalSongTime;

			//add song in the song map, key = tracknum, sets the title and the length in analog time min:sec
			artistMap[name].albumMap[album].songMap.insert(make_pair(trackNum, Song(title, sLength)));
		}
		//if the artist does exist
		else if (artistItr != artistMap.end()) {
			//add 1 to artist nSongs, add totalSongTime to artist time;
			artistItr->second.artistNsongs += 1;
			artistItr->second.artistTime += totalSongTime;
			albumItr = artistItr->second.albumMap.find(album);
			//if the album doesnt exist, add the album to the album map, add the total length to album time
			if (albumItr == artistItr->second.albumMap.end()) {
				artistItr->second.albumMap.insert(make_pair(album, Album(album)));
				artistItr->second.albumMap[album].albumTime += totalSongTime;

				//songItr = artistItr->second.albumMap[album].songMap.find(trackNum);
				//if song doesnt exist
				//may need to be if statement but i doubt
				artistItr->second.albumMap[album].songMap.insert(make_pair(trackNum, Song(title, sLength)));

			}
			//if the album exists, add the total time and add 1 to albumNsongs
			else if (albumItr != artistItr->second.albumMap.end()) {
				artistItr->second.albumMap[album].albumTime += totalSongTime;
				artistItr->second.albumMap[album].albumNsongs += 1;
				artistItr->second.albumMap[album].songMap.insert(make_pair(trackNum, Song(title, sLength)));
			}

		}

		iss.clear();
		ss.clear();
	}
	for (artistItr = artistMap.begin(); artistItr != artistMap.end(); artistItr++) {
		cout << artistItr->second.artistName << ": " << artistItr->second.artistNsongs << ", " << (artistItr->second.artistTime) / 60;
		if ((artistItr->second.artistTime % 60) >= 10) {
			cout << ":" << (artistItr->second.artistTime) % 60 << "\n";
		}
		else if ((artistItr->second.artistTime % 60) < 10) {
			cout << ":0" << (artistItr->second.artistTime) % 60 << "\n";
		}
		for (albumItr = artistItr->second.albumMap.begin(); albumItr != artistItr->second.albumMap.end(); albumItr++) {
			cout << "        " << albumItr->second.albumName << ": " << albumItr->second.albumNsongs << ", " << (albumItr->second.albumTime) / 60;
			if ((albumItr->second.albumTime % 60) >= 10) {
				cout << ":" << (albumItr->second.albumTime) % 60 << "\n";
			}
			else if ((albumItr->second.albumTime % 60) < 10) {
				cout << ":0" << (albumItr->second.albumTime) % 60 << "\n";
			}
			for (songItr = albumItr->second.songMap.begin(); songItr != albumItr->second.songMap.end(); songItr++) {
				cout << "                " << songItr->first << ". " << songItr->second.songTitle << ": " << songItr->second.songTime << "\n";
			}
		}
	}

	fin.close();
}

