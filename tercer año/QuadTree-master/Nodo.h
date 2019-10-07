#ifndef NODO_H
#define NODO_H

#include <SFML/Graphics.hpp>
#include <utility>
#include <stdlib.h>
#include <vector>
#include <iostream>

class Nodo
{
	public:
		Nodo(int p1x, int p1y, int p2x, int p2y)
		{
			p1=std::make_pair(p1x,p1y);
			p2=std::make_pair(p2x,p2y);
			rectangulo.setFillColor(sf::Color::Transparent);  //Asignar color a rectangulo (verde)
			this->altura=abs(p1y-p2y);
			this->ancho=abs(p1x-p2x);
		    rectangulo.setSize(sf::Vector2f(ancho-2,altura-2));
		    rectangulo.setPosition(p1x+1,p1y+1);
		    rectangulo.setOutlineColor(sf::Color::Red);
		    rectangulo.setOutlineThickness(1);
		    this->hijos=new Nodo*[4];
		    for(int i=0;i<4;i++)
		    {
		    	hijos[i]=0;
		    	/*
		    		hijo[0]=0
		    		hijo[1]=0
		    		hijo[2]=0
		    		hijo[3]=0
		    	*/
		    }
		}
		Nodo (std::pair<int,int> p1, std::pair<int,int> p2)
		{
			this->p1=p1;
			this->p2=p2;
			rectangulo.setFillColor(sf::Color::Transparent);  //Asignar color a rectangulo (verde)
			this->altura=abs(p1.second-p2.second);
			this->ancho=abs(p1.first-p2.first);
		    rectangulo.setSize(sf::Vector2f(ancho-2,altura-2));
		    rectangulo.setPosition(p1.first+1,p1.second+1);
		    rectangulo.setOutlineColor(sf::Color::Red);
		    rectangulo.setOutlineThickness(1);
		    this->hijos=new Nodo*[4];
		    for(int i=0;i<4;i++)
		    {
		    	hijos[i]=0;
		    	/*
		    		hijo[0]=0
		    		hijo[1]=0
		    		hijo[2]=0
		    		hijo[3]=0
		    	*/
		    }
		}

		void Dividir()
		{
			std::pair<int,int>pm1,pm2,pm3,pm4,centro;
			pm1=	std::make_pair(p1.first+ancho/2,p1.second);
			pm2=	std::make_pair(p1.first,p1.second+altura/2);
			pm3=	std::make_pair(p2.first,p2.second-altura/2);
			pm4=	std::make_pair(p2.first-ancho/2,p2.second);
			centro= std::make_pair(p1.first+ancho/2,p1.second+altura/2);
			
			this->hijos[0] = new Nodo(p1,centro);
			this->hijos[1] = new Nodo(pm1,pm3);
			this->hijos[2] = new Nodo(pm2,pm4);
			this->hijos[3] = new Nodo(centro,p2);
			
		}

		bool tieneHijos()
		{
			if (this->hijos[0] && this->hijos[1] && this->hijos[2] && this->hijos[3])
				return true;
			return false;
		}

		void recorrerHijos(sf::RenderWindow & window)
		{

			if (this->tieneHijos())
			{
				std::cout<<"Tiene hijos"<<std::endl;
				for (int i=0;i<4;i++)	
				{

					this->hijos[i]->recorrerHijos(window);
					
					//std::cout<<"va por: "<<i<<std::endl;
				}
			}
			else
			{
				std::cout<<"No Tiene hijos"<<std::endl;

				if (this->objetos.size()==5)
				{
					this->Dividir();
				}
				window.draw(this->rectangulo);
				return;
			}
		}

		~Nodo(){}
	public:
		sf::RectangleShape rectangulo;	//Rectangulo para graficar
		Nodo** hijos;	//Array de Nodos hijos
		std::pair<int, int> p1,p2;	//Coordenadas
		int altura, ancho;		//Ancho y Altura del cuadrante
		std::vector<sf::CircleShape> objetos; //Vector de objetos 
};

#endif