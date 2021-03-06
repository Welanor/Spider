#ifndef ABSTRACT_BOOST_CIRCULAR_BUFFER_HPP
# define ABSTRACT_BOOST_CIRCULAR_BUFFER_HPP

#include <memory>

#include <boost/circular_buffer.hpp>

#include "ICircularBuffer.hpp"

class BoostCircularBuffer : public ICircularBuffer
{
public:
    BoostCircularBuffer(size_t buffSize);
    virtual ~BoostCircularBuffer() = default;

    void pushData(const std::vector<uint8_t>& buffer) override;
    void discardData(std::size_t size) override;

private:
      boost::circular_buffer<uint8_t> _buff;
};

#endif
