//
// Created by conejo on 9/9/19.
//

#ifndef TECFLIX_MOVIE_H
#define TECFLIX_MOVIE_H


#include <string>
#include <map>

class Movie {
private:
    /**
    * @brief mapa que guarda la informacion de la pelicula
    **/
    std::map<std::string,std::string> movInfo;
    /**
    * @brief titulo de la pelicula
    **/
    std::string titulo="";
    /**
    * @brief titulo de la pelicula
    **/
    std::string trailer="";

public:
    /**
    * @brief metodo de encapsulacion para del trailer
    * @param trailer link trailer
    **/
    void setTrailer(const std::string &trailer);
    /**
    * @brief metodo de encapsulacion para del trailer
    **/
    const std::string &getTrailer() const;
    /**
    * @brief metodo de encapsulacion para del titulo
    **/
    const std::string &getTitulo() const;
    /**
    * @brief metodo de encapsulacion para del titulo
    * @param titulo titulo
    **/
    void setTitulo(const std::string &titulo);
    /**
    * @brief metodo de encapsulacion para del informacion de la pelicula
    **/
    const std::map<std::string, std::string> &getMovInfo() const;
    /**
    * @brief metodo de encapsulacion para del trailer
    * @param tag etiqueta de la informacion
    * @param info informacion de la pelicula
    **/
    void setMovInfo(std::string tag, std::string info);
};


#endif //TECFLIX_MOVIE_H
