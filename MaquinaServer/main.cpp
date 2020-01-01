
#include "Functions.h"


int main()
{
    init();
    sf::Socket::Status status = dispatcher.listen(50000);
    std::thread conThreads(&getNewConnections); // Esto se encarga de recibir todos los nuevos sockets
    conThreads.detach();

    while(gameRunning)
    {
        std::cout << "Hey, inserta E para cerrar: \n";
        char exitChar;
        std::cin >> exitChar;
        if(exitChar == 'E' || exitChar == 'e')
        {
            gameRunning = false;
        }
    }
    std::vector<sf::TcpSocket*>::iterator it;
    for (it = sockets.begin(); it != sockets.end(); ++it){
        (*it)->disconnect();
    }
    dispatcher.close();
    if(res != nullptr) //  Asegurarse porque, si no hemos hecho ninguna query esto petará
        res->close();
    delete(res);
    stmt->close();
    delete(stmt);
    con->close();
    delete(con);
    return 0;
}




