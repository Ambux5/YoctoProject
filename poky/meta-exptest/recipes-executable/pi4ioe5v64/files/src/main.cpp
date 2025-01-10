#include <iostream>
#include <string>
#include <cstdlib>
#include "pi4ioe5v64xx.h"
#include "i2c.hpp"
#include <optional>
#include <map>

#define IOEXPANDER_I2C_ADD 0X20
#define IOEXPANDER_I2C_REG "/dev/i2c-2"

std::optional<PI4IOE5V64XX::Port::Port> getPortFromPinName(const std::string &pinName)
{
    std::cout << "getPortFromPinName: " << pinName << std::endl;
    static const std::map<std::string, PI4IOE5V64XX::Port::Port> pinMap = {
        {"p00", PI4IOE5V64XX::Port::P00},
        {"p01", PI4IOE5V64XX::Port::P01},
        {"p02", PI4IOE5V64XX::Port::P02},
        {"p03", PI4IOE5V64XX::Port::P03},
        {"p04", PI4IOE5V64XX::Port::P04},
        {"p05", PI4IOE5V64XX::Port::P05},
        {"p06", PI4IOE5V64XX::Port::P06},
        {"p07", PI4IOE5V64XX::Port::P07},
        {"p10", PI4IOE5V64XX::Port::P10},
        {"p11", PI4IOE5V64XX::Port::P11},
        {"p12", PI4IOE5V64XX::Port::P12},
        {"p13", PI4IOE5V64XX::Port::P13},
        {"p14", PI4IOE5V64XX::Port::P14},
        {"p15", PI4IOE5V64XX::Port::P15},
        {"p16", PI4IOE5V64XX::Port::P16},
        {"p17", PI4IOE5V64XX::Port::P17}};

    auto it = pinMap.find(pinName);
    if (it != pinMap.end())
    {
        return it->second;
    }
    else
    {
        return std::nullopt;
    }
}

bool setupPinDirection(PI4IOE5V64XX::PI4IOE5V64XX<I2cDevice> &device, const std::string &pinName, const std::string &direction)
{
    std::cout << "setupPinDirection pinName: " << pinName << "direction: " << direction << std::endl;
    auto port = getPortFromPinName(pinName);
    if (!port)
    {
        std::cerr << "Invalid pin number: " << pinName << std::endl;
        return false;
    }

    PI4IOE5V64XX::Direction::Direction dir;
    if (direction == "in")
    {
        dir = PI4IOE5V64XX::Direction::IN;
    }
    else if (direction == "out")
    {
        dir = PI4IOE5V64XX::Direction::OUT;
    }
    else
    {
        std::cerr << "Invalid direction: " << direction << std::endl;
        return false;
    }
    std::cout << "Calling direction with port: " << static_cast<int>(*port)
              << " and dir: " << static_cast<int>(dir) << std::endl;
    bool result = device.direction(*port, dir);
    std::cout << "Result of direction: " << result << std::endl;
    return result;
}

bool setPinLevel(PI4IOE5V64XX::PI4IOE5V64XX<I2cDevice> &device, const std::string &pinName, const std::string &pinLevel)
{
    auto port = getPortFromPinName(pinName);
    if (!port)
    {
        std::cerr << "Invalid pin number: " << pinName << std::endl;
        return false;
    }

    PI4IOE5V64XX::Level::Level level;
    if (pinLevel == "high")
    {
        level = PI4IOE5V64XX::Level::H;
    }
    else if (pinLevel == "low")
    {
        level = PI4IOE5V64XX::Level::L;
    }
    else
    {
        std::cerr << "Invalid level parameter: " << pinLevel << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "Calling write with port: " << static_cast<int>(*port)
              << " and level: " << static_cast<int>(level) << std::endl;
    bool result = device.write(*port, level);
    std::cout << "Result of write: " << result << std::endl;
    return result;
}

bool getPinLevel(PI4IOE5V64XX::PI4IOE5V64XX<I2cDevice> &device, const std::string &pinName)
{
    auto port = getPortFromPinName(pinName);
    if (!port)
    {
        std::cerr << "Invalid pin name or number: " << pinName;
        return false;
    }

    PI4IOE5V64XX::Level::Level level = device.read(*port);

    if (level == PI4IOE5V64XX::Level::H)
    {
        std::cout << "Pin " << pinName << " level: HIGH" << std::endl;
    }
    else
    {
        std::cout << "Pin " << pinName << " level: LOW" << std::endl;
    }

    return true;
}

void printHelpMessage()
{
    std::cout << "List of supported commands:\r\n\n";
    std::cout << "help                                      - prints list of supported commands\r\n";
    std::cout << "Application allows users to configure individual pins\r\n";
    std::cout << "set_pin_direction <pin_name> <pin_direct> - Configure the direction of the specified GPIO pin (input or output)\r\n";
    std::cout << "set_pin_level <pin_name> <pin_level>      - Set the logic level of the specified GPIO pin (high or low)\r\n";
    std::cout << "get_pin_level <pin_name>                  - Retrieve the current logic level of the specified GPIO pin\r\n";
    std::cout << "Please provide a command to execute or \"help\" to help.\r\n";
};

int main(int argc, char *argv[])
{
    int ret_value = EXIT_SUCCESS;

    std::vector<std::string> args(argv + 1, argv + argc);

    I2cDevice i2c_device(IOEXPANDER_I2C_REG, IOEXPANDER_I2C_ADD);
    PI4IOE5V64XX::PI4IOE5V64XX<I2cDevice> device;
    device.attach(i2c_device, IOEXPANDER_I2C_ADD);

    if (args.empty())
    {
        printHelpMessage();
        ret_value = EXIT_FAILURE;
    }
    else
    {
        const std::string &command_name = args[0];
        if (args.size() == 1)
        {
            if (command_name == "help")
            {
                std::cerr << "Please provide a command to execute or \"help\" to help" << std::endl;
                printHelpMessage();
            }
        }
        else if (args.size() == 2)
        {
            const std::string &command_parameter = args[1];

            if (command_name == "get_pin_level")
            {
                std::cout << "get_pin_level: " << command_parameter << std::endl;
                if (!getPinLevel(device, command_parameter))
                {
                    std::cerr << "Failed to read level for pin " << command_parameter << std::endl;
                }
            }
            else
            {
                std::cerr << "Invalid command name: " << command_name << std::endl;
            }
        }
        else if (args.size() == 3)
        {
            const std::string &command_parameter = args[1];
            const std::string &value_parameter = args[2];
            std::cout << "args3+: 1" << command_parameter << "2:" << value_parameter << std::endl;
            if (command_name == "set_pin_direction")
            {
                bool success = setupPinDirection(device, command_parameter, value_parameter);

                if (success)
                {
                    std::cout << "Direction of pin " << command_parameter << " was set to " << value_parameter << std::endl;
                }
                else
                {
                    std::cerr << "Failed to set direction for pin " << command_parameter << std::endl;
                }
            }
            else if (command_name == "set_pin_level")
            {
                bool success = setPinLevel(device, command_parameter, value_parameter);
                if (success)
                {
                    std::cout << "Level of pin " << command_parameter << " was set to " << value_parameter << std::endl;
                }
                else
                {
                    std::cerr << "Failed to set level for pin " << command_parameter << std::endl;
                }
            }
            else
            {
                std::cerr << "Invalid command name: " << command_name << std::endl;
            }
        }
        else
        {
            std::cerr << "Wrong command format" << std::endl;
            printHelpMessage();
            ret_value = EXIT_FAILURE;
        }
    }

    ret_value ? std::cout << "ERROR\r\n" : std::cout << "OK\r\n";
    return ret_value;
}
