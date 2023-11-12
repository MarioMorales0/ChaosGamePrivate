// Include important C++ libraries here
// Group: Mario Mata, Ethan Henning

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>

// Make code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
    // Create a video mode object
	VideoMode vm(1920, 1080);
	// Create and open a window for the game
	RenderWindow window(vm, "Chaos Game", Style::Default);

    vector<Vector2f> vertices;
    vector<Vector2f> points;

    Font font;

    if (!font.loadFromFile("Sawasdee-Bold.ttf"))
    {
        cout << "Error loading font!!";
        return 2;
    }

    Text text;

    text.setFont(font);

    text.setString("Click three times on screen to create the triangle.");

    text.setCharacterSize(24);

    text.setFillColor(Color::White);

    srand(time(nullptr));

    int randNum;
    Vector2f randVertex, midpoint;

	while (window.isOpen())
	{
        /*
		****************************************
		Handle the players input
		****************************************
		*/
        randNum = rand() % 3;

        Event event;
		while (window.pollEvent(event))
		{
            if (event.type == Event::Closed)
            {
				// Quit the game when the window is closed
				window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    std::cout << "the left button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;

                    if(vertices.size() < 3)
                    {
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                    else if(points.size() == 0)
                    {
                        ///fourth click
                        ///push back to points vector
                        points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                }
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
        /*
		****************************************
		Update
		****************************************
		*/

        if(points.size() > 0)
        {
            ///generate more point(s)

            ///select random vertex
            randVertex = vertices.at(randNum);
            midpoint.x = (randVertex.x - points.back().x) / 2;
            midpoint.y = (randVertex.y - points.back().y) / 2;

            ///calculate midpoint between random vertex and the last point in the vector
            points.push_back(midpoint);
            ///push back the newly generated coord.
            //test
        }

        /*
		****************************************
		Draw
		****************************************
		*/
        window.clear();
        window.draw(text);
        for(int i = 0; i < vertices.size(); i++)
        {
            RectangleShape rect(Vector2f(10,10));
            rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
            rect.setFillColor(Color::White);
            window.draw(rect);
        }

        for(int i = 0; i < points.size(); i++)
        {
            RectangleShape rect(Vector2f(2,2));
            rect.setPosition(Vector2f(points[i].x, points[i].y));
            rect.setFillColor(Color::White);
            window.draw(rect);
        }

        window.display();
    }
}