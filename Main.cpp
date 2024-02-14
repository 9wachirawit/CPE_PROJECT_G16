#include <SFML/Graphics.hpp>
using namespace sf;

int main()
{
	RenderWindow window(VideoMode(800, 600), "TITLE");
	Event ev;

	while (window.isOpen())
	{
		while (window.pollEvent(ev))
		{
			if (ev.type == ev.Closed)
			{
				//window.close();
			}
		}
	}


}
	
