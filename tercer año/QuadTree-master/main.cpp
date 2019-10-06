#include <iostream>

#include <SFML/Graphics.hpp>
#include "Nodo.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 500), "QuadTree");
    /*sf::RectangleShape shape;	//Rectangulo
    shape.setFillColor(sf::Color::Transparent);  //Asignar color a shape (verde)
    shape.setSize(sf::Vector2f(30,100));
    shape.setPosition(1,1);
    shape.setOutlineColor(sf::Color::Red);
    shape.setOutlineThickness(1);*/
    Nodo hola(0,0,500,500);
    int x,y;
   	bool soltado=false;
   	std::vector<sf::CircleShape> circulos;

    while (window.isOpen())
    {
    	//Verificador de Eventos
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
            	if (event.key.code== sf::Keyboard::Escape)
            		window.close();
            }
            if (event.type==sf::Event::MouseButtonReleased)
            {
            	if (event.mouseButton.button == sf::Mouse::Left)
            	{
            		x=event.mouseButton.x;
            		y=event.mouseButton.y;
            		std::cout<<"Se solto: "<<x<<" "<<y<<std::endl;
            		soltado=true;
            	}
            }
        }

        if(soltado)
        {
        	sf::CircleShape nuevo(5);
        	nuevo.setPosition(x,y);
        	nuevo.setFillColor(sf::Color::Blue);
        	soltado=false;
        	std::cout<<"Se creo"<<std::endl;
        	circulos.push_back(nuevo);
        }
        window.clear();	//Limpiar la Ventana
        //window.draw(shape);	//Dibujar el circulo (shape)
        //window.draw(hola.rectangulo);
        for (auto i : circulos)
        {
        	window.draw(i);
            hola.objetos=circulos;
        }
        //hola.Dividir();
        hola.recorrerHijos(window);

        window.display();	//Mostrarlo en pantalla
    }
    return 0;
}