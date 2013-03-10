
//������1.RTP�������ַ 2.RTP�����ݴ�С 3.H264�����ַ 4.������ݴ�С
//���أ�true:��ʾһ֡����  false:֡δ���� һ��AAC��Ƶ���Ƚ�С��û�з�Ƭ��
bool UnpackRTPAAC(void * bufIn, int recvLen, void** pBufOut,  int* pOutLen)
{
    unsigned char*  bufRecv = (unsigned char*)bufIn;
    //char strFileName[20];
    unsigned char ADTS[] = {0xFF, 0xF1, 0x00, 0x00, 0x00, 0x00, 0xFC}; 
    int audioSamprate = 44100;//��Ƶ������
    int audioChannel = 2;//��Ƶ���� 1��2
    int audioBit = 16;//16λ �̶�
    ADTS[2] = 0x50;
    ADTS[3] = 0x80;
    int len = recvLen - 16 + 7;
    len <<= 5;//8bit * 2 - 11 = 5(headerSize 11bit)
    len |= 0x1F;//5 bit    1            
    ADTS[4] = len>>8;
    ADTS[5] = len & 0xFF;
    *pBufOut = (char*)bufIn+16-7;
    memcpy(*pBufOut, ADTS, sizeof(ADTS));
    *pOutLen = recvLen - 16 + 7;
    unsigned char* bufTmp = (unsigned char*)bufIn;
    bool bFinishFrame = false;
    if (bufTmp[1] & 0x80)
    {
        //DebugTrace::D("Marker");
        bFinishFrame = true;
    }
    else
    {
        bFinishFrame = false;
    }
    return true;
}