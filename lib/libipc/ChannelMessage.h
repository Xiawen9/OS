#ifndef __LIBIPC_CHANNELMESSAGE_H
#define __LIBIPC_CHANNELMESSAGE_H

/**
 * Basic message format for sending on a Channel
 */
class ChannelMessage
{
  public:

    /**
     * Message types
     */
    enum Type
    {
        Request  = 0,
        Response = 1
    };

    /** Message type is either a request or response */
    Type type:1;

    /** Optional request identifier */
    Size identifier:31;
};

#endif /* __LIBIPC_CHANNELMESSAGE_H */
