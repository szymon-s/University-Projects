#include "objects.h"


/*WERSJA FINALNA*/


/*ZWRACANIE POZYCJI OBIEKTU*/
std::pair  < int,  int> object::show_coordinates()
{
	return position;
}

/*ZWRACANIE OBSZARU ZAJMOWANEGO PRZEZ OBIEKT*/
sf::FloatRect object::show_hitbox()
{	
	return hitbox;
}

/*SPRAWDZANIE CZY OBIEKT KOLIDUJE Z INNYM OBIEKTEM*/
bool object::colision(sf::FloatRect other_object)
{
	if (hitbox.intersects(other_object))
		return 1;
	else
		return 0;
}

/*RYSOWANIE OBIEKTU*/
void object::draw(sf::RenderWindow& window)
{
	sf::Sprite sprite;
	sprite.setTexture(*(texture), true); /*USTAWIANIE TEKSTURY*/
	sprite.scale(SCALE_X, SCALE_Y);	/*SKALOWANIE*/
	sprite.setPosition((position.first - sprite.getLocalBounds().width / 2), (position.second - sprite.getLocalBounds().height / 2));/*USTAWIANIE POZYCJI*/
	hitbox = sprite.getGlobalBounds(); /*USTAWIANIE OBSZARU ZAJMOWANEGO PRZEZ OBIEKT*/
	window.draw(sprite);	/*RYSOWANIE OBIEKTU NA SCENIE*/
}

/*ZWRACANIE USTAWIONEGO WCZESNIEJ CZASU*/
sf::Time object_with_timers::check_time()
{
	return time;
}

/*ZWRACANIE CZASU OD OSTATNIEGO RESETU*/
sf::Time object_with_timers::check_clock()
{
	return clock.getElapsedTime();
}

/*DODANIE DO CZASU OKRESLONEJ WARTOSCI*/
void object_with_timers::change_time(float value)
{
	time += sf::seconds(value);
}

/*RESETOWANIE ZEGARA*/
void object_with_timers::reset_clock()
{
	clock.restart();
}

/*ZEROWANIE CZASU*/
void object_with_timers::reset_time()
{
	time = sf::seconds(0);
}

/*ZWRACANIE USTAWIONEGO WCZESNIEJ CZASU*/
sf::Time object_with_shared_timer::check_shared_time()
{
	return shared_time;
 }

/*ZWRACANIE CZASU OD OSTATNIEGO RESETU*/
sf::Time object_with_shared_timer::check_shared_clock()
{
	return shared_clock.getElapsedTime();
 }

/*DODANIE DO CZASU OKRESLONEJ WARTOSCI*/
void object_with_shared_timer::change_shared_time(float value)
{
	shared_time += sf::seconds(value);
 }

/*RESETOWANIE ZEGARA*/
void object_with_shared_timer::reset_shared_clock()
{
	shared_clock.restart();
 }

/*ZEROWANIE CZASU*/
void object_with_shared_timer::reset_shared_time()
{
	shared_time = sf::seconds(0);
 }

/*TWORZENIE OBIEKTU KLASY MISSILE PRZEZ STATEK*/
missile starship::send_missile(sf::Texture* texture_, int direction)
{
	return missile(position.first, position.second, direction, texture_);
}

/*OBSLUGA PRZEMIESZCZANIA SIE STATKU*/
void starship::move(int movement_speed)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			movement(-movement_speed, -movement_speed);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			movement(movement_speed, -movement_speed);
		}
		else
			movement(0, -movement_speed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			movement(-movement_speed, movement_speed);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			movement(movement_speed, movement_speed);
		}
		else
			movement(0, movement_speed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		movement(-movement_speed, 0);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		movement(movement_speed, 0);
	}
}


/*ZMIANA POZYCJI STATKU*/
void starship::movement(int x, int y)
{
	if (position.first > 0 && position.first < SCREEN_WIDTH)
		position.first +=x;
	else //STATEK WYKRACZA POZA ZAKRES EKRANU
	{
		if (position.first <= 0) //JESLI WYJDZIE ZA LEWA KRAWEDZ STATEK PRZEMIESZCZANY JEST PRZED PRAWA KRAWEDZ
			position.first = SCREEN_WIDTH - 1;
		else					//JESLI WYJDZIE ZA PRAWA KRAWEDZ STATEK PRZEMIESZCZANY JEST PRZED LEWA KRAWEDZ
			position.first = 1;
	}
	if (position.second > 0 && position.second < SCREEN_HEIGHT)
		position.second += y;
	else //STATEK BLOKUJE SIE NA GORNEL LUB DOLNEJ KRAWEDZI
	{
		if (position.second <= 0)
			position.second = 1;
		else
			position.second = SCREEN_HEIGHT - 1;
	}
}

/*USTAWIANIE PUNKTOW ZYCIA STATKU*/
void starship::set_health_points(int hp)
{
	health_points = hp;
}

/*ZWROCENIE PUNKTOW ZYCIA STATKU*/
int starship::show_health_points()
{
	return health_points;
}

/*DODANIE PUNKTOW ZYCIA DO ZYCIA STATKU*/
void starship::change_health_points(int hp)
{
	health_points += hp;
}

/*ZMIANA ULEPSZENIA POCISKOW STATKU*/
void starship::change_boost_status(int status)
{
	boost_enabled = status;
}

/*ZWROCENIE STANU ULEPSZENIA POCISKOW STATKU*/
int starship::show_boost_status()
{
	return boost_enabled;
}

/*USTAWIENIE POZYCJI STATKU*/
void starship::set_position(int x, int y)
{
	position.first = x;
	position.second = y;
}

/*ZWROCENIE KIERUNKU Y METEORYTU*/
int meteor::show_direction_y()
{
	return direction_y;
}

/*ZWROCENIE KIERUNKU X METEORYTU*/
int meteor::show_direction_x()
{
	return direction_x;
}

/*ZMIANA POZYCJI METEORYTU*/
void meteor::movement(int x, int y)
{
	if (position.first > 0 && position.first < SCREEN_WIDTH)
		position.first += x;

	else
	{
		direction_x =-direction_x;
		position.first += -x;
	}

	if (position.second > 0 && position.second < SCREEN_HEIGHT)
		position.second +=y;
	
	else
	{
		if (direction_y)
			direction_y = 0;
		else
			direction_y = 1;
		position.second += -y ;
	}
	
	
}

/*ZWRACANIE USTAWIONEGO WCZESNIEJ CZASU*/
sf::Time meteor::check_static_time()
{
	return meteor::meteors_time;
}

/*ZWRACANIE CZASU OD OSTATNIEGO RESETU*/
sf::Time meteor::check_static_clock()
{
	return meteor::meteors_clock.getElapsedTime();
}

/*DODANIE DO CZASU OKRESLONEJ WARTOSCI*/
void meteor::change_static_time(float value)
{
	meteor::meteors_time += sf::seconds(value);
}

/*RESETOWANIE ZEGARA*/
void meteor::reset_static_clock()
{
	meteor::meteors_clock.restart();
}

/*ZEROWANIE CZASU*/
void meteor::reset_static_time()
{
	meteor::meteors_time= sf::seconds(0);
}

/*INKREMENTACJA ILOSCI ZNISZCZONYCH METEORYTOW*/
void meteor::add_destroyed()
{
	destroyed++;
}


int meteor::show_destroyed()
{
	return destroyed;
}

/*ZEROWANIE ILOSCI ZNISZCZONYCH METEORYTOW*/
void meteor:: zero_destroyed()
{
	destroyed = 0;
}

/*STWORZENIE OBIEKTU KLASY MISSILE PRZEZ OBCEGO*/
missile alien::send_missile(sf::Texture* texture_, int direction)
{
	return missile(position.first, position.second, direction, texture_);
}

/*ZWRACANIE USTAWIONEGO WCZESNIEJ CZASU*/
sf::Time alien::check_static_time()
{
	return alien::aliens_time;
}

/*ZWRACANIE CZASU OD OSTATNIEGO RESETU*/
sf::Time alien::check_static_clock()
{
	return alien::aliens_clock.getElapsedTime();
}

/*DODANIE DO CZASU OKRESLONEJ WARTOSCI*/
void alien::change_static_time(float value)
{
	alien::aliens_time += sf::seconds(value);
}

/*RESETOWANIE ZEGARA*/
void alien::reset_static_clock()
{
	alien::aliens_clock.restart();
}

/*ZEROWANIE CZASU*/
void alien::reset_static_time()
{
	alien::aliens_time = sf::seconds(0);
}

/*ZWROCENIE ILOSCI ZNISZCZONYCH OBCYCH*/
int alien::show_destroyed()
{
	return destroyed;
}

/*ZEROWANIE ILOSCI ZNISZCZONYCH OBCYCH*/
void alien::zero_destroyed()
{
	destroyed = 0;
}

/*INKREMENTACJA ILOSCI ZNISZCZONYCH OBCYCH*/
void alien::add_destroyed()
{
	destroyed++;
}

/*ZMIANA POZYCJI OBCEGO*/
void alien::movement(int x, int y)
{
	if (position.first > 0 && position.first < SCREEN_WIDTH)
		position.first += x ;
	else //PO OSIAGNIECIU ZAKRESU EKRANU NASTEPUJE ZMIANA KIERUNKU OBCEGO
	{
		
		if (direction)
			direction = 0;
		else
			direction = 1;
		position.first +=-x;
		
	}
	position.second += y;
}

/*ZWROCENIE KIERUNKU OBCEGO*/
int alien::show_direction()
{
	return direction;
}

/*ZMIANA POZYCJI ULEPSZENIA POCISKU*/
void boost::movement(int x, int y)
{
	position.first += x ;
	position.second += y ;
}

/*ZMIANA ULEPSZENIA POCISKU STATKU PODCZAS KOLIZJI*/
void boost::colision_action(starship& starship_)
{
	if(starship_.show_boost_status()==0)
		starship_.change_boost_status(1);
	else
		starship_.change_boost_status(0);
}

/*DODANIE JEDNEGO PUNKTU ZYCIA DO STATKU PODCZAS KOLIZJI*/
void heal::colision_action(starship& starship_)
{
	starship_.change_health_points(1);
}

/*ZMIANA POZYCJI DODATKOWEGO ZYCIA*/
void heal::movement(int x, int y)
{
	position.first +=x;
	position.second +=y;
}

/*UTWORZENIE OBIEKTU KLASY MISSILE PRZEZ BOSSA*/
missile boss::send_missile(sf::Texture* texture_, int direction)
{
	return missile(position.first, position.second,direction,  texture_);
}

/*ZWROCENIE PUNKTOW ZYCIA BOSSA*/
int boss::show_hp()
{
	return hp;
}

/*DODANIE PUNKTOW ZYCIA DO ZYCIA BOSSA*/
void boss::change_hp(int change)
{
	hp += change;
}

/*USTAWIENIE PUNKTOW ZYCIA BOSSA*/
void boss::set_hp(int hp)
{
	boss::hp = hp;
}

/*ZMIANA POZYCJI BOSSA*/
void boss::movement(int x, int y)
{
	position.first +=x;
	position.second +=y;
}

/*SPRAWDZENIE CZY POCISK JEST POZA ZAKRESEM EKRANU*/
bool missile::out_of_range()
{
	if (position.second <= 0 || position.second >= SCREEN_HEIGHT)
		return true;
	else
		return false;
}

/*ZWROCENIE KIERUNKU POCISKU*/
int missile::show_direction()
{
	return direction;
}

/*ZMIANA POZYCJI POCISKU*/
void missile::movement(int x, int y)
{
	position.first += x;
	position.second += y;
}