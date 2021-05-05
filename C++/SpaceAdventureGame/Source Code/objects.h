#ifndef objects_h
#define objects_h
#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <utility>
#include <windows.h>
#include <iostream>
#include <list>
#include <time.h>
#include<memory>
#define SCREEN_WIDTH GetSystemMetrics(SM_CXSCREEN) 
#define SCREEN_HEIGHT GetSystemMetrics(SM_CYSCREEN)
#define SCALE_X (float)(1.0 + ((SCREEN_WIDTH  - 1920)/1920)) 
#define SCALE_Y (float)(1.0 + ((SCREEN_HEIGHT - 1080)/1080))


/*WERSJA FINALNA*/


/*KLASA object REPREZENTUJE OBIEKT I JEGO PODSTAWOWE PARAMETRY. JEST TO KLASA BAZOWA PO KTOREJ DZIEDZICZA POZOSTALE KLASY OBJEKTOW.*/
class object
{
protected:
	
	sf::FloatRect hitbox;				//OBSZAR ZAJMOWANY PRZEZ OBIEKT
	std::pair < int, int> position;		//POZYCJA OBIEKTU
	sf::Texture* texture = nullptr;		//TEKSTURA OBIEKTU
public:
	object() {  };
	object( int x,  int y, sf::Texture* texture_)  //KONSTRUKTOR PRZYJMUJE POZYCJE NOWEGO OBIEKTU ORAZ TEKSTURE, KTORA BEDZIE REPREZENTOWAL
	{
		position.first = x;
		position.second = y;
		texture = texture_;
	}
	std::pair < int,  int> show_coordinates();  //METODA ZWRACAJACA POZYCJE OBIEKTU
	sf::FloatRect show_hitbox();				//METODA ZWRACAJACA OBSZAR ZAJMOWANY PRZEZ OBIEKT
	void draw(sf::RenderWindow& window);		//METODA RYSUJACA OBIEKT NA SCENIE
	bool colision(sf::FloatRect other_object);	//METODA SPRAWDZAJACA CZY NIE DOSZLO DO KOLIZJI Z DRUGIM OBIEKTEM
	virtual void movement(int x, int y) = 0;	//WIRTUALNA METODA ZMIENIAJACA POZYCJE OBIEKTU
	
};

/*KLASA object_with_timers  REPREZENTUJE OBJEKTY, KTORE POSIADAJA SWOJE WLASNE ZEGARY ORAZ METODY UZYWAJACE ZEGAROW. 
ZEGARY UZYWANE SA PODCZAS WYZNACZANIA ODSTEPU CZASU POMIEDZY TWORZENIEM KOLEJNYCH OBIEKTOW. DZIEDZICZY PO KLASIE object.*/
class object_with_timers: public object
{
	sf::Clock clock;
	sf::Time time;
public:
	object_with_timers() {}
	object_with_timers(int x, int y, sf::Texture* texture_): object(x,y,texture_) {} //KONSTRUKTOR WYKORZYSTUJACY TWORZENIE OBIEKTU KLASY object
	sf::Time check_time();				//METODA ZWRACA USTAWIONY WCZESNIEJ CZAS
	sf::Time check_clock();				//METODA ZWRACA CZAS OD OSTATNIEGO RESETU ZEGARA
	void change_time(float value);		//METODA DODAJE DO CZASU WARTOSC Z ARGUMENTU
	void reset_clock();					//METODA RESETUJE ZEGAR
	void reset_time();					//METODA ZERUJE CZAS
};

/*KLASA object_with_shared_timer REPREZENTUJE OBIEKTY, KTORE POSIADAJA WSPOLNY, STATYCZNY ZEGAR. DZIEDZICZY PO KLASIE object.*/
class starship;	//WCZESNIEJSZA DEKLARACJA KLASY starship, POTRZEBNA DLA METODY WIRTUALNEJ colision_action(starship & starship_)
class object_with_shared_timer : public object
{
	static sf::Clock shared_clock;
	static sf::Time shared_time;
public:
	object_with_shared_timer() {}
	object_with_shared_timer(int x, int y, sf::Texture* texture_) : object(x, y, texture_) {}
	static sf::Time check_shared_time();				//METODA ZWRACA USTAWIONY WCZESNIEJ CZAS
	static sf::Time check_shared_clock();				//METODA ZWRACA CZAS OD OSTATNIEGO RESETU ZEGARA
	static void change_shared_time(float value);		//METODA DODAJE DO CZASU WARTOSC Z ARGUMENTU
	static void reset_shared_clock();					//METODA RESETUJE ZEGAR
	static void reset_shared_time();					//METODA ZERUJE CZAS
	virtual void colision_action(starship &starship_) = 0;  //METODA WIRTUALNA OKRESLAJACA AKCJE JAKA NASTAPI PODCZAS KOLIZJI Z OBIEKTEM KLASY starship
};

/*KLASA missile REPREZENTUJE OBIEKTY POCISKOW, KTORE MOGA ZOSTAC WYSTRZELONE PRZEZ STATEK GRACZA, STATKI OBCYCH(OBIEKTY KLASY alien) LUB BOSSA(OBIEKT KLASY boss).
KLASA DZIEDZICZY PO KLASIE object. DODANY ZOSTAL ATRYBUT OKRESLAJACY KIERUNEK LOTU POCISKU ORAZ METODY SPRAWDZAJACE CZY OBIEKT JEST POZA EKRANEM ORAZ ZWRACAJACE KIERUNEK LOTU POCISKU */
class missile : public object
{
	int direction=0;   //KIERUNEK LOTU POCISKU WYKORZYSTYWANY DLA POCISKOW WYSTRZELONYCH PRZEZ OBIEKT KLASY boss
public:
	missile() {};
	missile(int x, int y, int direction, sf::Texture* texture_) : object(x, y, texture_) { this->direction = direction; }
	void movement(int x, int y);	//PRZYSLONIECIE METODY WIRTUALNEJ KLASY object
	bool out_of_range();			//METODA SPRAWDZAJACA CZY OBIEKT WYSZEDL POZA ZAKRES EKRANU
	int show_direction();			//METODA ZWRACAJACA KIERUNEK LOTU POCISKU
	
};


/*KLASA starship REPREZENTUJE OBIEKT STATKU, KTOREGO KONTROLUJE GRACZ. POSIADA DODATKOWE ATRYBUTY W STOSUNKU DO KLASY Z KTOREJ DZIEDZICZY, SA TO health_points ORAZ boost_enabled. 
KLASA DZIEDZICZY PO KLASIE object_with_timers.*/
class starship : public object_with_timers
{
	int health_points = 3;   //ATRYBUT OKRESLAJACY ILOSC ZYC GRACZA
	int boost_enabled=0;	//ATRYBUT OKRESLA CZY AKTYWNE JEST WZMOCNIENIE POCISKOW GRACZA
public:
	starship() {};
	starship(int x, int y, sf::Texture* texture_) : object_with_timers(x, y, texture_) {}
	missile send_missile(sf::Texture* texture_, int direction);  //METODA ZWRACA OBIEKT KLASY missile KTORY PORUSZA SIE WE WSKAZANYM KIERUNKU
	int show_health_points();					//METODA ZWRACAJACA ILOSC ZYC GRACZA
	void change_health_points(int hp);			//METODA DODAJACA DO ANTRYBUTU health_points WSKAZANA LICZBE
	void set_health_points(int hp);				//METODA USTAWIAJACA ILOSC ZYCIA GRACZA
	void move(int movement_speed);				//METODA ODPOWIEDZIALNA ZA KIERUNEK LOTU STATKU GRACZA W ZALEZNOSCI OD WCISNIETEGO KLAWISZA
	void movement(int x, int y);				//PRZYSLONIECIE METODY WIRTUALNEJ KLASY object
	void set_position(int x, int y);			//METODA USTAWIAJACA POZYCJE STATKU
	void change_boost_status(int status);		//METODA ZMIENIAJACA ATRYBUT boost_enabled
	int show_boost_status();					//METODA ZWRACAJACA AKTUALNA WARTOSC ATRYBUTU boost_enabled
};


/*KLASA meteor REPREZENTUJE OBIEKTY METEORYTOW, KTORE NALEZY ZNISZCZYC LUB OMINAC. METEORY POJAWIAJA SIE ROWNO Z GORNA KRAWEDZIA EKRANU ORAZ PORUSZAJA SIE W LOSOWYCH KIERUNKACH.
ZAWIERA DODATKOWE ANTRYBUTY, TAKIE JAK LICZNIKI STWORZONYCH I ZNISCZONYCH OBIEKTOW
KLASY meteor, KIERUNKI W KTORYCH MA PORUSZAC SIE METEOR ORAZ STATYCZNY ZEGAR ORAZ CZAS, DLA KONTROLOWANIA CZASU POWSTAWANIA KOLEINYCH OBIEKTOW. KLASA DZIEDZICZY PO KLASIE object.*/
class meteor : public object
{

	int direction_y=0; // 0 LECI W DOL, 1 LECI W GORE
	int direction_x= 0; // 0 LECI W PRAWO , 1 LECI W LEWO
	static int destroyed;	//ATRYBUT OKRESLAJACY OLISC ZNISZCZONYCH OBIEKTOW
	static sf::Clock meteors_clock;
	static sf::Time meteors_time;
public:
	meteor() {};
	meteor(int x, int y, sf::Texture* texture_, int z) : object(x, y, texture_) { direction_x = z;}
	int show_direction_x();//METODA ZWRACAJACA KIERUNEK X
	int show_direction_y();//METODA ZWRACAJACA KIERUNEK Y
	void movement(int x, int y);//PRZYSLONIECIE METODY WIRTUALNEJ KLASY object
	static int show_destroyed(); //METODA ZWRACAJACA ILOSC ZNISZCZONYCH OBIEKTOW
	static void zero_destroyed();// METODA ZERUJACA ILOSC ZNISZCZONYCH OBIEKTOW
	void add_destroyed(); // METODA DODAJACA ZNISZCZONY OBIEKT

	//ZARZADZANIE CZASEM STATYCZNYM
	static sf::Time check_static_time();
	static sf::Time check_static_clock();
	static void change_static_time(float value);
	static void reset_static_clock();
	static void reset_static_time();

};

/*KLASA alien REPREZENTUJE OBIEKTY OBCYCH, KTORE NALEZY ZNISZCZYC. OBCY POTRAFIA STRZELAC POCISKAMI ORAZ PORUSZAJA SIE
OD JEDNEJ KRAWEDZI EKRANU DO DRUGIEJ. KLASA DZIEDZICZY PO KLASIE object_with timers.*/
class alien : public object_with_timers
{
	static int destroyed;	//ATRYBUT OKRESLAJACY OLISC ZNISZCZONYCH OBIEKTOW
	static sf::Clock aliens_clock;
	static sf::Time aliens_time;
	int direction=0; //  0 LECI W PRAWO , 1 LECI W LEWO
public:
	alien(){};
	alien( int x,  int y, sf::Texture* texture_, int direction_) : object_with_timers(x, y, texture_),direction(direction_) {}
	missile send_missile(sf::Texture* texture_,int direction_);
	int show_direction();//METODA ZWRACAJACA KIERUNEK
	void movement(int x, int y);//PRZYSLONIECIE METODY WIRTUALNEJ KLASY object
	static int show_destroyed(); //METODA ZWRACAJACA ILOSC ZNISZCZONYCH OBIEKTOW
	static void zero_destroyed();// METODA ZERUJACA ILOSC ZNISZCZONYCH OBIEKTOW
	void add_destroyed(); // METODA DODAJACA ZNISZCZONY OBIEKT

	//ZARZADZANIE CZASEM STATYCZNYM
	static sf::Time check_static_time();
	static sf::Time check_static_clock();
	static void change_static_time(float value);
	static void reset_static_clock();
	static void reset_static_time();


};
/*KLASA boost REPREZENTUJE OBIEKTY ULEPSZENIA POCISKOW. JESLI STATEK GRACZA UDERZY W OBIEKT KLASY boost NASTAPI ZMIANA ATRYBUTU boost_enable Z 0 NA 1
LUB 1 NA 0. BOOST ULEPSZA PODSTAWOWE POCISKI GRACZA NA SZYBSZE, LECZ O MNIEJSZEJ POWIERZCHNI. RAZEM Z KLASA heal DZIELI WSPOLNY ZEGAR. KLASA DZIEDZICZY PO KLASIE object_with_shared_timer.*/
class boost : public object_with_shared_timer
{
public:
	boost() {};
	boost( int x,  int y, sf::Texture* texture_) : object_with_shared_timer(x, y, texture_) {}
	void movement(int x, int y);//PRZYSLONIECIE METODY WIRTUALNEJ KLASY object
	void colision_action(starship& starship_);//METODA OKRESLA ZDARZENIE PO KOLIZJI Z OBIEKTEM KLASY starship

};

/*KLASA heal REPREZENTUJE OBIEKTY DODATKOWEGO ZYCIA. JESLI STATEK GRACZA UDERZY W OBIEKT KLASY heal ZYCIE GRACZA ZWIEKSZA SIE O 1. KLASA DZIEDZICZY PO KLASIE object_with_shared_timer.*/
class heal : public object_with_shared_timer
{
public:
	heal() {};
	heal( int x,  int y, sf::Texture* texture_) : object_with_shared_timer(x, y, texture_) {}
	void movement(int x, int y);//PRZYSLONIECIE METODY WIRTUALNEJ KLASY object
	void colision_action(starship& starship_);//METODA OKRESLA ZDARZENIE PO KOLIZJI Z OBIEKTEM KLASY starship


};

/*KLASA boss REPREZENTUJE OBIEKT BOSSA. BOSS POTRAFI WYSTRZELIC KILKA POCISKOW NARAZ, LECZ NIE PORUSZA SIE. GRA KONCZY SIE PO TYM GDY ZREDUKUJEMY ZYCIE BOSSA DO 0.
KLASA DZIEDZICZY PO KLASIE object_with_timers.*/
class boss : public object_with_timers
{
	int hp=100; //ATRYBUT OKRESLAJACY ZYCIE BOSSA
public:
	boss() {};
	boss(int x, int y, sf::Texture* texture_) : object_with_timers(x, y, texture_) {}
	missile send_missile(sf::Texture* texture, int direction); //METODA ZWRACAJACA OBIEKT KLASY missile
	int show_hp();	//METODA ZWRACAJACA ILOSC ZYCIA BOSSA
	void change_hp(int change);	//METODA DODAJACA DO ZYCIA BOSSA OKRESLONA WARTOSC
	void set_hp(int hp);	//METODA USTAWIAJACA ZYCIE BOSSA
	void movement(int x, int y);//PRZYSLONIECIE METODY WIRTUALNEJ KLASY object
};




#endif