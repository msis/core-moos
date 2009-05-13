/*
 *  XPCUdpSocket.cpp
 *  MOOS
 *
 *  Created by pnewman on 13/05/2009.
 *  Copyright 2009 Oxford University. All rights reserved.
 *
 */

#include "XPCUdpSocket.h"

// Sends a message to a connected host. The number of bytes sent is returned
int XPCUdpSocket::iSendMessage(void *_vMessage, int _iMessageSize)
{
    
    int iNumBytes=sendto(iSocket, _vMessage, _iMessageSize,0,
             (struct sockaddr *) &clientAddress, sizeof(clientAddress) );
    
    
    // Sends the message to the connected host
    if (iNumBytes == -1)
    {
        char sMsg[512];        
        sprintf(sMsg, "Error sending socket message: %s", sGetError());
        throw XPCException(sMsg);
        return 0;
    }
    return iNumBytes;
    
}

// Receives a UDP message 
int XPCUdpSocket::iRecieveMessage(void *_vMessage, int _iMessageSize, int _iOption)
{
    
    int iNumBytes;  // The number of bytes recieved
    
    
    // Recieves a UDP socket message.  The number of bytes received isreturned
    struct sockaddr SenderInfo;
    socklen_t SenderInfoLen;
    
    iNumBytes = recvfrom(iSocket, (char *)_vMessage,
                         _iMessageSize,
                         _iOption,(struct sockaddr *) &SenderInfo, &SenderInfoLen);
    if (iNumBytes <=0)
    {
        char sMsg[512];
        
        sprintf(sMsg, "Error receiving on socket: %s", sGetError());
        printf("%s\n",sMsg);
        throw XPCException(sMsg);
        
    }
    
    return iNumBytes;
    
}

// Binds the socket to an address and port number
void XPCUdpSocket::vBindSocket()
{
    
    // Bind the socket to the given address and port number
    if (bind(iSocket, (struct sockaddr *)&clientAddress,sizeof(clientAddress)) == -1)
    {
        char sMsg[512];
        sprintf(sMsg, "Error binding to socket: %s", sGetError());
        XPCException socketExcept(sMsg);
        throw socketExcept;
        return;
    }
        
}

// allows a read with a timeout to prevent from blocking indefinitely
int XPCUdpSocket::iReadMessageWithTimeOut(void *_vMessage, int _iMessageSize, double dfTimeOut,int _iOption)
{
    return -1;
}
