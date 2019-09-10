//
// Created by conejo on 9/9/19.
//

#ifndef TECFLIX_MOVIE_H
#define TECFLIX_MOVIE_H


#include <string>
#include <map>

class Movie {

public:
private:
    std::map<std::string,std::string> movInfo;
public:
    const std::map<std::string, std::string> &getMovInfo() const;

    void setMovInfo(std::string tag, std::string info);
};


#endif //TECFLIX_MOVIE_H
