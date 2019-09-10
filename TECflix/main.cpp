#include <iostream>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include "libray/csv.h"

void button_cb( Fl_Widget*, void* );
void make_window()

{
    Fl_Window *win = new Fl_Window(800, 600,"TECFlix");
    win->begin();
    Fl_Color c = fl_rgb_color(0,0,12);
    win->color(c);
    Fl_Button* but = new Fl_Button( 100, 100, 50, 40, "Comenzar" );
    but -> callback( ( Fl_Callback* ) button_cb );

    win->show();

};
void button_cb( Fl_Widget* obj , void* ){

    io::CSVReader<3> in("../csv/movie_metadata.csv");
    in.read_header(io::ignore_extra_column, "color", "director_name", "movie_title");
    std::string color,director_name, movie_title;
    int i=0;
    while(in.read_row(color, director_name, movie_title )&& i<10){
        std::cout<< color<< "  "+director_name<< "  "+movie_title<<std::endl;
        i++;
    }
    obj->hide();
    }

int main(int argc, char **argv) {
    make_window();



    return Fl::run();
    std::cout << "Hello, World!" << std::endl;
    return 0;
}