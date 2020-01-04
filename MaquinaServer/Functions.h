#include "ConnectivityFunctions.h"
#include <ctime>


void verifyUser(sf::TcpSocket* client, std::string userName, std::string password)
{
    if(sockets[client] != -1)
    {
        sendMessage(client, "ALREADYCON");
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
                    getGems(client);
                    if(UpdateRoulette(client))
                    {
                        std::cout << "Roulette\n";
                        spinRoulette(client);
                        sendMessage(client, "CONNECTED"); // Cambiar esto tras el merge
                    }
                    else
                    {
                        sendMessage(client, "CONNECTED");
                    }
                }
            }
            else if(exists == 0)
            {
                sendMessage(client, "INEXISTENT");
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
{
    if(sockets[client] == -1)
    {
        sendMessage(client, "Please enter session before trying to access\n");
        return;
    }
    std::string tmpDML = "UPDATE Cuentas SET LastRoulette = current_timestamp WHERE ID_User = '" + std::to_string(sockets[client]) + "'" ;
    try
    {
        int i =(rand() % 3) + 1;
        if(stmt->executeUpdate(tmpDML.c_str()) != 0)
        {
            collect(client, i);

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
            std::cout << "# ERR: " << e.what();
            std::cout << " (MySQL error code: " << e.getErrorCode();
            std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
            return;
            break;
        }
    }
}
bool UpdateRoulette(sf::TcpSocket* client)
{

    time_t lastRoulette;
    time_t currentTime;
    std::string tmpDML = "SELECT LastRoulette from Cuentas WHERE ID_User = '" + std::to_string(sockets[client])+ "'";
    std::string tmp;
    try
    {
        res = stmt->executeQuery(tmpDML.c_str());
        while(res->next())
            tmp = res->getString("LastRoulette");

        tm t;
        strptime(tmp.c_str(), "%F %T", &t);
        lastRoulette = mktime(&t);

        time(&currentTime);

        std::cout << currentTime << std::endl << lastRoulette << std::endl;
        if(difftime(currentTime, lastRoulette) >= maxTimeStamp)
        {
            return true;
        }
        else return false;

    }
    catch(sql::SQLException &e)
    {
        switch(e.getErrorCode())
        {
        case 1064:// Fallo de mensaje en la query
            sendMessage(client, "Error: Query name incorrect.\n");
            return false;
            break;
        default:
            std::cout << "# ERR: " << e.what();
            std::cout << " (MySQL error code: " << e.getErrorCode();
            std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
            return false;
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

    std::string tmpString =  "SELECT FK_Gema, Cantidad from GemasObtenidas WHERE FK_User = '" + std::to_string(sockets[client]) + "'";
    /// Zona limpia 2
    try
    {
        res = stmt->executeQuery(tmpString.c_str());
        sql::ResultSet* tmpRes;

        while(res->next())
        {
            tmpString = "SELECT Valor, Tipo FROM Gemas WHERE ID_Gema = '" + std::to_string(res->getInt("FK_Gema")) + "'";
            tmpRes = stmt->executeQuery(tmpString.c_str());
            if(tmpRes->next())
            {
                std::string tmpStr = "GEM_" + tmpRes->getString("Tipo") + "_" + std::to_string(res->getInt("Cantidad")) + "_" + std::to_string(tmpRes->getInt("Valor"));
                sendMessage(client, tmpStr);
            }
            else
            {
                std::cout << "Error: Gem Query failing\n";
                return;
            }
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
            std::cout << "# ERR: " << e.what();
            std::cout << " (MySQL error code: " << e.getErrorCode();
            std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
            break;
        }
    }
}

void getMaps(sf::TcpSocket* client)
{
    if(sockets[client] == -1)
    {
        sendMessage(client, "Please enter session before trying to access\n");
        return;
    }
    try
    {
        sendMessage(client, "This are the available maps: ");
        std::string tmpSQL = "SELECT * FROM Mapas";
        res = stmt->executeQuery(tmpSQL.c_str());
        while(res->next())
        {
            sendMessage(client, res->getString("NombreMapa"));
        }
    }
    catch(sql::SQLException &e)
    {
        std::cout << "# ERR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    }
}

void selectMap(sf::TcpSocket* client, int mapID)
{
    if(sockets[client] == -1)
    {
        sendMessage(client, "Please enter session before trying to access\n");
        return;
    }
    try
    {
        sendMessage(client, "Selecting map: " + std::to_string(mapID));
        std::string pathString;
        std::string tmpSQL = "SELECT XML FROM Mapas WHERE ID_Mapa = '" + std::to_string(mapID) + "'";
        res = stmt->executeQuery(tmpSQL.c_str());
        while(res->next())
        {
            pathString = res->getString("XML");
            sendMessage(client, pathString);
        }
    }
    catch(sql::SQLException &e)
    {
        std::cout << "# ERR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    }
}

void moveCharacter(sf::TcpSocket* client, directions _direction, vector2 playerPos)
{
    if(sockets[client] == -1)
    {
        sendMessage(client, "Please enter session before trying to move\n");
        return;
    }
    switch(_direction)
    {
    case directions::UP:
        playerPos.y--;
        break;
    case directions::DOWN:
        playerPos.y++;
        break;
    case directions::LEFT:
        playerPos.x--;
        break;
    case directions::RIGHT:
        playerPos.x++;
        break;
    case directions::NONE:
    default:
        break;
    }
    std::string newPos = "PLAYER_" + std::to_string(playerPos.x) + "_" + std::to_string(playerPos.y);
    sendMessage(client, newPos);
}

void battleAction(sf::TcpSocket* client, int pAt, int pDef)
{
        bool enemyAlive = true;
        int atEn = rand()% 15+1;
        int defEn = rand()% 15+1;
        int hpEn = 30;
        int gema = rand()% 3+1;
        int aux = 0;
        int auxDef = defEn;
        int auxHpEn = hpEn;
        int i = 0; ///turnos
    while(enemyAlive){
        i++;
        ///Ataque player
        defEn -= pAt;
        if(defEn < 0){
            aux = defEn;
            defEn= 0;
            hpEn += aux;
        }
        ///muerte enemigo
        if(hpEn <= 0){
            enemyAlive = false;
            sendMessage(client, "BATTLE_"+std::to_string(atEn)+"_"+std::to_string(auxDef)+"_"+std::to_string(auxHpEn)+"_"+std::to_string(i));


        }
        ///ataque enemy
        if(pDef > 0){
            pDef -= atEn;
        }
    }

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
        std::string tmpStr = "USER_" + std::to_string(counter) + "_" + getUserName(it->first);
        sendMessage(client, tmpStr);
    }

}


void updateEnemies(sf::TcpSocket* client)
{
}

void collect(sf::TcpSocket* client, int gemID)
{
    if(sockets[client] == -1)
    {
        sendMessage(client, "Please start session before doing anything else");
        return;
    }
    std::string tmpDML = "SELECT Cantidad from GemasObtenidas WHERE FK_User = '" + std::to_string(sockets[client]) + "' and FK_Gema = '" + std::to_string(gemID) + "'";
    try
    {
        res = stmt->executeQuery(tmpDML.c_str());
        if(res->next())
        {
            int currentQuantity = res->getInt("Cantidad");
            std::string tmpSQL = "UPDATE GemasObtenidas SET Cantidad = '" + std::to_string(currentQuantity+1)
                                 + "' WHERE FK_User = '" + std::to_string(sockets[client]) + "' and FK_Gema = '" + std::to_string(gemID)  + "'";

            if(stmt->executeUpdate(tmpSQL.c_str()) == 0)
            {
                std::cout << "Failed on update" << std::endl;
            }
            else
            {
                std::string tmpStr = "SELECT Tipo FROM Gemas WHERE ID_Gema = '" + std::to_string(gemID) + "'";
                res = stmt->executeQuery(tmpStr.c_str());
                if(res->next()){
                    std::string toSend = "Has obtenido una gema del tipo: " + res->getString("Tipo");
                    sendMessage(client, toSend);
                }
            }
        }
        else
        {
            tmpDML = "SELECT count(*) FROM Gemas WHERE ID_Gema = '" + std::to_string(gemID) + "'";
            res = stmt->executeQuery(tmpDML.c_str());
            if(res->next())
            {
                if(res->getInt(1) == 1)
                {
                    std::string tmpSQL = "INSERT INTO GemasObtenidas(FK_User, FK_Gema, Cantidad) VALUES('" + std::to_string(sockets[client]) + "', '" + std::to_string(gemID) + "', '1')";
                    std::cout << "Query de Insercion\n";
                    if(stmt->executeUpdate(tmpSQL.c_str()) == 0)
                        std::cout << "Failed on insert" << std::endl;
                }
                else if(res->getInt(1)== 0)
                {
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






