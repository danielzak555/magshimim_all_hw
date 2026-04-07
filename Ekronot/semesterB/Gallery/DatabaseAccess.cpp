#include <io.h> // for _access
#include <algorithm>
#include <iomanip>
#include <string>
#include <iostream>
#include <sstream>

#include "sqlite3.h"
#include "ItemNotFoundException.h"
#include "MyException.h"
#include "DatabaseAccess.h"
#include "AlbumManager.h"

//tomer the galleryDB.sqlite is the database ??, i hope so

int albumCallback(void* data, int argc, char** argv, char** azColName) {
    // Cast the 'data' pointer back to a list of Albums
    std::list<Album>* albumsList = (std::list<Album>*)data;

    int userId = 0;
    std::string name = "";
    std::string creationDate = "";

    for (int i = 0; i < argc; i++) {
        std::string columnName = azColName[i];
        std::string value = argv[i] ? argv[i] : "NULL";

        if (columnName == "USER_ID") {
            userId = std::stoi(value);
        } else if (columnName == "NAME") {
            name = value;
        } else if (columnName == "CREATION_DATE") {
            creationDate = value;
        }
    }

    // Create the object and add it to the list
    Album album(userId, name, creationDate);
    albumsList->push_back(album);

    return 0;
}

int existsCallback(void* data, int argc, char** argv, char** azColName) {
    bool* exists = (bool*)data;
    *exists = true; 
    return 0;
}

int printUsersCallback(void* data, int argc, char** argv, char** azColName) {
    std::cout << "User ID: " << argv[0] << ", Name: " << argv[1] << std::endl;
    return 0;
}   

int getUserCallback(void* data, int argc, char** argv, char** azColName) {
    User* user = (User*)data;

    for (int i = 0; i < argc; i++) {
        std::string columnName = azColName[i];
        std::string value = argv[i] ? argv[i] : "NULL";

        if (columnName == "ID") {
            user->setId(std::stoi(value));
        } else if (columnName == "NAME") {
            user->setName(value);
        }
    }

    return 0;
}

int countCallback(void* data, int argc, char** argv, char** azColName) {
    int* count = (int*)data;
    if (argc > 0 && argv[0]) {
        *count = std::stoi(argv[0]);
    }
    return 0;
}

int getPictureCallback(void* data, int argc, char** argv, char** azColName) {
    Picture* picture = (Picture*)data;

    for (int i = 0; i < argc; i++) {
        std::string columnName = azColName[i];
        std::string value = argv[i] ? argv[i] : "NULL";

        if (columnName == "ID") {
            picture->setId(std::stoi(value));
        } else if (columnName == "NAME") {
            picture->setName(value);
        } else if (columnName == "LOCATION") {
            picture->setPath(value);
        } else if (columnName == "CREATION_DATE") {
            picture->setCreationDate(value);
        }
    }

    return 0;
}

int pictureListCallback(void* data, int argc, char** argv, char** azColName) {
    std::list<Picture>* picturesList = (std::list<Picture>*)data;

    int id = 0;
    std::string name = "";
    std::string location = "";
    std::string creationDate = "";

    for (int i = 0; i < argc; i++) {
        std::string columnName = azColName[i];
        std::string value = argv[i] ? argv[i] : "NULL";

        if (columnName == "ID") {
            id = std::stoi(value);
        } else if (columnName == "NAME") {
            name = value;
        } else if (columnName == "LOCATION") {
            location = value;
        } else if (columnName == "CREATION_DATE") {
            creationDate = value;
        }
    }

    Picture picture(id, name, location, creationDate);
    picturesList->push_back(picture);

    return 0;
}

int userListCallback(void* data, int argc, char** argv, char** azColName) {
    std::list<User>* usersList = (std::list<User>*)data;

    int id = 0;
    std::string name = "";

    for (int i = 0; i < argc; i++) {
        std::string columnName = azColName[i];
        std::string value = argv[i] ? argv[i] : "NULL";

        if (columnName == "ID") {
            id = std::stoi(value);
        } else if (columnName == "NAME") {
            name = value;
        }
    }

    User user(id, name);
    usersList->push_back(user);

    return 0;
}

bool DatabaseAccess::open() {
    std::string dbFileName = "GalleryDB.sqlite";
    
    int file_exist = _access(dbFileName.c_str(), 0);
    
    // Open the connection. 
    int res = sqlite3_open(dbFileName.c_str(), &_db);
    
    if (res != SQLITE_OK) {
        std::string errMsg = (_db) ? sqlite3_errmsg(_db) : "Unknown opening error";
        _db = nullptr; 
        throw MyException("Failed to open database: " + errMsg);
    }
    
    if (file_exist != 0) {
        std::string sql = 
            "CREATE TABLE USERS (ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, NAME TEXT NOT NULL);"
            "CREATE TABLE ALBUMS (ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, NAME TEXT NOT NULL, CREATION_DATE TEXT NOT NULL, USER_ID INTEGER NOT NULL, FOREIGN KEY(USER_ID) REFERENCES USERS(ID));"
            "CREATE TABLE PICTURES (ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, NAME TEXT NOT NULL, LOCATION TEXT NOT NULL, CREATION_DATE TEXT NOT NULL, ALBUM_ID INTEGER NOT NULL, FOREIGN KEY(ALBUM_ID) REFERENCES ALBUMS(ID));"
            "CREATE TABLE TAGS (PICTURE_ID INTEGER NOT NULL, USER_ID INTEGER NOT NULL, PRIMARY KEY(PICTURE_ID, USER_ID), FOREIGN KEY(PICTURE_ID) REFERENCES PICTURES(ID), FOREIGN KEY(USER_ID) REFERENCES USERS(ID));";
        
        char* errMsg = nullptr;
        res = sqlite3_exec(_db, sql.c_str(), nullptr, nullptr, &errMsg);
        
        if (res != SQLITE_OK) {
            std::string error = errMsg ? errMsg : "Unknown initialization error";
            sqlite3_free(errMsg); // Free memory allocated by SQLite for the error message 
            throw MyException("Failed to initialize database: " + error);
        }
    }
    
    return true;
}

void DatabaseAccess::close() {
    if (_db) {
        sqlite3_close(_db);
        _db = nullptr;
    }
}

void DatabaseAccess::clear() {
    char* errMsg = nullptr;
    std::string sql = "DELETE FROM TAGS; DELETE FROM PICTURES; DELETE FROM ALBUMS; DELETE FROM USERS;";
    int res = sqlite3_exec(_db, sql.c_str(), nullptr, nullptr, &errMsg);
    
    if (res != SQLITE_OK) {
        std::string error = errMsg ? errMsg : "Unknown clearing error";
        sqlite3_free(errMsg); // Free memory allocated by SQLite for the error message 
        throw MyException("Failed to clear database: " + error);
    }
}

void DatabaseAccess::tagUserInPicture(const std::string& albumName, const std::string& pictureName, int userId)
{
    std::string sql = "INSERT INTO TAGS (PICTURE_ID, USER_ID) "
    "SELECT PICTURES.ID, " + std::to_string(userId) + " "
    "FROM PICTURES "
    "JOIN ALBUMS ON PICTURES.ALBUM_ID = ALBUMS.ID "
    "WHERE ALBUMS.NAME = '" + albumName + "' AND PICTURES.NAME = '" + pictureName + "'";
    char* errMsg = nullptr;
    int res = sqlite3_exec(_db, sql.c_str(), nullptr, nullptr, &errMsg);
    
    if (res != SQLITE_OK) {
        std::string error = errMsg ? errMsg : "Unknown error";
        sqlite3_free(errMsg);
        throw MyException("Failed to tag user in picture: " + error);
    }
}

void DatabaseAccess::untagUserInPicture(const std::string& albumName, const std::string& pictureName, int userId)
{
    std::string sql = "DELETE FROM TAGS "
    "WHERE USER_ID = " + std::to_string(userId) + " AND PICTURE_ID IN ("
    "SELECT PICTURES.ID "
    "FROM PICTURES "
    "JOIN ALBUMS ON PICTURES.ALBUM_ID = ALBUMS.ID "
    "WHERE ALBUMS.NAME = '" + albumName + "' AND PICTURES.NAME = '" + pictureName + "')";
    
    char* errMsg = nullptr;
    int res = sqlite3_exec(_db, sql.c_str(), nullptr, nullptr, &errMsg);
    
    if (res != SQLITE_OK) {
        std::string error = errMsg ? errMsg : "Unknown error";
        sqlite3_free(errMsg);
        throw MyException("Failed to untag user in picture: " + error);
    }
}

void DatabaseAccess::createUser(User& user)
{
    std::string sql = "INSERT INTO USERS (NAME) VALUES ('" + user.getName() + "');";
    char* errMsg = nullptr;
    int res = sqlite3_exec(_db, sql.c_str(), nullptr, nullptr, &errMsg);
    
    if (res != SQLITE_OK) {
        std::string error = errMsg ? errMsg : "Unknown error";
        sqlite3_free(errMsg);
        throw MyException("Failed to create user: " + error);
    }

    // now we need to set the right id
    std::string sqlGetId = "SELECT ID FROM USERS WHERE NAME = '" + user.getName() + "' ORDER BY ID DESC LIMIT 1;";
    res = sqlite3_exec(_db, sqlGetId.c_str(), getUserCallback, &user, &errMsg);
    if (res != SQLITE_OK) {
        std::string error = errMsg ? errMsg : "Unknown error";
        sqlite3_free(errMsg);
        throw MyException("Failed to retrieve new user ID: " + error);
    }

    user.setId(user.getId()); // Update the user object with the new ID
}

void DatabaseAccess::deleteUser(const User& user)
{
    std::string sql = "DELETE FROM USERS WHERE ID = " + std::to_string(user.getId()) + ";";
    char* errMsg = nullptr;
    int res = sqlite3_exec(_db, sql.c_str(), nullptr, nullptr, &errMsg);
    
    if (res != SQLITE_OK) {
        std::string error = errMsg ? errMsg : "Unknown error";
        sqlite3_free(errMsg);
        throw MyException("Failed to delete user: " + error);
    }
}

const std::list<Album> DatabaseAccess::getAlbums()
{
    std::list<Album> albums;
    std::string sql = "SELECT * FROM ALBUMS;";

    char* errMsg = nullptr;
    int res = sqlite3_exec(_db, sql.c_str(), albumCallback, &albums, &errMsg);
    
    if (res != SQLITE_OK) {
        std::string error = errMsg ? errMsg : "Unknown error";
        sqlite3_free(errMsg);
        throw MyException("Failed to get albums: " + error);
    }
    
    return albums;
}

const std::list<Album> DatabaseAccess::getAlbumsOfUser(const User& user)
{
    std::list<Album> albums;
    std::string sql = "SELECT * FROM ALBUMS WHERE USER_ID = " + std::to_string(user.getId()) + ";";

    char* errMsg = nullptr;
    int res = sqlite3_exec(_db, sql.c_str(), albumCallback, &albums, &errMsg);
    
    if (res != SQLITE_OK) {
        std::string error = errMsg ? errMsg : "Unknown error";
        sqlite3_free(errMsg);
        throw MyException("Failed to get albums of user: " + error);
    }
    
    return albums;
}

void DatabaseAccess::createAlbum(const Album& album)
{
    std::string sql = "INSERT INTO ALBUMS (NAME, CREATION_DATE, USER_ID) VALUES ('" + album.getName() + "', '" + album.getCreationDate() + "', " + std::to_string(album.getOwnerId()) + ");";
    char* errMsg = nullptr;
    int res = sqlite3_exec(_db, sql.c_str(), nullptr, nullptr, &errMsg);
    
    if (res != SQLITE_OK) {
        std::string error = errMsg ? errMsg : "Unknown error";
        sqlite3_free(errMsg);
        throw MyException("Failed to create album: " + error);
    }
}

void DatabaseAccess::deleteAlbum(const std::string& albumName, int userId)
{
    std::string sql = "DELETE FROM ALBUMS WHERE NAME = '" + albumName + "' AND USER_ID = " + std::to_string(userId) + ";";
    char* errMsg = nullptr;
    int res = sqlite3_exec(_db, sql.c_str(), nullptr, nullptr, &errMsg);
    
    if (res != SQLITE_OK) {
        std::string error = errMsg ? errMsg : "Unknown error";
        sqlite3_free(errMsg);
        throw MyException("Failed to delete album: " + error);
    }
}

bool DatabaseAccess::doesAlbumExists(const std::string& albumName, int userId)
{
    bool exists = false;
    std::string sql = "SELECT 1 FROM ALBUMS WHERE NAME = '" + albumName + "' AND USER_ID = " + std::to_string(userId) + " LIMIT 1;"; // tomer, i found out its faster with the select 1

    char* errMsg = nullptr;
    int res = sqlite3_exec(_db, sql.c_str(), existsCallback, &exists, &errMsg);
    
    if (res != SQLITE_OK) {
        std::string error = errMsg ? errMsg : "Unknown error";
        sqlite3_free(errMsg);
        throw MyException("Failed to check if album exists: " + error);
    }
    
    return exists;
}

Album DatabaseAccess::openAlbum(const std::string& albumName)
{
    std::list<Album> albums = getAlbums();
    Album* targetAlbum = nullptr;
    for (auto& album : albums) {
        if (album.getName() == albumName) {
            targetAlbum = &album;
            break;
        }
    }
    if (!targetAlbum) throw MyException("Album not found");

    std::list<Picture> albumPictures;
    std::string sqlPics = "SELECT * FROM PICTURES WHERE ALBUM_ID = (SELECT ID FROM ALBUMS WHERE NAME = '" + albumName + "');";
    sqlite3_exec(_db, sqlPics.c_str(), pictureListCallback, &albumPictures, nullptr);

    for (auto& pic : albumPictures) {
        std::list<User> taggedUsers;
        std::string sqlTags = "SELECT USERS.ID, USERS.NAME FROM USERS "
                              "JOIN TAGS ON USERS.ID = TAGS.USER_ID "
                              "WHERE TAGS.PICTURE_ID = " + std::to_string(pic.getId()) + ";";
        
        sqlite3_exec(_db, sqlTags.c_str(), userListCallback, &taggedUsers, nullptr);

        for (const auto& user : taggedUsers) {
            pic.tagUser(user);
        }

        targetAlbum->addPicture(pic);
    }

    return *targetAlbum;
}

void DatabaseAccess::closeAlbum(Album& album){
    //no action needed in sqlite
}

void DatabaseAccess::printAlbums()
{
    std::list<Album> albums = getAlbums();
    std::cout << "Albums list:" << std::endl;
    std::cout << "-----------------------" << std::endl;

    for (const auto& album : albums) {
        std::cout <<"   + [" << album.getName() <<"] - created on "<< album.getCreationDate() << " by user@" << album.getOwnerId() << std::endl; // thats is a nice design dont u think so tomer? :D
    }
}

void DatabaseAccess::addPictureToAlbumByName(const std::string& albumName, const Picture& picture){
    char* errMsg = nullptr;
    std::string  sql = "INSERT INTO PICTURES (NAME, LOCATION, CREATION_DATE, ALBUM_ID) VALUES ('" + picture.getName() + "', '" + picture.getPath() + "', '" + picture.getCreationDate() + "', (SELECT ID FROM ALBUMS WHERE NAME = '" + albumName + "'));";
    int res = sqlite3_exec(_db, sql.c_str(), nullptr, nullptr, &errMsg);

    if (res != SQLITE_OK) {
        std::string error = errMsg ? errMsg : "Unknown error";
        sqlite3_free(errMsg);
        throw MyException("Failed to add picture to album: " + error);
    }
}

void DatabaseAccess::removePictureFromAlbumByName(const std::string& albumName, const std::string& pictureName){
    char* errMsg = nullptr;
    std::string sql = "DELETE FROM PICTURES WHERE NAME = '" + pictureName + "' AND ALBUM_ID = (SELECT ID FROM ALBUMS WHERE NAME = '" + albumName + "');";
    int res = sqlite3_exec(_db, sql.c_str(), nullptr, nullptr, &errMsg);

    if (res != SQLITE_OK) {
        std::string error = errMsg ? errMsg : "Unknown error";
        sqlite3_free(errMsg);
        throw MyException("Failed to remove picture from album: " + error);
    }
}

void DatabaseAccess::printUsers()
{
    std::string sql = "SELECT * FROM USERS;";
    char* errMsg = nullptr;
    int res = sqlite3_exec(_db, sql.c_str(), printUsersCallback, nullptr, &errMsg);

    if (res != SQLITE_OK) {
        std::string error = errMsg ? errMsg : "Unknown error";
        sqlite3_free(errMsg);
        throw MyException("Failed to print users: " + error);
    }
}

User DatabaseAccess::getUser(int userId)
{
    User user = User(0, ""); // set to default because there is no normal default :()
    std::string sql = "SELECT * FROM USERS WHERE ID = " + std::to_string(userId) + ";";
    char* errMsg = nullptr;
    int res = sqlite3_exec(_db, sql.c_str(), getUserCallback, &user, &errMsg);

    if (res != SQLITE_OK) {
        std::string error = errMsg ? errMsg : "Unknown error";
        sqlite3_free(errMsg);
        throw MyException("Failed to get user: " + error);
    }

    return user;
}

bool DatabaseAccess::doesUserExists(int userId)
{
    bool exists = false;
    std::string sql = "SELECT 1 FROM USERS WHERE ID = " + std::to_string(userId) + " LIMIT 1;";

    char* errMsg = nullptr;
    int res = sqlite3_exec(_db, sql.c_str(), existsCallback, &exists, &errMsg);
    
    if (res != SQLITE_OK) {
        std::string error = errMsg ? errMsg : "Unknown error";
        sqlite3_free(errMsg);
        throw MyException("Failed to check if user exists: " + error);
    }
    
    return exists;
}

int DatabaseAccess::countAlbumsOwnedOfUser(const User& user)
{
    int count = 0;
    std::string sql = "SELECT COUNT(*) FROM ALBUMS WHERE USER_ID = " + std::to_string(user.getId()) + ";";

    char* errMsg = nullptr;
    int res = sqlite3_exec(_db, sql.c_str(), countCallback, &count, &errMsg);
    
    if (res != SQLITE_OK) {
        std::string error = errMsg ? errMsg : "Unknown error";
        sqlite3_free(errMsg);
        throw MyException("Failed to count albums owned by user: " + error);
    }

    return count;
}

int DatabaseAccess::countAlbumsTaggedOfUser(const User& user)
{
    int count = 0;
    std::string sql = "SELECT COUNT(DISTINCT ALBUMS.ID) FROM ALBUMS "
    "JOIN PICTURES ON ALBUMS.ID = PICTURES.ALBUM_ID "
    "JOIN TAGS ON PICTURES.ID = TAGS.PICTURE_ID "
    "WHERE TAGS.USER_ID = " + std::to_string(user.getId()) + ";";

    char* errMsg = nullptr;
    int res = sqlite3_exec(_db, sql.c_str(), countCallback, &count, &errMsg);
    
    if (res != SQLITE_OK) {
        std::string error = errMsg ? errMsg : "Unknown error";
        sqlite3_free(errMsg);
        throw MyException("Failed to count albums tagged of user: " + error);
    }

    return count;
}

int DatabaseAccess::countTagsOfUser(const User& user)
{
    int count = 0;
    std::string sql = "SELECT COUNT(*) FROM TAGS WHERE USER_ID = " + std::to_string(user.getId()) + ";";

    char* errMsg = nullptr;
    int res = sqlite3_exec(_db, sql.c_str(), countCallback, &count, &errMsg);
    
    if (res != SQLITE_OK) {
        std::string error = errMsg ? errMsg : "Unknown error";
        sqlite3_free(errMsg);
        throw MyException("Failed to count tags of user: " + error);
    }

    return count;
}

float DatabaseAccess::averageTagsPerAlbumOfUser(const User& user)
{
    int albumsTaggedCount = countAlbumsTaggedOfUser(user);

    if ( 0 == albumsTaggedCount ) {
        return 0;
    }

    int tagsCount = countTagsOfUser(user);
    float avg = (float)tagsCount / albumsTaggedCount;
    return avg;
}

User DatabaseAccess::getTopTaggedUser()
{
    User topUser = User(0, ""); // default value in case there are no users
    std::string sql = "SELECT USERS.ID, USERS.NAME, COUNT(*) AS TAG_COUNT FROM USERS "
    "JOIN TAGS ON USERS.ID = TAGS.USER_ID "
    "GROUP BY USERS.ID " // tomer i know it hard so i will explain, this line combines all the tags lines into a user lines, so the TAG_COUNT will have the sum of the tags
    "ORDER BY TAG_COUNT DESC "
    "LIMIT 1;";

    char* errMsg = nullptr;
    int res = sqlite3_exec(_db, sql.c_str(), getUserCallback, &topUser, &errMsg);
    
    if (res != SQLITE_OK) {
        std::string error = errMsg ? errMsg : "Unknown error";
        sqlite3_free(errMsg);
        throw MyException("Failed to get top tagged user: " + error);
    }

    return topUser;
}

Picture DatabaseAccess::getTopTaggedPicture()
{
    Picture topPicture = Picture(0, ""); // default value in case there are no pictures
    std::string sql = "SELECT PICTURES.ID, PICTURES.NAME, PICTURES.LOCATION, PICTURES.CREATION_DATE, COUNT(*) AS TAG_COUNT FROM PICTURES "
    "JOIN TAGS ON PICTURES.ID = TAGS.PICTURE_ID "
    "GROUP BY PICTURES.ID "
    "ORDER BY TAG_COUNT DESC "
    "LIMIT 1;";

    char* errMsg = nullptr;
    int res = sqlite3_exec(_db, sql.c_str(), getPictureCallback, &topPicture, &errMsg);
    
    if (res != SQLITE_OK) {
        std::string error = errMsg ? errMsg : "Unknown error";
        sqlite3_free(errMsg);
        throw MyException("Failed to get top tagged picture: " + error);
    }

    return topPicture;
}

std::list<Picture> DatabaseAccess::getTaggedPicturesOfUser(const User& user)
{
    std::list<Picture> pictures;
    std::string sql = "SELECT PICTURES.ID, PICTURES.NAME, PICTURES.LOCATION, PICTURES.CREATION_DATE FROM PICTURES "
    "JOIN TAGS ON PICTURES.ID = TAGS.PICTURE_ID "
    "WHERE TAGS.USER_ID = " + std::to_string(user.getId()) + ";";

    char* errMsg = nullptr;
    int res = sqlite3_exec(_db, sql.c_str(), pictureListCallback, &pictures, &errMsg);
    
    if (res != SQLITE_OK) {
        std::string error = errMsg ? errMsg : "Unknown error";
        sqlite3_free(errMsg);
        throw MyException("Failed to get tagged pictures of user: " + error);
    }

    return pictures;
}