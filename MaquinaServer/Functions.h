#include "ConnectivityFunctions.h"



void verifyUser(sf::TcpSocket* client, std::string userName, std::string password)
{
    if(sockets[client] != -1)
    {
        sendMessage(client, "Can't start two sessions");
        return;
    }
    std::string tmpString = "SELECT count(*) FROM Cuentas WHERE NombreUser = '" + userName + "' and PasswordUser = '" + password + "'" ;
    /// Zona limpia 2
    try
    {
        res = stmt->executeQuery(tmpString.c_str());

        if(res->next())
        {
            int exists = res->getInt(1);
            if(exists == 1)
            {
                tmpString =  "SELECT ID_User from Cuentas WHERE NombreUser = '" + userName + "'";
                res = stmt->executeQuery(tmpString.c_str());
                if(res->next())
                {
                    sockets[client] = res->getInt("ID_User");
                    sendMessage(client, "Correct :)\n");
                }
            }
            else if(exists == 0)
            {
                sendMessage(client, "User account doesn't exist:(\n");
            }
            else
            {
                sendMessage(client, "There's more than one user with this one?\n");
            }
        }
    }
    catch(sql::SQLException &e)
    {
        switch(e.getErrorCode())
        {
        case 1064:// Fallo de mensaje en la query
            sendMessage(client, "Error please do NOT send strange characters.\n");
            break;
        default:
            std::cout << e.getErrorCode() << std::endl;
            break;
        }
    }
}
void spinRoulette(sf::TcpSocket* client)
{ // TODO

    std::string tmpDML = "SELECT LastRoulette from Cuentas WHERE ID_User = '" + std::to_string(sockets[client])+ "'";
    try
    {
        res = stmt->executeQuery(tmpDML.c_str());
        while(res->next())
            std::cout << res->getString("LastRoulette") << std::endl;

    }
    catch(sql::SQLException &e)
    {
        switch(e.getErrorCode())
        {
        case 1064:// Fallo de mensaje en la query
            sendMessage(client, "Error: Query name incorrect.\n");
            return;
            break;
        default:
            std::cout << "Error: " << e.getErrorCode() << std::endl;
            return;
            break;
        }
    }
}
void getGems(sf::TcpSocket* client)
{
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
    if(sockets[client] == -1)
    {
        sendMessage(client, "Please enter session before trying to access\n");
        return;
    }


        int tmp;
        int counter = 0;
        std::map<sf::TcpSocket*, int>::iterator it;

        for (it = sockets.begin(); it != sockets.end(); ++it)
        {
            counter++;
            std::string tmpStr = "Player: " + std::to_string(counter) + " --> " + getUserName(it->first);
            sendMessage(client, tmpStr);

        }

}


void updateEnemies(sf::TcpSocket* client)
{
    sendMessage(client, "Updating enemies...");
}


void collect(sf::TcpSocket* client, int gemID)
{
    if(sockets[client] == -1){
        sendMessage(client, "Please start session before doing anything else");
        return;
    }
    std::cout << "Query de Busqueda\n";
    std::string tmpDML = "SELECT Cantidad from GemasObtenidas WHERE FK_User = '" + std::to_string(sockets[client]) + "' and FK_Gema = '" + std::to_string(gemID) + "'";
    try
    {
        res = stmt->executeQuery(tmpDML.c_str());
        if(res->next()){
            int currentQuantity = res->getInt("Cantidad");
            std::string tmpSQL = "UPDATE GemasObtenidas SET Cantidad = '" + std::to_string(currentQuantity+1)
                + "' WHERE FK_User = '" + std::to_string(sockets[client]) + "' and FK_Gema = '" + std::to_string(gemID)  + "'";

            std::cout << "Query de Actualizacion\n";


            if(stmt->executeUpdate(tmpSQL.c_str()) == 0)
                std::cout << "Failed on update" << std::endl;
            }
        else{
            tmpDML = "SELECT count(*) FROM Gemas WHERE ID_Gema = '" + std::to_string(gemID) + "'";
            res = stmt->executeQuery(tmpDML.c_str());
            if(res->next()){
                if(res->getInt(1) == 1){
                    std::string tmpSQL = "INSERT INTO GemasObtenidas(FK_User, FK_Gema, Cantidad) VALUES('" + std::to_string(sockets[client]) + "', '" + std::to_string(gemID) + "', '1')";
                    std::cout << "Query de Insercion\n";
                    if(stmt->executeUpdate(tmpSQL.c_str()) == 0)
                       std::cout << "Failed on insert" << std::endl;
                }else if(res->getInt(1)== 0){
                    std::cout << "Inexistent gem id\n";
                    return;
                }
            }
        }
    }
    catch(sql::SQLException &e)
    {
        switch(e.getErrorCode())
        {
        case 1064:// Fallo de mensaje en la query
            sendMessage(client, "Error: Query name incorrect.\n");
            return;
            break;
        default:
            std::cout << "# ERR: " << e.what() << " (MySQL error code: " << e.getErrorCode()<< ", SQLState: " << e.getSQLState() << " )" << std::endl;
            return;
            break;
        }
    }
}






