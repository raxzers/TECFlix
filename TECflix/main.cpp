#include <iostream>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Button.H>
#include "objects/movieManager.h"
#include <curl/curl.h>

movieManager manager;
Fl_Box *box;
Fl_Text_Buffer *buff;
Fl_Text_Display *disp;
Fl_Window *win;
void button_cb( Fl_Widget*, void* );
void make_window()

{
    win = new Fl_Window(800, 600,"TECFlix");
    win->begin();
    Fl_Color c = fl_rgb_color(0,0,12);
    win->color(c);
    Fl_Button* but = new Fl_Button( 700, 540, 100, 40, "Comenzar" );
    but -> callback( ( Fl_Callback* ) button_cb );
/*
    box = new Fl_Box(10, 10, 780, 580);

    box->box(FL_UP_BOX);
    box->labelfont(FL_HELVETICA_BOLD_ITALIC);
    box->labelsize(36);
    box->labeltype(_FL_SHADOW_LABEL);*/
    buff = new Fl_Text_Buffer();
    disp = new Fl_Text_Display(20, 20, 200-40, 150-40, "Display");
    disp->buffer(buff);
    disp->hide();
    win->resizable(*disp);
    win->show();



    win->show();

};
void button_cb( Fl_Widget* obj , void* ){

    manager.beginPages();

    disp->show();




    //aqui es para obtener la informacion de la pelicula
    std::map<std::string, std::string> mpeli= manager.getLActual()->getElement(0)->getData().getMovInfo();
    std::map<std::string, std::string>::iterator itr;
    std::string infoVent="";
    for (itr = mpeli.begin(); itr != mpeli.end(); ++itr) {
        infoVent.append(itr->first+": "+itr->second+"\n");

    }

    buff->text(infoVent.c_str());

    obj->hide();
    }

int main(int argc, char **argv) {

    make_window();



    return Fl::run();

}