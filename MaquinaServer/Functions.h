#include "ConnectivityFunctions.h"



void verifyUser(sf::TcpSocket* client, std::string userName, std::string password)
{
    sendMessage(client, "\nVerifying account...\n");
    std::string tmpString = "SELECT count(*) FROM Cuentas WHERE NombreUser = '" + userName + "' and PasswordUser = '" + password + "'" ;
    /// Zona limpia 2
    try
    {
        res = stmt->executeQuery(tmpString.c_str());
        /// Core dumped

        if(res->next())
        {
            int existe = res->getInt(1);
            if(existe == 1)
            {
                sendMessage(client, "\nUser account exists!\n:)\n");
            }
            else if(existe == 0)
            {
                sendMessage(client, "\nUser account doesn't exist\n:(\n");
            }
            else
            {
                sendMessage(client, "There's more than one user with this one?\n");
            }
        }
    }
    catch(sql::SQLException &e)
    {
        switch(e.getErrorCode()){
        case 1064:// Fallo de query
            break;
    default:
        std::cout << e.getErrorCode() << std::endl;
        break;
        }
    }
}
void spinRoulette(sf::TcpSocket* client)
{
    sendMessage(client,"Spinning Roulette...");
}
void getGems(sf::TcpSocket* client)
{
    sendMessage(client, "Getting available gems...");
}
void selectMap(sf::TcpSocket* client)
{
    sendMessage(client, "Selecting map...");

}
void moveCharacter(sf::TcpSocket* client)
{
    sendMessage(client, "Moving Character...");
}
void battleAction(sf::TcpSocket* client)
{
    sendMessage(client, "Using battle command...");
}
void getPlayers(sf::TcpSocket* client)
{
    sendMessage(client, "Getting available players...");
}

void updateEnemies(sf::TcpSocket* client)
{
    sendMessage(client, "Updating enemies...");
}






