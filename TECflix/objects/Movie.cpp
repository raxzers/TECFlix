//
// Created by conejo on 9/9/19.
//

#include "Movie.h"

const std::map<std::string, std::string> &Movie::getMovInfo() const {
    return movInfo;
}

void Movie::setMovInfo(std::string tag, std::string info) {

    movInfo.insert(std::pair<std::string, std::string>(tag, info));

}

const std::string &Movie::getTitulo() const {
    return titulo;
}

void Movie::setTitulo(const std::string &titulo) {
    Movie::titulo = titulo;
}


