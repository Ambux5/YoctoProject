#ifndef PI4IOE5V64XX_H
#define PI4IOE5V64XX_H

#include <stdint.h>
#include "i2c.hpp"

namespace PI4IOE5V64XX
{
    namespace Registers
    {
        enum : uint8_t
        {
            INPUT_PORT_0 = 0x00,
            INPUT_PORT_1,
            OUTPUT_PORT_0,
            OUTPUT_PORT_1,
            POLARITY_INVERSION_PORT_0,
            POLARITY_INVERSION_PORT_1,
            CONFIGURATION_PORT_0,
            CONFIGURATION_PORT_1,
            OUTPUT_DRIVE_STRENGTH_REGISTER_0_0 = 0x40,
            OUTPUT_DRIVE_STRENGTH_REGISTER_0_1,
            OUTPUT_DRIVE_STRENGTH_REGISTER_1_0,
            OUTPUT_DRIVE_STRENGTH_REGISTER_1_1,
            INPUT_LATCH_REGISTER_0,
            INPUT_LATCH_REGISTER_1,
            PULL_UP_DOWN_ENABLE_REGISTER_0,
            PULL_UP_DOWN_ENABLE_REGISTER_1,
            PULL_UP_DOWN_SELECTION_REGISTER_0,
            PULL_UP_DOWN_SELECTION_REGISTER_1,
            INTERRUPT_MASK_REGISTER_0,
            INTERRUPT_MASK_REGISTER_1,
            INTERRUPT_STATUS_REGISTER_0,
            INTERRUPT_STATUS_REGISTER_1,
            OUTPUT_PORT_CONFIGURATION_REGISTER
        };
    }

    namespace Port
    {
        enum Port : uint8_t
        {
            P00, P01, P02, P03, P04, P05, P06, P07,
            P10, P11, P12, P13, P14, P15, P16, P17
        };
    }

    namespace Level
    {
        enum Level : uint8_t { L, H };
        enum LevelAll : uint16_t { L_ALL = 0x0000, H_ALL = 0xFFFF };
    }

    namespace Polarity
    {
        enum Polarity : uint8_t { ORIGINAL, INVERTED };
        enum PolarityAll : uint16_t { ORIGINAL_ALL = 0x0000, INVERTED_ALL = 0xFFFF };
    }

    namespace Direction
    {
        enum Direction : uint8_t { OUT, IN };
        enum DirectionAll : uint16_t { OUT_ALL = 0x0000, IN_ALL = 0xFFFF };
    }

    namespace PullUpDownEnable
    {
        enum PullUpDownEnable : uint8_t { DISABLE, ENABLE };
        enum PullUpDownEnableAll : uint16_t { DISABLE_ALL = 0x0000, ENABLE_ALL = 0xFFFF };
    }

    namespace PullUpDownSelection
    {
        enum PullUpDownSelection : uint8_t { PULL_DOWN, PULL_UP };
        enum PullUpDownSelectionAll : uint16_t { PULL_DOWN_ALL = 0x0000, PULL_UP_ALL = 0xFFFF };
    }

    template <typename I2c = I2cDevice>
    class PI4IOE5V64XX
    {
        union Ports
        {
            uint16_t w;
            uint8_t b[2];
        };

        static constexpr uint8_t BASE_I2C_ADDR = 0x20;

        I2cDevice *i2c{nullptr};
        uint8_t addr{BASE_I2C_ADDR};
        Ports input{0x0000};
        Ports output{0xFFFF};
        Ports pol{0x0000};
        Ports dir{0xFFFF};
        Ports pe{0x0000};
        Ports pud{0x0000};
        uint8_t status{0x00};

    public:
        void attach(I2cDevice &device, uint8_t i2c_addr);
        uint16_t read();
        Level::Level read(const Port::Port port);
        bool write(const uint16_t value);
        bool write(const Port::Port port, const Level::Level level);
        bool polarity(const uint16_t value);
        bool polarity(const Port::Port port, const Polarity::Polarity pol);
        bool direction(const uint16_t value);
        bool direction(const Port::Port port, const Direction::Direction dir);
        bool pullUpDownEnable(const uint16_t value);
        bool pullUpDownEnable(const Port::Port port, const PullUpDownEnable::PullUpDownEnable pe);
        bool pullUpDownSelection(const uint16_t value);
        bool pullUpDownSelection(const Port::Port port, const PullUpDownSelection::PullUpDownSelection pud);
        uint8_t i2c_error() const;

    private:
        bool write_impl();
        bool polarity_impl();
        bool direction_impl();
        bool pullup_down_enable_impl();
        bool pullup_down_selection_impl();
        int8_t read_bytes(const uint8_t dev, const uint8_t reg, uint8_t *data, const uint8_t size);
        bool write_bytes(const uint8_t dev, const uint8_t reg, const uint8_t *data, const uint8_t size);
    };
}

#endif 
