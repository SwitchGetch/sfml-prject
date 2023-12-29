#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>
#include <string>
#include <vector>
#include <cmath>
using namespace std;
using namespace sf;
using namespace chrono;

double distance(Vector2f p1, Vector2f p2)
{
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

int main()
{
    high_resolution_clock::time_point start;
    high_resolution_clock::time_point end;
    string title;
    double fps;

    RenderWindow window(sf::VideoMode(1000, 750), "");
    window.setFramerateLimit(60);


    RectangleShape object0(Vector2f(100, 100));
    object0.setPosition(600, 300);
    object0.setFillColor(Color::Red);

    RectangleShape object1(Vector2f(100, 100));
    object1.setPosition(300, 400);
    object1.setFillColor(Color::Red);

    RectangleShape object2(Vector2f(100, 100));
    object2.setPosition(500, 500);
    object2.setFillColor(Color::Red);

    RectangleShape object3(Vector2f(100, 100));
    object3.setPosition(400, 200);
    object3.setFillColor(Color::Red);

    vector<RectangleShape> objects{object0, object1, object2, object3};

    Vector2f position(0, 0);
    double speed = 10;


    while (window.isOpen())
    {
        start = high_resolution_clock::now();


        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
        }


        if (Keyboard::isKeyPressed(Keyboard::W))
        {
            position.y += -speed;
        }
        if (Keyboard::isKeyPressed(Keyboard::A))
        {
            position.x += -speed;
        }
        if (Keyboard::isKeyPressed(Keyboard::S))
        {
            position.y += speed;
        }
        if (Keyboard::isKeyPressed(Keyboard::D))
        {
            position.x += speed;
        }


        window.clear();


        for (int i = 0; i < objects.size(); i++)
        {
            window.draw(objects[i]);
        }

        for (int i = 0; i < objects.size(); i++)
        {
            for (int j = 0; j < objects[i].getPointCount(); j++)
            {
                double x = position.x;
                double y = position.y;
                double x1 = objects[i].getPosition().x + objects[i].getPoint(j).x;
                double y1 = objects[i].getPosition().y + objects[i].getPoint(j).y;

                double l = distance(Vector2f(x, y), Vector2f(x1, y1));

                double cosa = (x1 - x) / l;
                double sina = (y1 - y) / l;

                Vector2f previous((l - 1) * cosa + x, (l - 1) * sina + y);

                if (!(previous.x >= objects[i].getPosition().x && previous.y >= objects[i].getPosition().y &&
                    previous.x <= objects[i].getPosition().x + objects[i].getSize().x && previous.y <= objects[i].getPosition().y + objects[i].getSize().y))
                {
                    VertexArray line(Lines, 2);

                    line[0].position = Vector2f(x, y);
                    line[1].position = Vector2f(x1, y1);

                    window.draw(line);
                }
            }
        }


        window.display();


        end = high_resolution_clock::now();

        fps = 1e9f / duration_cast<chrono::nanoseconds>(end - start).count();

        title = "FPS " + to_string(fps);

        window.setTitle(title.c_str());
    }
}