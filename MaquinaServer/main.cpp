#include <iostream>
#include <iostream>
#include <unistd.h>
#include <wait.h>
#include <vector>
#include "Functions.h"


int main()
{
    sf::Socket::Status status = dispatcher.listen(50001);
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
    return 0;
}




