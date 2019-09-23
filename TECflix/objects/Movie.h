//
// Created by conejo on 9/9/19.
//

#ifndef TECFLIX_MOVIE_H
#define TECFLIX_MOVIE_H


#include <string>
#include <map>

class Movie {


private:
    std::map<std::string,std::string> movInfo;
    std::string titulo="", trailer="";
public:
    void setTrailer(const std::string &trailer);

    const std::string &getTrailer() const;

public:
    const std::string &getTitulo() const;

    void setTitulo(const std::string &titulo);

    const std::map<std::string, std::string> &getMovInfo() const;

    void setMovInfo(std::string tag, std::string info);
};


#endif //TECFLIX_MOVIE_H
