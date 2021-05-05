#ifndef game_h
#define game_h
#include "objects.h"

/*WERSJA FINALNA*/



/*KLASA button REPREZENTUJE OBIEKTY PRZYCZISKOW. POSIADA ATRYBUTY OKRESLAJACE TEKSTURE ZAZNACZONEGO ORAZ NIEZAZNACZONEGO PRZYCISKU, 
TEKST UMIESZCZONY NA PRZYCISKU, POZYCJE PRZYCISKU, NUMER PRZYCISKU ORAZ STATYCZNY ZEGAR. PRZYCISKI WYKORZYSTYWANE SA W MENU GLOWNYM GRY. */
class button
{
	std::pair < int, int> position; //ATRYBUT OKRESLAJACY POZYCJE PRZYCISKU
	sf::Texture* texture = nullptr;	//ATRYBUT OKRESLAJACY TEKSTURE PRZYCISKU, KTORY NIE JEST WYBRANY
	sf::Texture* texture_selected = nullptr; //ATRYBUT OKRESLAJACY TEKSTURE PRZYCISKU, KTORY JEST WYBRANY
	sf::Text text;	//ATRUBYT OKRESLAJACY TEKST WIDOCZNY NA PRZYCISKU
	static sf::Clock clock;	//STATYCZNY ZEGAR KLASY
	int button_number=0;	//ATRYBUT OKRESLAJACY NUMER PRZYCISKU
public:
	static int selected_button; //ATRYBUT STATYCZNY OKRESLAJACY, KTORY Z PRZYCISKOW JEST AKTUALNIE WYBRANY
	static int number_of_buttons;	//ATRYBUT STATYCZNY OKRESLAJACY LICZBE PPRZYCISKOW
	sf::Sprite sprite;	// ATRYBUT SLUZACY DO RYSOWANIA PRZYCISKU NA SCENIE
	button(){}
	button(std::string button_text,sf::Texture* texture_ptr1, sf::Texture* texture_ptr2,int x,int y, sf::Font& font)
	{
		button_number = number_of_buttons; //WYZNACZANIE NUMERU PRZYCISKU
		text.setString(button_text);	//WYZNACZANIE TEKSTU WIDOCZNEGO NA PRZYCISKU
		text.setFont(font);		//USTAWIENIE CZCIONKI
		text.setFillColor(sf::Color::Red);	//USTAWIENIE KOLORU TEKSTU
		text.setCharacterSize(34);		//USTAWIENIE ROZMIARU CZCIONKI
		position.first = x;  //USTAWIENIE POZYCJI PRZYCISKU
		position.second = y;
		texture=texture_ptr1;		//USTAWIENIE TEKSTURY
		texture_selected = texture_ptr2;
		text.setPosition((position.first - text.getLocalBounds().width / 2), (position.second - text.getLocalBounds().height / 2));	//USTAWIENIE POZYCJI TEKSTU
		number_of_buttons++;	//INKREMENTACJA LICZBY PRZYCISKOW
	}
	void draw(sf::RenderWindow& window); //METODA SLUZACA TO RYSOWANAI OBIEKTU NA SCENIE
	int get_button_number(); //METODA ZWRACAJACA NUMER PRZYCISKU
	static sf::Time show_time();	//METODA ZWRACAJACA CZAS OD OSTATNIEGO RESETU ZEGARA
	static void reset_time();		//METODA RESETUJACA ZEGAR
	~button() //DESTRUKTOR DEKREMENTUJACY LICZBE PRZYCISKOW PO ZNISZCZENIU OBIEKTU
	{
		number_of_buttons--;
	}
};

/*KLASA logo REPREZENTUJE OBIEKT TUTU£U GRY WYSWIETLANY W MENU GLOWNYM GRY. POSIADA ATRYBUTY OKRESLAJACE POZYCJE ORAZ TEKSTURE.*/
class logo
{
	std::pair < int, int> position; //ATRYBUT OKRESLAJACY POLOZENIE TYTULU GRY
	sf::Texture* texture = nullptr; //ATRYBUT OKRESLAJACY TEKSTURE 
public:
	sf::Sprite sprite;
	logo() {}
	logo(sf::Texture* texture_ptr, int x, int y)
	{
		position.first = x;
		position.second = y;
		texture = texture_ptr;
	}
	void draw(sf::RenderWindow& window); //METODA RYSUJACA LOGO NA SCENIE
};



/*KLASA game TO GLOWNA KLASA, KTORA REPREZENTUJE CALA ZAWARTOSC GRY. ATRYBUTAMI TEJ KLASY SA KONTENERY PRZECHOWUJACE OBIEKTY WYKORZYSTYWANE W CZASIE GRY ORAZ ICH TEKSTURY,
A TAKZE LICZNIKI CZASU WYKORZYSTYWANE W ROZNYCH SYTUACJACH. ZAWIERA ROWNIEZ INFORMACJE O OBECNYM ORAZ NASTEPNYM ETAPIE GRY, A TAKZE WYNIKU GRACZA. METODY KLASY game
W DUZEJ MIERZE ODPOWIADAJA ZA CALOKSZTALT ROZGRYWKI WYKORZYSTUJAC OBIEKTY ZDEFINIOWANE W PLIKU objects.h. */
class game
{
	sf::Time game_time; //ATRYBUT OKRESLAJACY CZAS TRWANIA ROZGRYWKI
	sf::Clock game_clock; //ATRYBUT OKRESLAJACY ZEGAR ROZGRYWKI
	sf::Time stage_time;	//ATRYBUT OKRESLAJACY CZAS KONKRETNEGO ETAPU
	sf::Clock stage_clock;	//ATRYBUT OKRESLAJACY ZEGAR KONKRETNEGO ETAPU
	sf::Time loop_time;		//ATRYBUT OKRESLAJACY CZAS PETLI PROGRAMU
	sf::Clock loop_clock;	//ATRYBUT OKRESLAJACY ZEGAR PETLI PROGRAMU
	starship starship_;		//STATEK GRACZA
	boss boss_;				//BOSS
	std::vector<std::shared_ptr<object_with_shared_timer>>boost_and_heal;	//VECTOR ZE WSKAZNIKAMI NA OBIEKTY KLASY object_with_shared_timer
	std::list<missile> missiles;	//LISTA POCISKOW GRACZA
	std::list<missile>alien_missiles;	//LISTA POCISKOW WROGOW
	std::list<meteor> meteors;			//LISTA METEORYTOW
	std::list<alien> aliens;			//LISTA OBCYCH
	sf::Texture window_texture;							//TEKSTURA TLA
	sf::Texture button_texture;							//TEKSTURA PRZYCISKU
	sf::Texture button_selected_texture;				//TEKSTURA ZAZNACZONEGO PRZYCISKU
	sf::Texture logo_texture;							//TEKSTURA LOGA GRY
	sf::Texture starship_texture;						//TEKSTURA STATKU
	sf::Texture	starship_missile_texture;				//TEKSTURA STANDARDOWEGO POCISKU GRACZA
	sf::Texture starship_boosted_missile_texture;		//TEKSTURA ULEPSZONEGO POCISKU GRACZA
	sf::Texture	meteor_texture;							//TEKSTURA METEORYTU
	sf::Texture	alien_texture;							//TEKSTURA OBCEGO
	sf::Texture	alien_missile_texture;					//TEKSTURA POCISKOW OBCEGO
	sf::Texture	boss_texture;							//TEKSTURA BOSSA
	sf::Texture boss_missile_texture;					//TEKSTURA POCISKOW BOSSA
	sf::Texture heal_texture;							//TEKSTURA ZYCIA
	sf::Texture empty_heart_texture;					//TEKSTURA PUSTEGO ZYCIA
	sf::Texture boost_texture;							//TEKSTURA ULEPSZENIA POCISKOW
	sf::Text text;				
	int stage=0;			//ATRYBUT OKRESLAJACY ETAP GRY
	int next_stage = 0;		//ATRYBUT OKRESLAJACY NASTEPNY ETAP GRY
	int score=0;			//ATRYBUT OKRESLAJACY WYNIK GRACZA
	

public:
	game(){}
	game(std::vector<std::string>file_name, sf::Font & font) //KONSTRUKTOR LADUJE TEKSTURY POTRZEBNE DO TWORZENIA OBIEKTOW ORAZ CZCIONKE TEKSTU
	{
		starship_texture.loadFromFile(file_name[0]);
		starship_missile_texture.loadFromFile(file_name[1]);
		meteor_texture.loadFromFile(file_name[2]);
		alien_texture.loadFromFile(file_name[3]);
		alien_missile_texture.loadFromFile(file_name[4]);
		boss_texture.loadFromFile(file_name[5]);
		boss_missile_texture.loadFromFile(file_name[6]);
		heal_texture.loadFromFile(file_name[7]);
		boost_texture.loadFromFile(file_name[8]);
		window_texture.loadFromFile(file_name[9]);
		button_texture.loadFromFile(file_name[10]);
		button_selected_texture.loadFromFile(file_name[11]);
		logo_texture.loadFromFile(file_name[12]);
		empty_heart_texture.loadFromFile(file_name[13]);
		starship_boosted_missile_texture.loadFromFile(file_name[14]);
		text.setFont(font);
		text.setFillColor(sf::Color::Red);
	}


	void play_game(sf::RenderWindow& window, sf::Font& font); /*METODA W KTÓREJ ZNAJDUJE SIE GLOWNA PETLA GRY. TO TUTAJ SPRAWDZANY JEST OBECNY ETAP GRY 
															  ORAZ ZDARZENIA TAKIE JAK NACISNIECIE KLAWISZA ESC LUB ZAMKNIECIE OKNA. */ 
	void call_menu(sf::RenderWindow& window, sf::Font& font); //METODA, KTORA WYWOLUJE MENU GLOWNE GRY.
	void set_default_options();	//METODA RESETUJACA NIEKTORE PARAMETRY DO USTAWIEN DOMYSLNYCH
	int stage_one(sf::RenderWindow& window);	//METODA ODPOWIADAJACA ZA ROZGRYWKE W ETAPIE PIERWSZYM
	int stage_two(sf::RenderWindow& window);	//METODA ODPOWIADAJACA ZA ROZGRYWKE W ETAPIE DRUGIM
	int stage_three(sf::RenderWindow& window);	//METODA ODPOWIADAJACA ZA ROZGRYWKE W ETAPIE TRZECIM
	void show_stage_entry(std::string level, std::string description, sf::RenderWindow& window); //METODA RYSUJACA NA SCENIE OPIS ETAPU
	void show_stage_exit(std::string title, sf::RenderWindow& window); //METODA RYSUJACA NA SCENIE ZAKONCZENIE ETAPU
	void draw_objects(sf::RenderWindow& window); //METODA RYSUJACA NA SCENIE OBIEKTY
	void draw_background(sf::RenderWindow& window); //METODA RYSUJACA NA SCENIE TLO
	void game_over(sf::RenderWindow& window);	//METODA RYSUJACA NA SCENIE KOMUNIKAT O KONCU GRY
	void restart_timers();  //METODA RESETUJACA ZEGARY OBIEKTOW 
	void set_timers();      //METODA USTAWIAJACA CZASY OBIEKTOW
	void change_stage(int stage_number); //METODA ZMIENAIJACA ETAP GRY
	void new_stage();	//METODA PRZYGOTOWUJACA KONTENERY I ATRYBUTY DO ZMIANY ETAPU
	sf::Time get_time();
	void reset_time();	
	sf::Time get_stage_time();
	void show_score(sf::RenderWindow& window); //METODA RYSUJACA NA SCENIE WYNIK GRACZA
	void show_starship_health(sf::RenderWindow& window);	//METODA RYSUJACA NA SCENIE ZYCIA GRACZA
	void show_boss_health(sf::RenderWindow& window);	//METODA RYSUJACA NA SCENIE ZYCIE BOSSA
	void show_time(sf::RenderWindow& window);		//METODA RYSUJACA NA SCENIE AKTUALNY CZAS ROZGRYWKI
	void change_score(int value);			//METODA DODAJ¥CA WARTOŒÆ DO WYNIKU GRACZA
	float calculate_scale_x();				//METODA OBLICZAJACA WSPOLCZYNNIK SKALOWANIA OSI X
	float calculate_scale_y();				//METODA OBLICZAJACA WSPOLCZYNNIK SKALOWANIA OSI Y
	void starship_section(float fire_speed);		//METODA W KTOREJ ZARZADZANY JEST OBIEKT STATKU GRACZA
	void meteors_section(float meteors_frequency, int movement_speed);	//METODA W KTOREJ ZARZADZANE SA OBIEKTY KLASY METEOR
	void aliens_section(float aliens_frequency, float fire_speed, int movement_speed);//METODA W KTOREJ ZARZADZANE SA OBIEKTY KLASY ALIEN
	void missiles_section(int starship_missile_speed, int alien_missile_speed);//METODA W KTOREJ ZARZADZANE SA OBIEKTY KLASY MISSILE
	void boss_section(float fire_speed);//METODA W KTOREJ ZARZADZANY JEST OBIEKT KLASY BOSS
	void boost_and_heal_section(float frequency, int speed);//METODA W KTOREJ ZARZADZANE SA OBIEKTY KLASY OBJECT_WITH_SHARED_TIMER
};




#endif