#include "guiIncludes.h"
#include "objects/movieManager.h"
#include "estructuras/LinkedList.h"

movieManager manager;

Fl_Text_Buffer *buff;
Fl_Text_Display *disp;
Fl_Window *win, *mwin;
Fl_Color c = fl_rgb_color(4,44,98);
Fl_Button *nxt, *bck;
Fl_Group* Pl_group ;
Fl_Box *logo;
/**
 * @brief metodo que inicializa despeus del llamado del boton para
 * @param obj objeto de fltk para el callback
 * @param data puntero que permite pasar parametro
 * */
void begin_cb(Fl_Widget *obj, void *data);
/**
 * @brief metodo que inicializa despeus del llamado del boton para aceder la pagina siguiente
 * @param obj objeto de fltk para el callback
 * @param data puntero que permite pasar parametro
 * */
void nxt_cb( Fl_Widget* , void*);
/**
 * @brief metodo que inicializa despeus del llamado del boton para aceder la pagina anterior
 * @param obj objeto de fltk para el callback
 * @param data puntero que permite pasar parametro
 * */
void bck_cb( Fl_Widget* , void*);
/**
 * @brief metodo que inicializa despeus del llamado del boton para aceder la info de la pelicula
 * @param obj objeto de fltk para el callback
 * @param data puntero que permite pasar parametro
 * */
void info_cb( Fl_Widget* obj , void* data);
/**
 * @brief metodo que inicializa despeus del llamado del boton para aceder el trailer
 * @param obj objeto de fltk para el callback
 * @param data puntero que permite pasar parametro
 * */
void trailer_cb( Fl_Widget* obj , void* data);
/**
 * @brief metodo para cargar la imagen en la caja de la ventana principal
 * **/
void img2Box();
/**
 * @brief  metodo para cear las cajas en la ventana principal
 * **/
void createBoxes(){
    Pl_group->box(FL_NO_BOX);
    {auto *box = new Fl_Button(10, 10, 158, 300);
        box->box(FL_UP_FRAME);

    }
    {auto *box1 = new Fl_Button(168, 10, 158, 300);
        box1->box(FL_UP_BOX);

        }
    {auto *box = new Fl_Button( 326, 10, 158, 300);
        box->box(FL_UP_BOX);

        }
    {auto *box = new Fl_Button( 484, 10, 158, 300);
        box->box(FL_UP_BOX);

        }
    {auto *box = new Fl_Button(642, 10, 158, 300);
        box->box(FL_UP_BOX);

       }
    {auto *box = new Fl_Button(10, 310, 158, 300);
        box->box(FL_UP_BOX);

       }
    {auto *box = new Fl_Button(168, 310, 158, 300);
        box->box(FL_UP_BOX);

        }
    {auto *box = new Fl_Button(326, 310, 158, 300);
        box->box(FL_UP_BOX);

       }
    {auto *box = new Fl_Button(484, 310, 158, 300);
        box->box(FL_UP_BOX);


        }
        Pl_group->end();
    Pl_group->hide();
    char *pos;
    Pl_group->child(0)->callback(info_cb,pos="0");
    Pl_group->child(1)->callback(info_cb,pos="1");
    Pl_group->child(2)->callback(info_cb,pos="2");
    Pl_group->child(3)->callback(info_cb,pos="3");
    Pl_group->child(4)->callback(info_cb,pos="4");
    Pl_group->child(5)->callback(info_cb,pos="5");
    Pl_group->child(6)->callback(info_cb,pos="6");
    Pl_group->child(7)->callback(info_cb,pos="7");
    Pl_group->child(8)->callback(info_cb,pos="8");


};
/**
 * @brief metodo para cear la ventana principal
 * **/
void Main_window(){
    win = new Fl_Window(1266, 700,"TECFlix");
    win->begin();

    win->color(c);
    logo= new Fl_Box(350, 150, 600, 315);
    Fl_PNG_Image *img= new Fl_PNG_Image("../tecflix.png");
    logo->image(img);
    Fl_Button* but = new Fl_Button( 583, 400, 100, 40, "Comenzar" );
    but->callback((Fl_Callback *) begin_cb);
    nxt=new Fl_Button( 750, 620, 100, 40, "@->" );
    bck =new Fl_Button( 650, 620, 100, 40, "@<-" );
    bck->hide();
    nxt->hide();
    Pl_group=new Fl_Group(100, 10, 800, 600);
    createBoxes();
    nxt -> callback( ( Fl_Callback* ) nxt_cb );
    bck->callback(( Fl_Callback* )bck_cb);
    std::cout<< Fl::event_dy() <<std::endl;
    win->show();





};
/**
 * @brief metodo para cear la ventana secundaria  con la informacion de la pelicula
 * **/
void movieInfWind(int pos){
    mwin = new Fl_Window(800, 600);
    mwin->begin();
    mwin->color(c);
    buff = new Fl_Text_Buffer();
    disp = new Fl_Text_Display(10, 10, 780, 500);
    disp->buffer(buff);
    Movie mact=manager.getLActual()->getElement(pos)->getData();
    mwin->label(mact.getTitulo().c_str());
    std::map<std::string, std::string> mapapeli= mact.getMovInfo();
    std::map<std::string, std::string>::iterator itr;
    std::string infoVent="";
    for (itr = mapapeli.begin(); itr != mapapeli.end(); ++itr) {
        infoVent.append(itr->first+": "+itr->second+"\n"+"\n");

    }
    Fl_Button *button_Trailer = new Fl_Button(700,550,80,40,"Trailer");
      char * url = strdup(mact.getTrailer().c_str()) ;
    button_Trailer->callback(trailer_cb,url);
    buff->text(infoVent.c_str());
    mwin->show();
};


void begin_cb(Fl_Widget* obj , void* data ){

    manager.beginPages();
    logo->hide();

    nxt->show();




    if(manager.getPage()==1){
        bck->hide();
    }else{bck->show();}


    Pl_group->show();
    img2Box();
    win->redraw();
    obj->hide();
    };


void nxt_cb( Fl_Widget* obj , void* data){
    manager.nextPage();

    if(manager.getPage()==1){
        bck->hide();
    }else{bck->show();}

    bck->callback(( Fl_Callback* )bck_cb);
    img2Box();
    win->redraw();
}
void bck_cb( Fl_Widget* obj , void* data){
    manager.backPage();
    if(manager.getPage()==1){
        bck->hide();
    }else{bck->show();}

    img2Box();
    win->redraw();
}
void info_cb( Fl_Widget* obj , void* data){
    char *num= (char*)data;
    movieInfWind(atoi(num));
}
void trailer_cb( Fl_Widget* obj , void* data){
    char *url=(char*) data;
    system(url);
}

void img2Box(){
    for(int i=0;i<9;i++){
        std::string imgAdress="../images/"+manager.getLActual()->getElement(i)->getData().getTitulo()+".jpg";
        struct stat buffer;
        Fl_Image *imgScale;
        if(stat (imgAdress.c_str(), &buffer) != 0){
            imgAdress="../images/"+manager.getLActual()->getElement(i)->getData().getTitulo()+".png";
            Fl_PNG_Image *img= new Fl_PNG_Image(imgAdress.c_str());
            imgScale= img->copy(Pl_group->child(i)->w(),Pl_group->child(i)->h());
            delete img;
            Pl_group->child(i)->image(imgScale);
        }
        else{
            Fl_JPEG_Image *img= new Fl_JPEG_Image(imgAdress.c_str());
            imgScale= img->copy(Pl_group->child(i)->w(),Pl_group->child(i)->h());
            delete img;
            Pl_group->child(i)->image(imgScale);
        }
        Pl_group->child(i)->redraw();

    }

}

int handle(int event){
    int scro=Fl::event_dy();
    switch (event){
        case  FL_MOUSEWHEEL:
            if (Fl::event_dy()<0){manager.backPage();}
            else{manager.nextPage();}
            break;
    }
}
int main(int argc, char **argv) {

    Main_window();
    return Fl::run();

}