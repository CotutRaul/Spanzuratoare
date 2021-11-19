#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cstring>
#include <ctime>

using namespace std;

ifstream fin("savefile.txt");

int Check(char text[100]){
    for(int i=0;i<strlen(text);i++)
        if(isdigit(text[i])==0)
            return -1;
    return atoi(text);
}


class Word
{
    char *word;
    char *game_word;
    int word_lenght;
    int underlines;
    int tries;
public:
    Word(){
        this->setWord("");
        this->setGame_word("");
        this->setWord_lenght(0);
        this->setUnderlines(0);
        this->setTries(5);
    }
    Word(char *word, char *game_word, int word_lenght,int underlines, int tries){
        this->setWord(word);
        this->setGame_word(game_word);
        this->setWord_lenght(word_lenght);
        this->setUnderlines(underlines);
        this->setTries(tries);
    }
    ~Word(){
        delete [] word;
        delete [] game_word;
    }

    void createWord()
    {
        ifstream fin("words.txt");

        srand((int)time(0));
        int read=rand()%50;
        for(int i=0;i<read;i++)
            fin.getline(this->word,100);
        //strcpy(this->word+strlen(this->word)-1,this->word+strlen(this->word));
        this->word_lenght=strlen(this->word);
        strcpy(this->game_word,this->word);
        for(int i=1;i<this->word_lenght-1;i++)
        {
            if(this->game_word[i]!=this->word[0] && this->game_word[i]!=this->word[this->word_lenght-1])
            {
                this->game_word[i]='_';
                this->underlines++;
            }
        }

        fin.close();
    }
    void checkLetter(char c)
    {
        int ok=0;
        for(int i=0;i<this->word_lenght-1;i++)
            if(this->word[i]==c && this->game_word[i]=='_')
            {
                ok=1;
                this->game_word[i]=c;
                this->underlines--;
            }
        if(ok==0)
            this->tries--;
    }
    void checkWord(char c[100])
    {
        if(strcmp(this->word,c)==0)
        {
            strcpy(this->game_word,this->word);
            this->underlines=0;
        }
        else
        {
            this->tries--;
        }
    }


    void setWord(char *word){
        if(word!=NULL)
        {
            this->word=new char[100];
            strcpy(this->word,word);
        }
    }
    char *getWord() const{
        return this->word;
    }

    void setGame_word(char *game_word){
        if(game_word!=NULL)
        {
            this->game_word=new char[100];
            strcpy(this->game_word,game_word);
        }
    }
    char *getGame_word() const{
        return this->game_word;
    }
    void setUnderlines(int underlines)
    {
        this->underlines=underlines;
    }
    int getUnderlines()const
    {
        return this->underlines;
    }
    void setWord_lenght(int word_lenght){
        this->word_lenght=word_lenght;
    }
    int getWord_lenght() const{
        return this->word_lenght;
    }

    void setTries(int tries){
        this->tries=tries;
    }
    int getTries() const{
        return this->tries;
    }

};

class Game
{
    int score;
    int nr_words;
public:

    friend ifstream &operator >> (ifstream &in, Game &g)
    {
        in>>g.score;
        in>>g.nr_words;
        return in;
    }

    friend ostream &operator << (ostream &out, Game &g)
    {
        out<<"Scor: "<<g.score<<" --- cuvinte: "<<g.nr_words;
        return out;
    }
    friend ofstream &operator << (ofstream &out, Game &g)
    {
        out<<g.score<<" "<<g.nr_words<<endl;
        return out;
    }


    Game(){
        this->setScore(0);
        this->setNr_words(0);
    }
    Game(int score, int nr_words){
        this->setScore(score);
        this->setNr_words(nr_words);
    }
    ~Game(){}

    void setScore(int score){
        this->score=score;
    }
    int getScore() const{
        return this->score;
    }

    void setNr_words(int nr_words){
        this->nr_words=nr_words;
    }
    int getNr_word() const{
        return this->nr_words;
    }
    void operator +=(const Game &g)
    {
        score=g.score;
        nr_words=g.nr_words;
    }

};


class User
{
    char *name;
    int score_max;
    int nr_games;
    Game games[100];
public:

    friend ifstream &operator >> (ifstream &in, User &u)
    {
        in.getline(u.name,100);
        in>>u.score_max>>u.nr_games;
        for(int i=0;i<u.nr_games;i++)
            fin>>u.games[i];
        return in;
    }
    friend ostream &operator << (ostream &out, User &u)
    {
        out<<"Nume: "<<u.name<<"\nScor maxim: "<<u.score_max<<"\nNumar jocuri: "<<u.nr_games<<"\n\nIstoric:\n";
        for(int i=0;i<u.nr_games;i++)
            cout<<i+1<<". "<<u.games[i]<<endl;
        return out;
    }
    friend ofstream &operator << (ofstream &out, User &u)
    {
        ofstream fout("savefile.txt",ios::app);
        out<<u.name<<endl<<u.score_max<<endl<<u.nr_games<<endl;
        for(int i=0;i<u.nr_games;i++)
            fout<<u.games[i];
        fout.close();
        return out;
    }
    User(){
        this->setName("");
        this->setScore_max(0);
        this->setNr_games(0);
    }
    User(char *name, int score_max, int nr_games){
        this->setName(name);
        this->setScore_max(score_max);
        this->setNr_games(nr_games);
    }
    ~User(){
        delete [] name;
    }

    void setName(char *name){
        if(name!=NULL)
        {
            this->name=new char[100];
            strcpy(this->name,name);
        }
    }
    char *getName() const{
        return this->name;
    }

    void setScore_max(int score_max){
        this->score_max=score_max;
    }
    int getScore_max() const{
        return this->score_max;
    }

    void setNr_games(int nr_games){
        this->nr_games=nr_games;
    }
    int getNr_games() const{
        return this->nr_games;
    }

    void operator = (const User &u){
        this->setName(u.getName());
        this->setScore_max(u.getScore_max());
        this->setNr_games(u.getNr_games());
    }
    void operator +=(const Game &g)
    {
        games[nr_games]+=g;
        nr_games++;
        if(g.getScore()>score_max)
            score_max=g.getScore();
    }


};
void Meniu();
User user_list[100];
int nr_users=0;

int CheckUser(char nume[100])
{
    for(int i=0;i<nr_users;i++)
        if(strcmp(user_list[i].getName(),nume)==0)
            return i;
    return -1;
}


void DrawHangman(int tries)
{
    switch(tries)
    {
        case 5:
            cout<<"  +---+\n  |   |\n      |\n      |\n      |\n      |\n=========\n";
            break;
        case 4:
            cout<<"  +---+\n  |   |\n  O   |\n  |   |\n      |\n      |\n=========\n";
            break;
        case 3:
            cout<<"  +---+\n  |   |\n  O   |\n /|   |\n      |\n      |\n=========\n";
            break;
        case 2:
            cout<<"  +---+\n  |   |\n  O   |\n /|\\  |\n      |\n      |\n=========\n";
            break;
        case 1:
            cout<<"  +---+\n  |   |\n  O   |\n /|\\  |\n /    |\n      |\n=========\n";
            break;
        case 0:
            cout<<"  +---+\n  |   |\n  O   |\n /|\\  |\n / \\  |\n      |\n=========\n";
            break;
    }
}

int PlayingWord(Game &newgame)
{
    Word w;
    w.createWord();
    char letter_used[27]="";
    char guess[100];
    int ok=0;
    while(w.getTries()!=0 && w.getUnderlines()!=0)
    {
        system("cls");
        cout<<"Scor: "<<newgame.getScore()<<"    Cuvinte ghicite: "<<newgame.getNr_word()<<endl<<endl;
        DrawHangman(w.getTries());
        cout<<"Litere folosite:"<<letter_used<<endl<<endl;
        char aux[100];
        strcpy(aux,w.getGame_word());
        for(int i=0;i<strlen(aux);i++)
        {
            cout<<aux[i]<<" ";
        }
        cout<<endl<<endl;
        cin.getline(guess,100);
        if(strlen(guess)==1)
        {
            w.checkLetter(guess[0]);
            strcat(letter_used," ");
            strcat(letter_used,guess);
        }
        else
        {
            w.checkWord(guess);
        }
    }
    if(w.getTries()!=0)
    {
        newgame.setScore(newgame.getScore()+w.getWord_lenght());
        newgame.setNr_words(newgame.getNr_word()+1);
        ok=1;
    }
    system("cls");
    cout<<"Scor: "<<newgame.getScore()<<"    Cuvinte ghicite: "<<newgame.getNr_word()<<endl<<endl;
    DrawHangman(w.getTries());
    cout<<"Litere folosite:"<<letter_used<<endl<<endl;
    cout<<w.getWord()<<endl<<endl;
    cin.get();
    return ok;
}

void Save();
void ClasamentMaker();
void StartGame()
{

    Game newgame;
    char newUserName[100];
    while(PlayingWord(newgame)==1);
    system("cls");
    if(newgame.getScore()!=0)
    {
        cout<<"Scor final: "<<newgame.getScore()<<"   Cuvinte ghicite: "<<newgame.getNr_word()<<endl<<endl;
        cout<<"Introdu numele jucatorului: ";
        cin.getline(newUserName,100);
        if(CheckUser(newUserName)!=-1)
        {
            user_list[CheckUser(newUserName)]+=newgame;
        }
        if(CheckUser(newUserName)==-1)
        {
            user_list[nr_users].setName(newUserName);
            user_list[nr_users].setScore_max(newgame.getScore());
            user_list[nr_users]+=newgame;
            nr_users++;
        }
        ClasamentMaker();
    }
    Save();
    Meniu();
}

void ClasamentMaker()
{
    int CL[nr_users+2];
    ofstream fout("Clasament.txt");
    int aux;
    for(int i=0;i<nr_users;i++)
    {
        CL[i]=i;
    }
    for(int i=0;i<nr_users-1;i++)
    {
        for(int j=i+1;j<nr_users;j++)
        {
            if(user_list[CL[i]].getScore_max()<user_list[CL[j]].getScore_max())
            {
                aux=CL[i];
                CL[i]=CL[j];
                CL[j]=aux;
            }
        }
    }
    for(int i=0;i<nr_users;i++)
    {
        fout<<i+1<<". "<<user_list[CL[i]].getName()<<"   Score: "<<user_list[CL[i]].getScore_max()<<endl;
    }
    fout.close();
}

void Clasament()
{
    system("cls");
    cout<<"-=-=-=Clasament=-=-=-"<<endl<<endl;
    ifstream fin("Clasament.txt");
    char rand[100];
    while(fin.getline(rand,100))
    {
        cout<<rand<<endl;
    }
    fin.close();
    cin.get();
    Meniu();
}

void IstoricUser(int i)
{
    system("cls");
    cout<<user_list[i];

    cin.get();
    Meniu();
}

void Istoric()
{
    cout<<"-=-=-=Istoric=-=-=-\n\n";

    for(int i=0;i<nr_users;i++)
    {
        cout<<i+1<<". "<<user_list[i].getName()<<endl;
    }
    cout<<"\nIntroduceti numele sau numarul / Back pentru meniu: ";
    char nume[50];
    cin.getline(nume,50);
    if(strcmp(nume,"Back")==0)
        Meniu();

    if(Check(nume)-1>-1 && Check(nume)-1<nr_users)
    {
        system("cls");
        IstoricUser(Check(nume)-1);
    }
    if(CheckUser(nume)==-1)
    {
        system("cls");
        cout<<"Nu exista acel utilizator!\n";
        Istoric();
    }
    if(CheckUser(nume)!=-1)
    {
        system("cls");
        IstoricUser(CheckUser(nume));
    }
}

void CitireUsers()
{
    fin>>nr_users;
    for(int i=0;i<nr_users;i++)
    {
        fin.ignore();
        fin>>user_list[i];
    }

    fin.close();
}

void Save()
{
    remove("savefile.txt");
    ofstream fout("savefile.txt",ios::app);
    fout<<nr_users<<endl;
    for(int i=0;i<nr_users;i++)
        fout<<user_list[i];
    fout.close();
}

void Meniu(){
    system("cls");
    cout<<"-=-=-=SPANZURATOAREA=-=-=- \n\n";
    char *menu[]={
        "Incepe joc",
        "Vezi clasament",
        "Vezi istoric jocuri pentru un utilizator",
        "Resetare",

    };
    int i,n;
    n=4;
    for(i=0;i<n;++i){
        cout<<i+1<<". "<<menu[i]<<"\n";
    }
    cout<<"0. Iesire\n";
    cout<<"Introduceti optiunea dorita: ";

    char choicetxt[100];
    int choice;
    cin.getline(choicetxt,100);
    choice=Check(choicetxt);

    switch(choice){
        case 1:
        {
            system("cls");
            StartGame();
            break;
        }
        case 2:
        {
            system("cls");
            Clasament();
            break;
        }
        case 3:
        {
            system("cls");
            Istoric();
            break;
        }
        case 4:
        {
            remove("savefile.txt");
            remove("Clasament.txt");
            exit(0);
            break;
        }
        case 0:
        {
            Save();
            exit(0);
            break;
        }
        default:
        {
            system("cls");
            cout<<"Alegeti o optiune valida!\n";
            Meniu();
            break;
        }
    }
}

int main()
{
    if(fin)
    {
        CitireUsers();
        ClasamentMaker();
    }

    Meniu();
    Save();

    return 0;
}
