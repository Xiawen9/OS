#include "NetworkSocket.h"

NetworkSocket::NetworkSocket(Size packetSize)
    : m_receive(packetSize),
      m_transmit(packetSize)
{
    m_pid = 0;
}

NetworkSocket::~NetworkSocket()
{
}
