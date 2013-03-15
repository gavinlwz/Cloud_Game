#pragma once
typedef struct  
{  
    unsigned char forbidden_bit;           //! Should always be FALSE  
    unsigned char nal_reference_idc;       //! NALU_PRIORITY_xxxx  
    unsigned char nal_unit_type;           //! NALU_TYPE_xxxx    
    unsigned int startcodeprefix_len;      //! ǰ׺�ֽ���  
    unsigned int len;                      //! ����nal ͷ��nal ���ȣ��ӵ�һ��00000001����һ��000000001�ĳ���  
    unsigned int max_size;                 //! ����һ��nal �ĳ���  
    unsigned char * buf;                   //! ����nal ͷ��nal ����  
    unsigned int lost_packets;             //! Ԥ��  
} NALU_t;  
typedef struct   
{  
    //byte 0  
    unsigned char TYPE:5;  
    unsigned char NRI:2;  
    unsigned char F:1;          
} NALU_HEADER; // 1 BYTE 
typedef struct   
{  
    //byte 0  
    unsigned char TYPE:5;  
    unsigned char NRI:2;   
    unsigned char F:1;                
} FU_INDICATOR; // 1 BYTE  
typedef struct   
{  
    //byte 0  
    unsigned char TYPE:5;  
    unsigned char R:1;  
    unsigned char E:1;  
    unsigned char S:1;      
} FU_HEADER;   // 1 BYTES   


