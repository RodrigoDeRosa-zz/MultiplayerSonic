#ifndef SDLHANDLER_HPP
#define SDLHANDLER_HPP

class SDLHandler{
    private:
        SDLHandler();//Constructor
        ~SDLHandler();//Destructor
    public:
        /*Metodo de obtencion de la instancia del singleton*/
        static SDLHandler& getInstance();
        /*Incializa SDL y SDLImage*/
        bool init();
        /*Cierra SDL y SDLImage*/
        void close();
};

#endif /*SDLHANDLER_HPP*/
