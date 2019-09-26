//
// Created by conejo on 10/9/19.
//

#include "movieManager.h"

movieManager::movieManager() {
    base=0;
MAXSize=9;
limit=MAXSize;
}


void movieManager::beginPages() {
 io::CSVReader<13> in("../csv/movie_metadata.csv");
    in.read_header(io::ignore_extra_column, "color", "director_name", "movie_title","aspect_ratio","imdb_score","title_year"
            ,"content_rating","country","movie_imdb_link","plot_keywords",
                   "genres","gross","duration"
    );
    std::string color, director_name, movie_title,aspect_ratio,imdb_score,title_year
    ,content_rating,country,movie_imdb_link,plot_keywords,
            genres,gross,duration
    ;
    int i=0;
    LinkedList<Movie> *l1= new LinkedList<Movie>();

    while(in.read_row(color, director_name, movie_title,aspect_ratio,imdb_score,title_year
            ,content_rating,country,movie_imdb_link,plot_keywords,
                      genres,gross,duration )&& i < base + MAXSize){

        Movie h;
        h.setTitulo(movie_title);
        h.setMovInfo("color",color);
        h.setMovInfo("Director name",director_name);
        h.setMovInfo("Aspect_ratio",aspect_ratio);
        h.setMovInfo("IMDB score",imdb_score);
        h.setMovInfo("Title year",title_year);

        h.setMovInfo("Content_rating",content_rating);
        h.setMovInfo("Country",country);
        h.setMovInfo("Movie_imdb_link",movie_imdb_link);
        h.setMovInfo("Plot_keywords",plot_keywords);
        h.setMovInfo("Genres",genres);
        h.setMovInfo("Gross",gross);

        h.setMovInfo("Duration",duration);
        h.setTrailer(trailerURL(movie_imdb_link));
        //bringIMG(movie_imdb_link,movie_title);
        l1->insertAtEnd(h);
        std::cout<< movie_title<<std::endl;
        i++;



    }
    this->setLActual(l1);
    std::cout<< "lista siguiente:"<<std::endl;
    this->setLSiguiente(generatePage(limit+MAXSize,base+MAXSize)) ;


}

LinkedList<Movie> *movieManager::getLActual() const {
    return lActual;
}

void movieManager::setLActual(LinkedList<Movie> *lActual) {
    movieManager::lActual = lActual;
}

size_t movieManager::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void movieManager::bringIMG(std::string url, std::string nam) {
    CURL *curl;
    CURLcode res;
    std::string readBuffer;
    std::string imgurl,imgTag,nombre;
    const char *direct,*name;
    curl = curl_easy_init();

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        //std::cout << readBuffer << std::endl;
        int posI= readBuffer.find("<link rel='image_src' href=\"");
        int posF= readBuffer.find("  <meta property='og:image' content=\"");
        imgTag= readBuffer.substr(posI,posF-posI);
        posI=imgTag.find("https:");
        posF=imgTag.find("\">");
        imgurl=imgTag.substr(posI,posF-posI);


        //std::cout << imgurl << std::endl;
    }

    if (imgurl.find(".png")==-1){
        nombre="../images/"+nam+".jpg";
    }else{nombre="../images/"+nam+".png";}

    direct= imgurl.c_str();
    name=nombre.c_str();

    FILE *fp;
    int result;
    fp = fopen( name,"wb");
    curl = curl_easy_init();
    curl_easy_setopt(curl,CURLOPT_URL,direct);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA,fp);
    curl_easy_setopt(curl,CURLOPT_FAILONERROR,1l);
    result =curl_easy_perform(curl);

    if(result==CURLE_OK){
        //printf("descargo");
    }else {printf("error:%s\n", curl_easy_strerror(static_cast<CURLcode>(result)));}

    fclose(fp);
    curl_easy_cleanup(curl);
}

void movieManager::nextPage() {
    if(lAnterior!= nullptr){lAnterior->deleteAll();}
lAnterior=lActual;
lActual=lSiguiente;
lSiguiente= nullptr;
    base+=MAXSize;
    limit+=MAXSize;
std::cout<<"lista siguiente: " <<std::endl;
this->setLSiguiente(generatePage(limit+MAXSize,base+MAXSize));
//generatePages(base + MAXSize, lSiguiente);


}



void movieManager::backPage() {
    if(lSiguiente!= nullptr){lSiguiente->deleteAll();}
    lSiguiente=lActual;
    lActual=lAnterior;
    std::cout<<"lista anterior: " <<std::endl;
    this->setLAnterior(generatePage(limit-MAXSize,base-MAXSize));
    //corregir la actual
    //generatePages(base-9,lAnterior);
    base-=MAXSize;
}

std::string movieManager::trailerURL(std::string url) {
    CURL *curl;
    CURLcode res;
    std::string readBuffer;
    std::string VidURL,vidTag;

    curl = curl_easy_init();
    //std::cout << "obteniendo trailer" << std::endl;
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        //std::cout << readBuffer << std::endl;
        int posI= readBuffer.find("\"embedUrl\":");
        int posF= readBuffer.find("\"thumbnail\"");
        if(posI!=-1){
            vidTag= readBuffer.substr(posI, posF - posI);
            posI=vidTag.find("/v");
            posF=vidTag.find("\",");
            VidURL="firefox https://www.imdb.com";
            VidURL.append(vidTag.substr(posI, posF - posI));
        }
        else{
            VidURL="firefox https://www.youtube.com";
        }



        //std::cout << VidURL << std::endl;
    }
    return VidURL;
}

LinkedList<Movie> *movieManager::getLAnterior() const {
    return lAnterior;
}

void movieManager::setLAnterior(LinkedList<Movie> *lAnterior) {
    movieManager::lAnterior = lAnterior;
}

LinkedList<Movie> *movieManager::getLSiguiente() const {
    return lSiguiente;
}

void movieManager::setLSiguiente(LinkedList<Movie> *lSiguiente) {
    movieManager::lSiguiente = lSiguiente;
}

LinkedList<Movie> *movieManager::generatePage(int limi,int bas) {
    io::CSVReader<13> in("../csv/movie_metadata.csv");
    in.read_header(io::ignore_extra_column, "color", "director_name", "movie_title","aspect_ratio","imdb_score","title_year"
            ,"content_rating","country","movie_imdb_link","plot_keywords",
                   "genres","gross","duration"
    );
    std::string color, director_name, movie_title,aspect_ratio,imdb_score,title_year
    ,content_rating,country,movie_imdb_link,plot_keywords,
            genres,gross,duration
    ;
    int i=0;
    LinkedList<Movie> *l1= new LinkedList<Movie>();
    while(in.read_row(color, director_name, movie_title,aspect_ratio,imdb_score,title_year
            ,content_rating,country,movie_imdb_link,plot_keywords,
                      genres,gross,duration )&& i<limi){



        if(i < limi&&i>bas-1){
            Movie h;
            h.setTitulo(movie_title);
            h.setMovInfo("color",color);
            h.setMovInfo("Director name",director_name);
            h.setMovInfo("Aspect_ratio",aspect_ratio);
            h.setMovInfo("IMDB score",imdb_score);
            h.setMovInfo("Title year",title_year);

            h.setMovInfo("Content_rating",content_rating);
            h.setMovInfo("Country",country);
            h.setMovInfo("Movie_imdb_link",movie_imdb_link);
            h.setMovInfo("Plot_keywords",plot_keywords);
            h.setMovInfo("Genres",genres);
            h.setMovInfo("Gross",gross);

            h.setMovInfo("Duration",duration);
            h.setTrailer(trailerURL(movie_imdb_link));
            //bringIMG(movie_imdb_link,movie_title);
            l1->insertAtEnd(h);
            std::cout<< movie_title<<std::endl;
            i++;
            }
        else{
            i++;
            continue;
        }

    }

    return l1;
}





