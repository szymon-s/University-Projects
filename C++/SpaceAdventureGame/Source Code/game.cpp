#include "game.h"
#include "objects.h"

/*WERSJA FINALNA*/

/*RYSOWANIE NA SCENIE LOGA GRY*/
void logo::draw(sf::RenderWindow& window)
{
	sprite.setTexture(*(texture), true); //USTAWIENIE TEKSTURY LOGA
	sprite.setPosition((position.first - sprite.getLocalBounds().width / 2), (position.second - sprite.getLocalBounds().height / 2));//USTAWIENIE POZYCJI LOGA
	window.draw(sprite);	//NARYSOWANIE LOGA NA SCENIE
}

/*ZWRACAJACANIE CZASU OD OSTATNIEGO ZRESETOWANIA ZEGARA PRZYCISKU*/
sf::Time button::show_time()
{
	return  clock.getElapsedTime();
}

/*RESETOWANIE ZEGARA PRZYCISKU */
void button::reset_time()
{
	clock.restart();
}

/*ZWRACANIE NUMERU PRZYCISKU*/
int button::get_button_number()
{
	return button_number;
}

/*RYSOWANIE NA SCENIE PRZYCISKU*/
void button::draw(sf::RenderWindow& window)
{
	if (button_number == selected_button) //JESLI PRZYCISK JEST WYBRANY TO STOSUJEMY INNA TEKSTURE
		sprite.setTexture(*(texture_selected), true);
	else
		sprite.setTexture(*(texture), true);
	sprite.setPosition((position.first - sprite.getLocalBounds().width / 2), (position.second - sprite.getLocalBounds().height / 2));//USTALANIE POZYCJI PRZYCISKU
	window.draw(sprite);//RYSOWANIE PRZYCISKU NA SCENIE
	window.draw(text);//RYSOWANIE TEKSTU PRZYCISKU NA SCENIE
}

/*RYSOWANIE NA SCENIE WYNIKU GRACZA*/
void game::show_score(sf::RenderWindow& window)
{
	std::string score("SCORE: "); //USTALANIE NAPISU
	score += std::to_string(game::score);	//DODANIE DO NAPISU WYNIKU GRACZA
	text.setString(score); //USTAWIENIE TEKSTU DO WYSWIETLENIA
	text.setCharacterSize((unsigned int)(70.0 *SCALE_X)); //USTAWIENIE ROZMIARU TEKSTU
	text.setPosition((SCREEN_WIDTH / 2 - text.getLocalBounds().width / 2), (SCREEN_HEIGHT / 14 - text.getLocalBounds().height / 2)); //USTAWIANIE POZYCJI TEKSTU
	window.draw(text); //RYSOWANIE TEKSTU NA SCENIE

}

/*RYSOWANIE NA SCENIE ILOSCI ZYC GRACZA. W ZALEZNOSCI OD ILOSCI ZYCIA RYSOWANE SA PELNE LUB PUSTE SERCA.*/
void game::show_starship_health(sf::RenderWindow& window)
{
	//USTAWIANIE TEKSTURY DLA PELNEGO ZYCIA
	sf::Sprite full_heart;
	full_heart.setTexture(heal_texture);
	full_heart.scale(SCALE_X, SCALE_Y);

	//USTAWIANIE TEKSTURY DLA PUSTEGO ZYCIA
	sf::Sprite empty_heart;
	empty_heart.setTexture(empty_heart_texture);
	empty_heart.scale(SCALE_X, SCALE_Y);
	switch (starship_.show_health_points())
	{
	//JESLI GRACZ MA DWA ZYCIA TO RYSOWANE SA DWA PELENE SERCA I JEDNO PUSTE
	case 2:
		full_heart.setPosition((SCREEN_WIDTH / 5 - full_heart.getLocalBounds().width / 2), (SCREEN_HEIGHT / 14 - full_heart.getLocalBounds().height / 2));
		window.draw(full_heart);
		full_heart.setPosition((SCREEN_WIDTH / 5 + 110 - full_heart.getLocalBounds().width / 2), (SCREEN_HEIGHT / 14 - full_heart.getLocalBounds().height / 2));
		window.draw(full_heart);
		empty_heart.setPosition((SCREEN_WIDTH / 5 + 220 - empty_heart.getLocalBounds().width / 2), (SCREEN_HEIGHT / 14 - empty_heart.getLocalBounds().height / 2));
		window.draw(empty_heart);
		break;
		//JESLI GRACZ MA JEDNO ZYCIE RYSOWANE JEST JEDNO PELNE SERCE I DWA PUSTE
	case 1:
		full_heart.setPosition((SCREEN_WIDTH / 5 - full_heart.getLocalBounds().width / 2), (SCREEN_HEIGHT / 14 - full_heart.getLocalBounds().height / 2));
		window.draw(full_heart);
		empty_heart.setPosition((SCREEN_WIDTH / 5 + 110 - empty_heart.getLocalBounds().width / 2), (SCREEN_HEIGHT / 14 - empty_heart.getLocalBounds().height / 2));
		window.draw(empty_heart);
		empty_heart.setPosition((SCREEN_WIDTH / 5 + 220 - empty_heart.getLocalBounds().width / 2), (SCREEN_HEIGHT / 14 - empty_heart.getLocalBounds().height / 2));
		window.draw(empty_heart);
		break;
		//W INNYCH PRZYPADKACH RYSOWANE SA TRZY PELNE SERCA
	default:
		full_heart.setPosition((SCREEN_WIDTH /5 - full_heart.getLocalBounds().width / 2), (SCREEN_HEIGHT / 14 - full_heart.getLocalBounds().height / 2));
		window.draw(full_heart);
		full_heart.setPosition((SCREEN_WIDTH / 5 + 110 - full_heart.getLocalBounds().width / 2), (SCREEN_HEIGHT / 14 - full_heart.getLocalBounds().height / 2));
		window.draw(full_heart);
		full_heart.setPosition((SCREEN_WIDTH / 5 + 220 - full_heart.getLocalBounds().width / 2), (SCREEN_HEIGHT / 14 - full_heart.getLocalBounds().height / 2));
		window.draw(full_heart);
		break;
	}

}

/*RYSOWANIE NA SCENIE ZYCIA BOSSA*/
void game::show_boss_health(sf::RenderWindow& window)
{
	std::string boss_hp("BOSS HP: "); //PRZYGOTOWANIE NAPISU
	boss_hp += std::to_string(boss_.show_hp()); //DODANIE DO NAPISU ILOSCI ZYCIA BOSSA
	text.setString(boss_hp); //DODANIE TEKSTU DO WYSWIETLENIA
	text.setCharacterSize((unsigned int)(50.0 *SCALE_X)); //USTAWIENIE ROZMIARU TEKSTU
	text.setPosition((SCREEN_WIDTH*4/ 5 - text.getLocalBounds().width / 2), (SCREEN_HEIGHT / 3 - text.getLocalBounds().height / 2));//USTAWIANIE POZYCJI NAPISU
	window.draw(text);//RYSOWANIE NAPISU NA SCENIE
}

/*ZWROCENIE CZASU ETAPU ORAZ RESET ZEGARA*/
sf::Time game::get_stage_time()
{
	if (stage_clock.getElapsedTime().asSeconds() > 1)
	{
		stage_time += sf::seconds(1);
		stage_clock.restart();
	}
	return stage_time;
}

/*RYSOWANIE CZASU GRY NA SCENIE*/
void game::show_time(sf::RenderWindow& window)
{
	if (game_clock.getElapsedTime().asSeconds() > 1)
	{
		game_time += sf::seconds(1);
		game_clock.restart();
	}
	int minutes =(int) game_time.asSeconds() / 60; //OBLICZANIE ILOSCI MINUT
	int seconds = (int)game_time.asSeconds() % 60;  //OBLICZANIE ILOSCI SEKUND
	std::string time=""; //PRZYGOTOWYWANIE NAPISU
	if (minutes < 10)
	{
		time = "0";
	}
	time +=std::to_string(minutes);  //DODANIE DO NAPISU LICZBY MINUT
	time += ":";
	if (seconds < 10)
	{
		time += "0";
	}
	time += std::to_string(seconds);  //DODANIE DO NAPISU LICZBY SEKUND
	text.setString(time); //USTAWIENIE TEKSTU
	text.setCharacterSize((unsigned int)(70.0*SCALE_X)); //USTAWIENIE ROZMIARU TEKSTU
	text.setPosition((SCREEN_WIDTH*4/5 - text.getLocalBounds().width / 2), (SCREEN_HEIGHT / 14 - text.getLocalBounds().height / 2));  //USTAWIENIE POZYCJI TEKSTU
	window.draw(text);  //RYSOWANIE TEKSTU NA SCENIE
}

/*WYZEROWANIE ATRYBUTOW game_time, score ORAZ USTAWIENIE ULEPSZENIA POCZISKOW GRACZA NA 0*/
void game::set_default_options()
{
	game_time = sf::seconds(0);
	score = 0;
	starship_.change_boost_status(0);
}

/*ZARZADZANIE MENU GLOWNYM*/
void game::call_menu(sf::RenderWindow& window, sf::Font& font)
{
	window.clear();
	draw_background(window);
	logo logo(&(logo_texture), (int)(SCREEN_WIDTH * 0.5), (int)(SCREEN_HEIGHT * 0.3));
	logo.draw(window);
	if (next_stage == 0)
	{
		button new_game_button("NEW GAME", &(button_texture), &(button_selected_texture), (int)(SCREEN_WIDTH * 0.5), (int)(SCREEN_HEIGHT * 0.60), font);
		button exit_button("EXIT", &(button_texture), &(button_selected_texture), (int)(SCREEN_WIDTH * 0.5), (int)(SCREEN_HEIGHT * 0.70), font);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			switch (button::selected_button)
			{
			case 0:
				change_stage(1);
				set_default_options();
				break;
			case 1:
				window.close();
				break;
			}
		}
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && (button::show_time()>sf::seconds((float)0.3)))
		{
			switch (button::selected_button)
			{
			case 0:
				button::selected_button=1;
				break;
			case 1:
				button::selected_button =0;
				break;
			}
			button::reset_time();
		}
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && (button::show_time() > sf::seconds((float)0.3)))
		{
			switch (button::selected_button)
			{
			case 0:
				button::selected_button = 1;
				break;
			case 1:
				button::selected_button = 0;
				break;
			}
			button::reset_time();
		}
		new_game_button.draw(window);
		exit_button.draw(window);
		window.display();
	}
	else
	{
		button new_game_button("NEW GAME", &(button_texture), &(button_selected_texture), (int)(SCREEN_WIDTH * 0.5), (int)(SCREEN_HEIGHT * 0.60), font);
		button resume_button("RESUME", &(button_texture), &(button_selected_texture), (int)(SCREEN_WIDTH * 0.5), (int)(SCREEN_HEIGHT * 0.70), font);
		button exit_button("EXIT", &(button_texture), &(button_selected_texture), (int)(SCREEN_WIDTH * 0.5), (int)(SCREEN_HEIGHT * 0.80), font);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			switch ((button::selected_button))
			{
			case 0:
				change_stage(1);
				set_default_options();
				break;
			case 1:
				stage=next_stage;
				break;
			case 2:
				window.close();
				break;
			}
		}
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && (button::show_time() > sf::seconds((float)0.3)))
		{
			switch (button::selected_button)
			{
			case 0:
				button::selected_button = 2;
				break;
			case 1:
				button::selected_button = 0;
				break;
			case 2:
				button::selected_button =1;
				break;
			}
			button::reset_time();
		}
		else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && (button::show_time() > sf::seconds((float)0.3)))
		{
			switch (button::selected_button)
			{
			case 0:
				button::selected_button = 1;
				break;
			case 1:
				button::selected_button = 2;
				break; 
			case 2:
				button::selected_button = 0;
				break;
			}
			button::reset_time();
		}
		new_game_button.draw(window);
		resume_button.draw(window);
		exit_button.draw(window);
		window.display();
	}
	

}

/*RYSOWANIE NA SCENIE TEKSTU ROZPOCZYNAJACEGO ETAP*/
void game::show_stage_entry(std::string level, std::string description, sf::RenderWindow& window)
{
	text.setString(level);
	text.setCharacterSize((unsigned int)(256.0 * SCALE_X));
	text.setPosition((SCREEN_WIDTH / 2 - text.getLocalBounds().width / 2), (SCREEN_HEIGHT / 4 - text.getLocalBounds().height / 2));
	window.draw(text);
	text.setString(description);
	text.setCharacterSize((unsigned int)(64.0 * SCALE_X));
	text.setPosition((SCREEN_WIDTH / 2 - text.getLocalBounds().width / 2), (SCREEN_HEIGHT / 2 - text.getLocalBounds().height / 2));
	window.draw(text);
	window.display();
}

/*RYSOWANIE NA SCENIE TEKSTU KONCZACEGO ETAP*/
void game::show_stage_exit(std::string title, sf::RenderWindow& window)
{
	text.setString(title);
	text.setCharacterSize((unsigned int)(256.0*SCALE_X));
	text.setPosition((SCREEN_WIDTH / 2 - text.getLocalBounds().width / 2), (SCREEN_HEIGHT / 4 - text.getLocalBounds().height / 2));
	window.draw(text);
	std::string score = "YOUR SCORE IS: ";
	score += std::to_string(game::score);
	text.setString(score);
	text.setCharacterSize((unsigned int)(64.0 * SCALE_X));
	text.setPosition((SCREEN_WIDTH / 2 - text.getLocalBounds().width / 2), (SCREEN_HEIGHT / 2 - text.getLocalBounds().height / 2));
	window.draw(text);
	window.display();
}

/*ZARZADZANIE STRZELANIEM POCISKAMI PRZEZ STATEK*/
void game::starship_section(float fire_speed)
{
	if (starship_.show_boost_status()) //JESLI STATEK POSIADA ULEPSZENIE POCISKOW, MOZE CZESCIEJ STRZELAC
		fire_speed = fire_speed/(float)1.5;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && starship_.check_time().asSeconds() > fire_speed) //PO NACISNIECIU PRZYCISKU SPACJA STATEK STRZELA POCISKAMI CO PEWIEN CZAS
	{
		if(!starship_.show_boost_status()) // WYSLANIE ODPOWIEDNIEGO POCISKU W ZALEZNOSCI OD ULEPSZENIA
			missiles.push_back(starship_.send_missile(&starship_missile_texture, 0));
		else
			missiles.push_back(starship_.send_missile(&starship_boosted_missile_texture, 0));
		starship_.reset_time();
		starship_.reset_clock();
	}
}

/*ZARZADZANIE TWORZENIE ORAZ RUCH METEORYTOW*/
void game::meteors_section(float meteors_frequency, int movement_speed)
{
	if (meteor::check_static_time() > sf::seconds(meteors_frequency - get_stage_time().asSeconds() / 120)) //METEOR TWORZONY JEST RAZ NA OKRESLONA ILOSC CZASU, WRAZ Z UPLYWEM CZASU CORAZ CZESCIEJ
	{
		int direction = 0;
		while (direction == 0)//METEORY SPADAJA POD PEWNYM KATEM ROZNYM OD ZERA
		{
			direction = (rand() % (3+movement_speed)) - movement_speed;
		}
		meteors.push_back(meteor(rand() % (SCREEN_WIDTH - 10) + 10, 1, &meteor_texture, direction));
		meteor::reset_static_time();
		meteor::reset_static_clock();
	}
	for (auto iterator = meteors.begin(); iterator != meteors.end(); iterator++)
	{

		if (iterator->colision(starship_.show_hitbox())) //SPRAWDZANIE CZY METEORYT NIE UDERZYL W STATEK, JESLI UDERZYL TO ZYCIE GRASZA ZMNIEJSZA SIE, A METEORYT JEST USUWANY
		{
			if (iterator->colision(starship_.show_hitbox()))
			{
				starship_.set_position(int(SCREEN_WIDTH * 0.5), int(SCREEN_HEIGHT * 0.66));
				starship_.change_health_points(-1);
							}
			iterator->add_destroyed();
			iterator = meteors.erase(iterator);
			if (iterator == meteors.end())
				break;
		}
		for (auto iterator1 = missiles.begin(); iterator1 != missiles.end(); iterator1++) //SPRAWDZANIE CZY POCISK GRACZA NIE UDERZYL W METEORYT, JESLI UDERZYL, TO GRACZ ZYSKUJE PUNKTY I OBA OBIEKTY SA USUWANE
		{

			if (iterator->colision(iterator1->show_hitbox()))
			{
				change_score(10);
				iterator->add_destroyed();
				iterator1 = missiles.erase(iterator1);
				iterator = meteors.erase(iterator);
				if (iterator1 == missiles.end() || iterator == meteors.end())
					break;
			}

		}
		if (iterator == meteors.end())
			break;
		if (iterator->show_direction_y()) //PORUSZANIE SIE METEORYTU W ZALEZNOSCI OD KIERUNKU
		{

			iterator->movement(iterator->show_direction_x(), -movement_speed);
		}
		else
		{
			iterator->movement(iterator->show_direction_x(), movement_speed);
		}
	}
}

/*ZARZADZANIE TWORZENIEM, RUCHEM ORAZ STRZELANIEM OBCYCH*/
void game::aliens_section(float aliens_frequency, float fire_speed, int movement_speed)
{
	if (alien::check_static_time() > sf::seconds(aliens_frequency)) //TWORZENIE OBCEGO RAZ NA OKRESLANA ILSOC CZASU
	{
		int kierunek = (rand() % 2 + 1) % 2; //KIERUNEK OBCEGO WYBIERANY JEST LOSOWO (PRAWO ALBO LEWO)
		if (kierunek)
			aliens.push_back(alien(1, int(rand() % SCREEN_HEIGHT * 0.33), &alien_texture, kierunek));
		else
			aliens.push_back(alien(int(SCREEN_WIDTH - 1), int(rand() % SCREEN_HEIGHT * 0.33), &alien_texture, kierunek));
		alien::reset_static_time();
		alien::reset_static_clock();
	}

	for (auto iterator = aliens.begin(); iterator != aliens.end(); iterator++) //KAZDY OBCY WYSTRZELIWUJE POCISK RAZ NA OKRESLONA ILSOC CZASU fire_speed
	{
		if (iterator->check_time() > sf::seconds(fire_speed))
		{
			alien_missiles.push_back(iterator->send_missile(&alien_missile_texture, 0));
			iterator->reset_time();
			iterator->reset_clock();
		}
		for (auto iterator1 = missiles.begin(); iterator1 != missiles.end(); iterator1++) //SPRAWDZENIE CZY W OBCEGO NIE UDERZYL JAKIS POCISK GRACZA
		{

			if (iterator->colision(iterator1->show_hitbox())) //JESLI POCISK UDERZYL TO GRACZ OTRZYMUJE DODATWKOE PUNKTY, A POCISK RAZEM Z OBCYM SA USUWANE 
			{
				change_score(20);
				iterator->add_destroyed();
				iterator1 = missiles.erase(iterator1);
				iterator = aliens.erase(iterator);
				if (iterator1 == missiles.end() || iterator == aliens.end())
					break;
			}

		}
		if (iterator == aliens.end())
			break;
		if (iterator->show_direction()) //PORUSZANIE SIE OBCEGO W ZALEZNOSCI OD KIERUNKU
			iterator->movement(movement_speed, 0);
		else
			iterator->movement(-movement_speed, 0);
	}
}

/*ZARZADZANIE RUCHEM POCISKOW*/
void game::missiles_section(int starship_missile_speed, int alien_missile_speed)
{
	for (auto iterator = missiles.begin(); iterator != missiles.end(); iterator++) 
	{
		if(!starship_.show_boost_status()) //JESLI NIE JEST AKTYWNE ULEPSZENIE POCISK PORUSZA SIE WOLNIEJ
			iterator->movement(0, -starship_missile_speed);
		else
			iterator->movement(0, -starship_missile_speed*3); //Z AKTYWNYM ULEPSZENIEM POCISK PORUSZA SIE SZYBCIEJ
		if (iterator->out_of_range() || (iterator->colision(boss_.show_hitbox()) && stage==3)) 
		{
			if (iterator->colision(boss_.show_hitbox()) && stage==3) //JESLI POCISK UDERZY W BOSSA, ZMNIEJSZA SIE JEGO ZYCIE
				boss_.change_hp(-1);
			iterator = missiles.erase(iterator); //JESLI POCISK UDERZY W BOSSA LUB WYLECI POZA ZAKRES EKRANU, JEST USUWANY
			if (iterator == missiles.end())
				break;
		}
	}
	for (auto iterator = alien_missiles.begin(); iterator != alien_missiles.end(); iterator++)
	{
		iterator->movement(iterator->show_direction(), alien_missile_speed);
		if (iterator->out_of_range() || iterator->colision(starship_.show_hitbox()))
		{
			if (iterator->colision(starship_.show_hitbox()))//JESLI POCISK WROGA UDERZY W STATEK GRACZA, ZYCIE GRACZA ZMNIEJSZA SIE O 1 ORAZ RESTARTUJE SIE JEGO POLOZENIE
			{
				starship_.set_position(int(SCREEN_WIDTH * 0.5), int(SCREEN_HEIGHT * 0.66));
				starship_.change_health_points(-1);
			}
			iterator = alien_missiles.erase(iterator); //JESLI POCISK WROGA TRAFI W GRACZA LUB WYJDZIE POZA ZAKRES EKRANU, JEST USUWANY
			if (iterator == alien_missiles.end())
				break;
		}
	}
}

/*ZARZADZANIE TWORZENIEM POCISKOW PRZEZ BOSSA*/
void game::boss_section(float fire_speed)
{
	if (boss_.check_time() > sf::seconds(fire_speed)) //POCISKI ZOSTANA WYSTRZELONE RAZ NA OKRES CZASU OKRESLONY PRZEZ fire_speed
	{
		for (int i = -3; i < 4; i++) //WYSTRZELENIE 6 POCISKOW W KIERUNKACH ZALEZNYCH OD i
		{
			alien_missiles.push_back(boss_.send_missile(&boss_missile_texture, i));
		}
		boss_.reset_time();  //RESETOWANIE CZASU
		boss_.reset_clock();
	}
}

/*ZARZADZANIE TWORZENIEM I PORUSZANIEM SIE ULEPSZEN POCISKOW ORAZ DODATKOWYM ZYCIEM*/
void game::boost_and_heal_section(float frequency, int speed)
{
	if (object_with_shared_timer::check_shared_time() > sf::seconds(frequency))
	{
		if ((rand() % 3 + 1) % 2)
		{
			std::shared_ptr<object_with_shared_timer>new_object(new heal(rand() % (SCREEN_WIDTH - 10) + 10, 1, &heal_texture));
			boost_and_heal.push_back(new_object);
		}
		else
		{
			std::shared_ptr<object_with_shared_timer>new_object(new boost(rand() % (SCREEN_WIDTH - 10) + 10, 1, &boost_texture));
			boost_and_heal.push_back(new_object);
		}
		object_with_shared_timer::reset_shared_time();
		object_with_shared_timer::reset_shared_clock();
	}
	for (auto iterator = boost_and_heal.begin(); iterator != boost_and_heal.end(); iterator++)
	{
		(*iterator)->movement(0, speed);
		if ((*iterator)->colision(starship_.show_hitbox()))
		{
			(*iterator)->colision_action(starship_);
			iterator = boost_and_heal.erase(iterator);
			if (iterator == boost_and_heal.end())
				break;
		}
	}
}

/*ZARZADZANIE PIERWSZYM ETAPEM GRY*/
int game::stage_one(sf::RenderWindow& window)
{
	if ((loop_clock.getElapsedTime()+loop_time).asMicroseconds() < 2500) //SPRAWDZANIE CZASU PETLI, ABY GRA NIE DZIALALA ZBYT SZYBKO
	{
		return 0;
	}
	else
	{
		loop_clock.restart(); //RESETOWANIE CZASU PETLI
		window.clear();	//CZYSZCZENIE SCENY
		draw_background(window);	//RYSYWANIE TLA
		if (get_stage_time().asSeconds() < 5)  //PRZEZ PIERWSZE PIEC SEKUND ETAPU WYSWIETLANY JEST KOMUNIKAT
		{
			show_stage_entry("LEVEL I", "DESTROY 50 METEORS!",window);			
			score = 0;
			loop_time = loop_clock.getElapsedTime();
			return 0;
		}
		else
		{
			if (meteor::show_destroyed() >= 50) //PO ZNISZCZENIU 50 METEORYTOW WYSWIETLANY JEST KOMUNIKAT I ZMIENIANY JEST ETAP
			{
				show_stage_exit("WELL DONE!", window);				
				while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				{

				}
				loop_time = loop_clock.getElapsedTime();
				change_stage(2);
				return 0;
			}
			/*CZESC ZARZADZAJACA OBIEKTAMI*/
			starship_.move(2);
			starship_section((float)0.3);
			missiles_section(3,2);
			meteors_section((float)1.0,2);
			boost_and_heal_section((float)5.0,2);
			if (starship_.show_health_points() <= 0) //JESLI ZYCIE GRACZA SPADLO DO ZERA WYSWIETLANY JEST KOMUNIKAT I NASTEPUJE PRZEJSCIE DO MENU GLOWNEGO
			{
				game_over(window);
				return 1;
			}
			/*CZESC RYSUJACA OBIEKTY NA SCENIE*/
			draw_objects(window);
			show_starship_health(window);
			show_score(window);
			show_time(window);
			window.display(); //WYSWIETLANIE SCENY
			set_timers();
			restart_timers();
			return 0;
		}
	}
}

/*ZARZADZANIE DRUGIM ETAPEM GRY*/
int game::stage_two(sf::RenderWindow& window)
{
	if ((loop_clock.getElapsedTime() + loop_time).asMicroseconds() < 2500) //SPRAWDZANIE CZASU PETLI, ABY GRA NIE DZIALALA ZBYT SZYBKO
	{
		return 0;
	}
	else
	{
		loop_clock.restart(); //RESETOWANIE CZASU PETLI
		window.clear();	//CZYSZCZENIE SCENY
		draw_background(window);	//RYSYWANIE TLA
		if (get_stage_time().asSeconds() < 5)  //PRZEZ PIERWSZE PIEC SEKUND ETAPU WYSWIETLANY JEST KOMUNIKAT
		{
			show_stage_entry("LEVEL II", "DESTROY 50 ALIENS!", window);
			loop_time = loop_clock.getElapsedTime();
			return 0;
		}
		else
		{
			if (alien::show_destroyed() >= 50) //PO ZNISZCZENIU 50 OBCYCH WYSWIETLANY JEST KOMUNIKAT I ZMIENIANY ETAP
			{
				show_stage_exit("WELL DONE", window);				
				while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				{					
				}
				loop_time = loop_clock.getElapsedTime();
				change_stage(3);
				return 0;
			}
			/*CZESC ZARZADZAJACA OBIEKTAMI*/
			starship_.move(2);
			starship_section((float)0.3);
			missiles_section(3, 2);
			meteors_section((float)1.5,2);
			aliens_section((float)1.5, (float)1.1,2);
			boost_and_heal_section((float)5.0, 2);
			if (starship_.show_health_points() <= 0)//JESLI ZYCIE GRACZA SPADLO DO ZERA WYSWIETLANY JEST KOMUNIKAT I NASTEPUJE PRZEJSCIE DO MENU GLOWNEGO
			{
				game_over(window);
				return 1;
			}

			/*CZESC RYSUJACA OBIEKTY NA SCENIE*/
			draw_objects(window);
			show_starship_health(window);
			show_score(window);
			show_time(window);
			window.display(); //WYSWIETLANIE SCENY
			set_timers();
			restart_timers();
			return 0;
		}
	}
}

/*ZARZADZANIE TRZECIM ETAPEM GRY*/
int game::stage_three(sf::RenderWindow& window)
{
	if ((loop_clock.getElapsedTime() + loop_time).asMicroseconds() < 2500)//SPRAWDZANIE CZASU PETLI, ABY GRA NIE DZIALALA ZBYT SZYBKO
	{
		return 0;
	}
	else
	{
		loop_clock.restart(); //RESETOWANIE CZASU PETLI
		window.clear();	//CZYSZCZENIE SCENY
		draw_background(window);	//RYSYWANIE TLA
		if (get_stage_time().asSeconds() < 5)  //PRZEZ PIERWSZE PIEC SEKUND ETAPU WYSWIETLANY JEST KOMUNIKAT
		{
			show_stage_entry("LEVEL III", "DESTROY THE FINAL BOSS!", window);			
			loop_time = loop_clock.getElapsedTime();
			return 0;
		}
		else
		{
			if (boss_.show_hp() <= 0)//JESLI ZYCIE BOSSA SPADNIE DO 0 GRA ZAKONCZY SIE SUKCESEM GRACZA, WYSWIETLONY ZOSTANIE WYNIK I GRA PRZEJDZIE DO MENU GLOWNEGO
			{
				score += 300;
				show_stage_exit("GOOD JOB!",window );				
				while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
				{					
				}
				change_stage(0);
				loop_time = loop_clock.getElapsedTime();
				std::this_thread::sleep_for(std::chrono::seconds(1));
				return 0;
			}
			/*CZESC ZARZADZAJACA OBIEKTAMI*/
			starship_.move(2);
			starship_section((float)0.3);
			missiles_section(3,2);
			meteors_section((float)4.0,2);
			aliens_section((float)3.0, (float)1.5,2);
			boost_and_heal_section((float)5.0, 2);
			boss_section((float)3.0);

			if (starship_.show_health_points() <= 0)//JESLI ZYCIE GRACZA SPADLO DO ZERA WYSWIETLANY JEST KOMUNIKAT I NASTEPUJE PRZEJSCIE DO MENU GLOWNEGO
			{
				game_over(window);
				return 1;
			}

			/*CZESC RYSUJACA OBIEKTY NA SCENIE*/
			draw_objects(window);
			show_starship_health(window);
			show_score(window);
			show_time(window);
			show_boss_health(window);
			window.display();//WYSWIETLANIE SCENY
			set_timers();
			restart_timers();
			return 0;
		}
	}
}


/*RESETOWANIE ZEGAROW OBIEKTOW*/
void game::restart_timers()
{
	loop_time = loop_clock.getElapsedTime();
	starship_.reset_clock();
	meteor::reset_static_clock();
	object_with_shared_timer::reset_shared_clock();
	if (stage > 1)
	{
		alien::reset_static_clock();
		if (stage > 2)
			boss_.reset_clock();
	}
}

/*USTAWIANIE CZASOW OBIEKTOW*/
void game::set_timers()
{
	
	if (starship_.check_clock().asSeconds() > 0.5)
		starship_.change_time(0.5);
	else
		starship_.change_time(starship_.check_clock().asSeconds());
	if (object_with_shared_timer::check_shared_clock().asSeconds() > 0.5)
		object_with_shared_timer::change_shared_time(0.5);
	else
		object_with_shared_timer::change_shared_time(object_with_shared_timer::check_shared_clock().asSeconds());
	if (meteor::check_static_clock().asSeconds() > 0.5)
		meteor::change_static_time(0.5);
	else
		meteor::change_static_time(meteor::check_static_clock().asSeconds());
	if (stage > 1)
	{
		if (alien::check_static_clock().asSeconds() > 0.5)
			alien::change_static_time(0.5);
		else
			alien::change_static_time(alien::check_static_clock().asSeconds());
		if (stage > 2)
		{
			if (boss_.check_clock().asSeconds() > 0.5)
				boss_.change_time(0.5);
			else
				boss_.change_time(boss_.check_clock().asSeconds());
		}
	}
}

/*ZARZADZANIE RYSOWANIEM OBIEKTOW NA SCENIE*/
void game::draw_objects(sf::RenderWindow& window)
{
	starship_.draw(window); //RYSOWANIE STATKU
	for (auto iterator = missiles.begin(); iterator != missiles.end(); iterator++) //RYSOWANIE WSZYSTKICH POCISKOW GRACZA
		iterator->draw(window);
	for (auto iterator = meteors.begin(); iterator != meteors.end(); iterator++) //RYSOWANIE WSZYSTKICH METEORYTOW
		iterator->draw(window);
	for (auto iterator = boost_and_heal.begin(); iterator != boost_and_heal.end(); iterator++) //RYSOWANIE WSZYSTKICH ULEPSZEN I DODATKOWYCH ZYC
		(*iterator)->draw(window);
	if (stage > 1)
	{
		for (auto iterator = alien_missiles.begin(); iterator != alien_missiles.end(); iterator++) //RYSOWANIE WSZYSTKICH POCISKOW WROGOW
			iterator->draw(window);
		for (auto iterator = aliens.begin(); iterator != aliens.end(); iterator++) //RYSOWANIE WSZYSTKICH OBCYCH
		{
			iterator->draw(window);
			if (iterator->check_clock().asSeconds() > 0.5)
				iterator->change_time(0.5);
			else
				iterator->change_time(iterator->check_clock().asSeconds());
			iterator->reset_clock();
		}
		if(stage>2) //RYSOWANIE BOSSA
			boss_.draw(window);
	}
}

/*RYSOWANIE TLA NA SCENIE*/
void game::draw_background(sf::RenderWindow& window)
{
	sf::Sprite window_sprite;
	window_sprite.setTexture(window_texture);
	window_sprite.scale(calculate_scale_x(), calculate_scale_y());
	window_sprite.setPosition(0, 0);
	window.draw(window_sprite);
}

/*PRZYGOTOWANIE GRY NA PRZEJSCIE DO KOLEJNEGO ETAPU*/
void game::change_stage(int stage_number)
{
	stage = stage_number; //ZMIANA ETAPU GRY NA WSKAZANY ETAP
	stage_time = sf::seconds(0); //RESETOWANIE CZASU ETAPU
	meteor::zero_destroyed();//RESETOWANIE ZNISZCZONYCH METEOROW
	alien::zero_destroyed();//RESETOWANIE ZNISZCZONYCH OBCYCH
	boss_.set_hp(100); //RESETOWANIE ZDROWIA BOSSA
	new_stage(); //PRZYGOTOWANIE KONTENEROW Z OBIEKTAMI
	starship_.set_position(int(SCREEN_WIDTH * 0.5), int(SCREEN_HEIGHT * 0.66)); //RESETOWANIE POZYCJI STATKU
}

/*RYSOWANIE NA SCENIE KOMUNIKATU O KONCU GRY ORAZ PRZEJSCIE DO MENU GLOWNEGO*/
void game::game_over(sf::RenderWindow& window)
{
	text.setString("GAME OVER");
	text.setCharacterSize((unsigned int)(256*SCALE_X));
	text.setPosition((SCREEN_WIDTH/2 - text.getLocalBounds().width / 2), (SCREEN_HEIGHT/2 - text.getLocalBounds().height / 2));
	window.draw(text);
	change_stage(0);
	game_time = sf::seconds(0); //RESETOWANIE CZASU GRY
	next_stage = 0; //ZMIANA ETAPU NA MENU GLOWNE
	window.display();
}

/*PRZYGOTOWANIE GRY NA NOWY ETAP, USUWANIE OBIEKTOW Z PORZPEDNEIGO ETAPU ORAZ RESETOWANIE ZDROWIA GRACZA*/
void game::new_stage()
{
	if(!missiles.empty())
		missiles.clear();
	if (!alien_missiles.empty())
		alien_missiles.clear();
	if (!meteors.empty())
		meteors.clear();
	if (!aliens.empty())
		aliens.clear();
	if (!boost_and_heal.empty())
		boost_and_heal.clear();
	starship_.set_health_points(3);
}

/*ZAWRACANIE CZASU GRY*/
sf::Time game::get_time()
{
	return  game_clock.getElapsedTime();
}

/*RESETOWANIE CZASU GRY*/
void game::reset_time()
{
	game_clock.restart();
}


/*DODANIE DO WYNIKU GRACZA OKRESLONEJ WARTOSCI*/
void game::change_score(int value)
{
	score += value;
}

/*ZWROCENIE WSPOLCZYNNIKA SKALOWANIA X*/
float game::calculate_scale_x()
{
		return SCALE_X;
}

/*ZWROCENIE WSPOLCZYNNIKA SKALOWANIA Y*/
float game::calculate_scale_y()
{
	return SCALE_Y;
}

/*METODA ZARZADZAJACA ROZGRYWKA*/
void game::play_game(sf::RenderWindow& window, sf::Font& font)
{
	srand(time(NULL)); //USTAWIENIE GENERATORA LICZB PSEUDOLOSOWYCH
	window.setMouseCursorVisible(false);	//OPCJA UKRYWAJACA KUROSR MYSZY W OKNIE
	starship_=starship(int(SCREEN_WIDTH * 0.5),int(SCREEN_HEIGHT * 0.66), &starship_texture);	//STWORZENIE OBIEKTU KLASY STARSHIP WYKORZSTYWANEGO PODCZAS GRY
	boss_ = boss(int(SCREEN_WIDTH * 0.5), int(SCREEN_HEIGHT * 0.2), &boss_texture);		//STWORZENIE OBIEKTU KLASY BOSS WYKORZSTYWANEGO PODCZAS GRY
	sf::Event event;	
	while (window.isOpen())
	{
		int game_over = 0; //ZMIENNA FLAGOWA OKRESLAJACA CZY NASTAPIL KONIEC GRY
		while (window.pollEvent(event))	//OBSLUGA ZDARZEN PRIORYTETOWYCH, CZYLI ZAMKNIECIE OKNA LUB WCISNIECIE PRZYCISKU ESC
		{
			if (event.type == sf::Event::Closed)  
				window.close();
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)) /*PO NACISNIECIU KLAWISZA ESC PODCZAS ROGRYWKI NASTEPUJE WEJSCIE DO MENU GLOWNEGO
																								    I ODWROTNIE, PODCZAS MENU GLOWNEGO NASTEPUJE WYJSCIE DO GRY*/
			{
				if (stage != 0)
				{
					next_stage = stage;
					stage = 0;
				}
				else
					stage = next_stage;
			}
		}
		
		switch (stage) //W ZALEZNOSCI OD ETAPU GRY WYBIERANA JEST ODPOWIEDNIA METODA
		{
		case 0:
			call_menu(window,font);
			break;
		case 1:
			game_over = stage_one(window);
			break;
		case 2:
			game_over = stage_two(window);
			break;
		case 3:
			game_over = stage_three(window);
			break;	
		}
		
		while (game_over) //JESLI FLAGA game_over JEST PRAWDZIWA ZATRZYMUJEMY CZAS PRZED PRZEJSCIEM DO MENU GLOWNEGO
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				game_over = 0;
				std::this_thread::sleep_for(std::chrono::milliseconds(500));
			}
		}
	}
}
