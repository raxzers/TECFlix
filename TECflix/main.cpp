#include "guiIncludes.h"
#include "objects/movieManager.h"
#include "estructuras/LinkedList.h"

movieManager manager;
Fl_Box *box2,*box3,*box4,*box5,*box6,*box7,*box8,*box9;
Fl_Text_Buffer *buff;
Fl_Text_Display *disp;
Fl_Window *win, *mwin;
LinkedList<Fl_Box*> lbx= LinkedList<Fl_Box*>();
Fl_Color c = fl_rgb_color(1,1,12);
void button_cb( Fl_Widget*, void* );
void createBoxes(){

    for(int i=0;i<9;i++){
        auto *box = new Fl_Box(10*i, 10, 158, 300, "peli");
        box->box(FL_UP_BOX);
        box->show();
        lbx.insertAtEnd(box);
    }
    win->redraw();

};
void make_window(){
    win = new Fl_Window(1366, 768,"TECFlix");
    win->begin();

    win->color(c);
    Fl_Button* but = new Fl_Button( 700, 540, 100, 40, "Comenzar" );
    but -> callback( ( Fl_Callback* ) button_cb );

    createBoxes();

    win->resizable(*disp);
    win->show();





};

void newWind(int pos){
    mwin = new Fl_Window(800, 600);
    mwin->begin();
    mwin->color(c);
    buff = new Fl_Text_Buffer();
    disp = new Fl_Text_Display(10, 10, 780, 550, "Display");
    disp->buffer(buff);
    Movie mact=manager.getLActual()->getElement(pos)->getData();
    mwin->label(mact.getTitulo().c_str());
    std::map<std::string, std::string> mapapeli= mact.getMovInfo();
    std::map<std::string, std::string>::iterator itr;
    std::string infoVent="";
    for (itr = mapapeli.begin(); itr != mapapeli.end(); ++itr) {
        infoVent.append(itr->first+": "+itr->second+"\n");

    }

    buff->text(infoVent.c_str());
    mwin->show();
};


void button_cb( Fl_Widget* obj , void* ){

    manager.beginPages();

    newWind(2);

    createBoxes();

    for(int i=0;i<9;i++){
        lbx.getElement(i)->getData()->show();
    }

    //aqui es para obtener la informacion de la pelicula


    obj->hide();
    };

int main(int argc, char **argv) {

    make_window();



    return Fl::run();

}