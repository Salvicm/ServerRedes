#include "ConnectivityFunctions.h"



void verifyUser(sf::TcpSocket* client, std::string userName, std::string password)
{
    sendMessage(client, "\nVerifying account...\n");
    std::string tmpString = "SELECT count(*) FROM Cuentas WHERE NombreUser = '" + userName + "' and PasswordUser = '" + password + "'" ;
    /// Zona limpia 2
    try
    {
        res = stmt->executeQuery(tmpString.c_str());

        if(res->next())
        {
            int existe = res->getInt(1);
            if(existe == 1)
            {
                tmpString =  "SELECT ID_User from Cuentas WHERE NombreUser = '" + userName + "'";
                res = stmt->executeQuery(tmpString.c_str());
                if(res->next()){
                    sockets[client] = res->getInt("ID_User");
                    sendMessage(client, "\nUser account exists!\n:)\n");
                }


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
        case 1064:// Fallo de mensaje en la query
            sendMessage(client, "MessageError please do NOT send strange characters.\n");
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
    std::cout << sockets[client] << std::endl;
    if(sockets[client] == -1)
    {
        sendMessage(client, "Please enter session before trying to access\n");
        return;
    }

    sendMessage(client, "Getting available gems...");
    std::string tmpString =  "SELECT FK_Gema, Cantidad from GemasObtenidas WHERE FK_User = '" + std::to_string(sockets[client]) + "'";
    /// Zona limpia 2
    try
    {
        res = stmt->executeQuery(tmpString.c_str());
        /// Core dumped

        while(res->next())
        {
            std::string tmpStr = "GEM_" +std::to_string(res->getInt("FK_Gema")) + "_" + std::to_string(res->getInt("Cantidad"));
            sendMessage(client, tmpStr);
        }
    }
    catch(sql::SQLException &e)
    {
        switch(e.getErrorCode())
        {
        case 1064:// Fallo de mensaje en la query
            sendMessage(client, "MessageError please do NOT send strange characters.\n");
            break;
        default:
            std::cout << e.getErrorCode() << std::endl;
            break;
        }
    }
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






