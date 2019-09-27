//
// Created by conejo on 10/9/19.
//

#ifndef TECFLIX_MOVIEMANAGER_H
#define TECFLIX_MOVIEMANAGER_H

#include "../estructuras/LinkedList.h"
#include "Movie.h"
#include "../libray/csv.h"
#include <iostream>
#include <curl/curl.h>
#include <stdio.h>

class movieManager {
private:
    /**
	* @brief puntero pagina actual
	**/
    LinkedList<Movie> *lActual= nullptr ;
    /**
    * @brief puntero pagina anterior
    **/
    LinkedList<Movie>*lAnterior= nullptr;
    /**
    * @brief puntero pagina siguiente
    **/
    LinkedList<Movie>*lSiguiente= nullptr;
    /**
    * @brief metodo para generar paginas
    * @param limi limite de paginas
    * @param bas inicio de la pagina
    **/
    LinkedList<Movie>*generatePage(int limi,int bas);
    /**
    * @brief limite inferior de la paginas
    **/
    int base;
    /**
    * @brief tamaño maximo de paginas
    **/
    int MAXSize;
    /**
    * @brief limite superior de la paginas
    **/
    int limit;
    /**
    * @brief pagina actual
    **/
    int page;
public:
    /**
    * @brief metodo de encapsulacion para de la pagina actual
    **/
    int getPage() const;
    /**
    * @brief metodo de encapsulacion para de la pagina actual
    * @param cambio de pagina
    **/
    void setPage(int page);

    /**
    * @brief metodo de encapsulacion para de la lista actual
    * @param lActual puntero para la lista
    **/
    LinkedList<Movie> *getLAnterior() const;
    /**
    * @brief metodo de encapsulacion para de la lista anterior
    * @param lAnterior puntero para la lista
    **/
    void setLAnterior(LinkedList<Movie> *lAnterior);
    /**
    * @brief metodo de encapsulacion para de la lista siguiente
    **/
    LinkedList<Movie> *getLSiguiente() const;
    /**
    * @brief metodo de encapsulacion para de la lista siguiente
    * @param lSiguiente puntero para la lista
    **/
    void setLSiguiente(LinkedList<Movie> *lSiguiente);
    /**
    * @brief metodo para obtener la lista actual
    * @return la lista actual
    **/
    LinkedList<Movie> *getLActual() const;
    /**
    * @brief trae la imagen de la pagina de IMDB y las guarda en la carpete de imagenes
    * @param url direccion de pelicula
    * @param name nombre de la pelicula
    **/
    void bringIMG(std::string url,std::string name);
    /**
    * @brief metodo de encapsulacion para de la lista actual
    * @param lActual puntero para la lista
    **/
    void setLActual(LinkedList<Movie> *lActual);
    /**
    * @brief metodo auxiliar para la descarga de imagen y trailer
    * @param contents
    * @param size
    * @param nmemb
    * @param userp
    **/
    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
    /**
    * @brief trae el url del trailer de la pagina de IMDB
    * @param url direccion de IMDB
    * @return la direccion del trailer
    **/
    std::string trailerURL(std::string url);
    /**
    * @brief constructo de movieManager
    **/
    movieManager();
    /**
	* @brief metodo para traer la pagina siguiente
	**/
    void nextPage();
    /**
	* @brief metodo para traer la pagina anterior
	**/
    void backPage();
    /**
	* @brief metodo para traer la pagina siguiente y crear la actualal
	**/
    void beginPages();

};


#endif //TECFLIX_MOVIEMANAGER_H
