#include <iostream>
#include <iostream>
#include <unistd.h>
#include <wait.h>
#include <vector>
#include "Functions.h"




int main()
{
    sf::Socket::Status status = dispatcher.listen(50000);
    std::thread t(&getNewConnections);
    t.detach();

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




