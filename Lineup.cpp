//
// Created by Jan Kosinski on 27.12.2016.
// Funkcje zawarte w tym pliku nie zostaly przetestowane. JKO 28.12.2016
// Podstawowe testy zostaly przeprowadzone. Nie wykazaly bledow. JKO 29.12.2016
//

#include "Lineup.h"
#include "parameters.h"

bool distanceBetweenTechnicalBreaks = false;

void Lineup::setCj(int value) {
    this->cj = value;
}

int Lineup::getCj() {
    return this->cj;
}

std::vector<int> checkDistanceBetweenTechnicalBreaks(std::vector<Task>lineup) { // funkcja sprawdza czy maksymalny odstep x pomiedzy przerwami jest zachowany
    // jezeli nie jest przesuwa pierwsza przerwe ktora niespelnia warunku w lewo o jedno zadanie. Jezeli dalej warunek nie jest spelniony funkcja jest uruchamiana rekurencyjnie az warunek bedzie spelniony
    std::vector<int>tasksOrder;
    int endOfPrvBreak = 0;  // koniec ostatniej przerwy technicznej
    int breakToLeft = -1;   // id przerwy do przsuniecia w lewo
    for (int i = 0; i<lineup.size(); i++) { // iterujemy po wszystkich zadaniach i przerwach
        if (!lineup[i].isItTask()) {   // jezeli natrafimy na przerwe
            if (endOfPrvBreak == 0) {   // jezeli to jest pierwsza przerwa
                endOfPrvBreak = lineup[i].getBeginning_2m()+lineup[i].getLen_2m();  // to zapamietujemy jej koniec
            }
            else {  // jezeli to nie jest pierwsza przerwa
                if ( (lineup[i].getBeginning_2m() - endOfPrvBreak) > maxDistBetweenBreaks) {    // to sprawdzamy czy nie zaczyna sie pozniej niz x jednostek czasu po zakonczeniu ostatniej
                    breakToLeft = lineup[i].getId();    // jezeli zaczyna sie to ustawiamy id przerwy jako do przesuniecia w lewo
                    break;  // i mozna przerwac iterowanie. Jezeli po przesunieciu przerwy warunek nadal nie bedzie spelniony funkcja zostanie odpalona jeszcze raz. REKURENCJA!
                }
                else {  // jezeli wszystko jest ok to zapamietujemy koniec przerwy
                    endOfPrvBreak = lineup[i].getBeginning_2m()+lineup[i].getLen_2m();
                }
            }
        }
    }
    if (breakToLeft == -1) {
        distanceBetweenTechnicalBreaks = true;  //wszystko jest ok. Warunek spelniony
    }
    // i przesuwamy zadania. Albo jak nie trzeba zwracamy taka sama kolejnosc jak wejsciowa
    for (int j = 0; j<lineup.size(); j++) {   // iterujemy po wszystkich elementach
        if (j==lineup.size()) {
            if (lineup[j].getId() == breakToLeft) {    //jezeli to nasza przerwa
                ;   //juz wstawilismy ta przerwe. Drugi raz nie mozna
            }
            else {
                tasksOrder.push_back(lineup[j].getId());    //wstawiamy zadanie
            }
            break;
        }
        if (lineup[j+1].getId() == breakToLeft) {   // jezeli nastepny element to przerwa do przesuniecia
            tasksOrder.push_back(lineup[j+1].getId());  //wstawiamy ja
            tasksOrder.push_back(lineup[j].getId());    //a potem zadanie
        }
        else if (lineup[j].getId() == breakToLeft) {    //jezeli to nasza przerwa
            ;   //juz wstawilismy ta przerwe. Drugi raz nie mozna
        }
        else {
            tasksOrder.push_back(lineup[j].getId());    //wstawiamy zadanie
        }
    }
    return tasksOrder;
}

void Lineup::createLineup(std::vector<int> tasksOrder) {    // JKO 28.12.2016. Dodac warunek by przerwy byly w odstepie co najwyzej x
    std::vector<int>fixedBreaks;    // wektor zawierajacy kolejnosc zadan ze zmianami tak by zachowany byl max odstep x pomiedzy przerwami
    std::vector<Task>prvLineup = this->lineup;  //tworzymy kopie poprzedniego uszeregowania
    this->lineup.clear();   //czyscimy poprzednie uszeregowanie. W to miejsce bedziemy zapisywac nowe
    int currentTime = 0;    // czas zakonczenia ostatniego zadania na pierwszej maszynie
    int prvTaskLen_2m = 0;  // czas trwania ostatniego zadania na 2 maszynie
    for (int i = 0; i<tasksOrder.size(); i++) {     // iterujemy po wektorze reprezentujacym kolejnosc zadan
        for (int j = 0; j<prvLineup.size(); j++) {   // szukamy w biezacym uszeregowaniu zdania o id takim samym jak w wektorze reprezentujacym kolejnosc
            if (tasksOrder[i] == prvLineup[j].getId()) {
                if (prvTaskLen_2m > prvLineup[j].getLen_1m()) {   // jezeli czas trwania poprzedniego zadania na drugiej maszynie jest wiekszy niz obecnego na pierwszej
                    currentTime += prvTaskLen_2m - prvLineup[j].getLen_1m(); //trzeba wstawic zadanie tak zeby jego operacja na 2m mogla zaczac sie zaraz po zakonczeniu pierwszej
                }
                prvLineup[j].setBeginning_1m(currentTime);  //ustawiamy czas rozpoczecia zadania na pierwszej maszynie
                currentTime += prvLineup[j].getLen_1m();    //ustawiamy zmienna currentTime na czas zakonczenia ostatniego zadania na pierwszej maszynie
                prvLineup[j].setBeginning_2m(currentTime);  //zmienna currentTime warunkuje od razu kiedy powinno zaczynac sie zadanie na drugiej maszynie
                this->lineup.push_back(prvLineup[j]);   // dodajemy zadanie do nowo powstalego uszeregowania
                prvTaskLen_2m = prvLineup[j].getLen_2m();   //ustawiamy zmienna informujaca nas o czasie trwania ostatniego zadania na 2m
                break;  // jezeli znajdziemy konczymy szukanie
            }
        }
    }
    distanceBetweenTechnicalBreaks = false;     //zakladamy ze warunek z odstepami miedzy przerwami nie jest spelniony. Trzeba to sprawdzic
    fixedBreaks = checkDistanceBetweenTechnicalBreaks(this->lineup);    //sprawdzamy to. Jezeli nie jest przesuwamy pierwsza przerwe ktora nie spelnia warunku
    while (!distanceBetweenTechnicalBreaks) {   //tak dlugo jak warunek nie jest spelniony
        this->createLineup(fixedBreaks);        //tworzymy uszeregowanie z przesunieta przerwa
        fixedBreaks = checkDistanceBetweenTechnicalBreaks(this->lineup);    //sprawdzamy warunek i ewentualnie dokonujemy kolejnego przesuniecia
    }
    // zliczanie sumy czasów zakończenia zadań
    this->setCj(0);
    for (int i = 0 ; i<this->lineup.size(); i++) {
        if (this->lineup[i].isItTask()) {
            this->setCj(this->getCj()+this->lineup[i].getBeginning_2m()+this->lineup[i].getLen_2m());
        }
    }
    // koniec zliczania
}


