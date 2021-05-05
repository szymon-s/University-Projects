#include "objects.h"
#include "game.h"

/*WERSJA FINALNA*/


//DEFINIOWANIE POL STATYCZNYCH

int alien::destroyed = 0;
int meteor::destroyed = 0;
int button::number_of_buttons = 0;
int button::selected_button = 0;				
sf::Clock alien::aliens_clock;
sf::Time alien::aliens_time;
sf::Clock button::clock;
sf::Clock meteor::meteors_clock;
sf::Time meteor::meteors_time;
sf::Time object_with_shared_timer::shared_time;
sf::Clock object_with_shared_timer::shared_clock;

int main()
{
	//TWORZENIE OKNA PROGRAMU
	sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Space Adventure", sf::Style::Fullscreen);

	//VECTOR Z NAZWAMI PLIKOW GRAFICZNYCH Z TEKSTURAMI OBIEKTOW
	std::vector<std::string>file_names = { "textures\\starship.png","textures\\common_missile.png","textures\\meteor.png","textures\\alien.png","textures\\alien_missile.png","textures\\boss.png","textures\\boss_missile.png","textures\\heart_full.png","textures\\boost.png","textures\\background.jpeg","textures\\button.png","textures\\button_selected.png","textures\\Title.png","textures\\heart_empty.png","textures\\boosted_missile.png" };
	
	//WCZYTYWANIE UZYWANEJ CZCIONKI
	sf::Font font;
	font.loadFromFile("textures\\comic.ttf");

	//ROZPOCZECIE GRY
	game game(file_names, font);
	game.play_game(window,font);

    return 0;
}