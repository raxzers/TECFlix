//
// Created by conejo on 10/9/19.
//

#include "movieManager.h"

movieManager::movieManager() {

}

void movieManager::geeneratePages() {
    lActual = new LinkedList<Movie>();
    lAnterior = new LinkedList<Movie>();
    lSiguiente = new LinkedList<Movie>();

}

void movieManager::beginPages() {
    io::CSVReader<17> in("../csv/movie_metadata.csv");
    in.read_header(io::ignore_extra_column, "color", "director_name", "movie_title","aspect_ratio","imdb_score","title_year"
            ,"budget","content_rating","country","movie_imdb_link","plot_keywords",
                   "genres","gross","actor_1_name","actor_2_name","actor_3_name","duration"
    );
    std::string color, director_name, movie_title,aspect_ratio,imdb_score,title_year
    ,budget,content_rating,country,movie_imdb_link,plot_keywords,
            genres,gross,actor_1_name,actor_2_name,actor_3_name,duration
    ;
    int i=0;
    LinkedList<Movie> l1= LinkedList<Movie>();
    while(in.read_row(color, director_name, movie_title,aspect_ratio,imdb_score,title_year
            ,budget,content_rating,country,movie_imdb_link,plot_keywords,
                      genres,gross,actor_1_name,actor_2_name,actor_3_name,duration )&& i<9){
        Movie h;
        h.setTitulo(movie_title);
        h.setMovInfo("color",color);
        h.setMovInfo("director_name",director_name);
        h.setMovInfo("aspect_ratio",aspect_ratio);
        h.setMovInfo("imdb_score",imdb_score);
        h.setMovInfo("title_year",title_year);
        h.setMovInfo("budget",budget);
        h.setMovInfo("content_rating",content_rating);
        h.setMovInfo("country",country);
        h.setMovInfo("movie_imdb_link",movie_imdb_link);
        h.setMovInfo("plot_keywords",plot_keywords);
        h.setMovInfo("genres",genres);
        h.setMovInfo("gross",gross);
        h.setMovInfo("actor_1_name",actor_1_name);
        h.setMovInfo("actor_2_name",actor_2_name);
        h.setMovInfo("actor_3_name",actor_3_name);
        h.setMovInfo("duration",duration);

        //bringIMG(movie_imdb_link,movie_title);
        l1.insertAtEnd(h);
        //std::cout<< color<< "  "+director_name<< "  "+movie_title<<std::endl;
        i++;
    }
    this->lActual=&l1;
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
    std::cout << "descargando imagen" << std::endl;
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


