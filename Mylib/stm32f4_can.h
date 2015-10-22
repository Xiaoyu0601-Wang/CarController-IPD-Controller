/*----------------------------------------------------------------------------
 * Name:    CAN.h
 * Purpose: low level CAN definitions
 * Note(s):
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2009-2013 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

#ifndef __CAN_H
#define __CAN_H

#define STANDARD_FORMAT  0
#define EXTENDED_FORMAT  1

#define DATA_FRAME       0
#define REMOTE_FRAME     1

//#define __TEST

//#define USING_CAN1
//#define USING_CAN2

//#define USING_CAN1_TEST
//#define USING_CAN2_TEST


typedef struct  {
  unsigned int   id;                    /* 29 bit identifier */
  unsigned char  data[8];               /* Data field */
  unsigned char  len;                   /* Length of data field in bytes */
  unsigned char  format;                /* 0 - STANDARD, 1- EXTENDED IDENTIFIER */
  unsigned char  type;                  /* 0 - DATA FRAME, 1 - REMOTE FRAME */
} CAN_msg;



/* Functions defined in module CAN.c */
void CAN_setup         (unsigned int ctrl);
void CAN_start         (unsigned int ctrl);
void CAN_waitReady     (unsigned int ctrl);
void CAN_wrMsg         (unsigned int ctrl, CAN_msg *msg);
void CAN_rdMsg         (unsigned int ctrl, CAN_msg *msg);
void CAN_wrFilter      (unsigned int ctrl, unsigned int id, unsigned char filter_type);
void can_Init (void);
void CAN_testmode      (unsigned int ctrl, unsigned int testmode);

extern CAN_msg       CAN_TxMsg[2];      /* CAN messge for sending */
extern CAN_msg       CAN_RxMsg[2];      /* CAN message for receiving */                                
extern unsigned int  CAN_TxRdy[2];      /* CAN HW ready to transmit a message */
extern unsigned int  CAN_RxRdy[2];      /* CAN HW received a message */

#endif


