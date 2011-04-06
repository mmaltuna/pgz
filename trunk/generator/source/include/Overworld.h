#pragma once

#ifndef _OVERWORLD_H_
#define _OVERWORLD_H_

#include <time.h>
#include <vector>
#include <string>
#include <fstream>
#include "GenTypes.h"
#include "MapTile.h"


using namespace std;

// Clase encargada de almacenar los datos que genera la clase GenOverworld y de posteriormente crear los archivos de mapa que cargar� el motor.
/*
	Recibimos informaci�n de Decidator sobre el tama�o del mundo, zonas, mazmorras y zonas seguras.
	Una instancia de GenOverworld trabaja sobre nosotros y modifica mapTileMatrix, startLocation, prizePoints. Para ello, esta se instancia pas�ndole un puntero al propio objeto (this).
	Con toda esta informaci�n el generador de vida aportar� sus modificaciones adicionales.
	El Overwolrd finalizado llama a su operaci�n genScreens para generar los archivos de mapa.
*/

class Overworld{
	private:
		// Tama�o de la matriz mapTileMatrix
		int worldSizeH;	// Alto
		int worldSizeW;	// Ancho

		int worldDiff; // Dificultad del juego
		

	public:
		// Indicador del tama�o del overworld, genOverworld lo interpreta para asignar un ancho y alto adecuado.
		int worldSize;

		// Vector que contiene informaci�n sobre las zonas que deben generarse.
		vector<ZoneInfo>* zonesInfo;

		// Vector que contiene informaci�n sobre las mazmorras que deben generarse.
		vector<DungeonInfo>* dungeonsInfo;

		// Vector que contiene informaci�n sobre las zonas seguras que deben generarse.
		vector<SafeZoneInfo>* safeZonesInfo;

		// Punto donde comienza el personaje al iniciar por pirmera vez el juego, lo establece genOverworld y lo leer� genLife
		GPoint startLocation;

		// Puntos del overworld donde colocar premios/secretos, lo establece genOverworld y lo leer� genLife
		vector<GPoint> prizePoints;

		// Mega-matriz sobre la que trabaja genOverworld
		vector<MapTile*>* mapTileMatrix;

		// Constructora: recibe la informaci�n de Decidator y la almacena en sus atributos pertinentes.
		Overworld(int wSize, int wDiff, vector<ZoneInfo>* zonesI, vector<DungeonInfo>* dungeonsI, vector<SafeZoneInfo>* safeZonesI);

		// Destructora
		~Overworld();

		// Guarda un archivo con informaci�n global sobre el overworld que ha sido generado
		void save();

		// Getters utiles:
		int getNumZones();

		int getNumDungeons();

		int getNumSafeZones();

		int getWorldDiff();

		vector<ZoneInfo>* getZonesInfo();

		int getWorldSizeH();
		int getWorldSizeW();
		MapTile* getMapTile(int x, int y);
};

#endif