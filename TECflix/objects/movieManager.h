//
// Created by conejo on 10/9/19.
//

#ifndef TECFLIX_MOVIEMANAGER_H
#define TECFLIX_MOVIEMANAGER_H

#include "../estructuras/LinkedList.h"
#include "Movie.h"
#include "../libray/csv.h"
#include <curl/curl.h>
#include <stdio.h>

class movieManager {
private:
    LinkedList<Movie> *lActual,*lAnterior,*lSiguiente;
public:
    LinkedList<Movie> *getLActual() const;
    void bringIMG(std::string url,std::string name);
    void setLActual(LinkedList<Movie> *lActual);
    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);

public:
    movieManager();
    void geeneratePages();
    void beginPages();
};


#endif //TECFLIX_MOVIEMANAGER_H
