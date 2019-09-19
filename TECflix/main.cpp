#include "guiIncludes.h"
#include "objects/movieManager.h"
#include "estructuras/LinkedList.h"

movieManager manager;

Fl_Text_Buffer *buff;
Fl_Text_Display *disp;
Fl_Window *win, *mwin;
LinkedList<Fl_Box*> lbx= LinkedList<Fl_Box*>();
Fl_Color c = fl_rgb_color(4,44,98);
Fl_Button *nxt;



void button_cb( Fl_Widget*, void* );
void box_cb( Fl_Widget* , void*);
void createBoxes(){

    int x=10,y=10;
    for(int i=0;i<9;i++){
        std::string numero =std::to_string(i);

        auto *box = new Fl_Box(x, y, 158, 300, "1");
        box->box(FL_UP_BOX);
        box->hide();

        lbx.insertAtEnd(box);
        if(i==5){
            y=310;
            x=10;
        }
        else{x+=158;}

    }


};
void make_window(){
    win = new Fl_Window(1366, 768,"TECFlix");
    win->begin();

    win->color(c);
    Fl_Button* but = new Fl_Button( 700, 540, 100, 40, "Comenzar" );
    but -> callback( ( Fl_Callback* ) button_cb );
    nxt=new Fl_Button( 700, 540, 100, 40, "->" );
    nxt->hide();
    createBoxes();

    win->resizable(*disp);
    win->show();





};

void newWind(int pos){
    mwin = new Fl_Window(800, 600);
    mwin->begin();
    mwin->color(c);
    buff = new Fl_Text_Buffer();
    disp = new Fl_Text_Display(10, 10, 780, 550);
    disp->buffer(buff);
    Movie mact=manager.getLActual()->getElement(pos)->getData();
    mwin->label(mact.getTitulo().c_str());
    std::map<std::string, std::string> mapapeli= mact.getMovInfo();
    std::map<std::string, std::string>::iterator itr;
    std::string infoVent="";
    for (itr = mapapeli.begin(); itr != mapapeli.end(); ++itr) {
        infoVent.append(itr->first+": "+itr->second+"\n"+"\n");

    }


    buff->text(infoVent.c_str());
    mwin->show();
};


void button_cb( Fl_Widget* obj , void* data ){

    manager.beginPages();

    //manager.nextPage();
    nxt->show();

    win->redraw();
    for(int i=0;i<9;i++){
        lbx.getElement(i)->getData()->show();
    }

    //aqui es para obtener la informacion de la pelicula


    obj->hide();
    };


void box_cb( Fl_Widget* obj , void* data){

    int* pos=(int*) data;
    newWind(*pos);
}


int main(int argc, char **argv) {

    make_window();



    return Fl::run();

}