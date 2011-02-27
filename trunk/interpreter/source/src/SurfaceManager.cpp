#include "SurfaceManager.h"
		
/***********************************************
 *			Funciones P�blicas				   *
 ***********************************************/

/* SurfaceManager::SurfaceManager() */
/*
	Instanciamos la lista de direcciones/imagenes.
*/
SurfaceManager::SurfaceManager()
{
	list = new map<string,SurfaceManagerItem*>();
}

/* SurfaceManager::~SurfaceManager() */
/*
	Borramos primero todos los elementos y luego destruimos la lista.
*/
SurfaceManager::~SurfaceManager()
{
	//elimina todos los elementos y llama a la destructora de cada uno.
	//list->clear(); mejor hacerlo manual:
	map< string, SurfaceManagerItem* >::iterator it = list->begin();
	SurfaceManagerItem* tmp;
	while (it != list->end())
	{
		tmp = it->second;
		it++;
		if (tmp)
		{
			//Invocamos Destructora de SurfaceManagerItem
			delete tmp;
			tmp = NULL;
		}
	}

	delete list;
	list = NULL;
}
		
/* bool SurfaceManager::isLoaded(string fname) */
/*
	Buscamos si se encuentra el gr�fico con dicho nombre.
	Devuelve true si lo encontramos. En otro caso false.
*/
bool SurfaceManager::isLoaded(string fname)
{
	if(list)	//Comprueba si list no es NULL
		return list->find(fname) != list->end();
	else
		return false;
}
		
/* bool SurfaceManager::isLoaded(sf::Image* surf) */
/*
	Buscamos si est� la imagen/gr�fico ya cargada dado su puntero a ella.
	Devuelve true si la encuentra. False en caso contrario.
*/
bool SurfaceManager::isLoaded(sf::Image* surf)
{
	if(list)
	{
		map<string, SurfaceManagerItem*>::iterator it;
		for (it = list->begin(); it != list->end(); it++)
		{
			if (it->second->getSurface() == surf)
				return true;
		}
	}
	return false;
}
		
/* const sf::Image* SurfaceManager::getSurface(string fname) */
/*
	Devolvemos puntero a la imagen que corresponde al nombre dado(clave).
	Devuelve puntero a la imagen si la encuentra. En otro caso devuelve NULL
*/
const sf::Image* SurfaceManager::getSurface(string fname)
{
	if(list)
	{
		map<string, SurfaceManagerItem*>::iterator it;
		it = list->find(fname);
		if(it != list->end())
		{
			SurfaceManagerItem* tmp = it->second;
			//incrementamos la cantidad de enlaces con uno.
			tmp->link();
			//devolvemos el puntero a la imagen
			return tmp->getSurface();
		}
		else
			//no hemos encontrado la imagen solicitada
			return NULL;
	}
	else
		//no est� instanciada la lista
		return NULL;
}
		
/* bool SurfaceManager::setSurface(string fname, sf::Image* surf) */
/*
	Introducimos un nuevo par nombre e imagen.
	Devuelve true si se consigui� introducir correctamente.
	Si ya hay una entrada con ese nombre(clave) o con un puntero a la imagen,
	no se introduce y se devuelve false.
*/
bool SurfaceManager::setSurface(string fname, sf::Image* surf)
{
	if(list && surf) //ni list ni surf son NULL
	{
		map<string, SurfaceManagerItem*>::iterator it;
		it = list->find(fname);
		if(it == list->end()) //ha llegado al final del mapa sin encontrar fname?
		{
			SurfaceManagerItem* item = new SurfaceManagerItem(surf);
			list->insert(pair<string, SurfaceManagerItem*>(fname, item));
			return true;
		}
	}
	//Ya hay una imagen con ese nombre o surf = NULL o list = NULL
	return false;
}
		
/* bool SurfaceManager::remove(string fname) */
/*
	Elimina la entrada de la lista y el elemento que la encapsula dado su nombre
	PERO NO BORRA LA IMAGEN/SUPERFICIE, de eso se encarga gfxEngine.
	Devuelve true si la ha podido eliminar(se han agotado los enlaces simb�licos).
		En otro caso false.
*/
bool SurfaceManager::remove(string fname)
{
	if(list)
	{
		map<string, SurfaceManagerItem*>::iterator it;
		it = list->find(fname);
		if(it != list->end())
		{
			SurfaceManagerItem* tmp = it->second;
			if (tmp->unlink())
			{
				//delete tmp->getSurface(); // Esto lo debe hacer GfxEngine
				delete tmp;
				tmp = NULL;

				list->erase(it);
				//lo hemos eliminado del todo
				return true;
			}
			//solo hemos quitado un enlace simb�lico, pero hay m�s enlaces.
			return false;
		}
	}
	//No se encontr� la image con ese nombre o no hay lista.
	return false;
}
		
/* bool SurfaceManager::remove(const sf::Image* surf) */
/*
	Elimina la entrada de la lista y el elemento que la encapsula dado su puntero a la imagen
	PERO NO BORRA LA IMAGEN/SUPERFICIE, de eso se encarga gfxEngine.
	Devuelve true si la ha podido eliminar(se han agotado los enlaces simb�licos).
		En otro caso false.
*/
bool SurfaceManager::remove(const sf::Image* surf)
{
	if(list && surf) //ni list ni surf son NULL
	{
		map<string, SurfaceManagerItem*>::iterator it;
		for (it = list->begin(); it != list->end(); it++)
		{
			if (it->second->getSurface() == surf)
			{
				SurfaceManagerItem* tmp = it->second;
				if (tmp->unlink())
				{
					//delete tmp->getSurface(); // Esto lo debe hacer GfxEngine
					delete tmp;
					tmp = NULL;

					list->erase(it);
					//lo hemos eliminado del todo
					return true;
				}
				//solo hemos quitado un enlace simb�lico, pero hay m�s enlaces.
				return false;
			}
		}
	}
	//No se encontr� la image o param entrada NULL o no hay lista.
	return false;
}