/*************************************************************************************************/
/*!
 *  \file
 *
 *  \brief  WSF buffer IO for UART driver.
 *
 *  Copyright (c) 2013-2018 Arm Ltd. All Rights Reserved.
 *
 *  Copyright (c) 2019-2020 Packetcraft, Inc.
 *  
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *  
 *      http://www.apache.org/licenses/LICENSE-2.0
 *  
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */
/*************************************************************************************************/

// Modifications for Stratify OS, Copyright 2020 Stratify Labs, Inc

#include <string.h>

#include "wsf_types.h"
#include "wsf_bufio.h"

#include "wsf_cs.h"
#include "wsf_trace.h"
#include "wsf_os.h"

#include "pal_uart.h"

/**************************************************************************************************
  Data Types
**************************************************************************************************/

/*! \brief    TX structure */
typedef struct
{
  uint8_t      *pBuf;                              /*!< UART TX buffer pointer */
  uint16_t     size;                               /*!< UART TX buffer size */
  uint16_t     in;                                 /*!< UART TX buffer in index */
  uint16_t     out;                                /*!< UART TX buffer out index */
  uint16_t     crt;                                /*!< UART TX current number of bytes sent */
} WsfBufIoUartTx_t;

/*! \brief    RX structure */
typedef struct
{
  WsfBufIoUartRxCback_t   cback;                   /*!< UART RX callback. */
  uint8_t                 buf[1];                  /*!< UART RX buffer */
} WsfBufIoUartRx_t;

/**************************************************************************************************
  Local Variables
**************************************************************************************************/

/*! \brief    Control block. */
static struct
{
  WsfBufIoUartTx_t         tx;             /*!< Platform UART TX structure */
  WsfBufIoUartRx_t         rx;             /*!< Platform UART RX structure */
  bool_t                   initialized;    /*!< UART RX is initialized */
} WsfBufIoCb = {0};


/**************************************************************************************************
  Global Functions
**************************************************************************************************/

/*************************************************************************************************/
/*!
 *  \brief  Initialize the UART.
 *
 *  \param  pBuf    Tx Buffer pointer.
 *  \param  size    Length of buffer.
 *
 *  \return memory used.
 */
/*************************************************************************************************/
uint32_t WsfBufIoUartInit(void *pBuf, uint32_t size)
{
  return size;
}

/*************************************************************************************************/
/*!
 *  \brief  Register the UART RX callback.
 *
 *  \param  rxCback  Callback function for UART RX.
 */
/*************************************************************************************************/
void WsfBufIoUartRegister(WsfBufIoUartRxCback_t rxCback)
{
  if (rxCback != NULL)
  {
    WsfBufIoCb.rx.cback = rxCback;
  }
}

/*************************************************************************************************/
/*!
 *  \brief  Transmit buffer on UART.
 *
 *  \param  pBuf    Buffer to transmit.
 *  \param  len     Length of buffer in octets.
 *
 *  \return if write successfully.
 */
/*************************************************************************************************/
bool_t WsfBufIoWrite(const uint8_t *pBuf, uint32_t len)
{
  return TRUE;
}
