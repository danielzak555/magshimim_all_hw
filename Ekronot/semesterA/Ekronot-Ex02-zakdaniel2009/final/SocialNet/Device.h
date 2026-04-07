#pragma once
///////////////////////////////////////////////////////////
/*									    //
	Those definitions are used for tests,               //
	you can add your own, but please do not delete any. //
*/									    //
enum DeviceType {PHONE, PC, LAPTOP, TABLET};		    //
									    //
#define UbuntuOS "UbuntuLinux"                            //						
#define RedHatOS "RedHatLinux"				    //
#define MacOS "MacOS"						    //
#define IOS "IOS"							    //
#define WINDOWS7 "Windows7"                               //
#define WINDOWS10 "Windows10"                             //
#define WINDOWS11 "Windows11"                             //
#define ANDROID "Android"                                 //
									    //
/// ///////////////////////////////////////////////////////

#include <string>

class Device
{
private:
    unsigned int id;
    DeviceType type;
    std::string os;
    bool active;

public:
    
    void init(unsigned int id, DeviceType type, std::string os);

    unsigned int getID() const;
    DeviceType getType() const;
    std::string getOS() const;

    bool isActive() const;
    void activate();
    void deactivate();

};

