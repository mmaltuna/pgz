#pragma once

#ifndef __MAP_H__
#define __MAP_H__

#include "TileMap.h"
#include "SolidGrid.h"
#include "GfxEngine.h"

using namespace std;

//! Representa un mapa basado en tiles, tanto su parte g�fica como su parte de colisiones.
/*!
	Encapsula un TileMap para la parte gr�fica y un SolidGrid para la parte de colisiones.
	
	Proporciona m�todos para modificar las propiedades de las clases que encapsula y
	m�todos de carga, as� como uno de actualizaci�n y otro de renderizado, todos virtuales.
	
	Para una mayor comodidad, se puede derivar una clase de Map, sobreescribir los
	m�todos que interesen (por ejemplo el de carga) y pas�rsela al GameState pertinente
	para que la mantenga de forma autom�tica.
	
	La forma com�n de trabajar con Map es:
	- Instanciar el Map con el tama�o de tile deseado
	- Indicar al Map el tileset que debe utilizar mediante Map::setTileset().
	- Cargar el mapa:
		- Con el m�todo por defecto
		- De forma externa al Map, pas�ndoselo luego mediante Map::setSolids() y Map::setTiles()
	- Mantener actualizado el mapa con Map::update()
	- Renderizar el mapa cuando corresponda con Map::render();
	
	\sa GameState
	\sa TileMap
	\sa SolidGrid
*/

class Map
{
	private:
		//! Atributos de la clase SpriteMap.
		/*!
			\param tileMap aspecto gr�fico de un mapa de tiles
			\param solidGrid matriz de s�lidos de un mapa de tiles
		*/
		TileMap* tileMap;
		SolidGrid* solidGrid;
	
    public:

		//! Construye el Map con el ancho y alto de tile indicados
		/*!
			\param tileW Ancho de los tiles del mapa
			\param tileH Alto de los tiles del mapa
			\param gfxEngine Puntero al GfxEngine del sistema
		*/
		Map(int tileW, int tileH, GfxEngine* gfxEngine);

		//! Destruye el Map
        virtual ~Map();

		//! Carga el la parte de colisiones del mapa con el m�todo por defecto
		/*!
			\param fname Nombre del archivo a cargar
		*/
		virtual void loadSolids(string fname);
		
		//! Devuelve el contenido de la parte de colisiones del Map.
		virtual SolidGrid* getSolids();

		//! Establece el contenido de la parte de colisiones del Map.
		/*!
			\param solids Array con los tipos de las celdas
		*/
		virtual void setSolids(int x, int y, int** solids, int columns, int rows);
		
		//! Establece el tileset que utilizar� el mapa
		/*!
			\param fname Nombre de archivo del tileset
		*/
		virtual void setTileset(string fname);
		
		//! Carga el la parte de gr�ficos del mapa con el m�todo por defecto
		/*!
			\param fname Nombre del archivo a cargar
		*/
		virtual void loadTiles(string fname);
		
		//! Establece el contenido de la parte de gr�ficos del Map.
		/*!
			\param tiles Array con los tiles
		*/
		virtual void setTiles(int** tiles);

		//! Carga el mapa completo (gr�ficos y colisiones) con el m�todo por defecto
		/*!
			\param fname Nombre del archivo a cargar
		*/
		virtual void loadMap(string fname);

		//! Actualiza la imagen y el estado de los s�lidos del Map
		virtual void update();
		
		//! Muestra el mapa en la posici�n indicada
		/*!
			\param x Posici�n horizontal
			\param y Posici�n vertical
		*/
        virtual void render(int x, int y);
        
};

#endif // MAP_H
