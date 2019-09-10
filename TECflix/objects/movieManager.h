//
// Created by conejo on 10/9/19.
//

#ifndef TECFLIX_MOVIEMANAGER_H
#define TECFLIX_MOVIEMANAGER_H

#include "../estructuras/LinkedList.h"
#include "Movie.h"

class movieManager {
private:
    LinkedList<Movie> *lActual,*lAnterior,*Lsiguiente;
public:
    movieManager();
};


#endif //TECFLIX_MOVIEMANAGER_H
