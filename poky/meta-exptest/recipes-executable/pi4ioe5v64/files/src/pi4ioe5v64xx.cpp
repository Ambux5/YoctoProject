
#include "pi4ioe5v64xx.h"
namespace PI4IOE5V64XX {
template <typename I2c>
void PI4IOE5V64XX<I2c>::attach(I2cDevice &device, uint8_t i2c_addr)
{
    i2c = &device;
    addr = BASE_I2C_ADDR | (i2c_addr & 0x20);
}

template <typename I2c>
uint16_t PI4IOE5V64XX<I2c>::read()
{
    uint8_t buffer[2];
    i2c->R8DBlock(Registers::INPUT_PORT_0, buffer, 2);
    input.w = (static_cast<uint16_t>(buffer[1]) << 8) | buffer[0];
    return input.w;
}

template <typename I2c>
Level::Level PI4IOE5V64XX<I2c>::read(const Port::Port port)
{
    uint16_t value = read();
    return (value & (1 << port)) ? Level::H : Level::L;
}

template <typename I2c>
bool PI4IOE5V64XX<I2c>::write(const uint16_t value)
{
    output.w = value;
    return write_impl();
}

template <typename I2c>
bool PI4IOE5V64XX<I2c>::write(const Port::Port port, const Level::Level level)
{
    if (level == Level::H)
    {
        output.w |= (1 << port);
    }
    else
    {
        output.w &= ~(1 << port);
    }
    return write_impl();
}

template <typename I2c>
bool PI4IOE5V64XX<I2c>::polarity(const uint16_t value)
{
    pol.w = value;
    return polarity_impl();
}

template <typename I2c>
bool PI4IOE5V64XX<I2c>::polarity(const Port::Port port, const Polarity::Polarity pol)
{
    if (pol == Polarity::INVERTED)
    {
        this->pol.w |= (1 << port);
    }
    else
    {
        this->pol.w &= ~(1 << port);
    }
    return polarity_impl();
}

template <typename I2c>
bool PI4IOE5V64XX<I2c>::direction(const uint16_t value)
{
    dir.w = value;
    return direction_impl();
}

template <typename I2c>
bool PI4IOE5V64XX<I2c>::direction(const Port::Port port, const Direction::Direction dir)
{
    if (dir == Direction::IN)
    {
        this->dir.w |= (1 << port);
    }
    else
    {
        this->dir.w &= ~(1 << port);
    }
    return direction_impl();
}

template <typename I2c>
bool PI4IOE5V64XX<I2c>::pullUpDownEnable(const uint16_t value)
{
    pe.w = value;
    return pullup_down_enable_impl();
}

template <typename I2c>
bool PI4IOE5V64XX<I2c>::pullUpDownEnable(const Port::Port port, const PullUpDownEnable::PullUpDownEnable pe)
{
    if (pe == PullUpDownEnable::ENABLE)
    {
        this->pe.w |= (1 << port);
    }
    else
    {
        this->pe.w &= ~(1 << port);
    }
    return pullup_down_enable_impl();
}

template <typename I2c>
bool PI4IOE5V64XX<I2c>::pullUpDownSelection(const uint16_t value)
{
    pud.w = value;
    return pullup_down_selection_impl();
}

template <typename I2c>
bool PI4IOE5V64XX<I2c>::pullUpDownSelection(const Port::Port port, const PullUpDownSelection::PullUpDownSelection pud)
{
    if (pud == PullUpDownSelection::PULL_UP)
    {
        this->pud.w |= (1 << port);
    }
    else
    {
        this->pud.w &= ~(1 << port);
    }
    return pullup_down_selection_impl();
}

template <typename I2c>
uint8_t PI4IOE5V64XX<I2c>::i2c_error() const
{
    return status;
}

template <typename I2c>
bool PI4IOE5V64XX<I2c>::write_impl()
{
    return write_bytes(this->addr, Registers::OUTPUT_PORT_0, output.b, 2);
}

template <typename I2c>
bool PI4IOE5V64XX<I2c>::polarity_impl()
{
    return write_bytes(this->addr, Registers::POLARITY_INVERSION_PORT_0, pol.b, 2);
}

template <typename I2c>
bool PI4IOE5V64XX<I2c>::direction_impl()
{
    return write_bytes(this->addr, Registers::CONFIGURATION_PORT_0, dir.b, 2);
}

template <typename I2c>
bool PI4IOE5V64XX<I2c>::pullup_down_enable_impl()
{
    return write_bytes(this->addr, Registers::PULL_UP_DOWN_ENABLE_REGISTER_0, pe.b, 2);
}

template <typename I2c>
bool PI4IOE5V64XX<I2c>::pullup_down_selection_impl()
{
    return write_bytes(this->addr, Registers::PULL_UP_DOWN_SELECTION_REGISTER_0, pud.b, 2);
}

template <typename I2c>
int8_t PI4IOE5V64XX<I2c>::read_bytes(const uint8_t dev, const uint8_t reg, uint8_t *data, const uint8_t size)
{
    uint8_t reg_buffer[1] = {reg};
    i2c->WBlock(reg_buffer, 1);
    i2c->R8DBlock(reg, data, size);
    return 0;
}

template <typename I2c>
bool PI4IOE5V64XX<I2c>::write_bytes(const uint8_t dev, const uint8_t reg, const uint8_t *data, const uint8_t size)
{
    uint8_t buffer[size + 1];
    buffer[0] = reg;
    for (uint8_t i = 0; i < size; ++i)
    {
        buffer[i + 1] = data[i];
    }

    // Pokusíme se zavolat WBlock
    i2c->WBlock(buffer, size + 1);

    // Můžeš zavést nějaký způsob kontroly, zda zápis proběhl úspěšně.
    // Např. pomocí kontrolního bitu nebo následného čtení a ověření.
    return true;  // Nebo implementuj kontrolu úspěchu podle potřeby
}



template class PI4IOE5V64XX<I2cDevice>;
}