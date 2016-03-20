#include <stdio.h>
#include <sqlite3.h>
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdlib.h>
 #include "sqlite3.h"
#include <vector>
#include <cstdlib>
#include <boost/algorithm/string.hpp>
using namespace std;

void print( vector <string> & v )
{
  for (size_t n = 0; n < v.size(); n++)
    cout << "\"" << v[ n ] << "\"\n";
  cout << endl;
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
FILE *f = fopen("output.csv", "a");
   int i;
   const char *sep = "";
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
 	fprintf(f,"%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");

   }
   printf("\n");


fclose(f);
   return 0;
}

class artist{
int artist_id;
char artist_name[100];
};

class cd{
int id;
char title[70];
int artistcd_id;
char catalog[70];
};

class track{
int trackid;
int cd_id;
char track_title[70];
};

int main(int argc, char* argv[])
{
std::string artist[100];
string cd[100];
string track[100];
int id[100];
int aid[100];
int tid[100];
string line;
string trash;
int cdid[100];
string cdtitle[100];
int cdartist[100];
string cata[100];
string temp;
int i = 0;
sqlite3 *db;

   char *zErrMsg = 0;
   int rc;
 char *sql;
   rc = sqlite3_open("song.db", &db);

   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      exit(0);
   }else{
      fprintf(stderr, "Opened database successfully\n");
   }
   
   std::ifstream artistf;
   std::ifstream cdf;
	std::ifstream trackf;

artistf.open ("artist.txt");
cdf.open ("cd.txt");
trackf.open ("track.txt");
if (artistf.fail())
{
    std::cout << "open for file failed";
    exit (1);
}
if (cdf.fail())
{
    cout << "open for file failed";
    exit (1);
}
if (trackf.fail())
{
    cout << "open for file failed";
    exit (1);
}
//////////////   artist.txt ///////////

while (getline(artistf, line))
{
    istringstream iss(line);
    iss >> id[i] >> trash;
 line.erase (0,2);
artist[i] = line;
    //if (  { break; } // error
i++;
    
}
int n=0;
cout << "Saved to array" << endl;

sql = "CREATE TABLE artist("  \
         "ID INT PRIMARY KEY     NOT NULL," \
         "Name VARCHAR(100) NOT NULL);" ;
         
   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
   fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Table created successfully\n");
   }
cout << "Populated artist" << endl;

while(n < i){
cout << id[n] << " " << artist[n] << endl;
sql 	=	"INSERT INTO artist(id, name) values(1, 'Pink Floyd');"\
"insert into artist(id, name) values(2, 'Genesis');" \
"insert into artist(id, name) values(3, 'Einaudi');" \
"insert into artist(id, name) values(4, 'Melanie C');" ;

n++;
}
/* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Records created successfully\n");
   }
	

 /* Create SQL statement */
   sql = 	" SELECT * from artist";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Operation done successfully\n");
   }

//////////////   cd.txt ///////////
i=0;
string temp2;
cout << "Reading cd.txt" << endl;
while (getline(cdf, line))
{
 istringstream iss(line);
temp =line;
temp2 = line;
    iss >> cdid[i] >>trash;
 line.erase (0,2);
line.erase(line.end()-14,line.end()-0);
cdtitle[i] = line;

temp.erase(temp.end()-12,temp.end()-0);
temp.erase(temp.begin()+0,temp.end()-1);
 istringstream tss(temp);
tss >> cdartist[i];
temp2.erase(temp2.begin()+0,temp2.end()-11);
cata[i] = temp2;
cout << "artist id: " << cdartist[i] << endl;
cout << "Title: " <<cdtitle[i] << endl;
cout << "catalog: " << cata[i]<<endl;





    i++;
    
}
n=0;
cout << "Saved to array" << endl;

sql = 	"CREATE TABLE cd("  \
         "ID INT PRIMARY KEY     NOT NULL," \
         "title VARCHAR(70) NOT NULL," \
         "artist_id INTEGER NOT NULL," \
         "catalogue VARCHAR(30) NOT NULL );";
         
   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
   fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Table created successfully\n");
   }
cout << "Populated artist" << endl;

while(n < i){
//cout << id[n] << " " << cd[n] << endl;
sql 	=	"insert into cd(id, title, artist_id, catalogue) values(1, 'Dark Side of the Moon', 1, 'B000024D4P');" \
"insert into cd(id, title, artist_id, catalogue) values(2, 'Wish You Were Here', 1, 'B000024D4S');"\
"insert into cd(id, title, artist_id, catalogue) values(3, 'A Trick of the Tail', 2, 'B000024EXM');"\
"insert into cd(id, title, artist_id, catalogue) values(4, 'Selling England By the Pound', 2, 'B000024E9M');" \
"insert into cd(id, title, artist_id, catalogue) values(5, 'I Giorni', 3, 'B000071WEV');"\
"insert into cd(id, title, artist_id, catalogue) values(6, 'Northern Star', 4, 'B00004YMST');" ;

n++;
}
/* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Records created successfully\n");
   }
	

 /* Create SQL statement */
   sql = 	" SELECT * from cd";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Operation done successfully\n");
   }


//////////////   track.txt ///////////
i=0;
int trackid1[100];
int trackid2[100];
string tracktitle[100];
cout << "Reading track.txt" << endl;
while (getline(trackf, line))
{
 istringstream iss(line);

    iss >> trackid1[i] >>trash;

 line.erase (0,2);
trash.erase(0,1); 

trash.erase(trash.begin()+2, trash.end()-0);
istringstream dss(trash);
dss >> trackid2[i];
if(trackid2[i]>9)
{
n = 3;
}else{n=2;}
//cout << trash << endl;


line.erase(line.begin()+0,line.begin()+n);
tracktitle[i] = line;

 
cout << "track id1: " << trackid1[i] << endl;
cout << "track id2: " <<trackid2[i] << endl;
cout << "title: " << tracktitle[i]<<endl;

    i++;
    
}


n=0;
cout << "Saved to array" << endl;

sql = 	"CREATE TABLE track("  \
         "cd_id INTEGER NOT NULL," \
         "track_id INTEGER NOT NULL," \
         "title VARCHAR(70)," \
         "PRIMARY KEY(cd_id, track_id));";
         
   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
   fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Table created successfully\n");
   }
cout << "Populated artist" << endl;

while(n < i){
//cout << id[n] << " " << cd[n] << endl;
sql 	=	"insert into track(cd_id, track_id, title) values(1, 1, 'Speak to me');" \
"insert into track(cd_id, track_id, title) values(1, 2, 'Breathe');" \
"insert into track(cd_id, track_id, title) values(1, 3, 'On the run');" \
"insert into track(cd_id, track_id, title) values(1, 4, 'Time');" \
"insert into track(cd_id, track_id, title) values(1, 5, 'Great gig in the sky');" \
"insert into track(cd_id, track_id, title) values(1, 6, 'Mooney');" \
"insert into track(cd_id, track_id, title) values(1, 7, 'Us and them');" \
"insert into track(cd_id, track_id, title) values(1, 8, 'Any colour you like');" \
"insert into track(cd_id, track_id, title) values(1, 9, 'Brain damage');" \
"insert into track(cd_id, track_id, title) values(1, 10, 'Eclipse ');" \

"insert into track(cd_id, track_id, title) values(2, 1, 'Shine on you crazy diamond');" \
"insert into track(cd_id, track_id, title) values(2, 2, 'Welcome to the machine');" \
"insert into track(cd_id, track_id, title) values(2, 3, 'Have a cigar');" \
"insert into track(cd_id, track_id, title) values(2, 4, 'Wish you were here');" \
"insert into track(cd_id, track_id, title) values(2, 5, 'Shine on you crazy diamond pt.2');" \

"insert into track(cd_id, track_id, title) values(3, 1, 'Dance on a volcano');" \
"insert into track(cd_id, track_id, title) values(3, 2, 'Entangled');" \
"insert into track(cd_id, track_id, title) values(3, 3, 'Squonk');" \
"insert into track(cd_id, track_id, title) values(3, 4, 'Madman moon');" \
"insert into track(cd_id, track_id, title) values(3, 5, 'Robbery assault and battery');" \
"insert into track(cd_id, track_id, title) values(3, 6, 'Ripples');" \
"insert into track(cd_id, track_id, title) values(3, 7, 'Trick of the tail');" \
"insert into track(cd_id, track_id, title) values(3, 8, 'Los Endos');" \

"insert into track(cd_id, track_id, title) values(4, 1, 'Melodia Africana (part 1)');" \
"insert into track(cd_id, track_id, title) values(4, 2, 'I due fiumi');" \
"insert into track(cd_id, track_id, title) values(4, 3, 'In unaltra vita');" \
"insert into track(cd_id, track_id, title) values(4, 4, 'Melodia Africana (part 2)');" \
"insert into track(cd_id, track_id, title) values(4, 5, 'Stella del mattino');" \
"insert into track(cd_id, track_id, title) values(4, 6, 'I giorni');" \
"insert into track(cd_id, track_id, title) values(4, 7, 'Samba');" \
"insert into track(cd_id, track_id, title) values(4, 8, 'Melodia Africana (part 3)');" \
"insert into track(cd_id, track_id, title) values(4, 9, 'La nascita delle cose segrete');" \
"insert into track(cd_id, track_id, title) values(4, 10, 'Quel che resta');" \
"insert into track(cd_id, track_id, title) values(4, 11, 'Inizio');" \
"insert into track(cd_id, track_id, title) values(4, 12, 'Limbo');" \
"insert into track(cd_id, track_id, title) values(4, 13, 'Bella notte');" \
"insert into track(cd_id, track_id, title) values(4, 14, 'Canzone Africana (part 4)');" \

"insert into track(cd_id, track_id, title) values(6, 1, 'Go!');" \
"insert into track(cd_id, track_id, title) values(6, 2, 'Northern Star');" \
"insert into track(cd_id, track_id, title) values(6, 3, 'Goin Down');" \
"insert into track(cd_id, track_id, title) values(6, 4, 'I Turn To You');" \
"insert into track(cd_id, track_id, title) values(6, 5, 'If That Were Me');" \
"insert into track(cd_id, track_id, title) values(6, 6, 'Never Be The Same Again');" \
"insert into track(cd_id, track_id, title) values(6, 7, 'Why');" \
"insert into track(cd_id, track_id, title) values(6, 8, 'Suddenly Monday');" \
"insert into track(cd_id, track_id, title) values(6, 9, 'Ga Ga');" \
"insert into track(cd_id, track_id, title) values(6, 10, 'Be The One');" \
"insert into track(cd_id, track_id, title) values(6, 11, 'Closer');" \
"insert into track(cd_id, track_id, title) values(6, 12, 'Feel The Sun');"; 


n++;
}
/* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Records created successfully\n");
   }
	

 /* Create SQL statement */
   sql = 	" SELECT * from track";

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Operation done successfully\n");
   }
///////////// UPDATE///////
int input1;
int input2;
string input3;
char upt;
cout << "Which table need to be updated?\n	Enter 1 for artist\n2 for cd \n3 for track" <<endl; cin >> input1;

cout<< "enter cd id: "; cin >> input1;
cout<< "\nenter track id(0 if there is none): "; cin >> input2;
cout << "enter your new change: "; cin >> input3;


//sprintf(upt,input3);

cout << "After change." << endl;

sql = "update track set title='Money' where cd_id=1 and track_id=6;" \
        "SELECT * from track";
//cout << "heeeeeee"<<endl;
   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Operation done successfully\n");
   }
cout << "Delete all records? Y/N "; cin >> upt;
if(upt == 'Y')
{
sql = "DELETE from track; " \
       "DELETE from cd; " \
"DELETE from artist; " \
"SELECT * from track";
"SELECT * from cd";
"SELECT * from artist";

cout << "SELECT * from track" << endl;
cout << "SELECT * from cd" << endl;
cout << "SELECT * from artist" << endl;
cout << "All deleted." << endl;
   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
rc = sqlite3_exec(db, "drop table track", NULL, NULL,&zErrMsg);
rc = sqlite3_exec(db, "drop table cd", NULL, NULL,&zErrMsg);
rc = sqlite3_exec(db, "drop table artist", NULL, NULL, &zErrMsg);
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Operation done successfully\n");
   }

}

   sqlite3_close(db);

}